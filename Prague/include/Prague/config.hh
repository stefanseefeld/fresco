#ifndef _Prague_config_hh
#define _Prague_config_hh

#include <Prague/acconfig.hh>

#define PRAGUE_VERSION PACKAGE_VERSION

//silly autoconf defines them...*sigh*
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#ifndef HAVE_STRSIGNAL
#include <signal.h>
#  if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
inline const char *strsignal(int signo) { return sys_siglist[signo];}
#  else
inline const char *strsignal(int signo) { return _sys_siglist[signo];}
#  endif
#elif NEED_DECLARATION_strsignal
extern "C" const char *strsignal(int);
#endif

#ifndef HAVE_SOCKLEN_T
typedef int socklen_t;
#endif

#endif

