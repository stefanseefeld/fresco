/* Prague/Sys/includes.hh
 * 
 * This file translates #defined symbols into #include statements, based
 * (eventually) on configure tests.  An example will explain best:
 *     FreeBSD has the prototype for strerror() in string.h, while Linux
 *     puts it in unistd.h.  So, any source file that uses strerror()
 *     will #define PRAGUE_INCL_FOR_STRERROR.  On FreeBSD, this will be
 *     converted into #include <string.h>; on Linux, into <unistd.h>.
 *
 * This is a complicated scheme, and I'm not sure it's the best thing to
 * do.  But, I couldn't really evaluate how complicated it was until I
 * had actually tried it out.  So, here I am trying it out! -Thim
 */


/* these defines need to be made into configure tests, and put into
 * config.h (or something like that) */

#ifdef __FreeBSD__
        #define PRAGUE_INCL_STRERROR_STRING_H           /* strerror() */
        #define PRAGUE_INCL_WAITPID_SYS_TYPES_H         /* waitpid() */
        #define PRAGUE_INCL_WAITPID_SYS_WAIT_H
        #define PRAGUE_INCL_WAITPID_SYS_TIME_H
        #define PRAGUE_INCL_WAITPID_SYS_RESOURCE_H

#else
        #define PRAGUE_INCL_WAITPID_WAIT_H              /* waitpid() */
#endif /* __FreeBSD */


#ifdef PRAGUE_INCL_FOR_STRERROR
#if defined(PRAGUE_INCL_STRERROR_STRING_H) && !defined(PRAGUE_INCL_STRING_H)
#include <string.h>
#define PRAGUE_INCL_STRING_H
#endif
#endif /* PRAGUE_INCL_FOR_STRERROR */


#ifdef PRAGUE_INCL_FOR_WAITPID

#if defined(PRAGUE_INCL_WAITPID_SYS_TYPES_H) && !defined(PRAGUE_INCL_SYS_TYPES_H)
#include <sys/types.h>
#define PRAGUE_INCL_SYS_TYPES_H
#endif

#if defined(PRAGUE_INCL_WAITPID_SYS_WAIT_H) && !defined(PRAGUE_INCL_SYS_WAIT_H)
#include <sys/wait.h>
#define PRAGUE_INCL_SYS_WAIT_H
#endif

#if defined(PRAGUE_INCL_WAITPID_SYS_TIME_H) && !defined(PRAGUE_INCL_SYS_TIME_H)
#include <sys/time.h>
#define PRAGUE_INCL_SYS_TIME_H
#endif

#if defined(PRAGUE_INCL_WAITPID_SYS_RESOURCE_H) && !defined(PRAGUE_INCL_SYS_RESOURCE_H)
#include <sys/resource.h>
#define PRAGUE_INCL_SYS_RESOURCE_H
#endif

#if defined(PRAGUE_INCL_WAITPID_WAIT_H) && !defined(PRAGUE_INCL_WAIT_H)
#include <wait.h>
#define PRAGUE_INCL_WAIT_H
#endif

#endif /* PRAGUE_INCL_FOR_WAITPID */
