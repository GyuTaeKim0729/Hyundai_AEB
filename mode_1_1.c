/* Header Include */
#include "lib.h"

extern boolean mode1_status; // button -> checking mode / Use : [Main]

/* Global Data Definition */
unsigned char ResetFlag = ON;
unsigned char DistanceErr = OFF;

/* Static Data Definition */
static unsigned short LED_BLUE_Timer = CLEAR;
static unsigned short LED_RED_Timer = CLEAR;
static unsigned short LED_RGB_RED_Timer = CLEAR;
static unsigned short LED_RGB_GREEN_Timer = CLEAR;
static unsigned short LED_RGB_BLUE_Timer = CLEAR;
static unsigned short BUZZER_Timer = CLEAR;
static unsigned short ULTRASONIC_Timer = CLEAR;

static unsigned char LED_BLUE_TimerEn = TIMER_OFF;
static unsigned char LED_RED_TimerEn = TIMER_OFF;
static unsigned char LED_RGB_RED_TimerEn = TIMER_OFF;
static unsigned char LED_RGB_GREEN_TimerEn = TIMER_OFF;
static unsigned char LED_RGB_BLUE_TimerEn = TIMER_OFF;
static unsigned char BUZZER_TimerEn = TIMER_OFF;
static unsigned char ULTRASONIC_TimerEn = TIMER_OFF;

/* Temp Definition */
static unsigned char BUZZER = OFF;

