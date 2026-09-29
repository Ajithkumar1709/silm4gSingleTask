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
	int rejectcause;
}MBTK_REG_STATUS_INFO;

int mbtk_get_reg_status(MBTK_REG_STATUS_INFO *reg_info,int nw_mode);

/******************************
*Cell info
*
******************************/
#define MBTK_CELL_NUM_MAX 16
typedef struct
{
	int cell_type;
	int cid;
	int mcc;
	int mnc;
	int lac;
	int arfcn;
	char bsic;
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

MBTK_CELL_INFO *get_cell_info(void);
int mbtk_get_cell_info(MBTK_CELL_INFO *cell_info);
int mbtk_get_paging_cycle(void);
int mbtk_get_rrc_cycle(void);

#endif
