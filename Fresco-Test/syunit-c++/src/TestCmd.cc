#include "ResultsMap.hh"
#include "TestCmd.hh"
#include "TestCase.hh"
#include <iostream>
#include <cstdlib>
#include <cstring>

namespace SyUnit
{
  
  TestCmd::TestCmd(char argc, char** argv)
      : my_exec_name(argv[0]),
        my_action(INVALID),
        my_test_name(),
        my_tests()
  {
      if (argc == 1)
      {
          usage();
          exit(1);
      }
      if (!strcmp(argv[1], "run"))
      {
          my_action = RUN;
          if (argc == 2) my_test_name = "all";
          else if (argc == 3) my_test_name = argv[2];
          else
          {
              std::cerr << "Too many arguments to \"run\".\n";
              usage();
              exit(1);
          }
      }
      else if (!strcmp(argv[1], "list"))
      {
          my_action = LIST;
          if (argc > 2)
          {
              std::cerr << "Too many arguments to \"list\".\n";
              usage();
              exit(1);
          }
      }
      else
      {
          std::cerr << "Unknown command \"" << argv[1] << "\"\n";
          usage();
          exit(1);
      }
  }
  
  TestCmd::~TestCmd()
  {
      std::map<const std::string, TestCaseWrapper*>::iterator i;
      for (i = my_tests.begin(); i != my_tests.end(); i++)
      {
          delete(i->second);
      }
  }
  
  // This takes ownership of the passed in TestCaseWrapper
  void
  TestCmd::add(TestCaseWrapper* test)
  {
      if (!my_tests.count(test->name()))
      {
          my_tests[test->name()] = test;
      }
      else
      {
          std::cerr << "Multiple tests registered under name "
                    << test->name() << std::endl;
          exit(1);
      }
  }
  
  int
  TestCmd::run()
  {
      std::map<const std::string, TestCaseWrapper*>::iterator i;
      if (my_action == LIST)
      {
          for (i = my_tests.begin(); i != my_tests.end(); i++)
          {
              std::cout << i->first << std::endl;
          }
      }
      else if (my_action == RUN)
      {
          if (my_test_name == "all")
          {
              bool first_time = true;
              for (i = my_tests.begin(); i != my_tests.end(); i++)
              {
                  if (first_time)  first_time = false;
                  else std::cout << "\n";
                  std::cout << i->second->run();
              }
          }
          else
          {
              if (my_tests.find(my_test_name) != my_tests.end())
              {
                  std::cout << my_tests[my_test_name]->run();
              }
              else
              {
                  std::cerr << "No such test '" << my_test_name
                            << "'" << std::endl;
                  std::exit(2);
              }
          }
          
      }
      else
      {
          std::cerr << "Can't happen: invalid action in run()\n";
          exit(1);
      }
      return 0;
  }
  
  void
  TestCmd::usage()
  {
      std::cerr << "Usage:" << std::endl
                << "   " << my_exec_name << " list" << std::endl
                << "   " << my_exec_name << " run <test name>" << std::endl
                << "   " << my_exec_name << " run [all]" << std::endl;
  }
  
}
