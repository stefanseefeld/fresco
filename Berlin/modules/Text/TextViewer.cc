#include "Text/TextViewer.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/TextBuffer.hh"
#include "Text/Compositor.hh"

TextViewer::TextViewer(TextBuffer_ptr txt, TextKit_ptr tk, DrawingKit_ptr dk, Compositor *c) :
  myCanonicalDK(DrawingKit::_duplicate(dk)),
  myTextBuffer(TextBuffer::_duplicate(txt)),
  myCompositor(c)
{
  Unistring *us = myTextBuffer->value();
  Unistring single;
  single.length(1);
  for (unsigned long i = 0; i < us->length(); i++) {
    single[0] = us->[i];
    this->append(tk->chunk(single));
  }
}

void TextViewer::update(Subject_ptr s, const CORBA::Any &a) 
{
}

TextViewer::~TextViewer() {}

