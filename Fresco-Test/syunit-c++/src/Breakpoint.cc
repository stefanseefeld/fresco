#include "Breakpoint.hh"

extern "C"
{

  void
  SyUnit_fail_breakpoint()
  {
    SyUnit_problem_breakpoint();
  }

  void
  SyUnit_error_breakpoint()
  {
    SyUnit_problem_breakpoint();
  }

  void
  SyUnit_problem_breakpoint() {}  
}
