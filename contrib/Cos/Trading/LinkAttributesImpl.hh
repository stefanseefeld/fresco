#ifndef _LinkAttributesImpl_hh
#define _LinkAttributesImpl_hh

#include "CosTrading.hh"
#include "Trader.hh"

class LinkAttributesImpl : virtual public CosTrading::_sk_LinkAttributes
{
public:
  LinkAttributes(Trader *t) : trader(t) {}
  virtual CosTrading::FollowOption max_link_follow_policy() { return trader->maxLinkFollowPolicy();}
private:
  Trader *trader;
};

#endif
