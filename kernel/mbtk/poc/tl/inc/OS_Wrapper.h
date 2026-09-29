// jptt OEM platform headers

#ifndef __OS_WRAPPER_H__
#define __OS_WRAPPER_H__

#include <stddef.h>   // size_t defined here

/*
** init linux signal handler & exceptions
*/

extern int OS_Wrap_init_system(void);
extern void OS_Wrap_deinit_system(void);

/*
** mutex & semaphore
*/
extern void *OS_Wrap_get_mutex(void);
extern void OS_Wrap_ret_mutex(void *);
extern int OS_Wrap_mutex_lock(void *mtx);
extern int OS_Wrap_mutex_trylock(void *mtx);
extern int OS_Wrap_mutex_unlock(void *mtx);


extern void *OS_Wrap_get_semaphore(void);
extern void OS_Wrap_ret_semaphore(void *sema);
extern int OS_Wrap_semaphore_post(void *sema);
extern int OS_Wrap_semaphore_wait(void *sema);

/*
*/
extern unsigned short OS_Wrap_htons(unsigned short us);
extern unsigned int OS_Wrap_htonl(unsigned int ui);
extern unsigned short OS_Wrap_ntohs(unsigned short us);
extern unsigned int OS_Wrap_ntohl(unsigned int ui);

/*
** tcp socket
*/
extern int OS_Wrap_make_tcp_socket(const char* addr, unsigned short port, int s_tout, int r_tout);
extern int OS_Wrap_receive_tcp_socket(int cfd, char *buffer, int length);
extern int OS_Wrap_send_tcp_socket(int cfd, char *buffer, int length);
extern void OS_Wrap_shutdown_tcp_socket(int sock);

extern int OS_Wrap_set_tcp_timeout(int cfd, int ms);

extern int OS_Wrap_socket_wait_readable(int h_socket, unsigned int ms);
extern void OS_Wrap_socket_block(int h_socket, int block);
extern int OS_Wrap_socket_rbuf_ready(int h_socket);

/*
** udp socket
*/
extern int OS_Wrap_get_udp_socket(void);
extern int OS_Wrap_receive_udp(int usock, char *from_a, unsigned short from_p, char* buffer, int blen);
extern int OS_Wrap_send_udp(int usock, char *to_a, unsigned short to_p, char* buffer, int slen);
extern int OS_Wrap_set_udp_r_timeout(int usock, int msec);
extern int OS_Wrap_set_udp_s_timeout(int usock, int msec);
extern int OS_Wrap_set_usock_s_buffer(int sock, int slen);

extern void OS_Wrap_close_socket(int usock);

/*
** time service
*/
extern unsigned long current_time_millis(void);
extern void OS_Wrap_usleep(int us);
extern void OS_Wrap_set_wallclock(unsigned int wc);
extern unsigned int OS_Wrap_get_wallclock(void);
/*
** timer service
*/
extern void OS_Wrap_set_timeout_handler(void (*h)(int));
extern int OS_Wrap_create_timer(int tno);
extern int OS_Wrap_arm_timer(int tno, int msec);
extern int OS_Wrap_disarm_timer(int tno);
extern int OS_Wrap_delete_timer(int tno);

/*
**
*/
#define THRD_AUDIO_PRIORITY   (20)

extern void * OS_Wrap_create_thread(void (*func)(void *), void *param, unsigned int stack_sz);
extern void * OS_Wrap_create_thread_with_prio(void (*func)(void *), void *param, unsigned int stack_sz, int priority);
extern void OS_Wrap_thread_change_priority(void *tid, int newp);
extern int OS_Wrap_thread_cancel(void *tid);
extern int OS_Wrap_thread_join(void *tid);
extern int OS_Wrap_thread_detach(void *tid);
extern void OS_Wrap_thread_exit(void *tid);

/*
**  AMR codec used memory functions
*/
extern void *oscl_malloc(unsigned int sz);
extern void oscl_free(void *ptr);

extern void *oscl_memset(void *s, int c, unsigned int n);
extern void *oscl_memmove(void *dest, const void *src, unsigned int n);
extern void *oscl_memcpy(void *dest, const void *src, unsigned int n);

/*
** FILE 
*/
extern char *mk_file_name(const char *fname);
extern int  OS_Wrap_read_file(const char *fname, char *dbuf, int blen);
extern int  OS_Wrap_write_file(const char *fname, char *dbuf, int blen);
extern void OS_Wrap_delete_file(const char *fname);

#endif

