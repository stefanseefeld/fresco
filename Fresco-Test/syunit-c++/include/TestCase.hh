#ifndef _SYUNIT_TEST_CASE_H
#define _SYUNIT_TEST_CASE_H

#include <string>

#include "ResultsMap.h"

namespace SyUnit 
{

// A few cheap exception classes
class TestExit {}; 
class TestFailure : public TestExit {};
class TestError : public TestExit {};

class TestCase
{
public:
  TestCase() {}
  virtual ~TestCase() {}

  virtual void
  set_up() {}

  virtual void
  tear_down() {}

  ResultsMap result;

 protected:
  void
  fail(const std::string msg = "fail() called");
  
  void
  error(const std::string msg = "error() called");

  void
  assert_true(bool cond,
              const std::string msg = "assert_true failed");

  void
  assert_false(bool cond,
               const std::string msg = "assert_false failed");

  template <typename S, typename T>
  void
  assert_equals(S s,
                T t,
                const std::string msg = "assert_equals failed")
      { if (! (s == t) ) fail(msg); }

  void
  assert_equals_delta(double x, double y, double epsilon,
                      const std::string msg =
                      "assert_equals_delta failed");

  // Specializations to raise an error if assert_equals is used with
  // floating point numbers. 
  template <typename S>
  void
  assert_equals(S, float, const std::string = "")
      { error("Called assert_equals with a float argument."); }

  template <typename T>
  void
  assert_equals(float, T, const std::string = "")
      { error("Called assert_equals with a float argument."); }


  void
  assert_equals(float, float, const std::string = "");

  template <typename S>
  void
  assert_equals(S, double, const std::string = "")
      { error("Called assert_equals with a double argument."); }

  template <typename T>
  void
  assert_equals(double, T, const std::string = "")
      { error("Called assert_equals with a double argument."); }

  void
  assert_equals(double, double, const std::string = "");

};

class InterfaceTestCase : public TestCase {};
 
}

#endif  /* header guard */
