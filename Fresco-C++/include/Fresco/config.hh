#ifndef _config_hh
#define _config_hh

#define __x86__
//#define __linux__
#define __OSVERSION__ 2
#define __OMNIORB2__
#define _MIT_POSIX_THREADS
#define _REENTRANT
 
// this cruft is intended to help handle differences in ORBs. it's sad, really.

#define applyscope(scope, thing) scope##::##thing
#define skeletonize(interfacename) _lc_sk_##interfacename
#define implements(interface) virtual public skeletonize(interface)
#define implementsscoped(scope, interface) virtual public applyscope(scope, skeletonize(interface))

#endif /* _config_hh */
