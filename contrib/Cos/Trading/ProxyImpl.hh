#ifndef _ProxyImpl_hh
#define _ProxyImpl_hh

#include "CosTrading.hh"
#include "TraderComponentsImpl.hh"
#include "SupportAttributesImpl.hh"

class ProxyImpl : virtual public CosTrading::_sk_Proxy, public TraderComponentsImpl, public SupportAttributesImpl
{
public:  
  ProxyImpl(Trader *);
  char *export_proxy(CosTrading::Lookup_ptr, const char *,
		     const CosTrading::PropertySeq &, CORBA::Boolean,
		     const char *, const CosTrading::PolicySeq &);
  void withdraw_proxy(const char *);
  CosTrading::Proxy::ProxyInfo *describe_proxy(const char *);
};

#endif
