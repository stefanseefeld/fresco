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
using namespace CosTradingRepos;
/*****************************************************
 *
 * Used for Preferences
 *
 *****************************************************/

struct ProcessedOffer
{
  ProcessedOffer() : offer(0) {}
  ProcessedOffer(Offer *o, PreferencesSortType t, PreferencesReturn &r) : offer(o), type(t), ret(t) {}
  bool operator < (const ProcessedOffer &o) const
  {
    // Offers that caused an error in the preferences
    // are smaller then all the others => they are the last ones
    // in the list of offers returned to the client.
    if (ret.type == PreferencesReturn::PRT_ERROR && o.ret.type == PreferencesReturn::PRT_ERROR) return true;
    if (ret.type == PreferencesReturn::PRT_ERROR) return false;
    if (o.ret.type == PreferencesReturn::PRT_ERROR) return true;
    
    // Assume that all are equal
    if (type == PST_RANDOM || type == PST_FIRST) return true;
    if (type == PST_WITH) return !(ret.i < o.ret.i);
    if (ret.type == PreferencesReturn::PRT_NUM && o.ret.type == PreferencesReturn::PRT_NUM)
      return !(ret.i < o.ret.i);
    if (ret.type == PreferencesReturn::PRT_FLOAT && o.ret.type == PreferencesReturn::PRT_FLOAT)
      return !(ret.f < o.ret.f);
    if (ret.type == PreferencesReturn::PRT_NUM && _o.ret.type == PreferencesReturn::PRT_FLOAT)
      return !((float)ret.i < o.ret.i);
    if (ret.type == PreferencesReturn::PRT_FLOAT && _o.ret.type == PreferencesReturn::PRT_NUM)
      return !(ret.f < (float)o.ret.i);
    assert(0);
    return false;
  }  
  PreferencesReturn ret;
  PreferencesSortType type;
  Offer *offer;
};

Trader::Trader(CORBA::Object_ptr obj)
  : uniqueId(0)
{
  ///////////
  // Create a unique id as good as possible
  ///////////
  char buffer[ 100 ];
  sprintf( buffer, "%i.%i", (int)time( 0L ), (int)getpid() );
  int len = strlen( buffer );
  m_requestIdStem.length( len );
  for( int i = 0; i < len; i++ )
    m_requestIdStem[i] = buffer[i];
  
  ///////////
  // Create the trader components
  ///////////
  lookup = new LookupImpl(this, _obj);
  _register = new RegisterImpl(this);
  typeRepository = new ServiceTypeRepositoryImpl(this);
  link = new LinkImpl(this);
  proxy = new ProxyImpl(this);
}

Trader::Trader( const CORBA::BOA::ReferenceData &tag )
{
  m_uniqueId = 0;

  ///////////
  // Create a unique id as good as possible
  ///////////
  char buffer[ 100 ];
  sprintf( buffer, "%i.%i", (int)time( 0L ), (int)getpid() );
  int len = strlen( buffer );
  m_requestIdStem.length( len );
  for( int i = 0; i < len; i++ )
    m_requestIdStem[i] = buffer[i];
  
  m_pLookup = new Lookup_impl( this, tag );
  m_pRegister = new Register_impl( this );
  m_pTypeRepository = new TypeRepository_impl( this );
  m_pLink = new Link_impl( this );
  m_pProxy = new Proxy_impl( this );
}
  
