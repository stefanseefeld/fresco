#include "Breakpoint.hh"

extern "C"
{

  void
  Fresco_Test_fail_breakpoint()
  {
    Fresco_Test_breakpoint();
  }

  void
  Fresco_Test_error_breakpoint()
  {
    Fresco_Test_breakpoint();
  }

  void
  Fresco_Test_breakpoint() {}  
}
