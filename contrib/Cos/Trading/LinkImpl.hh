#ifndef _LinkImpl_hh
#define _LinkImpl_hh

#include "CosTrading.hh"
#include "TraderComponentsImpl.hh"
#include "SupportAttributesImpl.hh"
#include "LinkAttributesImpl.hh"

class LinkImpl : virtual public CosTrading::_sk_Link,
         public TraderComponents,
         public SupportAttributes,
         public LinkAttributes,
{
  typedef map<string, CosTrading::Link::LinkInfo> llist_t;
public:
  LinkImpl(Trader *);
  virtual void add_link(const char *, CosTrading::Lookup_ptr, CosTrading::FollowOption, CosTrading::FollowOption);
  virtual void remove_link(const char *);
  virtual CosTrading::Link::LinkInfo *describe_link(const char *);
  virtual CosTrading::LinkNameSeq *list_links();
  virtual void modify_link(const char *, CosTrading::FollowOption, CosTrading::FollowOption);
private:
  llist_t links;
};

#endif
