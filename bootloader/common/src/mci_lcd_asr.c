#ifdef CRANE_MCU_DONGLE
#include "mci_lcd.h"
#include "backlight_drv.h"
#else
#include "ui_log_api.h"
#include "fs_api.h"
#endif
#include "lcdd_asr.h"

PRIVATE struct asrlcdd_screen_info  g_mciLcdScreenInfo;
PRIVATE struct asrlcdd_screen_info  g_mciLcdFBInfo;
PRIVATE UINT32 g_mciLcdFBBitdepth = 16;

PUBLIC UINT8 g_mciLcdBrightnessLevel=0xff;
PUBLIC BOOL g_mciLcdBackLightOn=FALSE;
PUBLIC MCI_LCD_BPFUN_T     g_mciLcdBypassFunction=NULL;
extern unsigned char g_asrlcd_framebuffer[320*320*4];


void dump_lcd_framebuffer(void)
{
	int frame_count = 0;
	char ui_frame[32] = "d:/ui_f";
	INT32 fd;
	raw_uart_log("dump_lcd_framebuffer +++ \r\n");

	raw_uart_log("mci_LcdBlockWrite width = %d , height = %d \r\n",g_mciLcdFBInfo.width,g_mciLcdFBInfo.height);
#ifdef MMI_INTERFACE
#ifdef CRANE_MCU_DONGLE
    fd = FDI_fopen(ui_frame, "wb");
    FDI_fwrite((UINT8 *)g_asrlcd_framebuffer, g_mciLcdFBInfo.width*g_mciLcdFBInfo.height, sizeof(char), fd);
    FDI_fclose(fd);
#else
	fd = FS_Open(ui_frame,	FS_O_CREAT | FS_O_TRUNC | FS_O_WRONLY, 0);
	FS_Write(fd,(UINT8 *)g_asrlcd_framebuffer,g_mciLcdFBInfo.width*g_mciLcdFBInfo.height);
	FS_Close(fd);
#endif
#endif
	raw_uart_log("dump_lcd_framebuffer --- \r\n");
}



// ============================================================================
// mci_LcdInit
// ----------------------------------------------------------------------------
// ============================================================================
VOID mci_LcdInit(UINT32 background ,int panel_is_ready)
{
    static BOOL visitFlag = 0;
	raw_uart_log("mci_LcdInit ++\r\n");

	if (!visitFlag)
    {
    	raw_uart_log("mci_LcdInit\r\n");
        ASRLCDD_Open(panel_is_ready);
        ASRLCDD_GetScreenInfo(&g_mciLcdScreenInfo);
        /* fix URT bug# 82329 */
        if((background & (~0xffff)) == 0)
            mci_LcdClearScreen(background & 0xffff);
        g_mciLcdBypassFunction=NULL;
        visitFlag = 1;
    }
}
#ifdef ATA_TEST
int mci_LcdInit_ATA(UINT32 background, int panel_is_ready)
{
    static BOOL visitFlag = 0;
    static int ret = 0;
    raw_uart_log("mci_LcdInit_ATA ++\r\n");

    if (!visitFlag)
    {
        raw_uart_log("mci_LcdInit_ATA\r\n");
        ret = ASRLCDD_Open(panel_is_ready);
        ASRLCDD_GetScreenInfo(&g_mciLcdScreenInfo);
        /* fix URT bug# 82329 */
        if((background & (~0xffff)) == 0)
            mci_LcdClearScreen(background & 0xffff);
        g_mciLcdBypassFunction=NULL;
        visitFlag = 1;
    }

    return ret;
}
#endif
int mci_Logo_LcdInit(UINT32 background)
{
	int ret = 0;
    static BOOL visitFlag = 0;
	LCDLOGD("mci_Logo_LcdInit ++\r\n");

	if (!visitFlag)
    {
    	LCDLOGD("mci_Logo_LcdInit\r\n");
        //ret = ASRLCDD_Logo_Open();
		ret =  ASRLCDD_Open(0);
        ASRLCDD_GetScreenInfo(&g_mciLcdScreenInfo);
        g_mciLcdBypassFunction=NULL;
        visitFlag = 1;
    }
	return ret;
}
#ifdef ATA_TEST
int mci_Logo_LcdInit_ATA(UINT32 background)
{
    static BOOL visitFlag = 0;
    static int ret = 0;
    raw_uart_log("mci_Logo_LcdInit_ATA ++\r\n");

    if (!visitFlag)
    {
        raw_uart_log("mci_Logo_LcdInit_ATA\r\n");
        ret = ASRLCDD_Logo_Open();
        ASRLCDD_GetScreenInfo(&g_mciLcdScreenInfo);
        g_mciLcdBypassFunction=NULL;
        visitFlag = 1;
    }

    return ret;
}
#endif
VOID mci_ee_LcdInit(UINT32 background)
{
    static BOOL visitFlag = 0;
	raw_uart_log("mci_ee_LcdInit ++\r\n");

	if (!visitFlag)
	{
		raw_uart_log("mci_ee_LcdInit\r\n");
		ASRLCDD_Assert_Open();
		ASRLCDD_GetScreenInfo(&g_mciLcdScreenInfo);
		g_mciLcdBypassFunction=NULL;
		visitFlag = 1;
		}
}

