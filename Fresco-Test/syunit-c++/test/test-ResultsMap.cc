#include "TestCase.h"

#include <sstream>

#include "ResultsMap.hh"

namespace Fresco_Test
{
  
/**
 * This is a class-level comment.
 */
class ResultsMapTest : public Fresco_Test::TestCase
{
public:

  /**
   * This is a comment on set_and_get().
   */
  void
  set_and_get()
  {
    ResultsMap rm;
    rm["key1"] = "value1";
    assert_equals(rm["key1"], "value1", "Set/get don't work.");
  }

  /**
   * This is a comment on appending().
   *
   * @depends test_map_properties
   */
  void
  appending()
  {
    ResultsMap rm;
    rm["key1"] = "value1";
    rm["key1"] += "value2";
    assert_equals(rm["key1"], "value1value2", "Appending doesn't work");
  }

  /**
   * This is a comment on basic_printing().
   * @depends set_and_get
   */
  void
  basic_printing()
  {
    ResultsMap rm;
    rm["key1"] = "value1";
    rm["key2"] = "value2";
    std::stringstream s;
    s << rm;
    assert_equals(s.str(),
                  "key1: value1\n"
                  "key2: value2\n",
                  "Basic printing doesn't work.");
  }

  /**
   * This is a comment on final_newline_handling().
   *
   * @depends basic_printing
   */
  void
  final_newline_handling()
  {
    ResultsMap rm;
    rm["key1"] = "foo\n";
    rm["key2"] = "bar";
    rm["key3"] = "baz\n";
    std::stringstream s;
    s << rm;
    assert_equals(s.str(),
                  "key1: foo\n"
                  "key2: bar\n"
                  "key3: baz\n",
                  "End of value newline handling doesn't work.");
  }

  /**
   * This is a comment on multiline_indenting().
   *
   * @depends basic_printing
   * @depends final_newline_handling
   */
  void
  multiline_indenting()
  {
    ResultsMap rm;
    rm["key"] = "value\nmore value";
    rm["key2"] = "blah";
    std::stringstream actual, target;
    actual << rm;
    target << "key: value\n"
           << ResultsMap::continuation_indent << "more value\n"
           << "key2: blah\n";
    assert_equals(actual.str(), target.str(),
                  "Basic 2 line values don't work.");
  }

  void
  blank_line_quoting()
  {
    ResultsMap rm;
    rm["key"] = "value\nmore value\n\nanother line.";
    rm["key2"] = "blah";
    std::stringstream actual, target;
    actual << rm;
    target << "key: value\n"
           << ResultsMap::continuation_indent << "more value\n"
           << ResultsMap::continuation_indent
           << ResultsMap::blank_line_quote << "\n"
           << ResultsMap::continuation_indent << "another line.\n"
           << "key2: blah\n";
    assert_equals(actual.str(), target.str(),
                  "Blank line quoting doesn't work.");
  }

  /**
   * This is a comment on operator_equals().
   *
   * @depends set_and_get
   */
  void
  operator_equals()
  {
    ResultsMap rm1, rm2;
    rm1["key"] = "value";
    rm2["key"] = "value";
    assert_true(rm1 == rm2, "== gives false negatives");
    assert_false(rm1 != rm2, "!= gives false positives");
    rm2["key2"] = "value2";
    assert_false(rm1 == rm2, "== gives false positives");
    assert_true(rm1 != rm2, "!= gives false negatives");
  }

  /**
   * This is a comment on operator_equals_order().
   *
   * @depends operator_equals
   */
  void
  operator_equals_order()
  {
    ResultsMap rm1, rm2;
    rm1["key1"] = "value1";
    rm1["key2"] = "value2";
    rm2["key2"] = "value2";
    rm2["key1"] = "value1";
    assert_equals(rm1, rm2, "== is dependent on ordering.");
  }
  
  /**
   * This is a comment on ordering().
   *
   * @depends basic_printing
   * @depends operator_equals_order
   */
  void
  ordering()
  {
    ResultsMap rm1, rm2;
    rm1["key1"] = "value1";
    rm1["key2"] = "value2";
    rm2["key2"] = "value2";
    rm2["key1"] = "value1";
    std::stringstream s1, s2;
    s1 << rm1;
    s2 << rm2;
    assert_true(s1.str() != s2.str(),
                "Printing doesn't respect order of key creation.");
  }
  
  /**
   * This is a comment on copy_constructor().
   *
   * @depends operator_equals
   */
  void
  copy_constructor()
  {
    ResultsMap rm1;
    rm1["key"] = "value";
    ResultsMap rm2 = rm1;
    assert_equals(rm1, rm2,
                  "Copy constructor creates non-equal objects.");
  }

  /**
   * This is a comment on assignment_test().
   *
   * @depends operator_equals
   */
  void
  assignment_test()
  {
    ResultsMap rm1, rm2;
    rm1["key"] = "value";
    rm2["other-key"] = "other-value";
    rm2 = rm1;
    assert_equals(rm2, rm1,
                  "Assignment leaves non-equal objects");
  }

  /**
   * This is a comment on test_clear().
   *
   * @depends operator_equals
   */
  void
  test_clear()
  {
    ResultsMap rm1, rm2;
    rm1["key"] = "value";
    assert_true(rm1 != rm2, "Can't happen!");
    rm1.clear();
    assert_true(rm1 == rm2, "clear() didn't clear the object");
  }
};
 
}

// tag: njs@fresco.org 8c25f7e76cfac0c6dec27fbbb49e6eac
