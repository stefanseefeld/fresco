#ifndef _SYUNIT_BREAKPOINT_H
#define _SYUNIT_BREAKPOINT_H

extern "C"
{
  void SyUnit_fail_breakpoint();
  void SyUnit_error_breakpoint();
  void SyUnit_problem_breakpoint(); // called by the other two
}

#endif         /* header guard */
