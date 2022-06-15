/*
 * buzzer.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_BUZZER_H_
#define HEADERS_BUZZER_H_

#include "IfxCpu.h"
#include "IfxGtm_reg.h"

#define PC3_BIT_LSB_IDX 27

#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define DISR_BIT_LSB_IDX 0
#define DISS_BIT_LSB_IDX 1

#define FXCLK_SEL_BIT_LSB_IDX 0
#define EN_FXCLK_BIT_LSB_IDX 22
#define UPEN_CTRL11_BIT_LSB_IDX 22
#define ENDIS_CTRL11_BIT_LSB_IDX 6
#define OUTEN_CTRL11_BIT_LSB_IDX 6
#define SL_BIT_LSB_IDX 11
#define CLK_BIT_LSB_IDX 12
#define OSM_BIT_LSB_IDX 26
#define TRIGOUT_BIT_LSB_IDX 24
#define SEL3_BIT_LSB_IDX 6
#define HOST_TRIG_BIT_LSB_IDX 0

void InitBuzzer(void);
void OperationBuzzer(unsigned short);
void Mode2Buzzer(void);

#endif /* HEADERS_BUZZER_H_ */
