#
# Fresco extensions to qmtest -- test classes
#
# Copyright (C) 2002  Nathaniel Smith <njs@fresco.org>
#

# To load this file into an interactive interpreter, the following at
# least works:
#    $ export PYTHONPATH=''
#    $ cd ..../QMTest
#    $ python
#    >>> import sys
#    >>> sys.path += '/usr/lib/qm'
#    >>> import os
#    >>> os.environ["QM_HOME"] = "/usr/lib/qm"
#    >>> os.environ["QM_SHARE_PATH"] = "/usr/share/qm"
#    >>> import fresco.test.test
# These qmtest people are most vexing.

# TODO: update to use the new QMTest executable-running classes

# System libraries
import re
import os
from StringIO import StringIO

# QM libraries
import qm.test.test
from qm.test.test import Test
import qm.fields
from qm.test.result import Result
import qm.label

# our libraries
import util

class NoSuchFile (Exception):
    """Raised when a Testcmd cannot be found."""
    pass

class InvalidFormat (Exception):
    """Raised when a Testcmd gives un-parseable output."""
    pass

class TestcmdRunner (Test):
    """A Test class to harness executables fulfilling the "Testcmd" interface.

    This test class is used to call "Testcmd" executables, which are
    simply those that fulfill a certain interface.  In particular,
    they should support being called in the following ways:
      <executable> list - print to stdout a list of tests this
        executable can run, one per line
      <executable> run <test name> - run the test <test name>,
        printing the result to stdout in the format described below.
        Should return an exit code of 0.
      <executable> run all - run all tests, printing the result of
        each to stdout in the format described below.  Note that
        'all' is therefore not a valid name for a test.
      <executable> run - run all tests, printing the result of failed
        tests to stdout in whatever format is deemed most useful for
        debugging.
    This harness only uses the "run <test name>" form, but for
    consistency and use by real people, your Testcmds should support
    all of the forms.

    The output format is based on RFC 822 (ie, it looks like email
    headers).  It was chosen because it's easy to generate, easy to
    parse, and easy for humans to read (so you don't have to use this
    test framework to call your Testcmds, if you don't want to).
    Output should consist of a sequence of key/value pairs, one per
    logical line, with the key separated by the value by a colon (:)
    (and possibly whitespace around the colon).  A "logical line" is
    defined to stretch from the end of the previous logical line (or
    the beginning of output) until the next newline that is followed
    by a non-whitespace character.  Keys are case insensitive, and may
    consist of alphanumerics, hyphens, and underscores.  Other
    characters are permitted, but are treated as if they were
    underscores for comparision and the like.  For example:

      Test: warp_18
      Result: FAIL
      Cause: The engines canna take it, cap'n!
      Long-Line: this is one of those stupid examples that only occurs
        in documentation, as a way to demonstrate how continuation
        lines work.  Notice that we're indenting.  That's what makes
        this a single long line, instead of a bunch of shorter ones.
      Note: This is now the 5th logical line, and the 8th physical line.
      Note2: Numbers are allowed in keys.
      Hyphen-Example: hyphen's, too.

    Email headers allow duplicate keys; for simplicity, we do not.
    This means that the following is a parse error:
      Foo: bar
      Foo: baz

    Keys should consist of alphanumerics, underscore (_) and hyphen (-).
      
    If multiple tests are run, the results should be printed in this
    format, with the output for each test separated by a blank line.
    Eg:
      Test: test1
      Note: this is the output from one test

      Test: test2
      Note: and this is the output from a second, entirely different,
        one.

    Because of this, all blank lines that don't separate chunks should
    be "quoted" by placing a single period (.) on them.  Eg:

      Description: Sanity check.
        This test makes sure that our environment is reasonable.
        .
        Currently, it ensures that the oxygen content is within Earth
        norms, and that the temperature is human-acceptable.
        .
        FIXME: add air pressure checks.

    "." is pronounced "this line intentionally left blank".

    The following fields are interpreted specially by the harness:
      Result - either PASS, FAIL, or ERROR.  PASS means the test
        passed, FAIL means the test failed, and ERROR means there was
        some problem in the harness that prevented the test being
        run.  This field determines whether we consider the test a
        failure or what.  Case is significant, and any other value is
        interpreted as an ERROR.
      Cause - A short, preferably 1 line, description of why the test
        failed (if it did).  Eg, "Exception thrown".  This will set
        the CAUSE field of the result object.
      Exception - if the test failed due to an exception, this should
        be a brief description of the exception.  It will set the
        EXCEPTION field of the result object.
      Traceback - if the test failed due to an exception, this should
        be a brief description of the exception.  It will set the
        TRACEBACK field of the result object.
    The following fields are not interpreted specially by this
    harness, but do have a conventional meaning:
      Test - this should be the name of the test, to make the output
        more useful to humans calling the executable directly.
      Description - a detailed description of what exactly the test is
        supposed to be testing.      
      Details - a detailed description of what went wrong - like
        "Cause", but you can be as wordy as you want here.  Even if
        nothing went wrong, this is a fine place to record an
        execution trace or whatever.
    In addition, this harness will save the stderr and exit code of
    the executable, so in extreme cases (eg, things have gone so wrong
    that the normal output isn't possible to produce) it's ok to dump
    useful information there.  Beware, though, that we can't get at
    the exit code on Windows.

    If the program gives invalid output (ie, we encounter an error
    trying to parse the rfc822-alike output format), we count that as
    a FAIL.  If the program gives valid output, but the exit code shows
    that it exited with a non-zero value, or was killed by a signal,
    then we also count that as a FAIL.  This harness works hard to
    give reasonable output no matter what weird things happen to the
    harnessed program.

    On POSIX systems, the executable is called with everything from
    the test context stuck into the environment with "QMV_" at the
    front of the key -- so if context["foo"] == "bar", then in the
    child, getenv("QMV_foo") will return "bar".  In addition, the
    context key "env.extra" can be set to a string of the form
      "key1=value1 key2=value2 ..."
    to set extra environment variables.  These keys will not have
    anything prefixed to them -- they will be passed as is.
    
    Special context keys:
      env.extra - Used to add variables to the environment on POSIX
        systems, as described above.
      testcmd.path - the directories to search for the executable, in
        the same format as the normal path (ie, colon separated).
        If unset, defaults to current working directory.  (Which is
        probably the same as the test database directory.)

    """

    env_prefix = "QMV_"
    """The string prepended to context keys in the environment.

    When this class runs a Testcmd executable on a POSIX system, it
    will put all of the entries from the current context in that
    executable's environment, with this prefix stuck on the front of
    keys.  So if context["foo"] == "bar", then in the child process,
    getenv("QMV_foo") will return "bar".

    Currently 'QMV_', for compatibility with ExecTest.  This is sort
    of silly, though, and should perhaps be changed.  (It's silly
    because there's nothing QM-specific about the Testcmd interface,
    except for this prefix.)

    """

    arguments = [
        qm.fields.TextField(
            name="executable",
            title="Executable",
            description="Filename of executable to run.",
        ),
        qm.fields.TextField(
            name="test_name",
            title="Test name",
            description="The name of the test the executable should run.",
        ),
        ]

    def Run(self, context, result):
        """Runs the executable and the test contained therein."""
        executable = ""
        path = context.get("testcmd.path", os.curdir)
        for dir in path.split(":"):
            candidate = os.path.join(dir, self.executable)
            if os.path.isfile(candidate):
                executable = candidate
                break
        if not executable:
            raise NoSuchFile("Cannot find testcmd executable " +
                self.executable + " in path " + path)

        (exit_code, stdout, stderr) = self.__execute(
            executable, context)
