#include "LinkImpl.hh"
#include "Trader.hh"

using namespace CosTrading;

// LinkImpl::LinkImpl(Trader *t) : ::TraderComponents(t), ::SupportAttributes(t), ::LinkAttributes(t), MICO_SCOPE(CosTrading,Link_skel)()
// {
// }

void LinkImpl::add_link(const char *name, Lookup_ptr target, FollowOption def_pass_on_follow_rule, FollowOption limiting_follow_rule)
{
  if (links.find(name) != links.end())
    {
      Link::DuplicateLinkName exc;
      exc.name = CORBA::string_dup(name);
      throw exc;
    }
  if (CORBA::is_nil(target))
    {
      InvalidLookupRef exc;
      exc.target = Lookup::_duplicate(target);
      throw exc;
    }
  Register_var reg = target->register_if();
  if (CORBA::is_nil(reg))
    {
      InvalidLookupRef exc;
      exc.target = CosTrading::Lookup::_duplicate(target);
      throw exc;
    }
  if (def_pass_on_follow_rule > limiting_follow_rule)
    {
      Link::DefaultFollowTooPermissive exc;
      exc.def_pass_on_follow_rule = def_pass_on_follow_rule;
      exc.limiting_follow_rule = limiting_follow_rule;
      throw exc;
    }
  if (limiting_follow_rule > trader->maxLinkFollowPolicy())
    {
      Link::LimitingFollowTooPermissive exc;
      exc.limiting_follow_rule = limiting_follow_rule;
      exc.max_link_follow_policy = trader->maxLinkFollowPolicy();
      throw exc;
    }
  Link::LinkInfo info;
  info.target = Lookup::_duplicate(target);
  info.target_reg = reg;
  info.def_pass_on_follow_rule = def_pass_on_follow_rule;
  info.limiting_follow_rule = limiting_follow_rule;
  links[name] = info;
}

void LinkImpl::remove_link(const char *name)
{
  llist_t::iterator i = links.find(name);
  if (i == links.end())
    {
      Link::UnknownLinkName exc;
      exc.name = CORBA::string_dup(name);
      throw exc;
    }
  links.erase(i);
}

Link::LinkInfo *LinkImpl::describe_link(const char *name)
{
  llist_t::iterator i = links.find(name);

  if (i == links.end())
    {
      Link::UnknownLinkName exc;
      exc.name = CORBA::string_dup(name);
      throw exc;
    }
  Link::LinkInfo *info = new Link::LinkInfo;
  (*info) = (*i).second;
  return info;
}

LinkNameSeq *LinkImpl::list_links()
{
  LinkNameSeq *seq = new LinkNameSeq;
  seq->length(lins.size());
  
  llist_t::iterator i = links.begin();
  
  for (LinkName *j = seq->begin_buffer(); j != seq->begin_buffer() + seq->length(); i++, j++)
    (*j) = CORBA::string_dup((*i).first.c_str());
  return seq;
}

void LinkImpl::modify_link(const char *name, FollowOption def_pass_on_follow_rule, FollowOption limiting_follow_rule)
{
  if (links.find(name) == links.end())
  {
    Link::UnknownLinkName exc;
    exc.name = CORBA::string_dup(name);
    throw exc;
  }
  if (def_pass_on_follow_rule > limiting_follow_rule)
  {
    Link::DefaultFollowTooPermissive exc;
    exc.def_pass_on_follow_rule = def_pass_on_follow_rule;
    exc.limiting_follow_rule = limiting_follow_rule;
    throw exc;
  }
  if (limiting_follow_rule > trader->maxLinkFollowPolicy())
  {
    Link::LimitingFollowTooPermissive exc;
    exc.limiting_follow_rule = limiting_follow_rule;
    exc.max_link_follow_policy = trader->maxLinkFollowPolicy();
    throw exc;
  }
  links[name].def_pass_on_follow_rule = def_pass_on_follow_rule;
  links[name].limiting_follow_rule = limiting_follow_rule;
}
