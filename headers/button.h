/*
 * button.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_BUTTON_H_
#define HEADERS_BUTTON_H_

#include "IfxCpu.h"

#define PC0_BIT_LSB_IDX 3
#define PC1_BIT_LSB_IDX 11

#define EXIS0_BIT_LSB_IDX 4
#define FEN0_BIT_LSB_IDX 8
#define EIEN0_BIT_LSB_IDX 11
#define INP0_BIT_LSB_IDX 12
#define IGP0_BIT_LSB_IDX 14

#define EXIS1_BIT_LSB_IDX 20
#define FEN1_BIT_LSB_IDX 24
#define EIEN1_BIT_LSB_IDX 27
#define INP1_BIT_LSB_IDX 28
#define IGP1_BIT_LSB_IDX 30

#define SRPN_BIT_LSB_IDX 0
#define SRE_BIT_LSB_IDX 10
#define TOS_BIT_LSB_IDX 11
#define REN0_BIT_LSB_IDX 9

void InitButton(void);

#endif /* HEADERS_BUTTON_H_ */
