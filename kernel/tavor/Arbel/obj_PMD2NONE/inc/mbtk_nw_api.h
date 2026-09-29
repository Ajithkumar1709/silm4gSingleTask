#ifndef _MBTK_NW_API_H_
#define _MBTK_NW_API_H_


/******************************
*Network Config info
*AT*BAND?
******************************/
typedef enum 
{
    MBTK_NW_GSM_MODE  = 0,	/**< GSM */
    MBTK_NW_UMTS_MODE,    	/**< UMTS */
    
    MBTK_NW_DUAL_GSM_UMTS_MODE,   	/**< GSM_UMTS, auto */
    MBTK_NW_DUAL_GSM_UMTS_MODE_GSM,	/**< GSM_UMTS, GSM preferred */
    MBTK_NW_DUAL_GSM_UMTS_MODE_UMTS,	/**< GSM_UMTS, UMTS preferred */
    
    MBTK_NW_LTE_MODE,			/**< LTE */
    
    MBTK_NW_DUAL_GSM_LTE_MODE,		/**< GSM_LTE, auto, single link */
    MBTK_NW_DUAL_GSM_LTE_MODE_GSM,	/**< GSM_LTE, GSM preferred, single link */
    MBTK_NW_DUAL_GSM_LTE_MODE_LTE,	/**< GSM_LTE, LTE preferred, single link */
    
    MBTK_NW_DUAL_UMTS_LTE_MODE,		/**< UMTS_LTE, auto, single link */
    MBTK_NW_DUAL_UMTS_LTE_MODE_UMTS,	/**< UMTS_LTE, UMTS preferred, single link */
    MBTK_NW_DUAL_UMTS_LTE_MODE_LTE,	/**< UMTS_LTE, LTE preferred, single link */
    
    MBTK_NW_TRIP_MODE,		/**< GSM_UMTS_LTE, auto, single link */
    MBTK_NW_TRIP_MODE_GSM,	/**< GSM_UMTS_LTE, GSM preferred, single link */
    MBTK_NW_TRIP_MODE_UMTS,	/**< GSM_UMTS_LTE, UMTS preferred, single link */
    MBTK_NW_TRIP_MODE_LTE,	/**< GSM_UMTS_LTE, LTE preferred, single link */

    MBTK_NW_GSM_LTE_MODE_DUALLINK,	/**< GSM_LTE, dual link */
    MBTK_NW_UMTS_LTE_MODE_DUALLINK,	/**< UMTS_LTE, dual link */
    MBTK_NW_TRIP_MODE_DUALLINK,		/**< GSM_UMTS_LTE, dual link */

    MBTK_NW_MODE_NOT_CHANGE = 0xF0,
    
    MBTK_NUM_NW_MODES_SET

}MBTK_NW_MODE_ENUM;

typedef struct
{
	MBTK_NW_MODE_ENUM preferred_nw_mode;
	int gsmband_bitmap;
	int umtsband_bitmap;
	int ltebandh_bitmap;
	int ltebandl_bitmap;
	int roaming_pref;
}MBTK_NW_CONFIG_INFO;

int mbtk_set_nw_config(MBTK_NW_CONFIG_INFO *config_info);
int mbtk_get_nw_config(MBTK_NW_CONFIG_INFO *config_info);


/******************************
*Signal Strength info
*AT+CSQ  AT+CESQ
******************************/
typedef struct
{
	int rssi;
	int bitErrorRate;
	int rscp;
	int ecno;	
}MBTK_GW_SIGNAL_STRENGTH_INFO;

typedef struct
{
	int rssi;
	int rsrp;
	int rsrq;
	int cqi;
}MBTK_LTE_SIGNAL_STRENGTH_INFO;

typedef struct
{
	MBTK_GW_SIGNAL_STRENGTH_INFO CW_SignalStrength;
	MBTK_LTE_SIGNAL_STRENGTH_INFO LTE_SignalStrength;
}MBTK_SIGNAL_STRENGTH_INFO;
MBTK_LTE_SIGNAL_STRENGTH_INFO *get_let_signal(void);
int mbtk_get_csq(int *csq);
int mbtk_get_signal_strength(MBTK_SIGNAL_STRENGTH_INFO *signal_strength);

