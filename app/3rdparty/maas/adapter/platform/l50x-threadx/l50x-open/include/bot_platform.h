/*
 * Copyright (C) 2020-2021 Alibaba Group Holding Limited
 */
#ifndef __BOT_PLATFORM_H
#define __BOT_PLATFORM_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// yike
#include "mbtk_api.h"
#include "mbtk_comm_api.h"
#include "mbtk_customer_api.h"
#include "mbtk_open_at.h"
#include "mbtk_pub_def.h"
#include "mbtk_pub_type.h"
#include "bot_system_utils.h"

// os
#include "mbtk_os.h"
#include "ol_os_comm_event.h"
// nw
#include "mbtk_datacall_api.h"
#include "ol_nw_api.h"
#include "ol_nw_pub.h"

// drv
#include "mbtk_adc.h"
#include "mbtk_cam.h"
#include "mbtk_gpio.h"
#include "mbtk_i2c.h"
#include "mbtk_keypad.h"
#include "mbtk_lcd.h"
#include "mbtk_pwm.h"
#include "mbtk_spi.h"
#include "mbtk_uart.h"
#include "ol_audio.h"

// device
#include "mbtk_device_api.h"
#include "mbtk_gps.h"
#include "mbtk_pmu.h"
#include "mbtk_sim_api.h"
#include "ol_app_update.h"
#include "ol_fota.h"

// fs
#include "ol_flash_fs.h"
#include "ol_sdcard_fs.h"

// Network
#include "http_api.h"
#include "mbtk_socket_api.h"
#include "mbtk_ssl_hal.h"
#include "ol_mqttclient.h"

/* configuration about FS */
#define BOT_FS_STREAM_ENABLED       0       // support fs stream operation, like linux, windows.etc

typedef void  bot_statfs_t;     // TODO 
/***********************************************************************************************************************
 * Macro Definition
***********************************************************************************************************************/
#define BOT_FS_USER_DIR "/bot"

/* micro defination about file system, used for bot_open()'s flag */
#define BOT_O_RDONLY        00              /* 以只读方式打�?文件 */
#define BOT_O_WRONLY  	    01              /* 以只写方式打�?文件 */
#define BOT_O_RDWR    		02              /* 以可读写方式打开文件. 上述三种旗标是互斥的, 也就是不可同时使�?, 但可与下列的旗标利用OR(|)运算符组�?. */
#define BOT_O_APPEND  		02000           /* 当读写文件时会从文件尾开始移�?, 也就是所写入的数据会以附加的方式加入到文件后�?. */
#define BOT_O_CREAT   		0100            /* 若欲打开的文件不存在则自动建立该文件. */
#define BOT_O_TRUNC   		01000           /* 若文件存在并且以可写的方式打�?�?, 此旗标会令文件长度清�?0, 而原来存于该文件的资料也会消�?. */
#define BOT_O_EXCL    		0200            /* 如果O_CREAT 也被设置, 此指令会去检查文件是否存�?. 文件若不存在则建立该文件, 否则将导致打�?文件错误. 此外, 若O_CREAT 与O_EXCL 同时设置, 并且欲打�?的文件为符号连接, 则会打开文件失败. */
#define BOT_O_SYNC    		04010000        /* 以同步的方式打开文件. */
#define BOT_O_NOCTTY        0400            /* 如果欲打�?的文件为终端机设备时, 则不会将该终端机当成进程控制终端�?. */
#define BOT_O_NONBLOCK      04000           /* 以不可阻断的方式打开文件, 也就是无论有无数据读取或等待, 都会立即返回进程之中. */
#define BOT_O_NDELAY        04000           /* �? O_NONBLOCK. */
// #define BOT_O_NOFOLLOW      O_NOFOLLOW      /* 如果参数 path �?指的文件为一符号连接, 则会令打�?文件失败. */
// #define BOT_O_DIRECTORY     O_DIRECTORY     /* 如果参数 path �?指的文件并非为一目录, 则会令打�?文件失败。注：此为Linux2. 2 以后特有的旗�?, 以避免一些系统安全问�?. */
/* micro defination about file system, used for bot_fseek()'s/bot_seek()'s whence */
#define BOT_SEEK_SET        OL_FS_SEEK_SET
#define BOT_SEEK_CUR        OL_FS_SEEK_CUR
#define BOT_SEEK_END        OL_FS_SEEK_END