VOID mci_LcdSetFBInfo(int stride, int height)
{
	raw_uart_log("mci_LcdSetFBInfo (%d, %d)\r\n", stride, height);
	g_mciLcdFBInfo.width = stride;
	g_mciLcdFBInfo.height = height;
}

VOID mci_LcdSetFBBitdepth(int bitdepth)
{
	raw_uart_log("mci_LcdSetFBBitdepth (%d)\r\n", bitdepth);
	g_mciLcdFBBitdepth = bitdepth;
}

// ============================================================================
// mci_LcdStartBypass
// ----------------------------------------------------------------------------
// ============================================================================
BOOL mci_LcdStartBypass(MCI_LCD_BPFUN_T bypassFun)
{
#if 0 //Jessica
    UINT32 status = hal_SysEnterCriticalSection();
    if (g_mciLcdBypassFunction==NULL)
    {
        g_mciLcdBypassFunction=bypassFun;
        hal_SysExitCriticalSection(status);
        lcdd_EnableVidLayerMerge(TRUE);
        raw_uart_log("mci_LcdStartBypass\r\n");
        return TRUE;
    }
    else
    {
        hal_SysExitCriticalSection(status);
        raw_uart_log("mci_LcdStartBypass : Error LCD already bypassed");
        return FALSE;
    }
#else
	raw_uart_log("mci_LcdStartBypass ++\r\n");
	return TRUE;
#endif
}

// ============================================================================
// mci_LcdStopBypass
// ----------------------------------------------------------------------------
// ============================================================================
VOID mci_LcdStopBypass()
{
	raw_uart_log("mci_LcdStopBypass ++\r\n");

#if 0 //Jessica
    raw_uart_log("mci_LcdStopBypass");
    g_mciLcdBypassFunction=NULL;
    lcdd_EnableVidLayerMerge(FALSE);
#endif
}


// ============================================================================
// mci_LcdPowerOn
// ----------------------------------------------------------------------------
VOID mci_LcdPowerOn(BOOL on)
{
    raw_uart_log("mci_LcdPowerOn %d ++\r\n", on);
    // TODO
    // Currently not implemtented
    // Should use a pmd function
}

// ============================================================================
// mci_LcdScreenOn
// ----------------------------------------------------------------------------
VOID mci_LcdScreenOn(BOOL on)
{
    raw_uart_log("mci_LcdScreenOn %d ++\r\n", on);
    if ( on == TRUE )
    {
        //raw_uart_log("mci_LcdScreenOn: Turn On with brightness %d\r\n",g_mciLcdBrightnessLevel);
        ASRLCDD_SetBrightness(g_mciLcdBrightnessLevel);
    } 
    else 
    {
        raw_uart_log("mci_LcdScreenOn: Turn Off\r\n");
        ASRLCDD_SetBrightness(0);
    }
}

#if 0
// ============================================================================
// mci_LcdlayerMerge
// ----------------------------------------------------------------------------
VOID mci_LcdLayerMerge(UINT16* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
    LCDD_FBW_T frameBufferWin;
    UINT32 attempts = 0;

    if (!buffer)
    {
        raw_uart_log("mci_LcdLayerMerge buffer == 0");
    }
    else
    {
        raw_uart_log("mci_LcdLayerMerge %d %d %d %d",startx, starty, endx, endy);
        frameBufferWin.fb.buffer = buffer;
        frameBufferWin.fb.width = g_mciLcdScreenInfo.width;
        frameBufferWin.fb.height = g_mciLcdScreenInfo.height;

        frameBufferWin.roi.x=startx;
        frameBufferWin.roi.y=starty;
        frameBufferWin.roi.width=endx-startx+1;
        frameBufferWin.roi.height=endy-starty+1;

        while(ASRLCDD_LayerMerge(&frameBufferWin,startx,starty,TRUE) != LCDD_ERR_NO)
        {
            attempts++;
            if (attempts%1024)
            {
                raw_uart_log("mci_LcdLayerMerge Access Denied :%d!", attempts);
            }
            UOS_SleepTicks(64);
        }
    }
}
#endif