Lookup_ptr Trader::lookup_if() { return lookup->_this();}
Register_ptr Trader::register_if() { return _register->_this();}
Link_ptr Trader::link_if() { return link->_this();}
Proxy_ptr Trader::proxy_if() { return proxy->_this()}
TypeRepository_ptr Trader::typeRepository() { return typeRepository->_this()}
ServiceTypeRepository_ptr Trader::serviceTypeRepository() { return typeRepository->_this();}
CORBA::ULong Trader::defSearchCard() { return 100;}
CORBA::ULong Trader::maxSearchCard() { return 100;}
CORBA::ULong Trader::defMatchCard() { return 100;}
CORBA::ULong Trader::maxMatchCard() { return 100;}
CORBA::ULong Trader::defReturnCard() { return 100;}
CORBA::ULong Trader::maxReturnCard() { return 100;}
CORBA::ULong Trader::maxList() { return 100;}
CORBA::ULong Trader::defHopCount() { return 5;}
CORBA::ULong Trader::maxHopCount() { return 5;}
FollowOption Trader::defLinkFollowPolicy() { return if_no_local;}
FollowOption Trader::maxLinkFollowPolicy() { return always;}
void Trader::export_offer(Offer *offer)
{
  // Check wether we know this service type
  if (!typeRepository->isServiceTypeKnown(offer->vType.in()))
    {
      UnknownServiceType exc;
      exc.type = CORBA::string_dup(offer->vType.in());
      delete _offer;
      throw exc;
    }
  // This function can not raise an exception since we checked the service type already.
  // In addition its exceptions are a subset of ours
  ServiceTypeRepository::TypeStruct_var desc = typeRepository->fully_describe_type(offer->vType.in());

  // Check wether the passed object has the correct interface
  if (!offer->vReference->_is_a(desc->if_name.in()))
  {
    Register::InterfaceTypeMismatch exc;
    exc.reference = _offer->vReference;
    exc.type = CORBA::string_dup(offer->vType.in());
    delete offer;
    throw exc;
  }
  
  // Check wether property names are duplicated and
  // wether the types of the property values match the ones of the repository
  list<string> names;
  CORBA::ULong len = offer->properties.length();
  for(CORBA::ULong l0 = 0; l0 < len; l0++)
    {
      // Check for dupes
      if (find(names.begin(), names.end(), string(offer->properties[l0].name.in()) != names.end()))
    {
      DuplicatePropertyName exc;
      exc.name = CORBA::string_dup(offer->properties[l0].name.in());
      delete _offer;
      throw exc;
    }
      names.push_back(offer->properties[l0].name.in());
      // Find the corresponding property entry in the service type
      CORBA::ULong tlen = desc->props.length();
      for(CORBA::ULong t = 0; t < tlen; t++ )
    {
      if (strcmp(desc->props[t].name.in(), offer->properties[l0].name.in()) == 0L)
        {
          CORBA::TypeCode_var tc = offer->properties[l0].value.type();
          if (!tc->equaltype(desc->props[t].value_type.in()))
        {
          PropertyTypeMismatch exc;
          exc.prop = offer->properties[l0];
          exc.type = offer->vType.in();
          delete offer;
          throw exc;
        }
        }
    }
      // OMG does not specify an exception for properties which are not mentioned
      // in the type repository. So we just say: Ok 
    }
  // Check wether all mandatory properties are present
  len = desc->props.length();
  for(CORBA::ULong l1 = 0; l1 < len; l1++)
    {
      if (desc->props[l1].mode == ServiceTypeRepository::PROP_MANDATORY ||
      desc->props[l1].mode == ServiceTypeRepository::PROP_MANDATORY_READONLY)
    if (find( names.begin(), names.end(), string(desc->props[l1].name.in()) ) == names.end())
      {
        MissingMandatoryProperty exc;
        exc.type = CORBA::string_dup(offer->vType.in());
        exc.name = CORBA::string_dup(desc->props[l1].name.in());
        delete offer;
        throw exc;
      }
    }
  char buffer[100];
  sprintf(buffer, "%i", uniqueId++);
  offer->vOfferId = CORBA::string_dup(buffer);
  lstOffers.push_back(offer);
}

void Trader::remove(const char *id)
{
  list<Offer*>::iterator it(lstOffers.begin());
  for ( ; it != lstOffers.end(); ++it)
    {
      if (strcmp((*it)->vOfferId.in(), id) == 0)
    {
      Offer *p = *it;
      lstOffers.erase(it);
      delete p;
      return;
    }
    }
  UnknownOfferId exc;
  exc.id = id;
  throw exc;
}

