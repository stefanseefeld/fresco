#include "RegisterImpl.hh"
#include "Trader.hh"

using namespace CosTrading;

RegisterImpl::RegisterImpl(Trader *t) : TraderComponentsImpl(t), SupportAttributesImpl(t) {}
char *RegisterImpl::_export(CORBA::Object_ptr reference, const char *type, const PropertySeq &properties)
{
  if (CORBA::is_nil(reference))
  {
    Register::InvalidObjectRef exc;
    exc.ref = reference;
    throw exc;
  }    
  Offer *offer = new Offer;
  offer->vReference = CORBA::Object::_duplicate(reference);
  offer->vType = CORBA::string_dup(type);
  offer->properties = properties;
  offer->isProxy = false;
  trader->export_offer(offer);
  return CORBA::string_dup(offer->vOfferId.in());
}

void RegisterImpl::withdraw(const char *id) { trader->remove(id);}
Register::OfferInfo* RegisterImpl::describe(const char *id) { return trader->describe(id);}
void RegisterImpl::modify(const char *id, const PropertyNameSeq &del_list, const PropertySeq &modify_list)
{
  trader->modify(id, del_list, modify_list);
}

void RegisterImpl::withdraw_using_constraint(const char *type, const char *constr)
{
  trader->withdraw_using_constraint(type, constr);
}

Register_ptr RegisterImpl::resolve(const TraderName &name)
{
  Register::UnknownTraderName exc;
  exc.name = name;
  throw exc;
  return Register::_nil();
}
