#ifndef _NL_API_CAMREA_H_
#define _NL_API_CAMREA_H_

typedef struct cam_dev_tag
{
    char *pNamestr;
    uint32_t img_width;
    uint32_t img_height;
    uint32_t nPixcels;
} CAM_DEV_T, *CAM_DEV_T_PTR;

typedef struct
{
    CAM_DEV_T CamDev;
    lcdSpec_t lcddev;
    osiThread_t *camTask;
    uint8_t Decodestat;
    bool Openstat;
    bool MemoryState;
    bool gCamPowerOnFlag;
    bool issnapshot;
    uint32_t height;
    uint32_t width;
    uint32_t sweepsize;
    uint32_t times;
} camastae_t;

/**
 * @brief    CAMERA的初始化函数
 *
 * @return  0 –成功  -2 表示CAMERA已经初始化  -4 表示CAMERA初始化失败  -5 表示CAMERA上电失败
 */
INT32 nl_camera_init(void);

/**
 * @brief    获取CAMERA信息函数
 * 
 * @param < pstCamDevice >
 * CAMERA信息指针，具体定义如下：
 * char *pNamestr：CAMERA 名字；
 * uint32_t img_width：
 * CAMERA 图像宽度；
 * uint32_t img_height：
 * CAMERA图像高度；
 * uint32_t nPixcels：CAMERA图像所占空间（即长*宽*2）；
 *
 * @return  0 –成功  -3 表示CAMERA未初始化  -6 表示参数指针为空  -1 表示获取信息失败
 */
INT32 nl_camera_GetSensorInfo(CAM_DEV_T * pstCamDevice);

/**
 * @brief    CAMERA的去初始化函数
 *
 * @return  0 –成功  -3 表示CAMERA未初始化
 */
INT32 nl_camera_deinit(void);

/**
 * @brief    从摄像头预览数据中提取二维码或者条形码灰度信息，输出解码信息和信息长度。返回码制度类型：
 * UPCA,       1,
 * C39,        2,
 * C128,       3,
 * ITF25,      4,
 * C93,        5,
 * PDF417,     6,
 * QR,         7,
 * DATAMATRIX, 8,
 * CBAR,       9,
 * UPCE,      10,
 * EAN8,      11,
 * EAN13,     12,
 * 
 * @param <cam>:实例化camera，获取camera基本信息
 * @param <pFrame>，camera预览数据
 * @param <pDatabuf>，用户传入参数，用来保存从预览数据中提取的灰度信息
 * @param <pResult>，传出参数，解码信息
 * @param <rReslen>，传出参数，解码信息长度
 * @param <Type>，传出参数,码制类型
 *
 * @return  false - 解码失败  ture - 解码成功
 */
bool nl_sweep_code(camastae_t *cam, uint16_t *pFrame, uint8_t *pDatabuf, uint8_t *pResult, uint32_t *pReslen, int *type);

/**
 * @brief    开启CAMERA 的preview模式
 *
 * @return  0 –成功  -3 表示CAMERA未初始化  -1 表示获取信息失败
 */
INT32 nl_camera_StartPreview(void);

/**
 * @brief    关闭CAMERA 的preview模式
 *
 * @return  0 –成功  -3 表示CAMERA未初始化  -1 表示获取信息失败
 */
INT32 nl_camera_StopPreview(void);

/**
 * @brief    获取preview模式的帧数据，用于实时显示
 *
 * @param < pPreviewBuf >：preview模式下，获取的图像数据的指针的地址
 *
 * @return  0 –成功  -3 表示CAMERA未初始化  -6 表示参数指针为空  -1 表示获取信息失败
 */
INT32 nl_camera_GetPreviewBuf(UINT16 * * pPreviewBuf);

/**
 * @brief    当获取到一帧preview数据后，通知CAMERA获取下一帧preview数据
 *
 * @param < pPreviewBuf >：指向preview模式下数据的指针
 *
 * @return  0 –成功  -3 表示CAMERA未初始化  -6 表示参数指针为空
 */
INT32 nl_camera_PrevNotify(UINT16 * pPreviewBuf);

#endif