#ifndef __YT_TTS_CALLBACK_FUNCTION_DEFINE_HEADER__
#define __YT_TTS_CALLBACK_FUNCTION_DEFINE_HEADER__


	#define TTS_PLAY_STACK_SIZE        1024*8  //1024*8  tts stack size
	#define TTS_MAX_TEXT_SIZE            512
	#define PCM_BUFFER_MAX_SIZE  160*1024 //160*1024   /*modify by xw.guan 2021.0715*/
	/*Open flags */
	/** Open: Read only */
	#define O_RDONLY 0x0001
	/** Open: Write only */
	#define O_WRONLY 0x0002
	/** Open: Read/Write */
	#define O_RDWR   0x0003
	/** Open: Create file */
	#define O_CREAT  0x0100
	/** Open: Truncate file */
	#define O_TRUNC  0x0200
	/** Open: Exclusively  */
	#define O_EXCL   0x0400
	/** Open: For append */
	#define O_APPEND 0x0800


	void tts_printf(void *fmt,...);
	//6 APIs for File I/O access
	int yt_open_file_for_read(unsigned char *file_name_utf16);//open file for reading data only...
	int yt_open_file_for_write(unsigned char *file_name_utf16);//open file for reading data only...
	int yt_seek_file(int file_handle, unsigned int offset);//whence:VEN_FILE_SEEK_SET 
	unsigned int yt_read_file(int file_handle, void* pBuffer, unsigned int nDataLenInByte );
	unsigned int yt_write_file(int file_handle, void* pBuffer, unsigned int nDataLenInByte);
	int yt_close_file(int file_handle);


	//5 APIs for Networking
	char* yt_gethostbyname(char *strHostName);
	int yt_socket(char *dstIpAddr, char *hostname, int port);
	int yt_send(int sockfd, int timeout, char *httpPkg, int pkgLen);
	int yt_recv(int sockfd, int timeout, char **ppStrPkg, int pkgLen);
	int yt_closesocket(int sockfd);



	//1 API for retrieving IMEI
	int yt_get_imei(char *imei);


#endif