/******************************
*NITZ time info
*AT*CTZR?
******************************/
typedef struct
{
	char nitz_time[32];
	unsigned long abs_time;
}MBTK_NITZ_TIME_INFO;

int mbtk_get_nitz_time(MBTK_NITZ_TIME_INFO *nitz_info);

/******************************
*operator info
*AT*ASRCOPS?
******************************/
typedef struct
{
	char long_eons[128];
	char short_eons[128];
	char mcc[4];
	char mnc[4];
}MBTK_OPERATOR_INFO;
int mbtk_get_operator_info(MBTK_OPERATOR_INFO *operator_info);

/******************************
*reg status
*AT+CREG AT+CEREG
******************************/
typedef enum 
{
  MBTK_NW_REG_STA_NOT_REGED = 0, 				/**< Not registered and not searching */
  MBTK_NW_REG_STA_REG_HPLMN,     				/**< Registered on home PLMN */
  MBTK_NW_REG_STA_TRYING,        						/**< Not registered, but cellular subsystem is searching for a PLMN to register to */
  MBTK_NW_REG_STA_REG_DENIED,    				/**< Registration denied */
  MBTK_NW_REG_STA_UNKNOWN,       					/**< Unknown */
  MBTK_NW_REG_STA_REG_ROAMING,    				/**< Registered on visited PLMN */
  MBTK_NW_REG_STA_SMS_ONLY_HOME,				/**< registered for "SMS only", home network (applicable only when <AcT> indicates E-UTRAN) */
  MBTK_NW_REG_STA_SMS_ONLY_ROAMING,			/**< registered for "SMS only", roaming (applicable only when <AcT> indicates E-UTRAN) */
  MBTK_NW_REG_STA_EMERGENCY_ONLY_NOT_USED,		/**< attached for emergency bearer services only (see NOTE 2) (not applicable) */
  MBTK_NW_REG_STA_CSFB_NOT_PREFERRED_HOME,		/**<registered for "CSFB not preferred", home network (applicable only when <AcT> indicates E-UTRAN) */
  MBTK_NW_REG_STA_CSFB_NOT_PREFERRED_ROAMING,	/**<registered for "CSFB not preferred", roaming (applicable only when <AcT> indicates E-UTRAN) */
  MBTK_NW_REG_STA_REG_EMERGENCY,    							/**< attached for emergency bearer services only*/
  MBTK_NW_REG_STA_REG_DENIED_IN_ROAMING,       		/**< registeration denied in roaming, only used for SSG project by now*/
  MBTK_NW_REG_STA_SYNC_DONE_IN_LTE_ROAMING,    	/**< sync done in LTE roaming network, only used for SSG project by now*/
  MBTK_NW_REGSTATUS                											/**< Number of status values defined */

}MBTK_NW_REG_STATE;

typedef enum 
{
	MBTK_NW_ACT_GSM = 0,            			/**< GSM */
  	MBTK_NW_ACT_GSM_COMPACT,			/**< Not supported */
  	MBTK_NW_ACT_UTRAN,              			/**< UTRAN */
  	MBTK_NW_ACT_GSM_EGPRS,          	/**< GSM w/EGPRS */
  	MBTK_NW_ACT_UTRAN_HSDPA,        	/**< UTRAN w/HSDPA */
  	MBTK_NW_ACT_UTRAN_HSUPA,        	/**< UTRAN w/HSUPA */
  	MBTK_NW_ACT_UTRAN_HSPA,         	/**< UTRAN w/HSDPA and HSUPA */
  	MBTK_NW_ACT_EUTRAN,             		/**< E-UTRAN */  
  	MBTK_NW_ACT_UTRAN_HSPA_PLUS,	/**< UTRAN w/HSPA+ */ 
  	MBTK_NW_ACT_EUTRAN_PLUS,			/*E-UTRAN CA*/
  	MBTK_NW_ACT_UTRAN_DC_HSPA,		/*DC-HSPA*/
  	MBTK_NW_NUM_ACT
}MBTK_NW_ACCESS_TECHNOLOGY;

