#!/usr/bin/env python
# My experimental, rough-draft-but-functional, unit test harness generator
# Usage:  $0 foo.syn foo.cc
# Copyright (C) 2002  Nathaniel Smith <njs@fresco.org>

import re
import sys
from cStringIO import StringIO

# to process a tree, we take it from the linker, and we run our processor over
# it, building up a list of test to run
#
# Then we dump them all out again.
# In the future this should be refactored to be more general and more
# powerful, so that we can have a language-neutral core that does clever
# things to figure out the structure of tests (paying attention to all sorts
# of stuff -- tag extraction, dependency checking, etc.), and then modules
# that use this generate language- and build-system-specific harnesses.

from Synopsis import AST
import output  # our local copy of omniidl.output
ExpandingStream = output.Stream
ExpandingStringStream = output.StringStream

"""The class that all test classes inherit from.  This is how we find test
classes.  (We should also support a @is_test_class tag or something, for
classes that we're unable to detect this inheritance for (or don't actually
inherit at all.  Ideally, we should also detect when we neither inherit from
test_class_root nor have the @is_test_class tag, but do inherit from something
that does have the @is_test_class tag.
"""
test_class_root = ("SyUnit", "TestCase")

"""Methods that should be ignored."""
ignore_methods = ("set_up", "tear_down")

"""Illegal test names."""
bad_names = ("all",)

test_file_tmpl = """\
/* This file was automatically generated.  Do not edit! */
#include <TestCmd.hh>
#include <TestCase.hh>
#include <TestCaseWrapper.hh>

@test_class_includes@

int main(char argc, char** argv)
{
    SyUnit::TestCmd testcmd(argc, argv);
    SyUnit::TestCaseWrapper* test;
  
@all_tests@

  return testcmd.run();
}
"""

test_include_tmpl = """#include "@test_class_file@"
"""

single_test_tmpl = """test = new SyUnit::TestCaseWrapperImpl< @test_class@ >
    (// name of test
     "@name@",
     // test method to call
     &@test_class@::@method@,
     // description of this test
     "@desc@"
     );
testcmd.add(test);
"""

class ParsedTestMethod:
    def __init__(self, method_name, test_name, test_desc):
        self.__method_name = method_name
        self.__test_name = test_name
        self.__test_desc = test_desc
    def method_name(self):
        return self.__method_name
    def test_name(self):
        return self.__test_name
    def test_desc(self):
        return self.__test_desc

class ParsedTestClass:
    def __init__(self, class_name, file_name):
        self.__class_name = class_name
        self.__file_name = file_name
        self.__test_methods = []
    def add_test_method(self, method_name):
        self.__test_methods.append(method_name)
    def class_name(self):
        return self.__class_name
    def file_name(self):
        return self.__file_name
    def methods(self):
        return self.__test_methods

class FindTestsVisitor(AST.Visitor):
    def __init__(self, base_class):
        self.base_class = base_class
        self.in_test_class = 0
        self.current_class = None
        self.classes = []

    def visitClass(self, node):
        # looking at an AST.Class
        # figure out if this class inherits from base_class
        # probably this will broken on embedded classes -- how do we tell when
        # we exit a class scope?
        file_name = node.file().filename()
        class_name = "::".join(node.name())
        parent_names = [n.parent().name() for n in node.parents()]
        #print "Parent names of class %s (in %s): %s" % (class_name,
        #                                                file_name,
        #                                                `parent_names`)
        if self.base_class in parent_names:
            #print "Ah-hah, gotcha!"
            self.in_test_class = 1
            self.current_class = ParsedTestClass(class_name, file_name)
            self.classes.append(self.current_class)
            if node.template():
                self.in_test_class = 0
                print "Warning: ignoring template class " + class_name
                return
            for declaration in node.declarations():
                declaration.accept(self)
        
    def visitOperation(self, node):
        if not self.in_test_class:
            return
        if node.realname()[-1] in ignore_methods:
            return
        method = ParsedTestMethod(node.realname()[-1],
                                  node.realname()[-1],
                                  "Description goes here")
        if method.test_name() in bad_names:
            print "Error: bad test name %s, ignored." % method.test_name()
        else:
            self.current_class.add_test_method(method)

    def get_classes(self):
        return self.classes


def fill_template_from_ast(ast, outstream):
    visitor = FindTestsVisitor(test_class_root)
    visitor.visitAST(ast)
    test_files = []
    test_stream = ExpandingStringStream()
    test_stream.inc_indent()
    for tclass in visitor.get_classes():
        if tclass.file_name() not in test_files:
            test_files.append(tclass.file_name())
        class_name = tclass.class_name()
        for method in tclass.methods():
            test_stream.out(single_test_tmpl,
                            name=quote_for_cxx(method.test_name()),
                            test_class=tclass.class_name(),
                            method=method.method_name(),
                            desc=quote_for_cxx(method.test_desc()))

    include_stream = ExpandingStringStream()
    for file in test_files:
        include_stream.out(test_include_tmpl, test_class_file=file)
    
    ex_outstream = ExpandingStream(outstream)
    ex_outstream.out(test_file_tmpl,
                     test_class_includes=include_stream,
                     all_tests=test_stream)

# inefficient and incomplete, but should work well enough
def quote_for_cxx(str):
    """Quote a string so it can be written into a C++ source file."""
    str = re.sub(r"(\\|\")", r"\\\1", str)
    str = re.sub(r"\n", r"\\n", str)
    str = re.sub(r"\t", r"\\t", str)
    return str

def usage():
    print "Usage: %s astfile.syn outfile.cc" % sys.argv[0]

def main():
    if len(sys.argv) != 3:
        usage()
        return
    fill_template_from_ast(AST.load(sys.argv[1]), open(sys.argv[2], "w"))
# useful for debugging:
#    fill_template_from_ast(AST.load(sys.argv[1]), sys.stdout)

if __name__ == "__main__":
    main()
