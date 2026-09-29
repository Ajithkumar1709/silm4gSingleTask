
#include "bot_system.h"

#define SIOCGIFHWADDR 1

char *bot_network_get_mac(void);
int bot_network_init(void)
{
    if (bot_network_get_mac() == NULL) {
        bot_printf("fail to get mac\r\n");
        return -1;
    }
    return 0;
}

int bot_network_is_ready(void)
{
    return 1;
}

int bot_network_rssi_get(signed short *rssi)
{
    return 0;
}

static char bot_network_mac[16] = {0};
#define BOT_NETWORK_BUF_SIZE  2048
char *bot_network_get_mac(void)
{
    // struct ifreq ifreq;
    // struct ifconf ifc;
    // char buf[BOT_NETWORK_BUF_SIZE] = {0};
    // int sock;

    // bot_printf("entry to get mac\r\n");
    // if (bot_network_mac[0] != 0) {
    //     bot_printf("cached mac:%s\r\n", bot_network_mac);
    //     return bot_network_mac;
    // }
    
    // if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
    // {
    //     bot_printf("fail to get socket\r\n");
    //     return NULL;
    // }
    // memset(buf, 0, BOT_NETWORK_BUF_SIZE);
    // ifc.ifc_len = BOT_NETWORK_BUF_SIZE;
    // ifc.ifc_buf = buf;
    // if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
    //     close(sock);
    //     bot_printf("fail to get SIOCGIFCONF\r\n");
    //     return NULL;
    // }
    // struct ifreq *start = ifc.ifc_req;
    // const struct ifreq* const end = start + (ifc.ifc_len / sizeof(struct ifreq));
    // for (; start != end; start++) {
    //     if (strstr(start->ifr_name, "lo") == NULL) {
    //         break;
    //     }
    // }
    // bot_printf("mac name:%s\r\n", start->ifr_name);
    // strcpy(ifreq.ifr_name, start->ifr_name);
    // if (ioctl(sock, SIOCGIFHWADDR, &ifreq) < 0)
    // {
    //     close(sock);
    //     bot_printf("failt to get SIOCGIFHWADDR\r\n");
    //     return NULL;
    // }
    // bot_snprintf(bot_network_mac, 16, "%02X%02X%02X%02X%02X%02X",
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[0],
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[1],
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[2],
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[3],
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[4],
    //        (unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
    // bot_printf("mac:%s\r\n", bot_network_mac);
    // close(sock);
    // bot_printf("close sock:%d \r\n", sock);
    return bot_network_mac;
}

int bot_network_ccid_get(char *ccid)
{
    bot_snprintf(ccid, 32, "%s", bot_network_mac);
    bot_printf("imei:%s\r\n", ccid);
    return 0;
}

int bot_network_imei_get(char *imei)
{
    bot_snprintf(imei, 32, "%s", bot_network_mac);
    bot_printf("imei:%s\r\n", imei);
    return 0;
}

int bot_network_lbs_get(unsigned short *mcc, unsigned short *mnc, unsigned int *cid, unsigned int *lac)
{
    *mcc = 100;
    *mnc = 0;
    *cid = 20000;
    *lac = 50000;
    return 0;
}

int bot_network_rat_get(unsigned char *rat)
{
    *rat = 0;
    return 0;
}

int bot_network_dns_available(void)
{
    return 0;
}

