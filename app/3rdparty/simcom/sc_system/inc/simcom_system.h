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

#ifndef _SIMCOM_SYSTEM_H_
#define _SIMCOM_SYSTEM_H_

typedef enum
{
    SC_SYSTEM_SLEEP_DISABLE,
    SC_SYSTEM_SLEEP_ENABLE
}SC_SYSTEM_SLEEP_FLAG;


int sAPI_SystemSleepSet(SC_SYSTEM_SLEEP_FLAG flag);
SC_SYSTEM_SLEEP_FLAG sAPI_SystemSleepGet(void);
int sAPI_SystemSleepExSet(SC_SYSTEM_SLEEP_FLAG flag, unsigned char time);
//SC_SleepEx_str sAPI_SystemSleepExGet(void);
int sAPI_SystemAlarmClock2Wakeup(unsigned long time);




#endif