/* 参数mode 则有下列数种组合, 只有在建立新文件时才会生�?, 此外真正建文件时的权限会受到umask 值所影响, 因此该文件权限应该为 (mode-umaks). */
#define BOT_S_IRWXU         00700         /* 00700 权限, 代表该文件所有�?�具有可读�?�可写及可执行的权限. */
#define BOT_S_IRUSR         00400         /* �? S_IREAD, 00400 权限, 代表该文件所有�?�具有可读取的权�?. */
#define BOT_S_IWUSR         00200         /* �? S_IWRITE, 00200 权限, 代表该文件所有�?�具有可写入的权�?. */
#define BOT_S_IXUSR         00100         /* �? S_IEXEC, 00100 权限, 代表该文件所有�?�具有可执行的权�?. */
#define BOT_S_IRWXG         00070         /* 00070 权限, 代表该文件用户组具有可读、可写及可执行的权限. */
#define BOT_S_IRGRP         00040         /* 00040 权限, 代表该文件用户组具有可读的权�?. */
#define BOT_S_IWGRP         00020         /* 00020 权限, 代表该文件用户组具有可写入的权限. */
#define BOT_S_IXGRP         00010         /* 00010 权限, 代表该文件用户组具有可执行的权限. */
#define BOT_S_IRWXO         00007         /* 00007 权限, 代表其他用户具有可读、可写及可执行的权限. */
#define BOT_S_IROTH         00004         /* 00004 权限, 代表其他用户具有可读的权�? */
#define BOT_S_IWOTH         00002         /* 00002 权限, 代表其他用户具有可写入的权限. */
#define BOT_S_IXOTH         00001         /* 00001 权限, 代表其他用户具有可执行的权限. */


/* bot_exitdir() mode */
#define BOT_ACESS_R_OK      4               /* read OK */
#define BOT_ACESS_W_OK      2               /* write OK */
#define BOT_ACESS_X_OK      1               /* execute OK */
#define BOT_ACESS_F_OK      0               /* file exit: OK */

/* 返回值：若所有欲核查的权限都通过了检查则返回0 �?, 表示成功, 只要有一个权限被禁止则返�?-1. */
/* bot error code defination */

#define	BOT_E_EPERM         1	            /* 1, Operation not permitted */
#define	BOT_E_ENOENT        2		        /* 2, No such file or directory */
#define	BOT_E_ESRCH         3		        /* 3, No such process */
#define	BOT_E_EINTR         4		        /* 4, Interrupted system call */
#define	BOT_E_EIO           5		        /* 5, I/O error */
#define	BOT_E_ENXIO         6		        /* 6, No such device or address */
#define	BOT_E_E2BIG         7		        /* 7, Argument list too long */
#define	BOT_E_ENOEXEC       8	            /* 8, Exec format error */
#define	BOT_E_EBADF         9		        /* 9, Bad file number */
#define	BOT_E_ECHILD        10		        /* 10 No child processes */
#define	BOT_E_EAGAIN        11		        /* 11, Try again */
#define	BOT_E_ENOMEM        12 		        /* 12, Out of memory */
#define	BOT_E_EACCES        13		        /* 13, Permission denied */
#define	BOT_E_EFAULT        14		        /* 14, Bad address */
#define	BOT_E_ENOTBLK       15	            /* 15, Block device required */
#define	BOT_E_EBUSY         16		        /* 16, Device or resource busy */
#define	BOT_E_EEXIST        17		        /* 17, File exists */
#define	BOT_E_EXDEV         18		        /* 18, Cross-device link */
#define	BOT_E_ENODEV        19		        /* 19, No such device */
#define	BOT_E_ENOTDIR       20		        /* 20, Not a directory */
#define	BOT_E_EISDIR        21		        /* 21, Is a directory */
#define	BOT_E_EINVAL        22		        /* 22, Invalid argument */
#define	BOT_E_ENFILE        23		        /* 23, File table overflow */
#define	BOT_E_EMFILE        24		        /* 24, Too many open files */
#define	BOT_E_ENOTTY        25		        /* 25, Not a typewriter */
#define	BOT_E_ETXTBSY       26	            /* 26, Text file busy */
#define	BOT_E_EFBIG         27		        /* 27, File too large */
#define	BOT_E_ENOSPC        28		        /* 28, No space left on device */
#define	BOT_E_ESPIPE        29		        /* 29, Illegal seek */
#define	BOT_E_EROFS         30		        /* 30, Read-only file system */
#define	BOT_E_EMLINK        31		        /* 31, Too many links */
#define	BOT_E_EPIPE         32		        /* 32, Broken pipe */
#define	BOT_E_EDOM          33		        /* 33, Math argument out of domain of func */
#define	BOT_E_ERANGE        34		        /* 34, Math result not representable */


