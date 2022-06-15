
#ifndef HEADERS_LIB_H_
#define HEADERS_LIB_H_

#include "led.h"
#include "buzzer.h"
#include "potentiometer.h"

#define		TIMER_OFF					( ( unsigned char )( 0 ) ) 							/* Timer is Not Running */
#define		TIMER_ON					( ( unsigned char )( 1 ) ) 							/* Timer is Running */

#define		ON 							( ( unsigned char )( 1 ) )							/* on */
#define		OFF							( ( unsigned char )( 0 ) )							/* off */
#define		CLEAR						( ( unsigned char )( 0 ) )							/* clear */

#define     SEC_1                       ( ( unsigned short )( 100 ) )						/* 1 sec */
#define     SEC_2                       ( ( unsigned short )( 200 ) )						/* 2 sec */
#define     SEC_3                       ( ( unsigned short )( 300 ) )						/* 3 sec */

#define P3_BIT_LSB_IDX 3
#define P5_BIT_LSB_IDX 5
#define P7_BIT_LSB_IDX 7


unsigned char  LibTimer( unsigned char TimerEn, unsigned char timer, unsigned char Max );
unsigned char  LibCountUp( unsigned char Count, unsigned char Max );
unsigned char LibTimer_short( unsigned short TimerEn, unsigned short timer, unsigned short Max );
unsigned char LibCountUp_short( unsigned short Count, unsigned short Max );

unsigned short    FadeControl( unsigned short Target, unsigned short TargetDuty, unsigned short MaxDuty, unsigned short FadeInTime, unsigned short FadeOutTime );

void  Mode1_1( void );

#endif /* HEADERS_LIB_H_ */
