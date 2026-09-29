#ifndef MBTK_CIRCLE_BUF_H
#define MBTK_CIRCLE_BUF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef bool
typedef unsigned char              bool;
#endif

#ifndef NULL
#define NULL (void *)0
#endif


struct DRV_CIRCLE_BUF;
typedef struct DRV_CIRCLE_BUF DRV_CIRCLE_BUF_T;

void ol_cbuff_init(DRV_CIRCLE_BUF_T *cb, unsigned char *buf, unsigned size);
void ol_cbuff_flush(DRV_CIRCLE_BUF_T *cb);
bool ol_cbuff_is_empty(DRV_CIRCLE_BUF_T *cb);
bool ol_cbuff_is_full(DRV_CIRCLE_BUF_T *cb);
unsigned ol_cbuff_payload_size(DRV_CIRCLE_BUF_T *cb);
unsigned ol_cbuff_remain_size(DRV_CIRCLE_BUF_T *cb);
unsigned ol_cbuff_write(DRV_CIRCLE_BUF_T *cb, const unsigned char *data, unsigned size);
unsigned ol_cbuff_read(DRV_CIRCLE_BUF_T *cb, unsigned char *data, unsigned size);
unsigned char *ol_cbuff_linear_read(DRV_CIRCLE_BUF_T *cb, unsigned *size);
void ol_cbuff_skip_bytes(DRV_CIRCLE_BUF_T *cb, unsigned size);

// DONT access directly
struct DRV_CIRCLE_BUF
{
    unsigned char *buf;
    unsigned size;
    unsigned rd;
    unsigned payload;
};

#ifdef __cplusplus
}
#endif

#endif
