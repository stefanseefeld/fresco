#ifndef _FRESCO_TEST_TEST_CMD_H
#define _FRESCO_TEST_TEST_CMD_H

#include <string>
#include <map>

#include "TestCaseWrapper.h"

namespace Fresco_Test 
{

class TestCmd
{
public:
  TestCmd(char argc, char** argv);
  ~TestCmd();

  // This takes ownership of the passed in TestCaseWrapper
  void
  add(TestCaseWrapper* test);
  
  int
  run();

  void
  usage();
  
private:
  std::map<const std::string, TestCaseWrapper*> my_tests;
  enum { INVALID, LIST, RUN } my_action;
  std::string my_test_name;
  std::string my_exec_name;
};

}

#endif  /* header guard */
