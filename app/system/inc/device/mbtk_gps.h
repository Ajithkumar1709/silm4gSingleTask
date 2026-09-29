#ifndef __MBTK_GPS_H__
#define __MBTK_GPS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////gps 相关
 typedef struct
{
	uint8_t num;		
	//卫星编号
	uint8_t eledeg;	
	//卫星仰角
	uint16_t azideg;	
	//卫星方位角
	uint8_t sn;		
	//信噪比		   
}nmea_satellitemsg;
//北斗 NMEA-0183协议重要参数结构体定义 
//卫星信息
 typedef struct
{
	 uint8_t beidou_num;		
	 //卫星编号
	uint8_t beidou_eledeg;	
	 //卫星仰角
	uint16_t beidou_azideg;	
	 //卫星方位角
	uint8_t beidou_sn;		
	 //信噪比		   
}beidou_nmea_satellitemsg;

//UTC时间信息
 typedef struct
{
	uint8_t year;	//年份
	uint8_t month;	//月份
	uint8_t date;	//日期
	uint8_t hour; 	//小时
	uint8_t min; 	//分钟
	uint8_t sec; 	//秒钟
}nmea_utc_time;

 typedef struct nmea_msg
{
	uint8_t svnum;					
	//可见GPS卫星数
	uint8_t beidou_svnum;			
	//可见GPS卫星数
	nmea_satellitemsg slmsg[12];		
	//最多12颗GPS卫星
	beidou_nmea_satellitemsg beidou_slmsg[12];		
	//暂且算最多12颗北斗卫星
	nmea_utc_time utc;			
	//UTC时间
	uint8_t valid_states;
	//状态
	uint32_t latitude;				
	//纬度 分扩大100000倍,实际要除以100000
	uint8_t nshemi;					
	//北纬/南纬,N:北纬;S:南纬				  
	uint32_t longitude;			   
	//经度 分扩大100000倍,实际要除以100000
	uint8_t ewhemi;					
	//东经/西经,E:东经;W:西经
	uint8_t gpssta;					
	//GPS状态:0,未定位;1,非差分定位;2,差分定位;6,正在估算.				  
	uint8_t posslnum;				
	//用于定位的卫星数,0~12.(GPS和BD一共的卫星数)
	uint8_t possl[12];				
	//用于定位的gps卫星编号
	uint8_t posslbd[12];				
	//用于定位的BD卫星编号	
	uint8_t fixmode;					
	//定位类型:1,没有定位;2,2D定位;3,3D定位
	uint16_t pdop;					
	//位置精度因子 0~500,对应实际值0~50.0
	uint16_t hdop;					
	//水平精度因子 0~500,对应实际值0~50.0
	uint16_t vdop;					
	//垂直精度因子 0~500,对应实际值0~50.0 
	uint16_t azi;
	//方位角,放大了100倍,实际除以100
	int altitude;			 	
	//海拔高度,放大了10倍,实际除以10.单位:0.1m	 
	uint32_t speed;					
	//地面速率,放大了1000倍,实际除以1000.单位:0.001公里/小时
	uint16_t cog;
	//地面方位,放大了100倍,实际除以100,对应实际值000.00~359.99
}nmea_msg;
 //m^n函数
 //返回值:m^n次方.

//asr gps status
#define ASR_GPS_STATE_POWEROFF                 0
#define ASR_GPS_STATE_ACTIVE                   1
#define ASR_GPS_STATE_SLEEP                    2
#define ASR_GPS_STATE_SLEEPING                 3
#define ASR_GPS_STATE_POWEROFFING              4

 
 typedef enum
 {
	 MBTK_GNSS_POWEROFF = 0,
	 MBTK_GNSS_POWERON,
	 MBTK_GNSS_RESET,
//	 MBTK_GNSS_FW_DOWNLOAD,
//	 MBTK_GNSS_POWERON_NONEMA,
 }Mbtk_gnss_oper_enum;

 typedef enum 
 {
	 mbtk_gps_err = -1,
	 mbtk_gps_success = 0
 }mbtk_gps_return_enum;

 

  typedef enum
  {
	  MBTK_GNSS_CMD_SOFTREST = 0,
	  MBTK_GNSS_CMD_COLDSTART,     //冷启
	  MBTK_GNSS_CMD_WARMSTART,     //温启
      MBTK_GNSS_CMD_HOTSTART,     //热启
      MBTK_GNSS_CMD_SOFTSTOP,
      MBTK_GNSS_CMD_SOFTSTART,
	  MBTK_GNSS_CMD_PARSE_BY_USER,  //nmea数据如果设置了ol_gps_set_gps_nmea_cb，可以设置此项，此项可以关闭内部解析nmea数据，也就是导致ol_get_gps_info数据不会再更新
	  MBTK_GNSS_CMD_PARSE_BY_M,  //模块解析nmea数据，和MBTK_GNSS_CMD_PARSE_BY_USER相反
	  MBTK_GNSS_CMD_SLEEP,  //gps进入睡眠
	  MBTK_GNSS_CMD_WAKEUP,  //gps唤醒
      MBTK_GNSS_CMD_MAX
  }Mbtk_gnss_cmd_enum;



typedef struct
{
	nmea_msg  nmea;
	int state;
}mbtk_gps_info;

 typedef void(*mbtk_gps_nmea)(char *nmea);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_gps_info
 * DESCRIPTION 
 *  		获取gps信息的结构体指针
 * RETURN VALUES
			mbtk_gps_info *      
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_gps_info *ol_get_gps_info(void);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_gps_power
 * DESCRIPTION 
 *  		打开或关闭gps，   Mbtk_gnss_oper_enum 类型，仅支持on和off
  * PARAMETERS 
 *		on_off[IN]                  
 * RETURN VALUES
			mbtk_gps_info *      
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_gps_power(int on_off);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_gps_operation
 * DESCRIPTION 
 *  		打开gps
 * PARAMETERS 
 *		cmd[IN]        Mbtk_gnss_cmd_enum  定义类型，可用于设备冷启热启等
 * RETURN VALUES
			mbtk_gps_info *      
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_gps_operation(int cmd);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_gps_set_gps_nmea_cb
 * DESCRIPTION 
 *  		注册nmea数据回调，注册后，nmea数据会从cb接口输出，一次输出一行，回调接口内不能阻塞，否则会影响后续上报
 * RETURN VALUES
			int   0 成功
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_gps_set_gps_nmea_cb(mbtk_gps_nmea nmea_cb);

extern int ol_gps_get_status(void);

 /*****************************************************************************
 *
 * FUNCTIO 
 *		ol_gps_agps_open
 * DESCRIPTION 
 *  	get AGPS data from the AGNSS server.
 * PARAMETERS 
 *		None
 * RETURN VALUES
 *		0 : AGPS ok
 *   -2: GNSS not active
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_gps_agps_open(void);

#ifdef __cplusplus
}
#endif

#endif

