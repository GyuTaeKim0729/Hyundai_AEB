/*
 * timer.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_TIMER_H_
#define HEADERS_TIMER_H_

#include "IfxCpu.h"
#include "IfxCcu6_reg.h"

#define LCK_BIT_LSB_IDX 1
#define ENDINIT_BIT_LSB_IDX 0
#define DISR_BIT_LSB_IDX 0
#define DISS_BIT_LSB_IDX 1

#define T12CLK_BIT_LSB_IDX 0
#define T12PRE_BIT_LSB_IDX 3
#define CTM_BIT_LSB_IDX 7
#define T12STR_BIT_LSB_IDX 6
#define INPT12_BIT_LSB_IDX 10
#define ENT12PM_BIT_LSB_IDX 7
#define T12RS_BIT_LSB_IDX 1
#define T12RR_BIT_LSB_IDX 0

#define SRPN_BIT_LSB_IDX 0
#define SRE_BIT_LSB_IDX 10
#define TOS_BIT_LSB_IDX 11

#define T13CLK_BIT_LSB_IDX 8
#define T13PRE_BIT_LSB_IDX 11
#define T13STR_BIT_LSB_IDX 14
#define ENT13PM_BIT_LSB_IDX 9
#define INPT13_BIT_LSB_IDX 12
#define T13RS_BIT_LSB_IDX 9
#define T13RR_BIT_LSB_IDX 8

void InitTimer(void);
void OpertaionTimer(boolean, unsigned int);

#endif /* HEADERS_TIMER_H_ */
