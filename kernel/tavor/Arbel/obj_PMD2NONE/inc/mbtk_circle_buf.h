
#include "mbtk_pub_type.h"


struct DRV_CIRCLE_BUF;
typedef struct DRV_CIRCLE_BUF DRV_CIRCLE_BUF_T;

void DRV_CBufInit(DRV_CIRCLE_BUF_T *cb, u8 *buf, unsigned size);
void DRV_CBufFlush(DRV_CIRCLE_BUF_T *cb);
bool DRV_CBufIsEmpty(DRV_CIRCLE_BUF_T *cb);
bool DRV_CBufIsFull(DRV_CIRCLE_BUF_T *cb);
unsigned DRV_CBufPayloadSize(DRV_CIRCLE_BUF_T *cb);
unsigned DRV_CBufRemainSize(DRV_CIRCLE_BUF_T *cb);
unsigned DRV_CBufWrite(DRV_CIRCLE_BUF_T *cb, const u8 *data, unsigned size);
unsigned DRV_CBufRead(DRV_CIRCLE_BUF_T *cb, u8 *data, unsigned size);
u8 *DRV_CBufLinearRead(DRV_CIRCLE_BUF_T *cb, unsigned *size);
void DRV_CBufSkipBytes(DRV_CIRCLE_BUF_T *cb, unsigned size);

// DONT access directly
struct DRV_CIRCLE_BUF
{
    u8 *buf;
    unsigned size;
    unsigned rd;
    unsigned payload;
};
