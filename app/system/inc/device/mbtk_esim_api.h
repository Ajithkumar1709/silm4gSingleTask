#ifndef __MBTK_ESIM_API_H
#define __MBTK_ESIM_API_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESIM_MSG_CHIP_INFO = 1,
    ESIM_MSG_CHIP_DEFAULTSMDP,
    ESIM_MSG_CHIP_PURGE,
    ESIM_MSG_PROFILE_LIST,
    ESIM_MSG_PROFILE_NICKNAME,
    ESIM_MSG_PROFILE_ENABLE,
    ESIM_MSG_PROFILE_DISABLE,
    ESIM_MSG_PROFILE_DELETE,
    ESIM_MSG_PROFILE_DOWNLOAD,
    ESIM_MSG_PROFILE_DISCOVERY,
    ESIM_MSG_NOTIFICATION_LIST,
    ESIM_MSG_NOTIFICATION_PROCESS,
    ESIM_MSG_NOTIFICATION_REMOVE,

    ESIM_MSG_TYPE_ENUM_32_BIT = 0x7FFFFFFF
}EsimMessageType_t;


typedef enum {
    MBTK_ESIM_PROFILE_OPT_S = 1,    //SM-DP+ server, optional, if not provided, it will try to read the default sm-dp+ attribute.
    MBTK_ESIM_PROFILE_OPT_M,        //Matching ID, activation code,optional
    MBTK_ESIM_PROFILE_OPT_C,        //Confirmation Code,optional
    MBTK_ESIM_PROFILE_OPT_I,        //The IMEI of the device to which Profile is to be downloaded,optional.
    MBTK_ESIM_PROFILE_OPT_A,        //LPA qrcode activation code string, e.g: LPA:1$<sm-dp+ domain>$<matching id>, if provided this option takes precedence over the OPT_S and OPT_M options, optional.
    MBTK_ESIM_PROFILE_OPT_P,        //Interactive preview mode, optional.
    
    MBTK_ESIM_PROFILE_OPT_END = 0x7FFFFFFF
}Esim_Profile_Options;

typedef struct {
    Esim_Profile_Options opt_int;
    char *opt_string;
}EsimProfileOptList_t;

typedef void (*EsimMessageCallback)(EsimMessageType_t msg_type, const char *data, int data_len);


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_set_location
 * DESCRIPTION 
 *          This API is to set the sim0 or sim1.(single sim don't need) 
 * PARAMETERS 
 *        location        [IN]: sim0 or sim1
 * RETURN VALUES
 *          NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_esim_set_location(int location);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_chip_info
 * DESCRIPTION 
 *          This API is view information about your eUICC card itself. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error_callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_chip_info(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_chip_defaultsmdp
 * DESCRIPTION 
 *          This API is to modify the default SM-DP+ server address of your eUICC card.
 * PARAMETERS 
 *        defaultsmdp       [IN]:modify the default SM-DP+ server address of your eUICC card
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_chip_defaultsmdp(const char *defaultsmdp);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_chip_purge
 * DESCRIPTION 
 *          This API is to reset the eUICC and will clear all profiles. Use with caution! 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_chip_purge(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_list
 * DESCRIPTION 
 *          This API is to enumerates your eUICC Profile
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_list(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_nickname
 * DESCRIPTION 
 *          This API is to enumerates your eUICC Profile
 * PARAMETERS 
 *        iccid       [IN]:ICCID of Profile
 *        alias       [IN]:alias
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_nickname(const char *iccid, const char *alias);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_enable
 * DESCRIPTION 
 *          This API is to enables the specified Profile. The RefreshFlag status is enabled by default and can be omitted.
 * PARAMETERS 
 *        iccid       [IN]:ICCID or AID of Profile
 *        refreshflag [IN]:<0/1>
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_enable(const char *iccid_or_aid, int refreshflag);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_disable
 * DESCRIPTION 
 *          This API is to disables the specified Profile. The RefreshFlag state is enabled by default and can be omitted.
 * PARAMETERS 
 *        iccid       [IN]:ICCID or AID of Profile
 *        refreshflag [IN]:<0/1>
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_disable(const char *iccid_or_aid,int refreshflag);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_delete
 * DESCRIPTION 
 *          This API is to deletes the specified Profile.
 * PARAMETERS 
 *        iccid_or_aid       [IN]:ICCID or AID of Profile
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_delete(const char *iccid_or_aid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_download
 * DESCRIPTION 
 *          This API is to download profile from SM-DP server.
 * PARAMETERS 
 *        opt_list    [IN]:download options and parameters
 *        numbers     [IN]:size of opt_list
 *        timeout     [IN]:http timeout
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_download(EsimProfileOptList_t *opt_list, unsigned int numbers, unsigned int timeout);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_discovery
 * DESCRIPTION 
 *          This API is to detect available profile registered on SM-DS server.
 * PARAMETERS 
 *        opt_list    [IN]:discovery options and parameters
 *        numbers     [IN]:size of opt_list
 *        timeout     [IN]:http timeout
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_profile_discovery(EsimProfileOptList_t *opt_list, unsigned int numbers, unsigned int timeout);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_profile_read_new_iccid
 * DESCRIPTION 
 *          This API is to read the latest downloaded profile's ICCID.
 * PARAMETERS 
 *        iccid       [IN]:ICCID of Profile
 * RETURN VALUES
 *          NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_esim_profile_read_new_iccid(char *iccid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_notification_list
 * DESCRIPTION 
 *          This API is to enumerates your eUICC pending Notification list.
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_notification_list(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_notification_process
 * DESCRIPTION 
 *          This API is to send notification.
 * PARAMETERS 
 *        remove_flag  [IN]:notification of decision to remove
 *        all_flag     [IN]:send all notification
 *        sequence_id  [IN]:list of specified sequence IDs
 *        numbers      [IN]:size of sequence IDs
 *        timeout      [IN]:http timeout
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_notification_process(int remove_flag, int all_flag, unsigned long *sequence_id, unsigned int numbers, unsigned int timeout);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_notification_remove
 * DESCRIPTION 
 *          This API is to remove notification.
 * PARAMETERS 
 *        all_flag     [IN]:remove all notification
 *        sequence_id  [IN]:list of specified sequence IDs
 *        numbers      [IN]:size of sequence IDs
 * RETURN VALUES
 *        =0    : successful
 *        =-1   : error ,see the error callback
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_esim_notification_remove(int all_flag, unsigned long *sequence_id, unsigned int numbers);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_set_info_callback
 * DESCRIPTION 
 *          This API is to set results or progress message callback.
 * PARAMETERS 
 *        callback     [IN]:results or progress message callback
 * RETURN VALUES
 *          NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_esim_set_info_callback(EsimMessageCallback callback);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_esim_notification_remove
 * DESCRIPTION 
 *          This API is to set error message callback.
 * PARAMETERS 
 *        callback     [IN]:error message callback
 * RETURN VALUES
 *          NONE
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_esim_set_error_callback(EsimMessageCallback callback);

#ifdef __cplusplus
}
#endif


#endif
