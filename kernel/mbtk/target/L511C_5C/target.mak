# Define crane platform version
#
#  Copyright Statement:
#  ---------------------------
#  MBTK 添加整体项目宏
#
# *************************************************************************

MBTK_PRODUCT = L511C_5C

MBTK_PRODUCT_BSP = L511_5

MBTK_PRODUCT_SCATT_FILE = Crane_DS_4M_Ram_2M_Flash_XIP_CIPSRAM_Common_SingleSIM

MBTK_FOTA_SUPPORT = y

MBTK_CDC_UART_SUPPORT = y

MBTK_NOAUDIO_SUPPORT = y

MBTK_SPI_SUPPORT = y

#open TTS set = ivtts_ch / ivtts_en / ivtts_little    #close set = n
MBTK_TTS_SUPPORT = n

#open POC set = BND / HAWK / CHAYU / ZZD    #close set = n
MBTK_POC_SUPPORT = n

MBTK_MP3_SUPPORT = n

MBTK_FTP_ENABLE = n

MBTK_MQTT_SUPPORT = n

#open GNSS set = int    #close set = n
MBTK_GNSS_SUPPORT = n

MBTK_MINI_APP_FOTA = y

MBTK_FOAT_NORMAL = n

MBTK_SPINOR_SUPPORT = n

LFS_SUPPORT_V2 = y


