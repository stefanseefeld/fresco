#include "ResultsMap.hh"

namespace SyUnit
{
  
  const std::string ResultsMap::continuation_indent("   ");
  const std::string ResultsMap::blank_line_quote(".");
  
  void
  ResultsMap::clear()
  {
      my_keys.clear();
      my_map.clear();
  }
  
  std::string&
  ResultsMap::operator [] (const std::string& key)
  {
      // Is this really the best way to check whether a map already
      // contains an entry for a given key?
      if (!my_map.count(key))
      {
          my_keys.push_back(std::string(key));
      }
      return my_map[key];
  }
  
  bool
  ResultsMap::operator == (const ResultsMap& other) const
  {
      return my_map == other.my_map;
  }
  
  ResultsMap &
  ResultsMap::operator = (const ResultsMap& other)
  {
      my_keys = other.my_keys;
      my_map = other.my_map;
  }
  
  // This might be a bit inefficient, since we print one character at a
  // time, but the effect is probably negligible (and the code is
  // cleaner and probably faster than my first try that didn't do
  // that...)
  std::ostream&
  operator << (std::ostream& os, ResultsMap rm)
  {
      std::list<std::string>::const_iterator i;
      for (i = rm.my_keys.begin(); i != rm.my_keys.end(); i++)
      {
          // "<key>: "
          os << *i << ": ";
          
          // "<desc>"
          std::string& desc = rm[*i];
          
          bool seen_chars_this_line = true;
          std::string::iterator j = desc.begin();
          while (j != desc.end())
          {
              if (*j == '\n')
              {
                  if (!seen_chars_this_line) os << rm.blank_line_quote;
                  seen_chars_this_line = false;
                  os << *j;
                  j++;
                  if (j != desc.end()) os << rm.continuation_indent;
              }
              else
              {
                  seen_chars_this_line = true;
                  os << *j;
                  j++;
              }
          }
          // Add a final \n if necessary
          if (seen_chars_this_line) os << '\n';
      }
      
      return os;
  } 

}