// ============================================================================
// mci_LcdBlockWrite
// ----------------------------------------------------------------------------
VOID mci_LcdBlockWrite(UINT16* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
    struct asrlcdd_framebuffer_window frameBufferWin;
    UINT32 attempts = 0;
	UINT32 offset = 0;
    //raw_uart_log("mci_LcdBlockWrite ++\r\n");

    if (g_mciLcdBypassFunction)
    {
        raw_uart_log("mci_LcdBlockWrite bypassed %d %d %d %d\r\n",startx, starty, endx, endy);
        g_mciLcdBypassFunction(buffer,startx, starty, endx, endy);
    }
    else
    {
        //raw_uart_log("mci_LcdBlockWrite %d %d %d %d\r\n",startx, starty, endx, endy);
        frameBufferWin.frame_info.pbuffer = buffer;
        frameBufferWin.frame_info.stride = g_mciLcdFBInfo.width;//g_mciLcdScreenInfo.width * 2;//(endx-startx+1) * 2;//
        frameBufferWin.frame_info.height = g_mciLcdFBInfo.height;//g_mciLcdScreenInfo.height;//endy-starty+1;//
		frameBufferWin.frame_info.bitdepth = g_mciLcdFBBitdepth;

        frameBufferWin.roi_info.startX=startx;
        frameBufferWin.roi_info.startY=starty;
        frameBufferWin.roi_info.width=endx-startx+1;
        frameBufferWin.roi_info.height=endy-starty+1;

        frameBufferWin.roi_info.startX = (frameBufferWin.roi_info.startX >> 3) << 3;
        frameBufferWin.roi_info.startY = (frameBufferWin.roi_info.startY >> 2) << 2;
        frameBufferWin.roi_info.width = (frameBufferWin.roi_info.width + 7)/8*8;
        frameBufferWin.roi_info.height = (frameBufferWin.roi_info.height + 3)/4*4;

        if(frameBufferWin.roi_info.width > g_mciLcdScreenInfo.width){
                frameBufferWin.roi_info.width = g_mciLcdScreenInfo.width;
        }

        if(frameBufferWin.roi_info.height > g_mciLcdScreenInfo.height){
                frameBufferWin.roi_info.height = g_mciLcdScreenInfo.height;
        }

		//FIXME-ASR
		//#if 0
		//offset = frameBufferWin.frame_info.stride * starty + startx *frameBufferWin.frame_info.bitdepth/8;
		//CacheCleanMemory( (void *)((char*)buffer + offset), frameBufferWin.frame_info.stride*frameBufferWin.roi_info.height*frameBufferWin.frame_info.bitdepth/8);
		//#else
		//CacheCleanMemory( (void *)buffer, g_mciLcdFBInfo.width*g_mciLcdFBInfo.height);
		//#endif
		
        while(ASRLCDD_Blit16(&frameBufferWin,frameBufferWin.roi_info.startX,frameBufferWin.roi_info.startY)!=0)
        {
            attempts++;
            if (attempts%1024)
            {
                raw_uart_log("mci_LcdBlockWrite Access Denied :%d!\r\n", attempts);
				return;
            }
            //UOS_SleepTicks(64);
        }
	
    }
}

