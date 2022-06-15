#include "ultrasonic.h"

extern unsigned short tuned_distance_state; // rank 0 ~ 100
extern unsigned int potentio_value;
extern unsigned int range;
extern unsigned char range_valid_flag;
extern unsigned int time_cnt_rgb;
extern unsigned int time_emg;

unsigned int distance_old;
unsigned int ultrasonic_data;
unsigned int distance;

double distance_sub;
double velocity_gain = 0.000001;

double EMG_velocity;
double EMG_velocity_old;
double Tsamp;

double LPF_gain = 0.5;
double TTC;
double EMG_second = 0.00015; // 0.0002;
unsigned int LEDR_cnt;

extern boolean emg_state;

static void InitUsonic(void);
static void InitCCU61(void);

void InitUltrasonic(void)
{
    InitUsonic();
    InitCCU61();
}

void Sonic_CalculateDistance(void)
{
    
    // AEB (Auto Emergency Brake)

    if (range < 200)
        tuned_distance_state = (double)(range * potentio_value) / 200000 * 100;
    else
        tuned_distance_state = 100;

    distance_old = distance; // 이전 거리
    distance = range;        // 현재 거리

    distance_sub = velocity_gain * (distance - distance_old); // 속도 gain * (현재 - 이전)
    // distance_sub = (distance_sub >= 0 ? distance_sub : -1 * distance_sub); //항상 0보다 큰 양수이도록.

    EMG_velocity_old = EMG_velocity;      // 이전 긴급 속도
    EMG_velocity = distance_sub / (0.01); //                // Time period  (10ms) --> 만약 타이머가 10ms 가 아니라면 변경해줄 것.

    EMG_velocity = LPF_gain * EMG_velocity_old + (1 - LPF_gain) * EMG_velocity; // 현재 속도 = LPF_Gain * 이전 속도 + (1-LPF_Gain) * 현재 속도

    if (EMG_velocity > 0.01)
        TTC = (double)distance / EMG_velocity; // TCC = 현재 거리 / 현재 속도
    else
        TTC = (double)distance / 0.01; // TCC = 현재 거리 / 현재 속도

    if (TTC <= EMG_second && TTC > 0 && range > 60)
    {
        emg_state = TRUE;
        time_emg = 0;
        ResetLED();
    }

    if (emg_state)
    {
        if (time_emg % 20 == 0)
            ToggleLEDR();
        if (time_emg > 500)
            emg_state = FALSE;
    }
    else {
        ResetLED();
        ToggleLEDB();
    }

    // if (TTC <= EMG_second) // EMG_secnond : 위험상황을 판단 기준이 되는 값(second)
    // {
    //     // tuned_distance_state = 1;

    //     if (LEDR_cnt == 500)
    //     {
    //         ToggleLEDR();
    //         ToggleLEDB();
    //         LEDR_cnt = 0;
    //     }
    //     else
    //         LEDR_cnt++;
    // }
    // else
    // {
    //     ;
    // }

    /*
    if (tuned_distance_state < 10) {
        static boolean state;
        if (state){
            ToggleLEDR();
        }
        else
            ResetLED();
        if (20 < time_cnt_rgb)
        {
            state = !state;
            time_cnt_rgb = 0;
        }
    }
    else {
        ResetLED();
        ToggleLEDB();
    }
    */

    /*
    Code Variables

    // ultrasonic_data : 입력 받은 초음파 값
    // distance : 현재 샘플링 시점[k]의 거리
    // distance_old : 이전 샘플링 시점[k-1]의 거리
    // distance_sub : 현재 거리 값과 이전 거리 값의 오차
    // velocity_gain : 오차의 민감도를 조절할 수 있는 게인

    // EMG_velocity : 현재 샘플링 시점[k]시간에 따른 거리의 변화율 (=속도)
    // EMG_velocity_old : 이전 샘플링 시점[k-1]시간에 따른 거리의 변화율 (=속도)
    // Tsamp : Time period (PWM freq.) (10ms)
    // LPF_gain : low-pass filter 게인 (0 ~ 1 사이의 값)
    // TTC : 충돌까지 걸리는 시간 (second) (TTC : Time-to-collision)
    // // EMG_secnond : 위험상황을 판단 기준이 되는 값(second)

    */
}

