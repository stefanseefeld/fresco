#include "Text/TextViewer.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/TextBuffer.hh"
#include "Text/Compositor.hh"
#include "Prague/Sys/Thread.hh"

using namespace Prague;

TextViewer::TextViewer(TextBuffer_ptr txt, TextKit_ptr tk, DrawingKit_ptr dk, Compositor *c) :
  myTextBuffer(TextBuffer::_duplicate(txt)),
  myTextKit(TextKit::_duplicate(tk)),
  myCanonicalDK(DrawingKit::_duplicate(dk)),
  myCompositor(c)
{
  Unistring *us = myTextBuffer->value();
  Unistring single;
  single.length(1);
  for (unsigned long i = 0; i < us->length(); i++) {
    single[0] = (*us)[i];
    this->append(myTextKit->chunk(single));
  }
}

void TextViewer::update(Subject_ptr s, const CORBA::Any &a) 
{
  if (myTextBuffer->_is_equivalent(s)) {
    TextBuffer::Change *ch;  
    if (a >>= ch) {
      switch (ch->type) {

      case TextBuffer::insert:
	{
	  Unistring *u = myTextBuffer->getChars(ch->pos, (CORBA::ULong)ch->len);
	  CORBA::ULong len = u->length();
	  vector<edge_t> newEdges(len);
	  Unistring single;
	  single.length(1);
	  for (unsigned long i = 0; i < len; i++) {
	    single[0] = (*u)[i];
	    Graphic_var child = myTextKit->chunk(single);
	    edge_t edge(Graphic::_duplicate(child), tag());
	    newEdges.push_back(edge);
	    child->addParent(Graphic_var(_this()), edge.second);
	  }
	  {
	    MutexGuard guard(childMutex);
	    children.insert(children.begin()+len, newEdges.begin(), newEdges.end());
	  }	
	}
	break;

      case TextBuffer::remove:
	{
	  MutexGuard guard(childMutex);
	  unsigned long fin = children.size()-1;
	  unsigned long start = (ch->pos > fin ? fin : ch->pos);
	  unsigned long end = (start + ch->len > fin ? fin : start + ch->len);	    
	  for (clist_t::iterator i = children.begin()+start; i != children.begin()+end; i++)
	    (*i).first->removeParent(Graphic_var(_this()), (*i).second);
	  children.erase(children.begin()+start,children.begin()+end);
	}	
	break;
	
      case TextBuffer::cursor:
	// we'll do some cursor-ish stuff someday
	break;
      }
    }
    needResize();
  }
}

TextViewer::~TextViewer() {}