typedef struct
{
	MBTK_NW_REG_STATE state;
	MBTK_NW_ACCESS_TECHNOLOGY act;
	int lac;
	int cid;
	int t3324;
	int t3412ext2;
}MBTK_REG_STATUS_INFO;

typedef struct{
	int mcc;
	int mnc;
}MBTK_NW_CPSI_INFO;

typedef struct
{
	int mcc;
	int mnc;
	int rejectcause;
	char timestamp[64];
}MBTK_NW_REJECT_CAUSE;

typedef enum
{
	reject_by_register = 0,
	reject_by_active = 1,
}MBTK_NW_REJECT_TYPE;

typedef void (*mbtk_nw_reject_callback_ptr)(MBTK_NW_REJECT_CAUSE *casue);


void mbtk_nw_set_reject_callback(mbtk_nw_reject_callback_ptr cb);
int mbtk_get_reg_status(MBTK_REG_STATUS_INFO *reg_info,int nw_mode);

/******************************
*Cell info
*
******************************/
#define MBTK_CELL_NUM_MAX 16

typedef enum
{
	GSM_CELL_VALID,
	UMTS_CELL_VALID,
	LTE_CELL_VALID,
}MBTK_CELL_VALID_TYPE;

typedef enum
{
	CELL_PRESENT,
	CELL_NEIGHBORING,
	CELL_INTRA,
	CELL_INTER,
}MBTK_CELL_TYPE;

typedef struct
{
	int cell_type;
	int cid;
	int mcc;
	int mnc;
	int lac;
	int arfcn;
	char bsic;
	int rssi;
	int band;
	int ber;
}MBTK_GSM_CELL_INFO;

typedef struct
{
	int cell_type;
	int cid;
	int mcc;
	int mnc;
	int lac;
	int uarfcn;
	int psc;
}MBTK_UMTS_CELL_INFO;

typedef struct
{
	int cell_type;
	int cid;
	int mcc;
	int mnc;
	int tac;
	int pci;
	int earfcn;
	int rsrq;
	int rsrp;
	int rssi;
	int snr;
	int band;
	int ber;
}MBTK_LTE_CELL_INFO;

typedef struct
{
	//gsm
	int gsm_info_valid;
	int gsm_info_num;
	MBTK_GSM_CELL_INFO gsm_info[MBTK_CELL_NUM_MAX+1];
	//umts  not support now
	int umts_info_valid;
	int umts_info_num;
	MBTK_UMTS_CELL_INFO umts_info[MBTK_CELL_NUM_MAX+1];
	//lte
	int lte_info_valid;
	int lte_info_num;
	MBTK_LTE_CELL_INFO lte_info[MBTK_CELL_NUM_MAX+1];
}MBTK_CELL_INFO;

typedef struct
{	
	char vaild_type;
	int	t3402;
	int	t2412;
	int	t3412;
	int	t3412ext2;
	int	t3324;
	int	tedrx;
	int	tptw;
	int	qrxlevmin;

	union 
	{	
		struct
		{
			short						rssi;
			short						ber;
			unsigned int		ci;
			unsigned short	lac;
			unsigned short	mcc;
			unsigned short	mnc;
			unsigned short	band;
			unsigned short	arfcn;
		}gsm;
		
		struct
		{
			unsigned int		pci;
			unsigned int		ci;
			short						rssi;
			short						ber;
			short						rsrp;
			short						rsrq;
			short						snr;
			unsigned short	tac;
			unsigned short	mcc;
			unsigned short	mnc;
			unsigned short	band;
			unsigned short	earfcn;
		}lte;
	}present_cell_info;
	
	union 
	{
		unsigned short 		of_neighboring;
		struct
		{
			unsigned char 	of_intra;
			unsigned char 	of_inter;
		}lte;
	}nb_cell_num;

	union
	{
		struct 
		{
			unsigned int		ci;
			short						rssi;
		}gsm;

		struct
		{
			unsigned int		ci;
			unsigned int		pci;
			short						rsrp;
			short						rssi;
		}lte;
	}nb_cell_info[MBTK_CELL_NUM_MAX];
}MBTK_CELL_INFO_EX;



