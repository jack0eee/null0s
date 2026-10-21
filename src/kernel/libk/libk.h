
/* libk.h di lib kernel */

#ifndef LIBK_H
#define LIBK_H

#include "stddef.h" //????????????????? replicato da libc
#include "stdint.h" //????????????????? replicato da libc

#include "libvga.h"

enum {
        SYS_WRITE=0,
        SYS_READ,
        SYS_EXIT,
};

size_t sys_write        ( int fd, const void *buf, size_t len );
size_t console_write    ( const char *buf, size_t len );
long   syscall_dispatch ( long num, long a1, long a2, long a3 );

#endif

/* EOF */

