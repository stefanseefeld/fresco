#ifndef _SYUNIT_TEST_CASE_WRAPPER_H
#define _SYUNIT_TEST_CASE_WRAPPER_H

#include <string>

#include "ResultsMap.h"
#include "TestCase.h"
#include "Breakpoint.h"

namespace SyUnit
{

class ResultsMap;

// Pure virtual interface class, so the templatized version can
// inherit from it.
class TestCaseWrapper
{
public:
  virtual ResultsMap run() = 0;
  virtual const std::string name() const = 0;
  virtual const std::string description() const = 0;
}; 

template <typename TC>
class TestCaseWrapperImpl
  : public Fresco_Test::TestCaseWrapper
{
public:
  typedef void (TC::* method_type)();

  TestCaseWrapperImpl(const char* name,
                      method_type method,
                      const char* description = 0
                      ) :
    my_name(name),
    my_description(description),
    my_method(method)
  {}
    
  virtual ResultsMap
  run();

  virtual const std::string
  name() const { return my_name; }

  virtual const std::string
  description() const { return my_description; }
  
private:
  std::string my_name;
  std::string my_description;
  method_type my_method;
};

class TestExit;

template <typename TC> ResultsMap
TestCaseWrapperImpl<TC>::run()
{
  TC test;
    
  test.result["Test"] = my_name;
  if (my_description != "")  test.result["Description"] = my_description;
  test.result["Result"] = "PASS";

  try
  {
    test.set_up();
  }
  catch (std::exception& e)
  {
    SyUnit_error_breakpoint();
    test.result["Result"] = "ERROR";
    test.result["Cause"]  = "set_up() threw a std::exception: ";
    test.result["Exception"] = e.what();
    return test.result;
  }
  catch (...)
  {
    SyUnit_error_breakpoint();
    test.result["Result"] = "ERROR";
    test.result["Cause"] = "set_up() threw an unknown exception";
    return test.result;
  }

  try
  {
    (test.*my_method)();
  }
  catch (TestExit& e) {} // maybe should do some verifying that fields
  // match exception thrown...
  catch (std::exception& e)
  {
    SyUnit_error_breakpoint();
    test.result["Result"] = "ERROR";
    test.result["Cause"]  = "test method threw a std::exception";
    test.result["Exception"] += e.what();
  }
  catch (...)
  {
    SyUnit_error_breakpoint();
    test.result["Result"] = "ERROR";
    test.result["Cause"] = "test method threw an unknown exception";
  }
  // Always call tear_down()

  try
  {
    test.tear_down();
  }
  catch (std::exception& e)
  {
    SyUnit_error_breakpoint();
    std::string msg = "tear_down() threw a std::exception: ";
    msg += e.what();
    if (test.result["Result"] == "ERROR")
    {
      test.result["Details"] += msg;
      test.result["Details"] += "\n";
    }
    else
    {
      test.result["Result"] = "ERROR";
      test.result["Cause"] = msg;
    }
  }
  catch (...)
  {
    SyUnit_error_breakpoint();
    std::string msg = "tear_down() threw an unknown exception";
    if (test.result["Result"] == "ERROR")
    {
      test.result["Details"] += msg;
      test.result["Details"] += "\n";
    }
    else
    {
      test.result["Result"] = "ERROR";
      test.result["Cause"] = msg;
    }
  }  
  return test.result;
}

}

#endif  /* header guard */
