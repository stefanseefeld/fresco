#
# This builds the berlin documentation in HTML and optionally PDF
# it uses files found _within_ the berlin tree to save you the hassle
# of installing all the supporting machinery yourself. You will need
# jade, dia, jadetex/pdfjadetex, mogrify (imagemagick) and epstopdf 
# installed, however, as they're a little big to be distributing
# in our archive.
#

STYLESHEET := stylesheets/berlin.dsl
JADE_FLAGS := -c sgml.catalog
JADE_HTML_FLAGS := -V %use-id-as-filename% -ihtml -D ../ -d $(STYLESHEET)\#html $(JADE_FLAGS) -t sgml
JADE_TEX_FLAGS := -d $(STYLESHEET)\#print $(JADE_FLAGS) -t tex
BOOK_FILES := $(wildcard src/*.sgm)
HTML_OUTPUT := $(addprefix html/, $(notdir $(BOOK_FILES:.sgm=.html)))
PRINT_OUTPUT := $(addprefix print/, $(notdir $(BOOK_FILES:.sgm=.pdf)))
FIGURES := $(wildcard figures/*.dia)
FIGURE_VERSIONS := $(FIGURES:.dia=.pdf) $(FIGURES:.dia=.jpg)

all: figures html print

figures: $(FIGURE_VERSIONS)

html: $(HTML_OUTPUT)

print: $(PRINT_OUTPUT)

%.eps: %.dia
	dia --export=$@ $< 

%.jpg: %.eps
	mogrify -format jpg -geometry 55%x55% $<

figures/%.pdf: figures/%.eps
	cd figures; epstopdf $(notdir $<); cd ..;

html/%.html: src/%.sgm $(BOOK_FILES)
	cd html; jade $(JADE_HTML_FLAGS) $<; cd ../;

print/%.tex: src/%.sgm $(BOOK_FILES)
	jade $(JADE_TEX_FLAGS) -o $@ $< 

print/%.pdf: print/%.tex
	cd print; pdfjadetex $(notdir $<); cd ..;

clean:	
	rm -f html/*.html figures/*.jpg figures/*.pdf figures/*.eps print/*.pdf print/*.aux print/*.log
