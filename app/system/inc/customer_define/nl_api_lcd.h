#ifndef _NL_API_LCD_H_
#define _NL_API_LCD_H_



typedef struct
{
    uint16_t *buffer;
    ///  x coordinate of the layer. If only use one layer,normal set 0.
    uint16_t region_x;
    ///  y coordinate of the layer. If only use one layer,normal set 0.
    uint16_t region_y;
    ///the width of after convert. if don't need rotation and zoom ,set to  roginal width.
    uint16_t width;
    ///the height of after convert. if don't need rotation and zoom ,set to  roginal height.
    uint16_t height;
    ///image buffer width.
    uint16_t widthOriginal;
    uint16_t colorFormat;
    ///0 no rotation. 1 rotate 90 degree.
    uint16_t rotation;
    /// enable the color mask function.
    bool keyMaskEnable;
    /// mask color value
    uint16_t maskColor;
} lcdFrameBuffer_t;

typedef struct
{
    /// x coordinate of the top left corner of the lcd.
    uint16_t x;
    /// y coordinate of the top left corner of the lcd.
    uint16_t y;
    /// width of the lcd dislay area.
    uint16_t width;
    /// height of the lcd display area.
    uint16_t height;

} lcdDisplay_t;

typedef enum
{
    LCD_DIRECT_NORMAL = 0x00,
    LCD_DIRECT_ROT_90, // Rotation 90
    LCD_DIRECT_ROT_180, // Rotation 180
    LCD_DIRECT_NORMAL2,
    LCD_DIRECT_NORMAL2_ROT_90,
    LCD_DIRECT_NORMAL2_ROT_180,
    LCD_DIRECT_ROT_270,  // Rotation 270
    LCD_DIRECT_NORMAL2_ROT_270,
} lcdDirect_t;

/**
 * @brief    LCD的初始化函数
 * 
 * @return  0 –成功  -2 表示LCD已经初始化  -3 表示互斥信号量创建失败  -4 获取LCD信息失败  -5 获取LCD操作函数失败
 */
INT32 nl_lcd_init(void);

/**
 * @brief    旋转和缩放摄像头图像
 *
 * @param < width >：摄像头图像旋转90度后的宽度
 * @param < height >：摄像头图像旋转90度后的高度
 * @param < imageBufWidth >：摄像头图像原始图像的宽度（即旋转前的宽度）
 * 
 * @return  0 表示成功；-10 表示参数非法；-1 表示LCD未初始化或者设置失败。
 */
INT32 nl_lcd_Setvideosize(uint32_t width, uint32_t height, uint32_t imageBufWidth);

/**
 * @brief    发送一帧数据到lcd显示，目前LCD的显示分辨率为240*320
 *
 * @param <pstFrame>：帧数据的指针：
 * uint16_t *buffer：帧数据的地址；
 * uint16_t region_x：送显图像区域的起点x坐标；
 * uint16_t region_y：送显图像区域的起点y坐标；
 * uint16_t width：显示后图像的宽度；
 * uint16_t height：显示后图像的高度；
 * uint16_t widthOriginal：原始图像的宽度；
 * uint16_t colorFormat：图像的格式，目前支持RGB565 和 YUV422 格式的，包括UYVY和YUYV；
 * uint16_t rotation：旋转方向：0：不旋转，1：旋转90度；
 * bool keyMaskEnable：是否使能mask颜色功能：true：使能，false：禁止；
 * uint16_t maskColor：mask的颜色值。
 * 
 * @param < pstWindow >：显示区域：
 * uint16_t x：显示区域起点的x坐标；
 * uint16_t y：显示区域起点的y坐标；
 * uint16_t width：显示区域的宽度；
 * uint16_t height：显示区域的高度；
 * 
 * @param < pstFrame >：帧数据的指针，具体定义参考nl_lcd_FrameTransfer函数的入参定义。
 * 
 * @return  0 表示成功，  -10 表示参数为空，  -6 表示图像格式错误，  -7 表示帧数据地址为空，  -8 表示数据块配置错误，  -9 表示配置显示区域错误，  -1 表示LCD未初始化。
 */
INT32 nl_lcd_FrameTransfer(const lcdFrameBuffer_t * pstFrame, const lcdDisplay_t * pstWindow);

