#ifndef _OfferIteratorImpl_hh
#define _OfferIteratorImpl_hh

#include "CosTrading.h"

class OfferIterator : virtual public CosTrading::OfferIterator_skel
{
public:
  OfferIterator(CosTrading::OfferSeq *o) : offers(o), position(0) {}
  ~OfferIterator() { delete offers;}
  virtual CORBA::ULong max_left() { return offers->length() - position;}
  virtual CORBA::Boolean next_n(CORBA::ULong, CosTrading::OfferSeq *&);
  virtual void destroy();
protected:
  CosTrading::OfferSeq *offers;
  CORBA::ULong position;
};

#endif