#define	BOT_E_EDEADLK	    35		        /* 35, Resource deadlock would occur */
#define	BOT_E_ENAMETOOLONG	36	            /* 36, File name too long */
#define	BOT_E_ENOLCK	    37		        /* 37, No record locks available */

/*
 * This error code is special: arch syscall entry code will return
 * -ENOSYS if users try to call a syscall that doesn't exist.  To keep
 * failures of syscalls that really do exist distinguishable from
 * failures due to attempts to use a nonexistent syscall, syscall
 * implementations should refrain from returning -ENOSYS.
 */
#define	BOT_E_ENOSYS	        38		       /* 38, Invalid system call number */

#define	BOT_E_ENOTEMPTY	        39	            /* 39, Directory not empty */
#define	BOT_E_ELOOP	            40			    /* 40, Too many symbolic links encountered */
#define	BOT_E_EWOULDBLOCK	    11		        /* like, EAGAIN, Operation would block */
#define	BOT_E_ENOMSG	        42		        /* 42, No message of desired type */
#define	BOT_E_EIDRM	            43		        /* 43, Identifier removed */
#define	BOT_E_ECHRNG	        44		        /* 44, Channel number out of range */
#define	BOT_E_EL2NSYNC	        45	            /* 45, Level 2 not synchronized */
#define	BOT_E_EL3HLT	        46		        /* 46, Level 3 halted */
#define	BOT_E_EL3RST	        47		        /* 47, Level 3 reset */
#define	BOT_E_ELNRNG	        48		        /* 48, Link number out of range */
#define	BOT_E_EUNATCH	        49		        /* 49, Protocol driver not attached */
#define	BOT_E_ENOCSI	        50		        /* 50, No CSI structure available */
#define	BOT_E_EL2HLT	        51		        /* 51, Level 2 halted */
#define	BOT_E_EBADE	            52		        /* 52, Invalid exchange */
#define	BOT_E_EBADR	            53		        /* 53, Invalid request descriptor */
#define	BOT_E_EXFULL	        54		        /* 54, Exchange full */
#define	BOT_E_ENOANO	        55		        /* 55, No anode */
#define	BOT_E_EBADRQC	        56		        /* 56, Invalid request code */
#define	BOT_E_EBADSLT	        57		        /* 57, Invalid slot */

#define	BOT_E_EDEADLOCK	        35	            /* EDEADLK, Resource deadlock would occur */

