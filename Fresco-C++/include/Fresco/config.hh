#ifndef _config_hh
#define _config_hh

#define __x86__
//#define __linux__
#define __OSVERSION__ 2
#define __OMNIORB2__
#define _MIT_POSIX_THREADS
#define _REENTRANT

#define implements(interface) virtual public _lc_sk_##interface
#define implementsscoped(scope, interface) virtual public scope##::_lc_sk_##interface

#endif /* _config_hh */