// ============================================================================
// mci_LcdBlockWrite_sync
// ----------------------------------------------------------------------------
VOID mci_LcdBlockWrite_sync(UINT16* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
	struct asrlcdd_framebuffer_window frameBufferWin;
	UINT32 attempts = 0;
	UINT32 offset = 0;
	//UINT32 size = 0;
	//raw_uart_log("mci_LcdBlockWrite ++\r\n");

	if (g_mciLcdBypassFunction)
	{
		//raw_uart_log("mci_LcdBlockWrite bypassed %d %d %d %d\r\n",startx, starty, endx, endy);
		g_mciLcdBypassFunction(buffer,startx, starty, endx, endy);
	}
	else
	{
		//raw_uart_log("mci_LcdBlockWrite %d %d %d %d\r\n",startx, starty, endx, endy);
		frameBufferWin.frame_info.pbuffer = buffer;
		frameBufferWin.frame_info.stride = g_mciLcdFBInfo.width;//g_mciLcdScreenInfo.width * 2;//(endx-startx+1) * 2;//
		frameBufferWin.frame_info.height = g_mciLcdFBInfo.height;//g_mciLcdScreenInfo.height;//endy-starty+1;//
		frameBufferWin.frame_info.bitdepth = g_mciLcdFBBitdepth;

		frameBufferWin.roi_info.startX=startx;
		frameBufferWin.roi_info.startY=starty;
		frameBufferWin.roi_info.width=endx-startx+1;
		frameBufferWin.roi_info.height=endy-starty+1;
		//FIXME-ASR
	//#if 0
		//offset = frameBufferWin.frame_info.stride * starty + startx *frameBufferWin.frame_info.bitdepth/8;
		//CacheCleanMemory( (void *)((char*)buffer + offset), frameBufferWin.frame_info.stride*frameBufferWin.roi_info.height*frameBufferWin.frame_info.bitdepth/8);
	//#else
		//size = g_mciLcdFBInfo.width*g_mciLcdFBInfo.height;
		//size = ROUND_UP(size,32);
		//CacheCleanMemory( (void *)buffer, size);
	//#endif

		while(ASRLCDD_Blit16_sync(&frameBufferWin,startx,starty)!=0)
		{
			attempts++;
			if (attempts%1024)
			{
				raw_uart_log("mci_LcdBlockWrite Access Denied :%d!\r\n", attempts);
				return;
			}
			//UOS_SleepTicks(64);
		}
		
	}
}

#if defined (CONFIG_BOARD_CRANEM_EVB)
extern struct panel_spec *g_ppanel;
static VOID mci_MainLcdBlockWrite(UINT16* buffer, UINT16 startx, UINT16 starty, UINT16 endx, UINT16 endy)
{
	struct panel_spec *panel = g_ppanel;

	if (NULL == panel) {
		LCDLOGE(" %s: panel has not been inited!\r\n", __func__);
		return -1;
	}

	/* set the refresh area in panel
	 * here no need to do ¡°endx -1 and endy -1"
	 * */
	panel_before_refresh(panel, startx, starty, endx, endy);

	lcd_panel_refresh(panel, buffer);
}
#endif

VOID mci_Logo_LcdBlockWrite_sync(UINT8* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
	struct asrlcdd_framebuffer_window frameBufferWin;
	UINT32 attempts = 0;
	UINT32 offset = 0;
	//UINT32 size = 0;
	//raw_uart_log("mci_LcdBlockWrite ++\r\n");

#if defined (CONFIG_BOARD_CRANEM_EVB)
	mci_MainLcdBlockWrite(buffer, startx, starty, endx , endy);
#else
	if (g_mciLcdBypassFunction)
	{
		LCDLOGD("mci_Logo_LcdBlockWrite_sync bypassed %d %d %d %d\r\n",startx, starty, endx, endy);
		g_mciLcdBypassFunction((UINT16*)buffer,startx, starty, endx, endy);
	}
	else
	{
		//raw_uart_log("mci_LcdBlockWrite %d %d %d %d\r\n",startx, starty, endx, endy);
		//g_mciLcdFBInfo.width = 320 * 4;
		//g_mciLcdFBInfo.height = 320;
		frameBufferWin.frame_info.pbuffer = buffer;
		frameBufferWin.frame_info.stride = g_mciLcdFBInfo.width;//g_mciLcdScreenInfo.width * 2;//(endx-startx+1) * 2;//
		frameBufferWin.frame_info.height = g_mciLcdFBInfo.height;//g_mciLcdScreenInfo.height;//endy-starty+1;//
		frameBufferWin.frame_info.bitdepth = g_mciLcdFBBitdepth;

		frameBufferWin.roi_info.startX=startx;
		frameBufferWin.roi_info.startY=starty;
		frameBufferWin.roi_info.width=endx-startx+1;
		frameBufferWin.roi_info.height=endy-starty+1;
		//FIXME-ASR
	//#if 0
		//offset = frameBufferWin.frame_info.stride * starty + startx *frameBufferWin.frame_info.bitdepth/8;
		//CacheCleanMemory( (void *)((char*)buffer + offset), frameBufferWin.frame_info.stride*frameBufferWin.roi_info.height*frameBufferWin.frame_info.bitdepth/8);
	//#else
		//size = g_mciLcdFBInfo.width*g_mciLcdFBInfo.height;
		//size = ROUND_UP(size,32);
		//CacheCleanMemory( (void *)buffer, size);
	//#endif

		while(ASRLCDD_Logo_Blit16_sync(&frameBufferWin,startx,starty)!=0)
		{
			attempts++;
			if (attempts%1024)
			{
				LCDLOGD("mci_LcdBlockWrite Access Denied :%d!\r\n", attempts);
				return;
			}
			//UOS_SleepTicks(64);
		}

	}
#endif
}

