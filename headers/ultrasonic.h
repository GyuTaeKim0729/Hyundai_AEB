/*
 * ultrasonic.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_ULTRASONIC_H_
#define HEADERS_ULTRASONIC_H_

#include "IfxCpu.h"
#include "IfxCcu6_reg.h"
#include "led.h"

#define PC7_BIT_LSB_IDX     27
#define PC5_BIT_LSB_IDX     11
#define PC3_BIT_LSB_IDX     27
#define P7_BIT_LSB_IDX      7
#define P5_BIT_LSB_IDX      5
#define P3_BIT_LSB_IDX      3

#define PC6_BIT_LSB_IDX             19
#define PC4_BIT_LSB_IDX             3
#define P6_BIT_LSB_IDX              6
#define P4_BIT_LSB_IDX              4

// SCUR registers
#define LCK_BIT_LSB_IDX     1
#define ENDINIT_BIT_LSB_IDX 0
#define EXIS0_BIT_LSB_IDX   4
#define FEN0_BIT_LSB_IDX    8
#define REN0_BIT_LSB_IDX    9
#define EIEN0_BIT_LSB_IDX   11
#define INP0_BIT_LSB_IDX    12
#define IGP0_BIT_LSB_IDX    14

// SRC registers
#define SRPN_BIT_LSB_IDX    0
#define SRE_BIT_LSB_IDX     10
#define TOS_BIT_LSB_IDX     11

// CCU60 registers
#define DISS_BIT_LSB_IDX    1
#define DISR_BIT_LSB_IDX    0
#define CTM_BIT_LSB_IDX     7
#define T12CLK_BIT_LSB_IDX  0
#define T12PRE_BIT_LSB_IDX  3
#define T12STR_BIT_LSB_IDX  6
#define T12RS_BIT_LSB_IDX   1
#define INPT12_BIT_LSB_IDX  10
#define ENT12PM_BIT_LSB_IDX 7

void InitUltrasonic(void);
void GetDistance(void);
void usonicTrigger(void);

#endif /* HEADERS_ULTRASONIC_H_ */
