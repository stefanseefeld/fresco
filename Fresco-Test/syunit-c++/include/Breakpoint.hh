#ifndef _FRESCO_TEST_BREAKPOINT_H
#define _FRESCO_TEST_BREAKPOINT_H

extern "C"
{
  void Fresco_Test_fail_breakpoint();
  void Fresco_Test_error_breakpoint();
  void Fresco_Test_breakpoint(); // called by the other two
}

#endif         /* header guard */