void Trader::import(const char *type, const char *constr, const char *pref, const PolicySeq &policies,
            const Lookup::SpecifiedProps &desired_props, CORBA::ULong how_many,
            OfferSeq *&offers, OfferIterator_ptr &offer_itr,
            PolicyNameSeq *&limits_applied)
{
  /**
   * Variables which may be affected by policies.
   */
  CORBA::ULong search_card = defSearchCard();
  CORBA::ULong match_card = defMatchCard();
  CORBA::ULong return_card = defReturnCard();
  CORBA::ULong hop_count = defHopCount();
  FollowOption link_follow_rule = defLinkFollowPolicy();
  bool importer_link_follow_rule = false;
  string starting_trader;
  bool exact_type_match = false;
  Admin::OctetSeq stem;
  stem.length(0);
  
  /**
   * Policies
   */
  list<string> policy_names;
  CORBA::ULong max = policies.length();
  for (CORBA::ULong i0 = 0; i0 < max; i0++)
    {
      // Check wether no policy has a dupe
      if (find(policy_names.begin(), policy_names.end(), string(policies[i0].name.in())) != policy_names.end())
    {
      DuplicatePolicyName exc;
      exc.name = CORBA::string_dup(policies[i0].name.in());
      throw exc;
    }
      policy_names.push_back(policies[i0].name.in());
      if (strcmp( "hop_count", policies[i0].name) == 0)
    {
      if (!(policies[i0].value >>= hop_count))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      if (hop_count > maxHopCount())
        hop_count = maxHopCount();
    }
      else if (strcmp( "search_card", policies[i0].name) == 0)
    {
      if (!(policies[i0].value >>= search_card))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      if (search_card > maxSearchCard())
        search_card = maxSearchCard();
    }
      else if (strcmp( "match_card", policies[i0].name) == 0)
    {
      if (!(policies[i0].value >>= match_card))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      if (match_card > maxMatchCard())
        match_card = maxMatchCard();
    }
      else if (strcmp("return_card", policies[i0].name) == 0)
    {
      if (!(policies[i0].value >>= return_card))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      if (return_card > maxReturnCard())
        return_card = maxReturnCard();
    }
      else if (strcmp("link_follow_rule", policies[i0].name) == 0)
    {
      if (!(policies[i0].value >>= link_follow_rule))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      importer_link_follow_rule = true;
      // HACK: We rely on the fact the enums are numerated in an ascending manner
      if (link_follow_rule > maxLinkFollowPolicy())
        link_follow_rule = maxLinkFollowPolicy();
    }
      else if (strcmp("starting_trader", policies[i0].name) == 0)
    {
      char *str;
      if (!(policies[i0].value >>= str))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      starting_trader = (const char *)str;
    }
      else if (strcmp("exact_type_match", policies[i0].name) == 0)
    {
      CORBA::Boolean b;
      if (!(policies[i0].value >>= CORBA::Any::to_boolean(b)))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
      exact_type_match = (bool)b;
    }
      else if (strcmp("RequestId", policies[i0].name) == 0)
    {
      CORBA::Boolean b;
      if (!(policies[i0].value >>= stem))
        {
          Lookup::PolicyTypeMismatch exc;
          exc.the_policy = policies[i0];
          throw exc;
        }
    }
    }
  ////////////
  // Check wether we already processed this query.
  // We use the stem to find out
  ////////////
  bool cancel = true;
  CORBA::ULong stemlen = stem.length();
  if (stemlen == requestIdStem.length() && stemlen != 0)
    {
      for(CORBA::ULong i1 = 0; i1 < stemlen; i1++)
    if (stem[i1] != requestIdStem[i1])
      {
        cancel = false;
        break;
      }
    }
  else cancel = false;

  if (cancel)
    {
      cerr << "Canceling request to avoid loops" << endl;
      limits_applied = new PolicyNameSeq;
      limits_applied->length(0);
      offer_itr = 0L;
      offers = new OfferSeq;
      offers->length(0);
    return;
  }
  
  /**
   * Service Type Names
   */
  // Do we know this service type ?
  if (!typeRepository->isServiceTypeKnown(type))
    {
      UnknownServiceType exc;
      exc.type = CORBA::string_dup(type);
      throw exc;
    }
  // Find all offers matching the service type but not more then search_card
  list<Offer*> search;
  list<Offer*>::iterator it = lstOffers.begin();
  for( ; it != m_lstOffers.end(); ++it)
    {
      if (search.size() == search_card) break;
      cout << "Comparing " << (const char*)(*it)->vType << " and " << (const char*)type << endl;
      if ((!exact_type_match && typeRepository->isSubTypeOf((*it)->vType.in(), type)) ||
      (exact_type_match && strcmp(type, (*it)->vType.in()) == 0L))
    search.push_back((*it));
    }
  /**
   * Constraints
   */
  ParseTreeBase *constraint_tree = 0L;
  if (strlen(constr) > 0)
    {
      constraint_tree = parseConstraints(constr);
      if (constraint_tree == 0L)
    {
      IllegalConstraint exc;
      exc.constr = CORBA::string_dup( constr );
      throw exc;
    }
    }
  list<Offer*> match;
  list<Offer*>::iterator it2(search.begin());
  for( ; it2 != search.end(); ++it2)
    {
      if (match.size() == match_card) break;
      if (constraint_tree == 0L || (matchConstraint(constraint_tree, &((*it2)->properties)) == 1))
    {
      cout << "Got match" << endl;;
      match.push_back(*it2);
    }
      else cout << "Does not match constraint" << endl;
  }
  
  /**
   * Linked Traders
   */
  /*
   * The following strcmp calls were changed by
   * Oscar Stiffelman, oscar@internap.com
   * The orginal code used "policies" as the second parameter
   * I changed it to pols
   */
  // This variable is used to hold all linked offers and delete them
  // once we return from this function
  list<Offer> linked_offers;
  if (hop_count > 0 && (link_follow_rule == always || (link_follow_rule == if_no_local && match.size() == 0)))
    {
      // Iterate over every link
      map<string, Link::LinkInfo,less<string> >::iterator it = link->begin();
      for( ; it != m_pLink->end(); ++it)
    {
      /////////
      // Find the correct link_follow_rule
      /////////
      FollowOption follow = (*it).second.def_pass_on_follow_rule;
      // Did the user specify a whish for the link_follow_rule ?
      if (importer_link_follow_rule)
        {
          // Do we have to limit the users wish or not ?
          if (link_follow_rule <= (*it).second.limiting_follow_rule) follow = link_follow_rule;
          else follow = (*it).second.limiting_follow_rule;
        }
      ////////
      // Add/change the link_follow_rule policy
      ////////
      PolicySeq pols = policies;
      CORBA::ULong len = pols.length();
      bool found = false;
      for (CORBA::ULong i2 = 0; i2 < len; i2++)
        {
          if (strcmp("link_follow_rule", pols[i2].name) == 0)
        {
          found = true;
          pols[i2].value <<= follow;
          break;
        }
        }
      if (!found)
        {
          Policy p;
          p.name = CORBA::string_dup( "link_follow_rule" );
          p.value <<= follow;
          pols.length(len + 1);
          pols[len] = p;
        }
      /////////
      // We want to see ALL properties. Otherwise I can later on not evaluate
      // the preferences
      /////////
      Lookup::SpecifiedProps desired;
      desired._d(Lookup::all);
      
      /////////
      // Ask for as much offers as we are allowed to return at all.
      // Since we ask every link for this amount of offers we might get too many
      // of them here. But it is unpredictable how many offers the other links will deliver.
      /////////
      CORBA::ULong amount = return_card - match.size();
      
      /////////
      // Add/change the return_card policy to match our needs. It may happen that the default return
      // card of linked trader is too low, so we may have to ask for more using the return_card policy.
      /////////
      len = pols.length();
      found = false;
      for (CORBA::ULong i3 = 0; i3 < len; i3++)
        {
          if (strcmp("return_card", pols[i3].name) == 0)
        {
          found = true;
          pols[i3].value <<= amount;
          break;
        }
        }
      if (!found)
        {
          Policy p;
          p.name = CORBA::string_dup("return_card");
          p.value <<= amount;
          pols.length(len + 1);
          pols[len] = p;
        }
      
      /////////
      // Add/change the hop counts
      /////////
      len = pols.length();
      found = false;
      for (CORBA::ULong i4 = 0; i4 < len; i4++)
        {
          if (strcmp("hop_count", pols[i4].name) == 0)
        {
          found = true;
          pols[i4].value <<= hop_count - 1;
          break;
        }
        }
      if (!found)
        {
          Policy p;
          p.name = CORBA::string_dup("hop_count");
          p.value <<= hop_count - 1;
          pols.length(len + 1);
          pols[len] = p;
        }

      /////////
      // If there is no RequestId policy yet, then we create one,
      // otherwise we wont touch an existing one
      /////////
      found = false;
      len = pols.length();
      for (CORBA::ULong i5 = 0; i5 < len; i5++)
        {
          if (strcmp("RequestId", pols[i5].name) == 0)
        break;
        }
      if (!found)
        {
          Policy p;
          p.name = CORBA::string_dup("RequestId");
          p.value <<= m_requestIdStem;
          pols.length(len + 1);
          pols[len] = p;
        }

      /////////
      // Call the linked trader
      /////////
      OfferSeq_var result;
      OfferIterator_var itr;
      PolicyNameSeq_var limits;
      (*it).second.target->query(type, constr, pref, pols, desired, amount, result, itr, limits);
      
      // Release the iterator if there is any. We dont need it.
      if (!CORBA::is_nil(itr))
        {  
          itr->destroy();
          itr = 0L;
        }      

      /////////
      // Merge the result of the linked trader with the offers of this trader
      /////////
      len = result->length();
      for(CORBA::ULong l2 = 0; l2 < len; l2++)
        {
          Offer o;
          o.vReference = result[l2].reference;
          o.properties = result[l2].properties;
          o.vType = CORBA::string_dup(type);
          // We fake an offer id here. It is not used here so it does not matter
          o.vOfferId = CORBA::string_dup("");
          // We move the offer in this list so it becomes delete once the function returns or exits
          linked_offers.push_back(o);
          match.push_back(&(linked_offers.back()));
        }
    }
    }
       
  /**
   * Preferences
   */
  ParseTreeBase *pref_tree = 0L;
  PreferencesSortType ptype = PST_ERROR;
  if (strlen(pref) > 0)
    {
      pref_tree = parsePreferences(pref, ptype);
      if (pref_tree == 0L)
    {
      Lookup::IllegalPreference exc;
      exc.pref = CORBA::string_dup(pref);
      throw exc;
    }
    }
  list<ProcessedOffer> ret;
  list<Offer*>::iterator it3(match.begin());
  for( ; it3 != match.end(); ++it3)
    {
      // By default this struct is in error mode
      PreferencesReturn preturn;
      if (pref_tree != 0L)
    {
      int i = matchPreferences(pref_tree, &((*it3)->properties), preturn);
      if (preturn.type == PreferencesReturn::PRT_ERROR)
        cout << "Error in pref evaluation " << i << endl;
      else
        cout << "Got preference of " << preturn.i << endl;
    }
      if (ret.size() == return_card) break;
      ret.push_back(ProcessedOffer((*it3), ptype, preturn));
    }

  /**
   * Sort by preferences.
   */
  {
    set<ProcessedOffer, less<ProcessedOffer> > sorted_ret;
    list<ProcessedOffer>::iterator il;
    for (il = ret.begin(); il != ret.end(); ++il) sorted_ret.insert (*il);
    ret.erase (ret.begin(), ret.end());
    set<ProcessedOffer, less<ProcessedOffer> >::iterator is;
    for (is = sorted_ret.begin(); is != sorted_ret.end(); ++is) ret.push_back (*is);
  }
  
  /**
   * Limit number of returns and put the resulting offers in the out parameter "offers"
   * and in the OfferIterator.
   */
  max = return_card;
  if (ret.size() < max)
    max = ret.size();
  
  offers = new OfferSeq;
  
  OfferSeq *iterator_offers = 0L;
  if (max > how_many)
    {
      offers->length(how_many);
      iterator_offers = new OfferSeq;
      iterator_offers->length(max - how_many);
    }
  else offers->length(max);

  CORBA::ULong i = 0;
  list<ProcessedOffer>::iterator it4(ret.begin());
  OfferSeq *dest = offers;
  for( ; it4 != ret.end(); ++it4)
    {
      // Decide which offes have to go in the iterator
      if (i == how_many && dest == offers)
    {
      i = 0;
      dest = iterator_offers;
    }

      /**
       * Proxy handling
       **/
      Offer o;
      // Do we have to receive the object reference from a proxy ?
      if (!(*it4).offer->isProxy)
    o.reference = (*it4).offer->vReference;
      else
    {
      PolicySeq pols;
      OfferSeq_var seq;
      OfferIterator_var itr;
      PolicyNameSeq_var limits;
      
      // Append the proxies policies
      pols = policies;
      CORBA::ULong pl = pols.length();
      pols.length(pl + (*it4).offer->vProxy->policies_to_pass_on.length());
      for(CORBA::ULong l3 = 0; l3 < (*it4).offer->vProxy->policies_to_pass_on.length(); l3++)
        pols[pl + l3] = (*it4).offer->vProxy->policies_to_pass_on[l3];
      
      // Use recipe to construct the constraints
      string constraint = "";
      string recipe = (*it4).offer->vProxy->recipe.in();
      if ( recipe == "" )
        constraint = CORBA::string_dup(constr);
      else
        {
          char buf[2] = { 0, 0};
          // Iterate over recipe
          for (unsigned int p = 0; p < recipe.size(); ++p)
        {
          if (recipe[p] != '$')
            {
              buf[0] = recipe[p];
              constraint += buf;
            }
          else
            {
              p++;
              // No character after "$"
              if (p == recipe.size())
            {
              Proxy::IllegalRecipe exc;
              exc.recipe = CORBA::string_dup(recipe.c_str());
              throw exc;
            }
              char n = recipe[p++];
              // Add complete primary constraint
              if (n == '*') constraint += constr;
              // "$" was used as escape character
              else if (n != '(')
            {
              buf[0] = n;
              constraint += buf;
            }
              // Insert value of some property
              else
            {
              // Find the name in brackets
              int start = p;
              while (p < recipe.size() && recipe[p] != ')') p++;
              if (p == recipe.size())
                {
                  Proxy::IllegalRecipe exc;
                  exc.recipe = CORBA::string_dup(recipe.c_str());
                  throw exc;
                }
              p++;
              string name;
              name.assign(recipe, start, p - start);
              // Find property with that name
              CORBA::Long l = 0;
              while(l < (*it4).offer->properties.length() &&
                !(name == (*it4).offer->properties[l].name.in()))
                l++;
              if (l == (*it4).offer->properties.length())
                {
                  Proxy::IllegalRecipe exc;
                  exc.recipe = CORBA::string_dup(recipe.c_str());
                  throw exc;
                }
              // Append CORBA Any to string
              KOStrStream str(constraint);
              str << (*it4).offer->properties[l].value;
            }
            }
        }
        }
      cerr << "->Proxy" << endl;
      (*it4).offer->vProxy->target->query(type, constraint.c_str(), pref, policies, desired_props, 1, seq, itr, limits);
      cerr << "Proxy-<" << endl;
      // TODO: catch all exceptions here

      // Release iterator at once
      if (!CORBA::is_nil(itr))
        {
          cerr << "Destruct" << endl;
          itr->destroy();
          CORBA::release(itr);
        }

      // Check wether we got a result. Otherwise skip this offer completely
      if (seq->length() > 1)
        {
          cerr << "Oooops, the proxy did give us more than one return." << endl;
          dest->length(dest->length() - 1);
          continue;
        }
      else if (seq->length() == 0)
        {
          cerr << "Oooops, the proxy did not give us a return" << endl;
          dest->length(dest->length() - 1);
          continue;
        }
      o.reference = seq[(CORBA::ULong)0].reference;
      cerr << "Proxy call done" << endl;
    }
      
      /**
       * Which properties should we deliver ?
       */
      if (desired_props._d() == Lookup::all)
    o.properties = (*it4).offer->properties;
      else if (desired_props._d() == Lookup::some)
    {
      CORBA::ULong size = 0;
      CORBA::ULong dlen = desired_props.prop_names().length();
      CORBA::ULong len = (*it4).offer->properties.length();
      o.properties.length(size);
      for(CORBA::ULong l4 = 0; l4 < len; l4++)
        {
          for(CORBA::ULong d = 0; d < dlen; d++)
        if (strcmp((*it4).offer->properties[l4].name.in(), desired_props.prop_names()[d].in()) == 0)
          {
            o.properties.length(size + 1);
            o.properties[size] = (*it4).offer->properties[l4];
            size++;
          }
        }
    }
      else if (desired_props._d() == Lookup::none)
    {
      o.properties.length( 0 );
    }
      (*dest)[i++] = o;
    }

  /**
   * Policies again
   */
  // HACK
  limits_applied = new PolicyNameSeq;
  limits_applied->length( 0 );
  
  /**
   * Offer Iterator
   */
  if (iterator_offers == 0L)
    offer_itr = 0L;
  else
    offer_itr = OfferIterator::_duplicate(new OfferIterator(iterator_offers));
  
  /**
   * Clean up
   */
  if (constraint_tree)
    delete constraint_tree;
  if (pref_tree)
    delete pref_tree;
}