void Mode1_1(void)
{
    if (mode1_status)
    {
        OperationPotentio_FREQ();
        LED_BLUE_Timer = LibTimer_short(LED_BLUE_TimerEn, LED_BLUE_Timer, SEC_2);
        LED_RED_Timer = LibTimer_short(LED_RED_TimerEn, LED_RED_Timer, SEC_2);
        LED_RGB_RED_Timer = LibTimer_short(LED_RGB_RED_TimerEn, LED_RGB_RED_Timer, SEC_2);
        LED_RGB_GREEN_Timer = LibTimer_short(LED_RGB_GREEN_TimerEn, LED_RGB_GREEN_Timer, SEC_2);
        LED_RGB_BLUE_Timer = LibTimer_short(LED_RGB_BLUE_TimerEn, LED_RGB_BLUE_Timer, SEC_2);
        BUZZER_Timer = LibTimer_short(BUZZER_TimerEn, BUZZER_Timer, SEC_2);
        // ULTRASONIC_Timer = LibTimer_short(ULTRASONIC_TimerEn, ULTRASONIC_Timer, SEC_2);

        if (ResetFlag == ON)
        {
            LED_BLUE_Timer = CLEAR;
            LED_RED_Timer = CLEAR;
            LED_RGB_RED_Timer = CLEAR;
            LED_RGB_GREEN_Timer = CLEAR;
            LED_RGB_BLUE_Timer = CLEAR;
            BUZZER_Timer = CLEAR;
            ULTRASONIC_Timer = CLEAR;

            LED_BLUE_TimerEn = TIMER_ON;
            LED_RED_TimerEn = TIMER_OFF;
            LED_RGB_RED_TimerEn = TIMER_OFF;
            LED_RGB_GREEN_TimerEn = TIMER_OFF;
            LED_RGB_BLUE_TimerEn = TIMER_OFF;
            BUZZER_TimerEn = TIMER_OFF;
            ULTRASONIC_TimerEn = TIMER_OFF;

            ResetFlag = OFF;
        }

        if (LED_BLUE_TimerEn == TIMER_ON)
        {
            if (LED_BLUE_Timer < SEC_2)
            {
                //P10_OUT.U = (0x1 << P2_BIT_LSB_IDX); /* LED_BLUE ON */
                GTM_TOM0_CH2_SR1.U = FadeControl( GTM_TOM0_CH2_SR1.U, 12500, 12500, SEC_2, SEC_2 );
            }
            else
            {
                //P10_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); /* LED_BLUE OFF */
                GTM_TOM0_CH2_SR1.U = FadeControl( GTM_TOM0_CH2_SR1.U, 0, 12500, SEC_2, SEC_2 );

                LED_BLUE_Timer = CLEAR;
                LED_BLUE_TimerEn = TIMER_OFF;
                LED_RED_TimerEn = TIMER_ON;
            }
        }
        else if (LED_RED_TimerEn == TIMER_ON)
        {
            if (LED_RED_Timer < SEC_2)
            {
                //P10_OUT.U = (0x1 << P1_BIT_LSB_IDX); /* LED_RED OFF */
                GTM_TOM0_CH1_SR1.U = FadeControl( GTM_TOM0_CH1_SR1.U, 12500, 12500, SEC_2, SEC_2 );
                GTM_TOM0_CH2_SR1.U = FadeControl( GTM_TOM0_CH2_SR1.U, 0, 12500, SEC_2, SEC_2 );
                //GTM_TOM0_CH1_SR1.U = 12500;
            }
            else
            {
                //P10_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); /* LED_RED OFF */
                GTM_TOM0_CH1_SR1.U = FadeControl( GTM_TOM0_CH1_SR1.U, 0, 12500, SEC_2, SEC_2 );

                LED_RED_Timer = CLEAR;
                LED_RED_TimerEn = TIMER_OFF;
                LED_RGB_RED_TimerEn = TIMER_ON;
            }
        }
        else if (LED_RGB_RED_TimerEn == TIMER_ON)
        {
            if (LED_RGB_RED_Timer < SEC_2)
            {
                P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;    /* LED_RGB_RED ON */
                P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); /* LED_RGB_GREEN OFF */
                P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); /* LED_RGB_BLUE OFF */
                GTM_TOM0_CH1_SR1.U = FadeControl( GTM_TOM0_CH1_SR1.U, 0, 12500, SEC_2, SEC_2 );
                //GTM_TOM0_CH1_SR1.U = 0;
            }
            else
            {
                P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); /* LED_RGB_RED OFF */
                P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); /* LED_RGB_GREEN OFF */
                P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); /* LED_RGB_BLUE OFF */

                LED_RGB_RED_Timer = CLEAR;
                LED_RGB_RED_TimerEn = TIMER_OFF;
                LED_RGB_GREEN_TimerEn = TIMER_ON;
            }
        }
        else if (LED_RGB_GREEN_TimerEn == TIMER_ON)
        {
            if (LED_RGB_GREEN_Timer < SEC_2)
            {
                P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); /* LED_RGB_RED OFF */
                P10_OUT.U |= 0x1 << P5_BIT_LSB_IDX;    /* LED_RGB_GREEN ON */
                P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); /* LED_RGB_BLUE OFF */
            }
            else
            {
                P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); /* LED_RGB_RED OFF */
                P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); /* LED_RGB_GREEN OFF */
                P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); /* LED_RGB_BLUE OFF */

                LED_RGB_GREEN_Timer = CLEAR;
                LED_RGB_GREEN_TimerEn = TIMER_OFF;
                LED_RGB_BLUE_TimerEn = TIMER_ON;
            }
        }
        else if (LED_RGB_BLUE_TimerEn == TIMER_ON)
        {
            if (LED_RGB_BLUE_Timer < SEC_2)
            {
                P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); /* LED_RGB_RED OFF */
                P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); /* LED_RGB_GREEN OFF */
                P10_OUT.U |= 0x1 << P3_BIT_LSB_IDX;    /* LED_RGB_BLUE ON */
            }
            else
            {
                P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX); /* LED_RGB_RED OFF */
                P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); /* LED_RGB_GREEN OFF */
                P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); /* LED_RGB_BLUE OFF */

                LED_RGB_BLUE_Timer = CLEAR;
                LED_RGB_BLUE_TimerEn = TIMER_OFF;
                BUZZER_TimerEn = TIMER_ON;
            }
        }
        else if (BUZZER_TimerEn == TIMER_ON)
        {
            if (BUZZER_Timer < SEC_2)
            {
                BUZZER = ON; /* BUZZER ON */
                if ( BUZZER_Timer < SEC_1 )
                {
                     GTM_TOM0_CH11_SR1.U = FadeControl( GTM_TOM0_CH11_SR1.U, 11000, 11000, SEC_1, SEC_1 );
                //OperationBuzzer(1000);
                    GTM_TOM0_CH11_SR0.U = FadeControl( GTM_TOM0_CH11_SR0.U, 0, 12500, SEC_1, SEC_1 );
                //GTM_TOM0_CH11_SR1.U +=1;
                }
                else
                {
                    GTM_TOM0_CH11_SR1.U = FadeControl( GTM_TOM0_CH11_SR1.U, 0, 11000, SEC_1, SEC_1 );
                    GTM_TOM0_CH11_SR0.U = FadeControl( GTM_TOM0_CH11_SR0.U, 12500, 12500, SEC_1, SEC_1 );
                }
            }
            else
            {
                //GTM_TOM0_CH11_SR0.U = 10000;
                BUZZER = OFF; /* BUZZER OFF */
                //GTM_TOM0_CH11_SR1.U = FadeControl( GTM_TOM0_CH11_SR1.U, 0, 5000, SEC_2, SEC_2 );
                //OperationBuzzer(100);
                //GTM_TOM0_CH11_SR1.U -=1;
                //GTM_TOM0_CH11_SR1.U = FadeControl( GTM_TOM0_CH11_SR1.U, 0, 11000, SEC_2, SEC_2 );
                //GTM_TOM0_CH11_SR0.U = FadeControl( GTM_TOM0_CH11_SR0.U, 12500, 12500, SEC_2, SEC_2 );
                BUZZER_Timer = CLEAR;
                BUZZER_TimerEn = TIMER_OFF;
                // ULTRASONIC_TimerEn = TIMER_ON;
                LED_BLUE_TimerEn = TIMER_ON;
            }
        }
        #if 0
        else if (ULTRASONIC_TimerEn == TIMER_ON)
        {
            //GTM_TOM0_CH11_SR1.U = FadeControl( GTM_TOM0_CH11_SR1.U, 0, 11000, SEC_2, SEC_2 );
            //GTM_TOM0_CH11_SR0.U = FadeControl( GTM_TOM0_CH11_SR0.U, 12500, 12500, SEC_2, SEC_2 );
            OperationBuzzer(0);
            if (DistanceErr == ON)
            {
                if (ULTRASONIC_Timer < SEC_2)
                {
                    if (ULTRASONIC_Timer < SEC_1)
                    {
                        GTM_TOM0_CH1_SR1.U = 12500;       /* LED_RED ON */
                        GTM_TOM0_CH2_SR1.U = 0;          /* LED_BLUE OFF */
                    }
                    else
                    {
                        GTM_TOM0_CH1_SR1.U = 0;       /* LED_RED OFF */
                        GTM_TOM0_CH2_SR1.U = 0;   /* LED_BLUE OFF */
                    }

                }
                else
                {
                    ULTRASONIC_Timer = CLEAR;
                    ULTRASONIC_TimerEn = TIMER_OFF;
                    LED_BLUE_TimerEn = TIMER_ON;
                }
            }
            else
            {
                if (ULTRASONIC_Timer < SEC_2)
                {
                    if (ULTRASONIC_Timer < SEC_1)
                    {
                        GTM_TOM0_CH1_SR1.U = 0;       /* LED_RED ON */
                        GTM_TOM0_CH2_SR1.U = 12500;          /* LED_BLUE OFF */
                    }
                    else
                    {
                        GTM_TOM0_CH1_SR1.U = 0;       /* LED_RED OFF */
                        GTM_TOM0_CH2_SR1.U = 0;   /* LED_BLUE OFF */
                    }
                }
                else
                {

                    ULTRASONIC_Timer = CLEAR;
                    ULTRASONIC_TimerEn = TIMER_OFF;
                    LED_BLUE_TimerEn = TIMER_ON;
                }
            }
        }
        #endif
        else
        {

        }
    }
}
