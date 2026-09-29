#include <stdio.h>

//#include "FDI_FILE.h"
#include "sockets.h"
#include "netdb.h"
#include "stdarg.h"
#include "UART.h"

#ifdef MBTK_TTS_SUPPORT_ytTTS
void tts_printf(void *fmt,...)
{
    va_list ap;
    char buffer[128] = {0};
    static int fatal_uart_inited = 0;

    memset(buffer, 0, sizeof(buffer));
    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer)-1, fmt, ap);
    va_end(ap);

    mbtk_debug_log("%s\n", buffer);
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//6 callback functions for file I/O routines: [START]
int yt_open_file_for_read(unsigned char *strFileName)//open file for reading data only...
{
    int nFileHandle = -1;

    //nFileHandle = FS_Open((UINT8*)strFileName,O_RDONLY|O_TRUNC,0);
    nFileHandle = FDI_fopen((UINT8*)strFileName, "rb");
    tts_printf("yt_open_file_for_read, file_id=%d",nFileHandle);
    if(!nFileHandle)
        return -1;

    return nFileHandle;
}


int yt_open_file_for_write(unsigned char *strFileName)//open file for writing data only...
{
	int nFileHandle = -1;

	//nFileHandle = FS_Open((UINT8*)strFileName,O_WRONLY|O_CREAT,0);
	nFileHandle = FDI_fopen((UINT8*)strFileName, "wb");
	tts_printf("yt_open_file_for_write, file_id=%d",nFileHandle);
	if(!nFileHandle)
	    return -1;
	
	return nFileHandle;
}



int yt_seek_file(int file_handle, unsigned int offset)//seek file with offset
{
	int nReturn = -1;

		//nReturn = FS_Seek(file_handle,(long long)offset,SEEK_SET);
	nReturn = FDI_fseek(file_handle,(long)offset,SEEK_SET);
    tts_printf("yt_seek_file, nReturn=%d",nReturn);

	return nReturn;
}


unsigned int yt_read_file(int file_handle, void* pBuffer, unsigned int nDataLenInByte )
{
	int nReturn = 0;

	//nReturn = FS_Read(file_handle, (unsigned char*)pBuffer,nDataLenInByte);
	nReturn = FDI_fread(pBuffer,1,nDataLenInByte,file_handle);
	tts_printf("yt_read_file, nReturn=%d",nReturn);

	return (unsigned int) nReturn;
}



unsigned int yt_write_file(int file_handle, void* pBuffer, unsigned int nDataLenInByte)
{
	int nReturn = 0;

	//nReturn = FS_Write(file_handle, (unsigned char*)pBuffer,nDataLenInByte);
	nReturn = FDI_fwrite(pBuffer,1,nDataLenInByte,file_handle);
	tts_printf("yt_write_file, nReturn=%d",nReturn);
	

	return (unsigned int)nReturn;
}


int yt_close_file(int file_handle)
{
	int nReturn = 0;

	nReturn = FDI_fclose(file_handle);
	tts_printf("yt_close_file, nReturn=%d",nReturn);

	return nReturn;
}

//6 callback functions for file I/O routines: [END]
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//5 socket callback function prototypes:  [START]

