#ifndef _OL_NW_PUB_H_
#define _OL_NW_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************
*NW config info
******************************/
typedef enum 
{
    OL_NW_GSM_MODE  = 0,	/**< GSM */
    OL_NW_UMTS_MODE,    	/**< UMTS */
    
    OL_NW_DUAL_GSM_UMTS_MODE,   	/**< GSM_UMTS, auto */
    OL_NW_DUAL_GSM_UMTS_MODE_GSM,	/**< GSM_UMTS, GSM preferred */
    OL_NW_DUAL_GSM_UMTS_MODE_UMTS,	/**< GSM_UMTS, UMTS preferred */
    
    OL_NW_LTE_MODE,			/**< LTE */
    
    OL_NW_DUAL_GSM_LTE_MODE,		/**< GSM_LTE, auto, single link */
    OL_NW_DUAL_GSM_LTE_MODE_GSM,	/**< GSM_LTE, GSM preferred, single link */
    OL_NW_DUAL_GSM_LTE_MODE_LTE,	/**< GSM_LTE, LTE preferred, single link */
    
    OL_NW_DUAL_UMTS_LTE_MODE,		/**< UMTS_LTE, auto, single link */
    OL_NW_DUAL_UMTS_LTE_MODE_UMTS,	/**< UMTS_LTE, UMTS preferred, single link */
    OL_NW_DUAL_UMTS_LTE_MODE_LTE,	/**< UMTS_LTE, LTE preferred, single link */
    
    OL_NW_TRIP_MODE,		/**< GSM_UMTS_LTE, auto, single link */
    OL_NW_TRIP_MODE_GSM,	/**< GSM_UMTS_LTE, GSM preferred, single link */
    OL_NW_TRIP_MODE_UMTS,	/**< GSM_UMTS_LTE, UMTS preferred, single link */
    OL_NW_TRIP_MODE_LTE,	/**< GSM_UMTS_LTE, LTE preferred, single link */

    OL_NW_GSM_LTE_MODE_DUALLINK,	/**< GSM_LTE, dual link */
    OL_NW_UMTS_LTE_MODE_DUALLINK,	/**< UMTS_LTE, dual link */
    OL_NW_TRIP_MODE_DUALLINK,		/**< GSM_UMTS_LTE, dual link */

    OL_NW_MODE_NOT_CHANGE = 0xF0,
    
    OL_NUM_NW_MODES_SET

}OL_NW_MODE_ENUM;

typedef struct
{
	OL_NW_MODE_ENUM preferred_nw_mode;
	int gsmband_bitmap;
	int umtsband_bitmap;
	int ltebandh_bitmap;
	int ltebandl_bitmap;
	int roaming_pref;
	int ltebandext_bitmap;
}ol_NW_CONFIG_INFO;



/******************************
*Signal Strength info
******************************/
typedef struct
{
	int rssi;
	int bitErrorRate;
	int rscp;
	int ecno;	
}OL_GW_SIGNAL_STRENGTH_INFO;

typedef struct
{
	int rssi;
	int rsrp;
	int rsrq;
	int cqi;
}OL_LTE_SIGNAL_STRENGTH_INFO;

typedef struct
{
	OL_GW_SIGNAL_STRENGTH_INFO CW_SignalStrength;
	OL_LTE_SIGNAL_STRENGTH_INFO LTE_SignalStrength;
}ol_SIGNAL_STRENGTH_INFO;

/******************************
*NITZ time info
******************************/
typedef struct
{
	char nitz_time[32];
	unsigned long abs_time;
}ol_NITZ_TIME_INFO;


/******************************
*operator info
******************************/
typedef struct
{
	char long_eons[128];
	char short_eons[128];
	char mcc[4];
	char mnc[4];
}ol_OPERATOR_INFO;

/******************************
*reg status
******************************/
typedef enum 
{
  OL_NW_REG_STA_NOT_REGED = 0, 				/**< Not registered and not searching */
  OL_NW_REG_STA_REG_HPLMN,     				/**< Registered on home PLMN */
  OL_NW_REG_STA_TRYING,        						/**< Not registered, but cellular subsystem is searching for a PLMN to register to */
  OL_NW_REG_STA_REG_DENIED,    				/**< Registration denied */
  OL_NW_REG_STA_UNKNOWN,       					/**< Unknown */
  OL_NW_REG_STA_REG_ROAMING,    				/**< Registered on visited PLMN */
  OL_NW_REG_STA_SMS_ONLY_HOME,				/**< registered for "SMS only", home network (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_SMS_ONLY_ROAMING,			/**< registered for "SMS only", roaming (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_EMERGENCY_ONLY_NOT_USED,		/**< attached for emergency bearer services only (see NOTE 2) (not applicable) */
  OL_NW_REG_STA_CSFB_NOT_PREFERRED_HOME,		/**<registered for "CSFB not preferred", home network (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_CSFB_NOT_PREFERRED_ROAMING,	/**<registered for "CSFB not preferred", roaming (applicable only when <AcT> indicates E-UTRAN) */
  OL_NW_REG_STA_REG_EMERGENCY,    							/**< attached for emergency bearer services only*/
  OL_NW_REG_STA_REG_DENIED_IN_ROAMING,       		/**< registeration denied in roaming, only used for SSG project by now*/
  OL_NW_REG_STA_SYNC_DONE_IN_LTE_ROAMING,    	/**< sync done in LTE roaming network, only used for SSG project by now*/
  OL_NW_REGSTATUS                											/**< Number of status values defined */

}OL_NW_REG_STATE;

