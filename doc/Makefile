# this is a graydon's-home-machine-specific
# makefile for building the HTML and PDF berlin books
# if anyone would like to make it a little more portable
# please feel free

STYLESHEETS = /usr/lib/dsssl/stylesheets/docbook
HTML_SHEET = $(STYLESHEETS)/html/docbook.dsl
PRINT_SHEET = $(STYLESHEETS)/print/docbook.dsl
DOCBOOK_VARS = -V %use-id-as-filename% 
BOOK_FILES = berlin-man.sgm berlin-intro.sgm berlin-prog.sgm berlin-user.sgm
BOOK_ROOT = berlin-man.sgm

all: html/HTML.manifest print/berlin-man.tex


html/HTML.manifest: $(BOOK_FILES)
	cd html; jade $(DOCBOOK_VARS) -d $(HTML_SHEET) -t sgml ../$(BOOK_ROOT); cd ..;

print/berlin-man.tex: $(BOOK_FILES)
	jade -d $(PRINT_SHEET) -t tex -o print/berlin-man.tex $(BOOK_ROOT);\
	cd print; jadetex berlin-man.tex; \
	dvips -o berlin-man.ps berlin-man.dvi; cd ..;
