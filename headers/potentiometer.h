/*
 * potentiometer.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_POTENTIOMETER_H_
#define HEADERS_POTENTIOMETER_H_

#include "IfxCpu.h"
#include "IfxVadc_reg.h"
#include "timer.h"

#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define DISR_BIT_LSB_IDX 0
#define DISS_BIT_LSB_IDX 1
#define PRIO0_BIT_LSB_IDX 0
#define CSM0_BIT_LSB_IDX 3
#define ASEN0_BIT_LSB_IDX 24
#define ENGT_BIT_LSB_IDX 0
#define FLUSH_BIT_LSB_IDX 10
#define ANONC_BIT_LSB_IDX 0
#define RESPOS_BIT_LSB_IDX 21
#define ICLSEL_BIT_LSB_IDX 0
#define ASSCH7_BIT_LSB_IDX 7
#define TREV_BIT_LSB_IDX 9
#define VF_BIT_LSB_IDX 31
#define RESULT_BIT_LSB_IDX 0
#define RESREG_BIT_LSB_IDX 16
#define CMS_BIT_LSB_IDX 8

void InitPotentio(void);
static void InitVADC(void);
void CalculateRotation(const int*);
static void VADC_startConversion(void);
static unsigned int VADC_readResult(void);
void OperationPotentio_FREQ(void);

#endif /* HEADERS_POTENTIOMETER_H_ */