/**
 * @brief    设置LCD/SD/SIM2/CAMERA(LG项目)供电的电压
 *
 * @param <pmu_type>设置ldo要调整的类型；
 * 0：LCD的ldo
 * 1：SD的ldo
 * 2: SIM2的ldo
 * 3: camera的ldo(目前仅支持LG项目)
 * 
 * @param <level>要设置的电压等级；
 * 0:1.8V
 * 1:3.2V
 * 
 * @return  1：成功  -1：失败
 */
INT32 nl_hal_pmu_setlevel(UINT8 pmu_type,UINT8 level);

/**
 * @brief    用于设置屏的刷新方向
 *
 * @param < direct_type >图像刷新方向设置：
 * 0：默认模式，竖屏，起始点在左上角，终点在右下角。
 * 1：横屏（在0的状态下逆时针旋转90度），起始点在左上角，终点在右下角。
 * 2：竖屏（在0的状态下逆时针旋转180度），起始点在左上角，终点在右下角。
 * 3：竖屏，起始点在左下角，终点在右上角。
 * 4：横屏（在3的状态下逆时针旋转90度），起始点在左下角，终点在右上角。
 * 5：竖屏（在3的状态下逆时针旋转180度），起始点在左下角，终点在右上角。
 * 6：横屏（在0的状态下逆时针旋转270度），起始点在左上角，终点在右下角。
 * 7：横屏（在3的状态下逆时针旋转270度），起始点在左下角，终点在右上角。
 * 
 * @return  0：成功  -11 表示配置失败，-1 表示LCD未初始化。
 */
INT32 nl_lcd_SetBrushDirection(lcdDirect_t direct_type);

/**
 * @brief    给一个区域填充一种颜色
 *
 * @param < pstWindow >：显示区域，具体定义参考nl_lcd_FrameTransfer函数参数定义；
 * @param < ulBgcolor >：颜色值
 * 
 * @return  0 表示成功，-10 表示参数为空或区域坐标x、y不合法。-9 表示配置显示区域错误，-1 表示LCD未初始化。
 */
INT32 nl_lcd_FillRect(const lcdDisplay_t * pstWindow, UINT16 ulBgcolor);

/**
 * @brief    显示单个像素，与nl_lcd_FillRect函数配合使用，先刷背景色，然后在上面画点。
 *
 * @param < ulx >：显示像素的x坐标；
 * @param < uly >：显示像素的y坐标；
 * @param < ulcolor >：颜色值
 * 
 * @return  0 表示成功，-10 表示参数为空或x、y坐标不合法。-9 表示配置显示区域错误，-1 表示LCD未初始化。
 */
INT32 nl_lcd_SetPixel(UINT16 ulx, UINT16 uly, UINT16 ulcolor);

/**
 * @brief    从起始点到终点画一条线，与nl_lcd_FillRect函数配合使用，先刷背景色，然后在上面画线。
 *
 * @param < ulx >：< ulSx >：起始点x坐标；
 * @param < ulSy >：起始点y坐标；
 * @param < ulEx >：终点x坐标；
 * @param < ulExy>：终点y坐标；
 * @param < ulColor >：线条颜色值；
 * 
 * @return  0 表示成功，-10 表示参数为空或x、y坐标不合法。-9 表示配置显示区域错误，-1 表示LCD未初始化。
 */
INT32 nl_lcd_DrawLine(UINT16 ulSx, UINT16 ulSy, UINT16 ulEx, UINT16 ulEy, UINT16 ulColor);

/**
 * @brief    Lcd 初始化完成后，用于获取lcd的宽度和高度像素数。
 *
 * @param < puldevid >：获取的LCD 的设备ID；
 * @param < pulwidth >：获取的LCD的宽度的像素数
 * @param < pulheight >：获取的LCD的高度的像素数
 * 
 * @return  0 表示成功；-10 表示参数为空；-1 表示LCD未初始化。
 */
INT32 nl_lcd_Getinfo(uint32_t * puldevid, uint32_t * pulwidth, uint32_t * pulheight);

/**
 * @brief    LCD睡眠/唤醒函数
 *
 * @param <mode>true： LCD进入睡眠模式；false：LCD退出睡眠模式
 * 
 * @return  0 表示成功；-1 表示LCD未初始化。
 */
INT32 nl_lcd_Sleep(BOOL mode);

/**
 * @brief    LCD的去初始化函数。
 *
 * @return  0 表示成功；-1 表示LCD未初始化。
 */
INT32 nl_lcd_deinit(void);

#endif