typedef enum 
{
	OL_NW_ACT_GSM = 0,            			/**< GSM */
  	OL_NW_ACT_GSM_COMPACT,			/**< Not supported */
  	OL_NW_ACT_UTRAN,              			/**< UTRAN */
  	OL_NW_ACT_GSM_EGPRS,          	/**< GSM w/EGPRS */
  	OL_NW_ACT_UTRAN_HSDPA,        	/**< UTRAN w/HSDPA */
  	OL_NW_ACT_UTRAN_HSUPA,        	/**< UTRAN w/HSUPA */
  	OL_NW_ACT_UTRAN_HSPA,         	/**< UTRAN w/HSDPA and HSUPA */
  	OL_NW_ACT_EUTRAN,             		/**< E-UTRAN */  
  	OL_NW_ACT_UTRAN_HSPA_PLUS,	/**< UTRAN w/HSPA+ */ 
  	OL_NW_ACT_EUTRAN_PLUS,			/*E-UTRAN CA*/
  	OL_NW_ACT_UTRAN_DC_HSPA,		/*DC-HSPA*/
  	OL_NW_NUM_ACT
}OL_NW_ACCESS_TECHNOLOGY;

typedef struct
{
	OL_NW_REG_STATE state;
	OL_NW_ACCESS_TECHNOLOGY act;
	int lac;
	int cid;
	int t3324;
	int t3412ext2;
}ol_REG_STATUS_INFO;

typedef struct
{
	int mcc;
	int mnc;
	int rejectcause;
	char timestamp[64];
}ol_NW_REJECT_CAUSE;

typedef void (*ol_nw_reject_callback_ptr)(ol_NW_REJECT_CAUSE *casue);

/******************************
*Cell info
******************************/

#define OL_NW_CELL_NUM_MAX 16
typedef enum
{
	GSM_CELL_VALID,
	UMTS_CELL_VALID,
	LTE_CELL_VALID,
}OL_CELL_VALID_TYPE;

typedef enum
{
	CELL_PRESENT,
	CELL_NEIGHBORING,
	CELL_INTRA,
	CELL_INTER,
}OL_CELL_TYPE;


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
}OL_GSM_CELL_INFO;

typedef struct
{
	int cell_type;
	int cid;
	int mcc;
	int mnc;
	int lac;
	int uarfcn;
	int psc;
}OL_UMTS_CELL_INFO;

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
}OL_LTE_CELL_INFO;


typedef struct
{
	//gsm
	int gsm_info_valid;
	int gsm_info_num;
	OL_GSM_CELL_INFO gsm_info[OL_NW_CELL_NUM_MAX+1];
	//umts  not support now
	int umts_info_valid;
	int umts_info_num;
	OL_UMTS_CELL_INFO umts_info[OL_NW_CELL_NUM_MAX+1];
	//lte
	int lte_info_valid;
	int lte_info_num;
	OL_LTE_CELL_INFO lte_info[OL_NW_CELL_NUM_MAX+1];
}ol_CELL_INFO;

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
	}nb_cell_info[OL_NW_CELL_NUM_MAX];
}ol_CELL_INFO_EX;


typedef enum
{
	MBTK_NW_REG_EVENT,
	MBTK_NW_PDP_EVENT,
	MBTK_NW_MAX_EVENT
}MBTK_NW_CB_EVENT;



typedef struct mbtk_nw_cb_reg_status
{
	OL_NW_REG_STATE state;
	OL_NW_ACCESS_TECHNOLOGY act;
}mbtk_nw_cb_reg_status;

typedef struct mbtk_nw_cb_pdp_status
{
	unsigned char cid;  //mbtk_data_call_cid_index_enum
	unsigned char  state;  //mbtk_data_call_state
}mbtk_nw_cb_pdp_status;



typedef struct mbtk_nw_status_struct 
{
	MBTK_NW_CB_EVENT event; // ??¦Ì¡Â¡ä£¤¡¤¡é¦Ì?¨º??t
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

typedef enum 
{
    OL_PSM_DISABLE = 0,//Disable the use of PSM
    OL_PSM_ENABLE = 1, //Enable the use of PSM
    OL_PSM_ENABLE2 = 2,//Disable the use of PSM and discard all parameters for PSM or, if available, reset to the manufacturer specific default values.
}OL_PSM_MODE;

typedef struct 
{
    OL_PSM_MODE mode;
    unsigned char T3312[12];//Requested_Periodic-RAU      cat1 not support
    unsigned char T3314[12];//Requested_GPRS-READY-timer  cat1 not support
    unsigned char T3412[12];//Requested_Periodic-TAU
    unsigned char T3324[12];//Requested_Active-Time
}ol_psm_info;

#ifdef __cplusplus
}
#endif

#endif