#define	BOT_E_EBFONT	        59		        /* 59, Bad font file format */
#define	BOT_E_ENOSTR	        60		        /* 60, Device not a stream */
#define	BOT_E_ENODATA	        61		        /* No data available */
#define	BOT_E_ETIME	            62		        /* Timer expired */
#define	BOT_E_ENOSR	            63		        /* Out of streams resources */
#define	BOT_E_ENONET	        64		        /* Machine is not on the network */
#define	BOT_E_ENOPKG	        65		        /* Package not installed */
#define	BOT_E_EREMOTE	        66		        /* Object is remote */
#define	BOT_E_ENOLINK	        67		        /* Link has been severed */
#define	BOT_E_EADV	            68		        /* Advertise error */
#define	BOT_E_ESRMNT	        69		        /* Srmount error */
#define	BOT_E_ECOMM	            70		        /* Communication error on send */
#define	BOT_E_EPROTO	        71		        /* Protocol error */
#define	BOT_E_EMULTIHOP	        72	            /* Multihop attempted */
#define	BOT_E_EDOTDOT	        73		        /* RFS specific error */
#define	BOT_E_EBADMSG	        74		        /* Not a data message */
#define	BOT_E_EOVERFLOW	        75	            /* Value too large for defined data type */
#define	BOT_E_ENOTUNIQ	        76	            /* Name not unique on network */
#define	BOT_E_EBADFD	        77		        /* File descriptor in bad state */
#define	BOT_E_EREMCHG	        78		        /* Remote address changed */
#define	BOT_E_ELIBACC	        79		        /* Can not access a needed shared library */
#define	BOT_E_ELIBBAD	        80		        /* Accessing a corrupted shared library */
#define	BOT_E_ELIBSCN	        81		        /* .lib section in a.out corrupted */
#define	BOT_E_ELIBMAX	        82		        /* Attempting to link in too many shared libraries */
#define	BOT_E_ELIBEXEC  	    83	            /* Cannot exec a shared library directly */
#define	BOT_E_EILSEQ	        84		        /* Illegal byte sequence */
#define	BOT_E_ERESTART	        85	            /* Interrupted system call should be restarted */
#define	BOT_E_ESTRPIPE  	    86	            /* Streams pipe error */
#define	BOT_E_EUSERS	        87		        /* Too many users */
#define	BOT_E_ENOTSOCK  	    88	            /* Socket operation on non-socket */
#define	BOT_E_EDESTADDRREQ	    89	            /* Destination address required */
#define	BOT_E_EMSGSIZE	        90	            /* Message too long */
#define	BOT_E_EPROTOTYPE	    91	            /* Protocol wrong type for socket */
#define	BOT_E_ENOPROTOOPT	    92	            /* Protocol not available */
#define	BOT_E_EPROTONOSUPPORT	93	            /* Protocol not supported */
#define	BOT_E_ESOCKTNOSUPPORT	94		        /* Socket type not supported */
#define	BOT_E_EOPNOTSUPP	    95		        /* Operation not supported on transport endpoint */
#define	BOT_E_EPFNOSUPPORT  	96		        /* Protocol family not supported */
#define	BOT_E_EAFNOSUPPORT	    97		        /* Address family not supported by protocol */
#define	BOT_E_EADDRINUSE	    98		        /* Address already in use */
#define	BOT_E_EADDRNOTAVAIL	    99		        /* Cannot assign requested address */
#define	BOT_E_ENETDOWN	        100	    	    /* Network is down */
#define	BOT_E_ENETUNREACH	    101	    	    /* Network is unreachable */
#define	BOT_E_ENETRESET	        102	    	    /* Network dropped connection because of reset */
#define	BOT_E_ECONNABORTED	    103	            /* Software caused connection abort */
#define	BOT_E_ECONNRESET	    104	    	    /* Connection reset by peer */
#define	BOT_E_ENOBUFS	        105		    	/* No buffer space available */
#define	BOT_E_EISCONN	        106		    	/* Transport endpoint is already connected */
#define	BOT_E_ENOTCONN	        107	     	    /* Transport endpoint is not connected */
#define	BOT_E_ESHUTDOWN	        108		        /* Cannot send after transport endpoint shutdown */
#define	BOT_E_ETOOMANYREFS	    109	            /* Too many references: cannot splice */
#define	BOT_E_ETIMEDOUT	        110	    	    /* Connection timed out */
#define	BOT_E_ECONNREFUSED	    111	            /* Connection refused */
#define	BOT_E_EHOSTDOWN	        112	            /* Host is down */
#define	BOT_E_EHOSTUNREACH	    113	            /* No route to host */
#define	BOT_E_EALREADY	        114	    	    /* Operation already in progress */
#define	BOT_E_EINPROGRESS	    115	    	    /* Operation now in progress */
#define	BOT_E_ESTALE	        116		    	/* Stale file handle */
#define	BOT_E_EUCLEAN	        117		    	/* Structure needs cleaning */
#define	BOT_E_ENOTNAM	        118		    	/* Not a XENIX named type file */
#define	BOT_E_ENAVAIL	        119		    	/* No XENIX semaphores available */
#define	BOT_E_EISNAM	        120		    	/* Is a named type file */
#define	BOT_E_EREMOTEIO 	    121	    	    /* Remote I/O error */
#define	BOT_E_EDQUOT	        122		    	/* Quota exceeded */