##        print "Exit code: " + repr(exit_code) + "\n"  # debugging
##        print "Stdout: " + repr(stdout) + "\n"        # debugging
##        print "Stderr: " + repr(stderr) + "\n"        # debugging

        prefixer = qm.label.AsAbsolute("testcmd")

        if exit_code != 0:
            result.Fail()

            # This might be useful for debugging, but I think it's
            # really just superflous.

            l = prefixer("exit_reason")
            if os.WIFSTOPPED(exit_code):
                result[l] = "Stopped by signal: "
                result[l] += str(os.WSTOPSIG(exit_code))
            elif os.WIFSIGNALED(exit_code):
                result[l] = "Killed by signal: "
                result[l] += str(os.WTERMSIG(exit_code))
            elif os.WIFEXITED(exit_code):
                result[l] = "Exited with code: "
                result[l] += str(os.WEXITSTATUS(exit_code))
            else:  # shouldn't happen
                result[l] = "Exited with failure due to unknown causes"
                result[prefixer("raw_exit_code")] = str(exit_code)

            result[Result.CAUSE] = result[l]
            result[prefixer("STDOUT")] = util.quotify(stdout)
            result[prefixer("STDERR")] = util.quotify(stderr)
            return            

        # Well, if we get here, then we know the program at least ran.
        # Let's try parsing the output.
        parses = ()
        bad_parse = 0
        msgs = []
        try:
            parses = self.__parse_rfc822(stdout)
        except InvalidFormat, arg:
            bad_parse = 1
            msgs.append(str(arg))
        if len(parses) != 1 and not bad_parse:
             bad_parse = 1
             msgs.append("Found %s tests described; should be 1" % len(parses))
        if len(parses) >= 1 and parses[0] == {}:
             bad_parse = 1
             msgs.append("First (maybe only) test description contains no " +
                 "information?")

        if bad_parse:
            # we've done all we can
            result.Fail("Invalid output.")
            result[prefixer("details")]  = "Encountered following errors:"
            result[prefixer("details")] += "\n  -- ".join(msgs)
            result[prefixer("STDOUT")] = util.quotify(stdout)
            result[prefixer("STDERR")] = util.quotify(stderr)
            return

        # If we get this far, then we know the program ran and produced
        # valid output.  Lets see what that output looks like.
        parse = parses[0]

        # first set the result & cause
        if not parse.has_key("result"):
            # They failed to create correct output, and that's a
            # failure.
            result.Fail("Parseable output, but no Result: field")
            result[prefixer("STDOUT")] = util.quotify(stdout)
            result[prefixer("STDERR")] = util.quotify(stderr)
            return
        elif parse["result"] == "PASS":
            # Results start out in PASS state, so do nothing.
            pass
        elif parse["result"] == "FAIL":
            result.Fail(parse.get("cause", "Cause unknown."))
        else:  # ERROR, or invalid
            result.SetOutcome(Result.ERROR)
            if parse.has_key("cause"):
                result[Result.CAUSE] = parse["cause"]
            elif parse["result"] == "ERROR":
                result[Result.CAUSE] = "Cause unknown."
            if parse["result"] != "ERROR":
                result[prefixer("RESULT_WARNING")] = (
                    "Bad result field: " + repr(parse["result"]))
        if parse.has_key("result"): del parse["result"]
        if parse.has_key("cause"): del parse["cause"]

        # Now exception fields
        if parse.has_key("exception"):
            result[Result.EXCEPTION] = parse["exception"]
            del parse["exception"]
        if parse.has_key("traceback"):
            result[Result.TRACEBACK] = util.quotify(parse["traceback"])
            del parse["traceback"]

        # and stick the stderr in too
        result[prefixer("STDERR")] = util.quotify(stderr)

        # ok, that's it for magic fields, just stick the rest in
        # willy-nilly
        for key, val in parse.items():
            result[prefixer(key)] = util.quotify(val)

    def __execute(self, executable, context):
        """Runs the command, returning its output, etc.

        Returns a tuple (exit_code, stdout, stderr), where the first
        is an integer and the rest strings.  On non-POSIX systems, the
        exit_code is always 0.  Raises an error if the command cannot
        be executed.  (Actually, this doesn't work right now -- some
        sort of garbage will be returned instead.  Doing subprocesses
        Right under python is non-trivial, and this method should be
        rewritten to do all the messy stuff command.ExecTest does.)

        """
        
        if os.name == "posix":
            # Build a dict containing all the keys to add to the environment
            env_extra = {}
            #   Add all context keys
            for key, val in context.items():
                env_extra[self.env_prefix + key] = val

            #   Add any special context keys
            # FIXME: this doesn't deal with quotes, so it's just
            # impossible to create an environment variables with
            # spaces in its value.
            for assignment in context.get("env.extra", "").split():
                key, val = assignment.split("=", 1)
                env_extra[key] = val

            #   Now build a string for the shell
            cmd_list = []
            if env_extra:
                cmd_list.append("export")
                for key, val in env_extra.items():
                    cmd_list.append("%s='%s'" % (key, val))
                cmd_list.append(";")
            cmd_list.append(executable)
            cmd_list.append("run")
            cmd_list.append("'" + self.test_name + "'")

            # Now use the unix-only Popen3 class, so we can get the
            # return value.
            ## print " ".join(cmd_list)  # debug
            from popen2 import Popen3
            child = Popen3(" ".join(cmd_list), 1)
            
            # FIXME: will this work if stdout and stderr both dump a
            # bunch of output?  I can imagine the kernel filling a
            # buffer and blocking child writes to stderr until we've
            # read some out, but we'll never read any out, because we
            # don't start reading from stderr until the child closes
            # stdout (probably by exiting)... so perhaps we should
            # do alternating incremental reads from each.  But doing
            # that correctly requires mucking about with select() and
            # the like.
            stdout = child.fromchild.read()
            stderr = child.childerr.read()
            exit_code = child.wait()
            return (exit_code, stdout, stderr)
        else:
            # Use boring portable functions
            (stdin_p, stdout_p, stderr_p) = popen3(
                executable + " run '" + self.test_name + "'")
            stdout = stdout_p.read()
            stderr = stderr_p.read()
            return (0, stdout, stderr)

    separation_re = re.compile(r"^\s*$")
    """Recognize separator lines."""
    continuation_re = re.compile(r"^(\s+)")
    """Recognize continuation lines."""
    period_re = re.compile(r"^\s*\.\s*$")
    """Recognize "period only" lines.

    We have a \s* (and not \s+) at the beginning because whitespace is
    stripped before this regexp is used."""    
    bad_key_chars_re = re.compile(r"[^a-zA-Z0-9_-]")
    """Match characters that should be replaced by "_" in keys."""
    def __parse_rfc822(self, str):
        """Converts an rfc822 formatted string into a list of maps.

        Parses str as an rf822 string (well, that imitation of rfc822
        that we document in the class docstring, anyway), and converts
        it to a list of maps.  Each map will have keys normalized to
        lower case, with characters not in a-zA-Z0-9_- replaced by
        "_".  (This incidentally makes all keys into valid labels.)
        Continuation lines will have indentation stripped in the
        appropriate way.  Values will have no trailing newline, though
        they may have embedded newlines.  horizontal Whitespace
        surrounding the : will be stripped.

        Raises InvalidFormat if a parse error occurs.

        """

        s = StringIO(str)
        current = {}
        list = [ current ]
        continuation = 0
        indent = 0
        currkey = ""

        # This is silly, but will do until we can use file iterators
        line = s.readline()
        while line:
            # always ignore right horizontal whitespace
            line = line.rstrip()
            # first we skip ahead on blank lines
            if self.separation_re.match(line):
                # don't generate lots of blank maps when multiple
                # blank lines occur... and also if str starts with
                # one or more blank lines.
                if current != {}:
                    currkey = ""
                    continuation = 0
                    current = {}
                    list.append(current)
            # now handle continuation lines
            elif self.continuation_re.match(line):
                match = self.continuation_re.match(line)
                if not currkey:
                    raise InvalidFormat(
                        "Encountered continuation line with no key")
                if not continuation:
                    continuation = 1
                    indent = len(match.group(1))
                # strip left whitespace, but only as much as is there,
                # or as much as the first continuation line had
                my_indent = len(match.group(1))
                line = line[min(indent, my_indent):]
                # now append it, re-adding the "\n" we stripped out
                # before.  This is where the "internal newlines, but
                # no trailing newline" rule comes from.
                ### print repr(line)  # debug
                if self.period_re.match(line):
                    current[currkey] += "\n"
                else:
                    current[currkey] += "\n" + line
            # ok, we've got a normal start line
            else:
                try:
                    (key, value) = line.split(":", 1)
                except ValueError:
                    raise InvalidFormat("No colon in key line " + repr(line))
                if not key:
                    raise InvalidFormat("No key in line " + repr(line))
                currkey = key.rstrip().lower()
                currkey = self.bad_key_chars_re.sub("_", currkey)
                continuation = 0
                if current.has_key(currkey):
                    raise InvalidFormat("Key " + `currkey` + " used twice.")
                current[currkey] = value.lstrip()
            line = s.readline()
        # Fixup for trailing blank lines -- remove empty maps
        # at the end of the list.
        if len(list) >= 1 and list[-1] == {}:
            list = list[:-1]
        return list
