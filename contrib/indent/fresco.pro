// This file attempts to implement the Fresco style guidelines for
// indent(1).
// To use, copy to ~/.indent.pro, or just set the environment variable
// INDENT_PROFILE to point to it.
// Please reports bugs and improvements at issues.fresco.org.

// Blank lines
--blank-lines-after-declarations
--blank-lines-after-procedures
--blank-lines-before-block-comments
--leave-optional-blank-lines

// Comments
--comment-delimiters-on-blank-lines
--start-left-side-of-comments

// Braces
--braces-after-if-line
--brace-indent0
--dont-cuddle-do-while
--case-indentation0
--case-brace-indentation0
--space-special-semicolon

// Spaces and newlines
--no-space-after-function-call-names
--blank-before-sizeof
--space-after-cast
--space-after-for
--space-after-if
--space-after-while
--no-space-after-parentheses
--no-blank-lines-after-commas // newlines after
commas in function declarations
--procnames-start-lines
--braces-after-struct-decl-line

// Indentation
--indent-level4
--continuation-indentation4
--continue-at-parentheses
--leave-preprocessor-space

// Line length
--line-length78
