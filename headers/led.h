/*
 * led.h
 *
 *  Created on: 2022. 6. 13.
 *      Author: user
 */

#ifndef HEADERS_LED_H_
#define HEADERS_LED_H_

#include "IfxCpu.h"

#define PC1_BIT_LSB_IDX 11
#define PC2_BIT_LSB_IDX 19
#define P1_BIT_LSB_IDX 1
#define P2_BIT_LSB_IDX 2

// GTM registers
#define DISS_BIT_LSB_IDX            1
#define DISR_BIT_LSB_IDX            0
#define SEL7_BIT_LSB_IDX            14
#define SEL8_BIT_LSB_IDX            16
#define EN_FXCLK_BIT_LSB_IDX        22
#define FXCLK_BIT_LSB_IDX           0

// GTM - TOM0 registers
#define UPEN_CTRL1_BIT_LSB_IDX      18
#define UPEN_CTRL2_BIT_LSB_IDX      20
#define HOST_TRIG_BIT_LSB_IDX      0
#define ENDIS_CTRL1_BIT_LSB_IDX     2
#define ENDIS_CTRL2_BIT_LSB_IDX     4
#define OUTEN_CTRL1_BIT_LSB_IDX     2
#define OUTEN_CTRL2_BIT_LSB_IDX     4
#define CLK_SRC_SR_BIT_LSB_IDX      12
#define OSM_BIT_LSB_IDX             26
#define TRIGOUT_BIT_LSB_IDX         24
#define SL_BIT_LSB_IDX              11


// SCUR registers
#define LCK_BIT_LSB_IDX     1
#define ENDINIT_BIT_LSB_IDX 0
#define EXIS0_BIT_LSB_IDX   4
#define FEN0_BIT_LSB_IDX    8
#define REN0_BIT_LSB_IDX    9
#define EIEN0_BIT_LSB_IDX   11
#define INP0_BIT_LSB_IDX    12
#define IGP0_BIT_LSB_IDX    14

// led.c
void InitLED(void);
void ToggleLEDR(void);
void ToggleLEDB(void);
void ResetLED(void);
void initREDLEDPWM(void);
//void initGTM(void);

// led_rgb.c
void InitRGB(void);
void OperationRGB(boolean state, char color);
void ResetRGB(void);
void Mode2RGB(void);
void Mode2Led(void);

#endif /* HEADERS_LED_H_ */
