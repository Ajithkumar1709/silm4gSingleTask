/**************************************************************************/
/*                                                                        */
/*            Copyright (c) 1996-2006 by Express Logic Inc.               */
/*                                                                        */
/*  This software is copyrighted by and is the sole property of Express   */
/*  Logic, Inc.  All rights, title, ownership, or other interests         */
/*  in the software remain the property of Express Logic, Inc.  This      */
/*  software may only be used in accordance with the corresponding        */
/*  license agreement.  Any unauthorized use, duplication, transmission,  */
/*  distribution, or disclosure of this software is expressly forbidden.  */
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */
/*  written consent of Express Logic, Inc.                                */
/*                                                                        */
/*  Express Logic, Inc. reserves the right to modify this software        */
/*  without notice.                                                       */
/*                                                                        */
/*  Express Logic, Inc.                                                   */
/*  11423 West Bernardo Court               info@expresslogic.com         */
/*  San Diego, CA  92127                    http://www.expresslogic.com   */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/**   ThreadX Component                                                   */
/**                                                                       */
/**   POSIX Compliancy Wrapper (POSIX)                                    */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  EKP DEFINITIONS                                        RELEASE        */
/*                                                                        */
/*    errno.h                                             PORTABLE C      */
/*                                                           5.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Express Logic, Inc.                                                 */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the constants, structures, etc.needed to          */
/*    implement the Evacuation Kit for POSIX Users (POSIX)                */
/*                                                                        */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  12-12-2005         Stefaan Kiebooms          Initial Version          */
/*                                                                        */
/**************************************************************************/

#ifndef _ERRNO_H
#define _ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TX_POSIX_SOURCE
#define errno (posix_get_pthread_errno(pthread_self()))
//-jrs#define errno posix_errno
//-jrsextern unsigned int posix_errno;
#endif

/* the POSIX standard does not impose particular values for errno.h        */
/* error codes between 200 and 1000 are not used by the Threadx wrapper    */
/* but supplied for completeness.                                          */




#define E2BIG           200

#define EACCES          13

#define EADDRINUSE      201

#define EADDRNOTAVAIL   202

#define EAFNOSUPPORT    203

#define EAGAIN          11

#define EALREADY        204

#define EBADF           9

#define EBADMSG         205

#define EBUSY           9999

#define ECANCELED       206

#define ECHILD          207

#define ECONNABORTED    208

#define ECONNREFUSED    209

#define ECONNRESET      210

#define EDEADLK         3333

#define EDESTADDRREQ    211

#define EDOM            212

#define EDQUOT          213

#define EEXIST          17      

#define EFAULT          214

#define EFBIG           215

#define EHOSTUNREACH    216

#define EIDRM           217

#define EILSEQ          218

#define EINPROGRESS     219

#define EINTR           4

#define EINVAL          22

#define EIO             220

#define EISCONN         221

#define EISDIR          222

#define ELOOP           223

#define EMFILE          224

#define EMLINK          225

#define EMSGSIZE        36

#define EMULTIHOP       226

#define ENAMETOOLONG    26

#define ENETDOWN        227

#define ENETRESET       228

#define ENETUNREACH     229

#define ENFILE          230

#define ENOBUFS         231

#define ENODATA         232

#define ENODEV          233

#define ENOENT          2

#define ENOEXEC         234

#define ENOLCK          235

#define ENOLINK         236

#define ENOMEM          4444

#define ENOMSG          237

#define ENOPROTOOPT     238

#define ENOSPC          28

#define ENOSR           239

#define ENOSTR          240

#define ENOSYS          71

#define ENOTCONN        241

#define ENOTDIR         242

#define ENOTEMPTY       243

#define ENOTSOCK        244

#define ENOTSUP         126

#define ENOTTY          245

#define ENXIO           246

#define EOPNOTSUPP      247

#define EOVERFLOW       248

#define EPERM           2222

#define EPIPE           249

#define EPROTO          250

#define EPROTONOSUPPORT 251

#define EPROTOTYPE      252

#define ERANGE          253

#define EROFS           254

#define ESPIPE          255

#define ESRCH           3

#define ESTALE          256

#define ETIME           257

#define ETIMEDOUT       5555

#define ETXTBSY         258

#define EWOULDBLOCK     259

#define EXDEV           260

#ifdef __cplusplus
}
#endif

#endif