Register::OfferInfo* Trader::describe( const char* id )
{
  list<Offer*>::iterator it = m_lstOffers.begin();
  for( ; it != m_lstOffers.end(); ++it )
  {
    if ( strcmp( (*it)->vOfferId.in(), id ) == 0L )
    {
      Register::OfferInfo* info = new Register::OfferInfo;
      info->reference = (*it)->vReference;
      info->type = CORBA::string_dup( (*it)->vType.in() );
      info->properties = (*it)->properties;
      return info;
    }
  }
  
  UnknownOfferId exc;
  exc.id = CORBA::string_dup( id );
  mico_throw( exc );
  return NULL;
  
}

void Trader::modify( const char* id, const PropertyNameSeq& del_list,
             const PropertySeq& modify_list )
{
  list<Offer*>::iterator it = m_lstOffers.begin();
  for( ; it != m_lstOffers.end(); ++it )
  {
    if ( strcmp( (*it)->vOfferId.in(), id ) == 0L )
    {
      ServiceTypeRepository::TypeStruct_var desc = m_pTypeRepository->fully_describe_type( (*it)->vType.in() );

      CORBA::ULong plen = (*it)->properties.length();
      CORBA::ULong ptlen = desc->props.length();

      /**
       * Check del_list properties.
       */
      list<string> del;
      CORBA::ULong len = del_list.length();
      for( CORBA::ULong l5 = 0; l5 < len; l5++ )
      {
    // Check for dupes in del_list ?
    if( find( del.begin(), del.end(), string(del_list[l5].in()) ) != del.end() )
    {
      DuplicatePropertyName exc;
      exc.name = del_list[l5].in();
      mico_throw( exc );
    }
    del.push_back( del_list[l5].in() );

    // Check wether the property is mandatory.
    // In this case we may not remove it.
    for( CORBA::ULong t = 0; t < ptlen; t++ )
    {
      if( strcmp( del_list[l5].in(), desc->props[t].name.in() ) == 0L )
      {
        if( desc->props[t].mode == ServiceTypeRepository::PROP_MANDATORY_READONLY ||
        desc->props[t].mode == ServiceTypeRepository::PROP_MANDATORY )
        {
          Register::MandatoryProperty exc;
          exc.type = CORBA::string_dup( (*it)->vType.in() );
          exc.name = CORBA::string_dup( del_list[l5].in() );
          mico_throw( exc );
        }
      }
    }

    // Does the property exist ?
    bool found = false;
    for( CORBA::ULong p = 0; p < plen; p++ )
    {
      if( strcmp( del_list[l5].in(), (*it)->properties[p].name.in() ) == 0L )
      {
        found = true;
        break;
      }
    }
    if ( !found )
    {
      Register::UnknownPropertyName exc;
      exc.name = CORBA::string_dup( del_list[l5].in() );
      mico_throw( exc );
    }
      }
      
      /**
       * Which modified properties do right now not exist and have to be added
       * and which ones have to be modified
       */
      map<string, Property,less<string> > add;
      map<string, Property,less<string> > modify;
      len = modify_list.length();
      for( CORBA::ULong l6 = 0; l6 < len; l6++ )
      {
    // Check for dupes in modify_list
    if ( add.find( modify_list[l6].name.in() ) != add.end() ||
         modify.find( modify_list[l6].name.in() ) != modify.end() )
    {
      DuplicatePropertyName exc;
      exc.name = del_list[l6].in();
      mico_throw( exc );
    }
    
    // Does the offer already contain this property
    bool found = false;
    for( CORBA::ULong p = 0; p < plen; p++ )
    {
      if( strcmp( modify_list[l6].name.in(), (*it)->properties[p].name.in() ) == 0L )
      {
        found = true;
        break;
      }
    }
    if ( !found )
      add[ modify_list[l6].name.in() ] = modify_list[l6];
    else
    {
      // Check wether the property is readonly
      // In this case we may not modify it
      for( CORBA::ULong t = 0; t < ptlen; t++ )
      {
        if( strcmp( modify_list[l6].name.in(), desc->props[t].name.in() ) == 0L )
        {
          if( desc->props[t].mode == ServiceTypeRepository::PROP_MANDATORY_READONLY ||
          desc->props[t].mode == ServiceTypeRepository::PROP_READONLY )
          {
        Register::ReadonlyProperty exc;
        exc.type = CORBA::string_dup( (*it)->vType.in() );
        exc.name = CORBA::string_dup( modify_list[l6].name.in() );
        mico_throw( exc );
          }
        }
      }
      modify[ modify_list[l6].name.in() ] = modify_list[l6];
    }

      }
      
      /**
       * Copy the properties, exclude deleted one and change modified ones.
       */
      PropertySeq props;
      props.length( (*it)->properties.length() - del_list.length() + add.size() );
      CORBA::ULong idx = 0;
      for( CORBA::ULong p = 0; p < plen; p++ )
      {
    list<string>::iterator sit = find( del.begin(), del.end(), string((*it)->properties[p].name.in()) );
    if ( sit != del.end() )
      continue;
    map<string, Property,less<string> >::iterator mit = modify.find( (*it)->properties[p].name.in() );
    if ( mit != modify.end() )
      props[idx++] = (*mit).second;
    else
      props[idx++] = (*it)->properties[p];
      }
      
      // Add new properties
      map<string, Property,less<string> >::iterator mit = add.begin();
      for( ; mit != add.end(); ++mit )
    props[idx++] = (*mit).second;

      (*it)->properties = props;
      
      return;
    }
  }

  UnknownOfferId exc;
  exc.id = CORBA::string_dup( id );
  mico_throw( exc );
}

