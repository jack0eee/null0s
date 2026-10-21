/*
.---------------------------------------------------------.
|                                                         |
|                                                         |
|                                                         |
|                                                         |
|                           LIBK                          |
|                                                         |
|                                                         |
|                                                         |
'---------------------------------------------------------' */

#include "libk.h"

/* =============== CATEGORIA-1  ================= */

/*
.--------------------------------------------------.
| console_write |                                  |
|                                                  |
|                                                  |
'--------------------------------------------------' */
size_t console_write(const char *buf, size_t len)
{
        for (size_t i = 0; i < len; i++)
                vga_putchar(buf[i]);

        return len;
}

/*
.--------------------------------------------------.
| sys_write |                                      |
|                                                  |
|                                                  |
'--------------------------------------------------' */
size_t sys_write (int fd, const void *buf, size_t len)
{
	if (fd == 1) // STDOUT_FILENO)
		return console_write(buf, len);

	return -1 ;
}

/*
.--------------------------------------------------.
| syscall_dispatch |                               |
|                                                  |
|                                                  |
'--------------------------------------------------' */
long syscall_dispatch(long num, long a1, long a2, long a3)
{
        switch(num) {

                case SYS_WRITE:

                        return 0; // sys_write((int)a1, (count char *)a2, (size_t)a3);

                default:

                        return -1;
        }
}

/* :::... EOF */