#define	BOT_E_ENOMEDIUM	        123	    	    /* No medium found */
#define	BOT_E_EMEDIUMTYPE	    124	    	    /* Wrong medium type */
#define	BOT_E_ECANCELED	        125	    	    /* Operation Canceled */
#define	BOT_E_ENOKEY	        126			    /* Required key not available */
#define	BOT_E_EKEYEXPIRED	    127	    	    /* Key has expired */
#define	BOT_E_EKEYREVOKED	    128	    	    /* Key has been revoked */
#define	BOT_E_EKEYREJECTED	    129	            /* Key was rejected by service */

/* for robust mutexes */
#define	BOT_E_EOWNERDEAD	    130	    	    /* Owner died */
#define	BOT_E_ENOTRECOVERABLE	131	            /* State not recoverable */

#define	BOT_E_ERFKILL           132		    	/* Operation not possible due to RF-kill */

#define	BOT_E_EHWPOISON         133	    	    /* 133, Memory page has hardware error */
//-----------------------------------------------------
// Socket Macro
#define BOT_AF_UNSPEC       OL_AF_UNSPEC
#define BOT_SOCK_STREAM     OL_SOCK_STREAM
#define BOT_SOCK_DGRAM      OL_SOCK_DGRAM
#define BOT_IPPROTO_TCP     OL_IPPROTO_TCP
#define BOT_IPPROTO_UDP     OL_IPPROTO_UDP
#define BOT_SOL_SOCKET      OL_SOL_SOCKET