VOID mci_ee_LcdBlockWrite_sync(UINT8* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
	struct asrlcdd_framebuffer_window frameBufferWin;
	UINT32 attempts = 0;
	UINT32 offset = 0;
	//UINT32 size = 0;
	//raw_uart_log("mci_LcdBlockWrite ++\r\n");
	
	if (g_mciLcdBypassFunction)
	{
		//raw_uart_log("mci_ee_LcdBlockWrite_sync bypassed %d %d %d %d\r\n",startx, starty, endx, endy);
		g_mciLcdBypassFunction((UINT16*)buffer,startx, starty, endx, endy);
	}
	else
	{
		//raw_uart_log("mci_LcdBlockWrite %d %d %d %d\r\n",startx, starty, endx, endy);
		//g_mciLcdFBInfo.width = 320 * 4;
		//g_mciLcdFBInfo.height = 320;
		frameBufferWin.frame_info.pbuffer = buffer;
		frameBufferWin.frame_info.stride = g_mciLcdFBInfo.width;//g_mciLcdScreenInfo.width * 2;//(endx-startx+1) * 2;//
		frameBufferWin.frame_info.height = g_mciLcdFBInfo.height;//g_mciLcdScreenInfo.height;//endy-starty+1;//
		frameBufferWin.frame_info.bitdepth = g_mciLcdFBBitdepth;
	
		frameBufferWin.roi_info.startX=startx;
		frameBufferWin.roi_info.startY=starty;
		frameBufferWin.roi_info.width=endx-startx+1;
		frameBufferWin.roi_info.height=endy-starty+1;
		//FIXME-ASR
	//#if 0
		//offset = frameBufferWin.frame_info.stride * starty + startx *frameBufferWin.frame_info.bitdepth/8;
		//CacheCleanMemory( (void *)((char*)buffer + offset), frameBufferWin.frame_info.stride*frameBufferWin.roi_info.height*frameBufferWin.frame_info.bitdepth/8);
	//#else
		//size = g_mciLcdFBInfo.width*g_mciLcdFBInfo.height;
		//size = ROUND_UP(size, 32);
		//CacheCleanMemory( (void *)buffer, size);
	//#endif

		while(ASRLCDD_Assert_Blit16_sync(&frameBufferWin,startx,starty)!=0)
		{
			attempts++;
			if (attempts%1024)
			{
				raw_uart_log("mci_LcdBlockWrite Access Denied :%d!\r\n", attempts);
				return;
			}
			//UOS_SleepTicks(64);
		}
		
	}
}


VOID mci_LcdLayerMerge(UINT16* buffer, UINT16 startx,UINT16 starty,UINT16 endx,UINT16 endy)
{
    raw_uart_log("mci_LcdLayerMerge ++\r\n");
}

// ============================================================================
// mci_LcdGetDimension
// ----------------------------------------------------------------------------
VOID mci_LcdGetDimension(UINT16 *out_LCD_width,UINT16 *out_LCD_height)
{
    raw_uart_log("mci_LcdGetDimension ++");
    *out_LCD_width=g_mciLcdScreenInfo.width;
    *out_LCD_height=g_mciLcdScreenInfo.height;
}

// ============================================================================
// mci_LcdSleep
// ----------------------------------------------------------------------------
VOID mci_LcdSleep(VOID)
{
    BOOL orig_status = g_mciLcdBackLightOn;

    ASRLCDD_SetBrightness(0);
    /*
    * the variable g_mciLcdBackLightOn MUST be
    * set AFTER calling ASRLCDD_SetBrightness()
    */
    g_mciLcdBackLightOn = FALSE;

    raw_uart_log("mci_LcdSleep, backlight flag:[%d,%d]\n", orig_status, g_mciLcdBackLightOn);
}