void Trader::withdraw_using_constraint( const char* type, const char* constr )
{
  // Check wether we know this service type
  if ( !m_pTypeRepository->isServiceTypeKnown( type ) )
  {    
    UnknownServiceType exc;
    exc.type = CORBA::string_dup( type );
    mico_throw( exc );
  }

  /**
   * Constraints
   */
  ParseTreeBase *constraint_tree = 0L;
  if ( strlen( constr ) > 0 )
    constraint_tree = parseConstraints( constr );
  if ( constraint_tree == 0L )
  {
    IllegalConstraint exc;
    exc.constr = CORBA::string_dup( constr );
    mico_throw( exc );
  }

  // Find matching offers
  list<Offer*> del;
  list<Offer*>::iterator it( m_lstOffers.begin() );
  for( ; it != m_lstOffers.end(); ++it )
  {
    if ( strcmp( type, (*it)->vType.in() ) == 0L )
    {    
      if ( constraint_tree == 0L || ( matchConstraint( constraint_tree, &((*it)->properties) ) == 1 ) )
    del.push_back( *it );
    }
  }
  
  delete constraint_tree;

  // Did we match no offers => raise an exception
  if ( del.size() == 0 )
  {
    Register::NoMatchingOffers exc;
    exc.constr = CORBA::string_dup( constr );
    mico_throw( exc );
  }
  
  // Remove matching offers
  it = del.begin();
  for( ; it != del.end(); ++it )
  {
    list<Offer*>::iterator it2 = find( m_lstOffers.begin(), m_lstOffers.end(), *it );
    if ( it2 != m_lstOffers.end() )
    {
      m_lstOffers.erase( it2 );
      delete *it2;
    }
  }
}