void GetDistance(void)
{
    // for (unsigned int i = 0; i < 1000000; i++);
    usonicTrigger();
    while (range_valid_flag == 1)
        ;
    Sonic_CalculateDistance();

    // if (range >= 250) // red
    // {
    //     P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;
    //     P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
    //     P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);

    //     // GTM_TOM0_CH1_SR1.U  = 0;
    // }
    // else if (range >= 200) // green
    // {
    //     P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    //     P10_OUT.U |= 0x1 << P5_BIT_LSB_IDX;
    //     P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX);

    //     // GTM_TOM0_CH1_SR1.U  = 1000;
    // }
    // else if (range >= 100) // blue
    // {
    //     P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);
    //     P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX);
    //     P10_OUT.U |= 0x1 << P3_BIT_LSB_IDX;

    //     // GTM_TOM0_CH1_SR1.U  = 7000;
    // }
    // else // white
    // {
    //     P02_OUT.U |= 0x1 << P7_BIT_LSB_IDX;
    //     P10_OUT.U |= 0x1 << P5_BIT_LSB_IDX;
    //     P10_OUT.U |= 0x1 << P3_BIT_LSB_IDX;

    //     // GTM_TOM0_CH1_SR1.U  = 12500;
    // }
}

static void InitUsonic(void)
{
    P02_IOCR4.U &= ~(0x1F << PC6_BIT_LSB_IDX); // reset P10 PC1
    P00_IOCR4.U &= ~(0x1F << PC4_BIT_LSB_IDX); // reset P10 PC1

    P00_IOCR4.U |= 0x01 << PC4_BIT_LSB_IDX; // set P0.4
    P02_IOCR4.U |= 0x10 << PC6_BIT_LSB_IDX; // set P2.6 Trigger

    P02_OUT.U &= ~(0x1 << P6_BIT_LSB_IDX);
}

void usonicTrigger(void)
{
    P02_OUT.U |= 0x1 << P6_BIT_LSB_IDX;
    range_valid_flag = 0;
    CCU60_TCTR4.U = 0x1 << T12RS_BIT_LSB_IDX;
}

static void InitCCU61(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    CCU61_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable CCY

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    // CCU60 T12 configuration
    while ((CCU61_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0)
        ; // wait until CCU60 module enabled

    CCU61_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX); // f_T12 = f_CCU6 / prescaler
    CCU61_TCTR0.U |= 0x2 << T12CLK_BIT_LSB_IDX;    // f_CCU6 = 50 MHz, prescaler = 1024

    CCU61_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX; // f_T12 = 48,828Hz PRE(1/256)is not used. = 12.5MHz

    // CCU61_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX); // T12 auto reset when period match (PM) occur

    // CCU60_T12PR.U   = 24414 - 1;                                // PM interrupt freq. f_T12 / (T12PR + 1) 0.5초마다
    CCU61_T12PR.U = 100000 - 1;
    CCU61_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX; // load T12PR from shadow register

    // CCU61_TCTR2.B.T12SSC = 0x1; // Single shot control

    CCU61_T12.U = 0; // clear T12 counter register

    //    // CCU60 T23 PM interrupt setting
    //    CCU61_INP.U &= ~( 0x3 << INPT12_BIT_LSB_IDX );              // setting request output SR0 selected
    //    CCU61_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX;                  // load T12PR from shadow register
    //
    //    // SRC setting for CCU60
    //    SRC_CCU6_CCU61_SR0.U    &= ~(0xFF << SRPN_BIT_LSB_IDX);
    //    SRC_CCU6_CCU61_SR0.U    |= 0x0A << SRPN_BIT_LSB_IDX;        // set priority 0x0B
    //
    //    SRC_CCU6_CCU61_SR0.U    &= ~(0x03 << TOS_BIT_LSB_IDX);      // CPU0 service T12 PM interrupt
    //
    //    SRC_CCU6_CCU61_SR0.U    |= 0x1 << SRE_BIT_LSB_IDX;          // SR0 enabled

    // CCU60 T12 counting start
    // CCU60_TCTR4.U   |= 0x1 << T12RS_BIT_LSB_IDX;                 // T12 start counting (when I want)
}