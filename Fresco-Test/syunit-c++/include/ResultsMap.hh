#ifndef _SYUNIT_RESULTSMAP_H
#define _SYUNIT_TEST_RESULTSMAP_H

#include <string>
#include <list>
#include <map>
#include <iostream>

namespace SyUnit
{

class ResultsMapTest;

// This class is YAGNI compliant.
// It maybe be a little short on the error checking, though; it won't
// notice if you try and assign twice to the same key, for example.
// (This is because the only accessor is [], and we want to allow
// rewriting via [] to allow things like appending to a partial
// message.)  Of course, the expected semantics for blah[i] = "foo" is
// to overwrite blah[i], not add a new additional i field, anyway.
// Worse, it won't do any validation of the key fields, for improper
// characters like "@" or ":".
class ResultsMap {
public:
  ResultsMap() :
    my_keys(),
    my_map()
    {};

  ResultsMap(const ResultsMap& other) :
    my_keys(other.my_keys),
    my_map(other.my_map)
  {}

  void
  clear();

  bool
  operator == (const ResultsMap& other) const;

  bool
  operator != (const ResultsMap& other) const
      { return ! (*this == other); }
  
  ResultsMap &
  operator = (const ResultsMap& other);

  std::string &
  operator [] (const std::string & key);

  // We don't use a ResultsMap& because if we use a reference, we have
  // to make it const (or we won't be able to print nonce objects).
  // But we can't make it const, because operator[] is non-const, and
  // we can't print without using operator[]...
  friend std::ostream &
  operator << (std::ostream &, ResultsMap);

private:
  //. A list to let us print in the same order things were added.
  std::list<std::string> my_keys;
  std::map<std::string, std::string> my_map;

  static const std::string continuation_indent;
  static const std::string blank_line_quote;

  friend class ResultsMapTest;
};
 
}


#endif  /* header guard */