/***********************************************************
 *
 * Proxy
 *
 ***********************************************************/

char* Trader::export_proxy(Lookup_ptr target, const char *type,
               const PropertySeq &properties, CORBA::Boolean if_match_all,
               const char *recipe, const PolicySeq &policies_to_pass_on)
{
  cerr << "ADDING proxy of type " << type << endl;
  
  Proxy::ProxyInfo* info = new Proxy::ProxyInfo;
  info->target = Lookup::_duplicate( target );
  info->type = CORBA::string_dup( type );
  info->properties = properties;
  info->if_match_all = if_match_all;
  info->recipe = CORBA::string_dup( recipe );
  info->policies_to_pass_on = policies_to_pass_on;
  
  Offer* o = new Offer;
  o->vProxy = info;
  o->vType = CORBA::string_dup( type );
  o->properties = properties;
  o->isProxy = true;
  
  char buffer[ 100 ];
  sprintf( buffer, "%i", m_uniqueId++ );
  o->vOfferId = CORBA::string_dup( buffer );

  m_lstOffers.push_back( o );
  
  return CORBA::string_dup( buffer );
}

void Trader::withdraw_proxy( const char* id )
{
  list<Offer*>::iterator it( m_lstOffers.begin() );
  for( ; it != m_lstOffers.end(); ++it )
  {
    if ( strcmp( (*it)->vOfferId.in(), id ) == 0 )
    {
      Offer* p = *it;
      if ( !p->isProxy )
      {
    Proxy::NotProxyOfferId exc;
    exc.id = CORBA::string_dup( id );
    mico_throw( exc );
      }
      
      m_lstOffers.erase( it );
      delete p;
      return;
    }
  }

  UnknownOfferId exc;
  exc.id = id;
  mico_throw( exc );
}