// ============================================================================
// mci_LcdWakeup
// ----------------------------------------------------------------------------
VOID mci_LcdWakeup(VOID)
{
    BOOL orig_status = g_mciLcdBackLightOn;

    if(g_mciLcdBackLightOn == FALSE)
        ASRLCDD_WakeUp();
    else{
        ASRLCDD_SetBrightness(g_mciLcdBrightnessLevel);
        g_mciLcdBackLightOn = TRUE;
    }

    raw_uart_log("mci_LcdWakeup, backlight flag:[%d,%d]\n", orig_status, g_mciLcdBackLightOn);
}

// ============================================================================
// mci_LcdPartialOn
// ----------------------------------------------------------------------------
VOID mci_LcdPartialOn(UINT16 startLine,UINT16 endLine)
{
    raw_uart_log("mci_LcdPartialOn %d %d ++\r\n",startLine, endLine);
}

// ============================================================================
// mci_LcdPartialOff
// ----------------------------------------------------------------------------
VOID mci_LcdPartialOff(VOID)
{
    raw_uart_log("mci_LcdPartialOff ++\r\n");
}

// ============================================================================
// mci_LcdClearScreen
// ----------------------------------------------------------------------------
VOID mci_LcdClearScreen(UINT16 background)
{
    struct asrlcdd_roi_info roi;

    raw_uart_log("mci_LcdClearScreen %d ++\r\n",background);
    roi.startX=0;
    roi.startY=0;
    roi.width=g_mciLcdScreenInfo.width;
    roi.height=g_mciLcdScreenInfo.height;

    ASRLCDD_FillRect16(&roi, background);
}

// ============================================================================
// mci_LcdGetParam
// ----------------------------------------------------------------------------
UINT8 mci_LcdGetParam(MCI_LCD_PARAM_T param_id)
{
    raw_uart_log("mci_LcdGetParam %d ++\r\n");
    switch(param_id)
    {
        // TODO implement other parameters
        case MCI_LCD_BIAS:
        case MCI_LCD_CONTRAST:
        case MCI_LCD_LINE_RATE:
        case MCI_LCD_TEMP_COMP:
            return 0;
            //break;
        case MCI_LCD_BRIGHTNESS:
            return g_mciLcdBrightnessLevel;
            //break;
        default:
            break;
    }
    return 0;
}

// ============================================================================
// mci_LcdSetBrightness
// ----------------------------------------------------------------------------
VOID mci_LcdSetBrightness(UINT8 level)
{   
    raw_uart_log("mci_LcdSetBrightness %d++\r\n", level);
    g_mciLcdBrightnessLevel = level;
    ASRLCDD_SetBrightness(g_mciLcdBrightnessLevel);
}
VOID mci_LcdSetBrightnessLevel(UINT8 level)
{   
    //raw_uart_log("mci_LcdSetBrightnessLevel %d++\r\n", level);
    g_mciLcdBrightnessLevel = level;
}
VOID mci_LcdSetBrightnessExt(UINT8 level)
{   
    //raw_uart_log("mci_LcdSetBrightnessExt %d++\r\n", level);
    ASRLCDD_SetBrightness(level);
}

VOID mci_LcdTurnOffBacklight(void)
{   
    backlight_set_brightness(0);
}

// ============================================================================
// mci_LcdSetBias
// ----------------------------------------------------------------------------
VOID mci_LcdSetBias(UINT8 bias)
{
    raw_uart_log("mci_LcdSetBias %d++\r\n", bias);
}

// ============================================================================
// mci_LcdSetContrast
// ----------------------------------------------------------------------------
VOID mci_LcdSetContrast(UINT8 contrast)
{
    raw_uart_log("mci_LcdSetContrast %d++\r\n",contrast);
}

// ============================================================================
// mci_LcdSetLineRate
// ----------------------------------------------------------------------------
VOID mci_LcdSetLineRate(UINT8 linerate)
{
    raw_uart_log("mci_LcdSetLineRate %d++\r\n",linerate);
}

// ============================================================================
// mci_LcdSetTempComp
// ----------------------------------------------------------------------------
VOID mci_LcdSetTempComp(UINT8 compensate)
{
    raw_uart_log("mci_LcdSetTempComp %d++\r\n",compensate);
}

BOOL mci_LcdIsActive(void)
{
    return ASRLCDD_LcdIsActive();
}

VOID mci_Read_Panel_ID(void)
{
	ASRLCDD_Read_Panel_ID();
}
