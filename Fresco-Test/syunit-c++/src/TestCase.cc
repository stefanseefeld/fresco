#include <sstream>

#include "TestCase.hh"
#include "Breakpoint.hh"
#include "ResultsMap.hh"

namespace SyUnit
{

void
TestCase::fail(const std::string msg)
{
  SyUnit_fail_breakpoint();
  result["Result"] = "FAIL";
  result["Cause"] = msg;
  throw TestFailure();
}

void
TestCase::error(const std::string msg)
{
  SyUnit_error_breakpoint();
  result["Result"] = "ERROR";
  result["Cause"] = msg;
  throw TestError();
}

void
TestCase::assert_true(bool cond,
                      const std::string msg)
{
  if (!cond) fail(msg);
}

void
TestCase::assert_false(bool cond,
                       const std::string msg)
{
  if (cond) fail(msg);
}

void
TestCase::assert_equals_delta(double x, double y, double epsilon,
                              const std::string msg)
{
  if (! (-epsilon < x-y && epsilon > x-y) )
  {
    if (msg != "") fail(msg);
    else
    {
      std::stringstream my_msg;
      my_msg << "assert_equals_delta failed: "
             << x << " - " << y << " = " << x - y
             << "; epsilon was " << epsilon << ".";
      fail(my_msg.str());
    }
  }
}

void
TestCase::assert_equals(float, float, const std::string)
{
  error("Called assert_equals with two float arguments.");
}

void
TestCase::assert_equals(double, double, const std::string)
{
  error("Called assert_equals with two double arguments.");
}

}
