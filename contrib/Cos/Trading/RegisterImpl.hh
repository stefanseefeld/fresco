#ifndef _RegisterImpl_hh
#define _RegisterImpl_hh

#include "TraderComponentsImpl.hh"
// class Trader;
// class Register;

class RegisterImpl : virtual public CosTrading::_sk_Register,
		     public TraderComponentsImpl, public SupportAttributesImpl
{
public:
  RegisterImpl(Trader *);
  char *_export(CORBA::Object_ptr, const char *, const CosTrading::PropertySeq &);
  void withdraw(const char *);
  CosTrading::Register::OfferInfo *describe(const char *);
  void modify(const char *, const CosTrading::PropertyNameSeq &, const CosTrading::PropertySeq &);
  void withdraw_using_constraint(const char *, const char *);
  CosTrading::Register_ptr resolve(const CosTrading::TraderName &);
};

#endif
