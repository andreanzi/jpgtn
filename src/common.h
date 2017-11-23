#ifndef JPGTN_COMMON_H
#define JPGTN_COMMON_H 1

#if HAVE_CONFIG_H
#    include "config.h"
#endif

#include <stdio.h> 

#if HAVE_SYS_TYPES_H
#    include <sys/types.h>
#endif

#if HAVE_SYS_STAT_H
#    include <sys/stat.h>
#endif

#if STDC_HEADERS
#    include <stdlib.h>
#    include <string.h>
#    include <setjmp.h>
#elif HAVE_STRINGS_H
#    include <strings.h>
#endif

#if HAVE_UNISTD_H
#    include <unistd.h>
#endif

#if HAVE_LIBJPEG
#include <jpeglib.h>
#endif

#if HAVE_ERRNO_H
#    include <errno.h>
#endif
#ifndef errno
extern int errno; 
#endif

#if !HAVE_STRRCHR && HAVE_RINDEX
#    define strrchr rindex
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#endif /* !JPGTN_COMMON_H */
