#include "Trader.hh"
#include "parse_tree.h"
#include "ServiceTypeRepositoryImpl.hh"
#include "link.h"
#include "proxy.h"

#include "kstrstream.h"
#include "kany.h"

#include <sys/stat.h>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <unistd.h>

using namespace CosTrading;

CORBA::Boolean OfferIterator::next_n(CORBA::ULong n, OfferSeq *&o)
{
  CORBA::ULong len = n;
  if (len > offers->length() - position) len = offers->length() - position;
  o = new OfferSeq;
  o->length(len);
  for(CORBA::ULong l = 0; l < len; l++) (*o)[l] = (*offers)[position++];
  if (position < offers->length()) return true;
  return false;
}

void OfferIterator::destroy()
{
  CORBA::release(this);
}

