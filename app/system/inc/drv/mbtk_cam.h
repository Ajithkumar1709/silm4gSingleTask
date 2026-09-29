#ifndef __MBTK_CAM_H__
#define __MBTK_CAM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"

/*****************************************************************************
 * FUNCTION
 *  ol_camera_start
 * DESCRIPTION
 *  This API is to power on camera and start preview
 *
 * PARAMETERS
 *  width          : [IN]  camera preivew frame width. 
 *  height         : [IN]  camera preivew frame height.
 * RETURN VALUES
 *   -1: fail  
 *    0: success
 *
 *****************************************************************************/
extern int ol_camera_start(uint16_t width, uint16_t height);

/*****************************************************************************
 * FUNCTION
 *  ol_camera_stop
 * DESCRIPTION
 *  This API is to stop preview and power off
 *
 * PARAMETERS

 * RETURN VALUES
 *   -1: fail  
 *    0: success
 *
 *****************************************************************************/
extern int ol_camera_stop(void );

/*****************************************************************************
 * FUNCTION
 *  ol_camera_preview
 * DESCRIPTION
 *  This API is to start camera 
 *
 * PARAMETERS
 * RETURN VALUES
 *  0: no	
 *  1: yes
 *****************************************************************************/
extern int ol_camera_preview(void);

/*****************************************************************************
 * FUNCTION
 *  ol_camera_get_yuv
 * DESCRIPTION
 *  This API is to get yuv buffer from camera isq buffer with width and height 
 *
 * PARAMETERS
 *  yuv420_buff      : [OUT]  yuv buffer that want get
 
 * RETURN VALUES
 *  0: no	
 *  1: yes
 *
 *****************************************************************************/
extern int ol_camera_get_yuv(uint8_t *yuv420_buff);


/*****************************************************************************
 * FUNCTION
 *  ol_camera_get_rgb565
 * DESCRIPTION
 *  This API is to get rgb565 buffer from camera isq buffer
 *
 * PARAMETERS
 *  rgb565_buff         : [OUT]  rgb565 buffer that want get, with the size set for ol_camera_start set (width, heigth)
 * RETURN VALUES
 *  0: no	
 *  1: yes
 *****************************************************************************/
extern int ol_camera_get_rgb565(uint8_t *rgb565_buff);

/*****************************************************************************
 * FUNCTION
 *  ol_camera_buffer_consumer
 * DESCRIPTION
 *  This API is to notify camera to update old buffer
 *
 * PARAMETERS

 * RETURN VALUES
 *
 *****************************************************************************/
extern void ol_camera_buffer_consumer(void);


/*****************************************************************************
 * FUNCTION
 *  ol_camera_get_on_flag
 * DESCRIPTION
 *  This API is to check camera is power on or off
 *
 * PARAMETERS
 * RETURN VALUES
 *   1: camera on  
 *   0: camera off
 *
 *****************************************************************************/
extern int ol_camera_get_on_flag(void);

#ifdef __cplusplus
}
#endif

#endif

