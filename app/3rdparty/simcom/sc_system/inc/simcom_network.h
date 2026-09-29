/**
 * \file ssl.h
 *
 * \brief SSL/TLS functions.
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
//#include "ci_mm.h"
#ifndef _SIMCOM_NETWORK_H_
#define _SIMCOM_NETWORK_H_

#include "simcom_os.h"

/**  \brief Encoded bit error rate (BER) indication */
/** \remarks Common Data Section */
typedef UINT8 SCCiMmEncodedBER; /**< Reported as an index between 0-7, inclusive  */

/** \brief  Signal quality indications: information structure */
typedef struct SCCiMmSigNormalQualityInfo_struct {
    UINT8        Rssi; 
    SCCiMmEncodedBER Ber;
} SCCiMmSigNormalQualityInfo;

typedef struct{
    char networkmode[20];
    char Mnc_Mcc[20];
    int LAC;
    int CellID;
    int Arfcn;
    char GSMBandStr[20];
    char LTEBandStr[20];
    int Rxlev;
    int VCO;
    int C1;
    int C2;
    int TAC;
    int SCellID;
    int PCellID;
    int EARFCN,DLBW,ULBW,RSRQ,RSRP,RSSI,SINR;
}CpsiParm;

typedef struct{
    UINT8 cid;
    UINT8 isActived;
    UINT8 isdefine;
}SCAPNact;


typedef struct{
    UINT8 cid;
    UINT8 authtype;
    char user[40];
    char passwd[40];
}SCCGAUTHParm;

typedef struct{
    UINT8 cid;
    UINT8 iptype;
    char ApnStr[40];
}SCApnParm;

typedef struct{
    UINT8 cid;
    UINT8 iptype;
    char ipv4addr[40];
    char ipv6addr[40];
}SCcgpaddrParm;

typedef struct{
    char networkmode[16];
    char Mnc_Mcc[16];
    int LAC;
    int CellID;
    char GSMBandStr[16];
    char LTEBandStr[16];
    int TAC;
    int Rsrp;
    int RXLEV;
    int TA;
    int SINR;
}SCcpsiParm;

typedef struct{
    char Mnc_Mcc[16];
    int TAC;
    int CellID;
    int Rsrp;
    int Rsrq;
    int RXSIGLEVEL;
}SCcnetciParm;

typedef struct{
    char apn[40];
    char user[40];
    char pswd[40];
    char ip_type[40];
    int auth;
}SCdialapnparm;

enum networkid
{
    GET_CSQ_RES = 100,
    GET_CREQ_RES,
    GET_CGREQ_RES,
    GET_CPSI_RES,
    GET_CNMP_RES,
    GET_COPS_RES,
    GET_CGDCONT_RES,
    GET_CGACT_RES,
    GET_CGATT_RES,
    GET_CPIN_RES
};

typedef enum
{
    SC_NET_SUCCESS,
    SC_NET_FAIL
}SC_Net_Return_Code;

void sAPI_NetworkInit(void);
unsigned int sAPI_NetworkGetCsq(UINT8 *pCsq);
unsigned int sAPI_NetworkGetCreg(int *pReg);
unsigned int sAPI_NetworkGetCgreg(int *pGreg);
unsigned int sAPI_NetworkGetCpsi(SCcpsiParm *pStr);
unsigned int sAPI_NetworkGetCnmp(int *pCnmp);
unsigned int sAPI_NetworkSetCnmp(int CnmpValue);
unsigned int sAPI_NetworkGetCops(char *pCops);
unsigned int sAPI_NetworkSetCops(int modeVal,int formatVal,char *networkOperator,int accTchVal);
unsigned int sAPI_NetworkGetCgdcont(SCApnParm *pCgdcont);
unsigned int sAPI_NetworkSetCgdcont(int primCid,char *type,char *APNstr);
unsigned int sAPI_NetworkGetCgact(SCAPNact * pCgact);
unsigned int sAPI_NetworkSetCgact(int pdpState,int cid);
unsigned int sAPI_NetworkGetCgatt(int* pCgatt);
unsigned int sAPI_NetworkSetCgatt(int CgattValue);
unsigned int sAPI_NetworkGetCfun(UINT8 *pCfun);
unsigned int sAPI_NetworkSetCfun(int CfunValue);
unsigned int sAPI_NetworkGetCgauth(SCCGAUTHParm *pCgauth,int cid);
unsigned int sAPI_NetworkSetCgauth(SCCGAUTHParm *pCgauth,BOOL delflag);
unsigned int sAPI_NetworkGetCgpaddr(int Cid,SCcgpaddrParm *Pstr);
unsigned int sAPI_NetworkGetCnetci(SCcnetciParm *pStr);




unsigned int sAPI_SimPinGet(void);

#endif