Proxy::ProxyInfo* Trader::describe_proxy( const char* id )
{
  list<Offer*>::iterator it( m_lstOffers.begin() );
  for( ; it != m_lstOffers.end(); ++it )
  {
    if ( strcmp( (*it)->vOfferId.in(), id ) == 0 )
    {
      Offer* p = *it;
      if ( !p->isProxy )
      {
    Proxy::NotProxyOfferId exc;
    exc.id = CORBA::string_dup( id );
    mico_throw( exc );
      }
      Proxy::ProxyInfo* info = new Proxy::ProxyInfo;
      (*info) = p->vProxy.in();
      return info;
    }
  }

  UnknownOfferId exc;
  exc.id = id;
  mico_throw( exc );
  return NULL;
  
}

/***********************************************************
 *
 * OfferIterator
 *
 ***********************************************************/

OfferIterator::OfferIterator(OfferSeq* _offers )
{
  m_pOffers = _offers;
  m_pos = 0;
}

OfferIterator::~OfferIterator()
{
  delete m_pOffers;
}

CORBA::ULong OfferIterator::max_left()
{
  return ( m_pOffers->length() - m_pos );
}

CORBA::Boolean OfferIterator::next_n( CORBA::ULong n, OfferSeq*& offers )
{
  CORBA::ULong len = n;
  if ( len > m_pOffers->length() - m_pos )
    len = m_pOffers->length() - m_pos;
  
  offers = new OfferSeq;
  offers->length( len );
  
  for( CORBA::ULong l = 0; l < len; l++ )
    (*offers)[l] = (*m_pOffers)[m_pos++];
  
  if ( m_pos < m_pOffers->length() )
    return true;
  return false;
}

void OfferIterator::destroy()
{
  CORBA::release( this );
}