#define BOT_ERROK           OL_ERROK           /* err ok set, no err happen */
#define BOT_EPERM           OL_EPERM           /* Operation not permitted */
#define BOT_ENOENT          OL_ENOENT          /* No such file or directory */
#define BOT_ESRCH           OL_ESRCH           /* No such process */
#define BOT_EINTR           OL_EINTR           /* Interrupted system call */
#define BOT_EIO             OL_EIO             /* I/O error */
#define BOT_ENXIO           OL_ENXIO           /* No such device or address */
#define BOT_E2BIG           OL_E2BIG           /* Arg list too long */
#define BOT_ENOEXEC         OL_ENOEXEC         /* Exec format error */
#define BOT_EBADF           OL_EBADF           /* Bad file number */
#define BOT_ECHILD          OL_ECHILD          /* No child processes */
#define BOT_EAGAIN          OL_EAGAIN          /* Try again */
#define BOT_ENOMEM          OL_ENOMEM          /* Out of memory */
#define BOT_EACCES          OL_EACCES          /* Permission denied */
#define BOT_EFAULT          OL_EFAULT          /* Bad address */
#define BOT_ENOTBLK         OL_ENOTBLK         /* Block device required */
#define BOT_EBUSY           OL_EBUSY           /* Device or resource busy */
#define BOT_EEXIST          OL_EEXIST          /* File exists */
#define BOT_EXDEV           OL_EXDEV           /* Cross-device link */
#define BOT_ENODEV          OL_ENODEV          /* No such device */
#define BOT_ENOTDIR         OL_ENOTDIR         /* Not a directory */
#define BOT_EISDIR          OL_EISDIR          /* Is a directory */
#define BOT_EINVAL          OL_EINVAL          /* Invalid argument */
#define BOT_ENFILE          OL_ENFILE          /* File table overflow */
#define BOT_EMFILE          OL_EMFILE          /* Too many open files */
#define BOT_ENOTTY          OL_ENOTTY          /* Not a typewriter */
#define BOT_ETXTBSY         OL_ETXTBSY         /* Text file busy */
#define BOT_EFBIG           OL_EFBIG           /* File too large */
#define BOT_ENOSPC          OL_ENOSPC          /* No space left on device */
#define BOT_ESPIPE          OL_ESPIPE          /* Illegal seek */
#define BOT_EROFS           OL_EROFS           /* Read-only file system */
#define BOT_EMLINK          OL_EMLINK          /* Too many links */
#define BOT_EPIPE           OL_EPIPE           /* Broken pipe */
#define BOT_LWIPEDOM        OL_LWIPEDOM        /* Math argument out of domain of func */
#define BOT_LWIPERANGE      OL_LWIPERANGE      /* Math result not representable */
#define BOT_EDEADLK         OL_EDEADLK         /* Resource deadlock would occur */
#define BOT_ENAMETOOLONG    OL_ENAMETOOLONG    /* File name too long */
#define BOT_ENOLCK          OL_ENOLCK          /* No record locks available */
#define BOT_ENOSYS          OL_ENOSYS          /* Function not implemented */
#define BOT_ENOTEMPTY       OL_ENOTEMPTY       /* Directory not empty */
#define BOT_ELOOP           OL_ELOOP           /* Too many symbolic links encountered */
#define BOT_EWOULDBLOCK     OL_EWOULDBLOCK     /* Operation would block */
#define BOT_ENOMSG          OL_ENOMSG          /* No message of desired type */
#define BOT_EIDRM           OL_EIDRM           /* Identifier removed */
#define BOT_ECHRNG          OL_ECHRNG          /* Channel number out of range */
#define BOT_EL2NSYNC        OL_EL2NSYNC        /* Level 2 not synchronized */
#define BOT_EL3HLT          OL_EL3HLT          /* Level 3 halted */
#define BOT_EL3RST          OL_EL3RST          /* Level 3 reset */
#define BOT_ELNRNG          OL_ELNRNG          /* Link number out of range */
#define BOT_EUNATCH         OL_EUNATCH         /* Protocol driver not attached */
#define BOT_ENOCSI          OL_ENOCSI          /* No CSI structure available */
#define BOT_EL2HLT          OL_EL2HLT          /* Level 2 halted */
#define BOT_EBADE           OL_EBADE           /* Invalid exchange */
#define BOT_EBADR           OL_EBADR           /* Invalid request descriptor */
#define BOT_EXFULL          OL_EXFULL          /* Exchange full */
#define BOT_ENOANO          OL_ENOANO          /* No anode */
#define BOT_EBADRQC         OL_EBADRQC         /* Invalid request code */
#define BOT_EBADSLT         OL_EBADSLT         /* Invalid slot */
#define BOT_EDEADLOCK       OL_EDEADLOCK
#define BOT_EBFONT          OL_EBFONT          /* Bad font file format */
#define BOT_ENOSTR          OL_ENOSTR          /* Device not a stream */
#define BOT_ENODATA         OL_ENODATA         /* No data available */
#define BOT_ETIME           OL_ETIME           /* Timer expired */
#define BOT_ENOSR           OL_ENOSR           /* Out of streams resources */
#define BOT_ENONET          OL_ENONET          /* Machine is not on the network */
#define BOT_ENOPKG          OL_ENOPKG          /* Package not installed */
#define BOT_EREMOTE         OL_EREMOTE         /* Object is remote */
#define BOT_ENOLINK         OL_ENOLINK         /* Link has been severed */
#define BOT_EADV            OL_EADV            /* Advertise error */
#define BOT_ESRMNT          OL_ESRMNT          /* Srmount error */
#define BOT_ECOMM           OL_ECOMM           /* Communication error on send */
#define BOT_EPROTO          OL_EPROTO          /* Protocol error */
#define BOT_EMULTIHOP       OL_EMULTIHOP       /* Multihop attempted */
#define BOT_EDOTDOT         OL_EDOTDOT         /* RFS specific error */
#define BOT_EBADMSG         OL_EBADMSG         /* Not a data message */
#define BOT_EOVERFLOW       OL_EOVERFLOW       /* Value too large for defined data type */
#define BOT_ENOTUNIQ        OL_ENOTUNIQ        /* Name not unique on network */
#define BOT_EBADFD          OL_EBADFD          /* File descriptor in bad state */
#define BOT_EREMCHG         OL_EREMCHG         /* Remote address changed */
#define BOT_ELIBACC         OL_ELIBACC         /* Can not access a needed shared library */
#define BOT_ELIBBAD         OL_ELIBBAD         /* Accessing a corrupted shared library */
#define BOT_ELIBSCN         OL_ELIBSCN         /* .lib section in a.out corrupted */
#define BOT_ELIBMAX         OL_ELIBMAX         /* Attempting to link in too many shared libraries */
#define BOT_ELIBEXEC        OL_ELIBEXEC        /* Cannot exec a shared library directly */
#define BOT_LWIPEILSEQ      OL_LWIPEILSEQ      /* Illegal byte sequence */
#define BOT_ERESTART        OL_ERESTART        /* Interrupted system call should be restarted */
#define BOT_ESTRPIPE        OL_ESTRPIPE        /* Streams pipe error */
#define BOT_EUSERS          OL_EUSERS          /* Too many users */
#define BOT_ENOTSOCK        OL_ENOTSOCK        /* Socket operation on non-socket */
#define BOT_EDESTADDRREQ    OL_EDESTADDRREQ    /* Destination address required */
#define BOT_EMSGSIZE        OL_EMSGSIZE        /* Message too long */
#define BOT_EPROTOTYPE      OL_EPROTOTYPE      /* Protocol wrong type for socket */
#define BOT_ENOPROTOOPT     OL_ENOPROTOOPT     /* Protocol not available */
#define BOT_EPROTONOSUPPORT OL_EPROTONOSUPPORT /* Protocol not supported */
#define BOT_ESOCKTNOSUPPORT OL_ESOCKTNOSUPPORT /* Socket type not supported */
#define BOT_EOPNOTSUPP      OL_EOPNOTSUPP      /* Operation not supported on transport endpoint */
#define BOT_EPFNOSUPPORT    OL_EPFNOSUPPORT    /* Protocol family not supported */
#define BOT_EAFNOSUPPORT    OL_EAFNOSUPPORT    /* Address family not supported by protocol */
#define BOT_EADDRINUSE      OL_EADDRINUSE      /* Address already in use */
#define BOT_EADDRNOTAVAIL   OL_EADDRNOTAVAIL   /* Cannot assign requested address */
#define BOT_ENETDOWN        OL_ENETDOWN        /* Network is down */
#define BOT_ENETUNREACH     OL_ENETUNREACH     /* Network is unreachable */
#define BOT_ENETRESET       OL_ENETRESET       /* Network dropped connection because of reset */
#define BOT_ECONNABORTED    OL_ECONNABORTED    /* Software caused connection abort */
#define BOT_ECONNRESET      OL_ECONNRESET      /* Connection reset by peer */
#define BOT_ENOBUFS         OL_ENOBUFS         /* No buffer space available */
#define BOT_EISCONN         OL_EISCONN         /* Transport endpoint is already connected */
#define BOT_ENOTCONN        OL_ENOTCONN        /* Transport endpoint is not connected */
#define BOT_ESHUTDOWN       OL_ESHUTDOWN       /* Cannot send after transport endpoint shutdown */
#define BOT_ETOOMANYREFS    OL_ETOOMANYREFS    /* Too many references: cannot splice */
#define BOT_ETIMEDOUT       OL_ETIMEDOUT       /* Connection timed out */
#define BOT_ECONNREFUSED    OL_ECONNREFUSED    /* Connection refused */
#define BOT_EHOSTDOWN       OL_EHOSTDOWN       /* Host is down */
#define BOT_EHOSTUNREACH    OL_EHOSTUNREACH    /* No route to host */
#define BOT_EALREADY        OL_EALREADY        /* Operation already in progress */
#define BOT_EINPROGRESS     OL_EINPROGRESS     /* Operation now in progress */
#define BOT_ESTALE          OL_ESTALE          /* Stale NFS file handle */
#define BOT_EUCLEAN         OL_EUCLEAN         /* Structure needs cleaning */
#define BOT_ENOTNAM         OL_ENOTNAM         /* Not a XENIX named type file */
#define BOT_ENAVAIL         OL_ENAVAIL         /* No XENIX semaphores available */
#define BOT_EISNAM          OL_EISNAM          /* Is a named type file */
#define BOT_EREMOTEIO       OL_EREMOTEIO       /* Remote I/O error */
#define BOT_EDQUOT          OL_EDQUOT          /* Quota exceeded */
#define BOT_ENOMEDIUM       OL_ENOMEDIUM       /* No medium found */
#define BOT_EMEDIUMTYPE     OL_EMEDIUMTYPE     /* Wrong medium type */
#endif /* __BOT_PLATFORM_H */
