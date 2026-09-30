#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "../common.h"
#include "lampStatusFinder.h"
#include "../mqttTask.h"

#define D_FILE_INDEXUSED      1
#define D_FILE_INDEXNOTUSED   5
/* C:/U: NVM partition is only ~172KB total, shared with storedDatas.bin,
 * its backup, and OTA state -- keep this log's footprint modest so it
 * doesn't crowd out everything else sharing the partition.
 * 14 * sizeof(fsDataBackUp_t) = 3710 bytes. */
#define D_MAX_FILEINDEX       24
#define D_NOTUPLOADED         0
#define D_UPLOADED            1

typedef struct __attribute__((packed)){
    U1 state;
    U1 data[70]; /* actual payload (serveTransmitPkt_t) is 19 bytes; 40 leaves headroom */
    U2 dataLength;
    U1 uploadStatus;
    U4 ts;
    U1 crc;
} fsDataBackUp_t;

/* Recovers currentFileIndex from the on-flash circular log (so a reboot
 * resumes writing after the last used slot instead of overwriting it), and
 * creates the mutex guarding the log file. Call once at task startup. */
void dataStore_init(void);

/* Persists the packet into the next circular-log slot before it's published,
 * then returns an mqttQueue_t ready to hand to mqtt_publish(). */
mqttQueue_t storeDtata(serveTransmitPkt_t serveTransmitPkt);

/* Marks the given slot as uploaded once mqtt_publish() for it has actually
 * succeeded (ol_mqtt_publish() is synchronous here, so this is just called
 * right after a successful publish -- no async ack callback needed). */
void fsDataUpdateUploadState(U2 index);

/* Scans up to the last 100 slots backward from currentFileIndex and
 * re-publishes any still marked D_NOTUPLOADED (e.g. left over from a publish
 * that failed, or from before a reboot). Call once per cycle after the
 * shared-attributes exchange. */
void payLoadAutoUpload(U2 currentFileIndex, mqtt_client_t *client);

/* TEMP DIAGNOSTIC: reads and prints every slot 0..D_MAX_FILEINDEX-1's raw
 * on-flash contents (state/dataLength/uploadStatus/ts/crc), independent of
 * currentFileIndex. Lets us see the whole log's real state at once instead
 * of only whatever payLoadAutoUpload's scan happens to touch. */
void dataStore_dumpAll(void);

#endif /* DATA_STORE_H */