int ValSocketInit(char *dstIpAddr, char *hostname, int port)
{
    int sockfd;
    struct sockaddr_in sockaddr;
    socklen_t len = sizeof(sockaddr);
    struct hostent * host_entry = NULL;
    int timeout = 20 * 1000;
    tts_printf("hostname[%s]", hostname);    
    host_entry = gethostbyname(hostname);
    if(host_entry == NULL)
        return -1;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        return -1;
    
    memset(&sockaddr, 0, len);
    sockaddr.sin_port = htons(port);
    sockaddr.sin_family = AF_INET;
    memcpy(&(sockaddr.sin_addr.s_addr), host_entry->h_addr, host_entry->h_length);

    int set = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        int ret = connect(sockfd, (struct sockaddr*)&sockaddr, len);
        if (ret < 0)
        {
            tts_printf("connect error!");
            return -1;
        }
        tts_printf("connect success, fd=%d\n",sockfd);
        return sockfd;
    
}
int ValSocketClose(int sockfd)
{
    closesocket(sockfd);
    return 0;
}
int ValSendPkgToServ(int sockfd, int timeout, char *httpPkg, int pkgLen)
{
    int sentLen = 0;
    int rc  = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    
    rc = send(sockfd, httpPkg, pkgLen, 0);
    tts_printf("ValSendPkgToServ: [%s]", httpPkg);
    tts_printf("ValSendPkgToServ: %d, %d",rc,pkgLen);
    if (rc < 0)
    {
        tts_printf("send [%s] error!", httpPkg);
        return -1;
    }
    return rc;   
}
int ValRecvPkgFromServExt(int sockfd, int timeout, char **ppStrPkg, int pkgLen)
{
    //int recvLen = 0;
    int rc  = 0;
    //while(recvLen < pkgLen)
    //{
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,  &timeout, sizeof(timeout));

        //rc = recv(sockfd, *ppStrPkg+ recvLen , pkgLen - recvLen, 0);
        rc = recv(sockfd, *ppStrPkg, pkgLen, 0);
        tts_printf("ValRecvPkgFromServExt: [%s]", *ppStrPkg);
        tts_printf("ValRecvPkgFromServExt: %d, %d",rc, pkgLen);
        //if(rc > 0)
            //recvLen += rc;
        //else 
        if (rc <= 0)
        {
            tts_printf("err, recv error happen, errno = %d", rc);
            return -1;
        }
    //}
    //tts_printf("recvLen: %d",recvLen);
    return rc;
}
char *ValGetIpByHostName(char *hostname,char *ipAddr)
{
    struct hostent * host_entry = NULL;
    host_entry = gethostbyname(hostname);
    if(host_entry == NULL)
    {
        //tts_printf("gethostbyname error [%d]",hstrerror(h_errno));
        tts_printf("gethostbyname error");
        return -1;
    }
    else
    {
        tts_printf("get[%s]  ip[%d.%d.%d.%d]", host_entry->h_name,host_entry->h_addr_list[0][0] & 0xff, 
            host_entry->h_addr_list[0][1] & 0xff, host_entry->h_addr_list[0][2] & 0xff, host_entry->h_addr_list[0][3] & 0xff);
        sprintf(ipAddr,"%d.%d.%d.%d",host_entry->h_addr_list[0][0] & 0xff, host_entry->h_addr_list[0][1] & 0xff,
            host_entry->h_addr_list[0][2] & 0xff, host_entry->h_addr_list[0][3] & 0xff);
        tts_printf("%s",ipAddr);
        return 0;
    }
    
}


char* yt_gethostbyname(char *strHostName)
{	
	//static char  ip_addr[30]="211.152.53.226";
	char  ip_addr[30];
	int nReturn;
	memset(ip_addr,0,30);
	tts_printf("strHostName[%s]",strHostName);
	nReturn = ValGetIpByHostName(strHostName,ip_addr);
	tts_printf("GetIpByHostName [%d][%s]",nReturn,ip_addr);
	return (char*)ip_addr;
}





int yt_socket(char *dstIpAddr, char *hostname, int port)
{
	int nSocketHandle = 0;
        tts_printf("dstIpAddr [%s]",dstIpAddr);
	nSocketHandle = ValSocketInit(dstIpAddr, hostname, port);

	return nSocketHandle;
}




int yt_send(int sockfd, int timeout, char *httpPkg, int pkgLen)
{
	int nReturn = 0;
        tts_printf("enter yt_send");
		nReturn = ValSendPkgToServ(sockfd, timeout, httpPkg,pkgLen); 

 return nReturn;	
}


int yt_recv(int sockfd, int timeout, char **ppStrPkg, int pkgLen)
{
	int nReturn = 0;
        tts_printf("enter yt_recv");
		nReturn = ValRecvPkgFromServExt(sockfd, timeout, ppStrPkg, pkgLen);

	return nReturn;
}



int yt_closesocket(int sockfd)
{
	int nReturn = 0;
    tts_printf("enter yt_close");
	nReturn = ValSocketClose(sockfd);

	return nReturn;
}


//5 socket callback function prototypes:  [END]
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//1 callback function for retrieving ChipID: [START]
unsigned int yt_get_chip_info(void)
{
	unsigned int nChipID = 0;

	nChipID = GetChipID();

	return nChipID;
}
//1 callback function for retrieving ChipID: [END]
//////////////////////////////////////////////////////////////////


char imeibuf[20] = {0};
unsigned int yt_get_imei_info(char *imei)
{
	int iret =0;
	uart_printf("demo_mbtk_get_imei \r\n");
	if(iret = mbtk_get_imei(imeibuf) != 0)
	{
		return -1;
	}

	//后台不处理引号，直接去掉引号
	//imei[0]='\"';
	//strcpy(&imei[1],imeibuf);
	//imei[strlen(imeibuf)+1]='\"';
	strcpy(imei, imeibuf);

	uart_printf("demo_mbtk_get_imei2 : %s\n", imei);
	return 0;
}
#endif
