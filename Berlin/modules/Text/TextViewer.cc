#include "Text/TextViewer.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/TextBuffer.hh"
#include "Text/Compositor.hh"
#include "Prague/Sys/Thread.hh"
#include <algorithm>

using namespace Prague;

TextViewer::TextViewer(TextBuffer_ptr txt, TextKit_ptr tk, DrawingKit_ptr dk, Compositor *c) :
  HBox(),
  myTextBuffer(TextBuffer::_duplicate(txt)),
  myTextKit(TextKit::_duplicate(tk)),
  myCanonicalDK(DrawingKit::_duplicate(dk)),
  myCompositor(c)
{
  // this is not possible at the moment. you need to do the insert
  // _after_ you attach a view.

//   cerr << "in TextViewer ctor" << endl;
//   Unistring *us = myTextBuffer->value();
//   Unistring single;
//   single.length(1);
//   cerr << "built scratch string" << endl;
//   for (unsigned long i = 0; i < us->length(); i++) {
//     single[0] = (*us)[i];
//     cerr << "assigned char" << endl;
//     this->append(Graphic::_duplicate(myTextKit->chunk(single)));
//     cerr << "appended graphic" << endl;
//   }
//   cerr << "appended chunks" << endl;
}

TextViewer::~TextViewer() 
{
}

void TextViewer::update(Subject_ptr s, const CORBA::Any &a) 
{
 if (myTextBuffer->_is_equivalent(s)) {
    TextBuffer::Change *ch;  
    if (a >>= ch) {
      switch (ch->type) {

      case TextBuffer::insert:
	{
	  MutexGuard guard(childMutex);
	  Unistring *u = myTextBuffer->getChars(ch->pos, (CORBA::ULong)ch->len);
	  CORBA::ULong len = u->length();
	  Unistring single;
	  single.length(1);
	  for (unsigned long i = 0; i < len; i++) {
	    single[0] = (*u)[i];
	    Graphic_var child = myTextKit->chunk(single);
	    edge_t edge(Graphic::_duplicate(child), tag());
	    children.insert(children.begin() + ch->pos + i, edge);
	    child->addParent(Graphic_var(_this()), edge.second);
	  }
	}
	break;

      case TextBuffer::remove:
	{
	  MutexGuard guard(childMutex);
	  unsigned long start = min(ch->pos, static_cast<CORBA::ULong>(children.size()));
	  unsigned long end = min(ch->pos + ch->len, static_cast<CORBA::ULong>(children.size()));
	  if (ch->len < 0) swap(start, end);
	  for (clist_t::iterator i = children.begin() + start; i != children.begin() + end; i++)
	    (*i).first->removeParent(Graphic_var(_this()), (*i).second);
	  children.erase(children.begin() + start, children.begin() + end);
	}	
	break;
	
      case TextBuffer::cursor:
	// we'll do some cursor-ish stuff someday
	break;
      }
    }
//     needResize();
    needRedraw();
  }
}