typedef enum
{
	MBTK_NW_REG_EVENT,
	MBTK_NW_PDP_EVENT,
	MBTK_NW_MAX_EVENT
}MBTK_NW_CB_EVENT;



typedef struct mbtk_nw_cb_reg_status
{
	MBTK_NW_REG_STATE state;
	MBTK_NW_ACCESS_TECHNOLOGY act;
}mbtk_nw_cb_reg_status;

typedef struct mbtk_nw_cb_pdp_status
{
	unsigned char cid;  //mbtk_data_call_cid_index_enum
	unsigned char  state;  //mbtk_data_call_state
}mbtk_nw_cb_pdp_status;



typedef struct mbtk_nw_status_struct 
{
	MBTK_NW_CB_EVENT event; // ??|¨¬????¡ê¡è?¡è?¨¦|¨¬?¡§o??t
	union
	{
		mbtk_nw_cb_reg_status reg_status;
		mbtk_nw_cb_pdp_status pdp_status;
	}nw_status;
}mbtk_nw_status_struct;



typedef enum 
{
	OL_NW_AUTH_NONE = 0,            			/**< none */
  	OL_NW_AUTH_PAP,			/**< pap */
  	OL_NW_AUTH_CHAP,              			/**< chap */
}OL_NW_AUTH_TYPE;


typedef enum
{
	OL_NW_IPV4,
	OL_NW_IPV6,
	OL_NW_IPV4V6
}OL_NW_IPTYPE;

#define MBTK_GPRS_DEFAULT_CID 0
#define MBTK_DNS_MAX_LEN 64
#define MBTK_USER_DNS_SERVER_FILE	"user_dns_server.txt"

typedef struct 
{
	unsigned char ipv4_pri_dns[MBTK_DNS_MAX_LEN];
	unsigned char ipv4_sec_dns[MBTK_DNS_MAX_LEN];
	unsigned char ipv6_pri_dns[MBTK_DNS_MAX_LEN];
	unsigned char ipv6_sec_dns[MBTK_DNS_MAX_LEN];
}mbtk_dns_server_info_struct;

typedef enum 
{
    MBTK_PSM_DISABLE = 0,//Disable the use of PSM
    MBTK_PSM_ENABLE = 1, //Enable the use of PSM
    MBTK_PSM_ENABLE2 = 2,//Disable the use of PSM and discard all parameters for PSM or, if available, reset to the manufacturer specific default values.
}MBTK_PSM_MODE;

typedef struct 
{
    MBTK_PSM_MODE mode;
    unsigned char T3312[12];//Requested_Periodic-RAU      cat1 not support
    unsigned char T3314[12];//Requested_GPRS-READY-timer  cat1 not support
    unsigned char T3412[12];//Requested_Periodic-TAU
    unsigned char T3324[12];//Requested_Active-Time
}mbtk_psm_info;

MBTK_CELL_INFO *get_cell_info(void);
int mbtk_get_cell_info(MBTK_CELL_INFO *cell_info);
int mbtk_get_cell_info_ex(MBTK_CELL_INFO_EX *cell_info);
int mbtk_get_paging_cycle(void);
int mbtk_get_rrc_cycle(void);
int ol_get_freq(char *freq);
int ol_get_curr_band(void);
int ol_set_default_auth(OL_NW_AUTH_TYPE auth_type, char *user, char *name);
int ol_get_default_auth(OL_NW_AUTH_TYPE *auth_type, char *user, char *name);
int ol_set_default_lte_apn(OL_NW_IPTYPE iptype, char *apn);
int ol_get_default_lte_apn(OL_NW_IPTYPE *iptype, char *apn);
int ol_set_default_lte_apn_valid_in_ems(char is_valid);
int ol_get_default_lte_apn_valid_in_ems(char *is_valid);
int ol_set_dns(OL_NW_IPTYPE iptype ,char *dns1Str, char *dns2Str);
int ol_get_dns(OL_NW_IPTYPE iptype, char *dns1Str, char *dns2Str);
int mbtk_get_curr_band(void);
int mbtk_get_freq(char *freq);
int mbtk_set_psm_config(mbtk_psm_info *psm_info);
int mbtk_get_psm_config(mbtk_psm_info *psm_info);


#endif
