#include "ProxyImpl.hh"

using namespace CosTrading;

// ProxyImpl::ProxyImpl(Trader *t) : ::TraderComponents(t), ::SupportAttributes(t), trader(t) {}
char *ProxyImpl::export_proxy(Lookup_ptr target, const char *type, const PropertySeq &properties, CORBA::Boolean if_match_all,
			      const char *recipe, const PolicySeq &policies_to_pass_on)
{
  return trader->export_proxy(target, type, properties, if_match_all, recipe, policies_to_pass_on);
}

void ProxyImpl::withdraw_proxy(const char *id) { trader->withdraw_proxy(id);}
Proxy::ProxyInfo *ProxyImpl::describe_proxy(const char *id) { return trader->describe_proxy(id);}
