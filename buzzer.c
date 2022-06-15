#include "buzzer.h"
#include "led.h"
extern unsigned short tuned_distance_state;
extern unsigned int time_cnt;
extern unsigned int potentio_value; // delete
extern unsigned int rgb_en;
extern boolean emg_state;

static void InitGPIO(void);
static void InitGTM(void);

void InitBuzzer(void)
{
    InitGPIO();
    InitGTM();
    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x1 << HOST_TRIG_BIT_LSB_IDX;
    OperationBuzzer(0);
}

static void InitGPIO(void)
{
    P02_IOCR0.U &= ~(0x1F << PC3_BIT_LSB_IDX);
    P02_IOCR0.U |= 0x11 << PC3_BIT_LSB_IDX;
}


static void InitGTM(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    GTM_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable VADC

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    while ((GTM_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0)
        ; // wait until GTM module enabled

    // GTM clock configuration
    GTM_CMU_FXCLK_CTRL.U &= ~(0xF << FXCLK_SEL_BIT_LSB_IDX); // input clock of CMU_FXCLK --> CMU GCLK_EN
    GTM_CMU_CLK_EN.U |= 0x2 << EN_FXCLK_BIT_LSB_IDX;         // enable all CMU_FXCLK

    // GTM TOM0 PWM configuration
    GTM_TOM0_TGC1_GLB_CTRL.U |= 0x2 << UPEN_CTRL11_BIT_LSB_IDX;    // TOM channel 11 update enable
    GTM_TOM0_TGC1_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL11_BIT_LSB_IDX; // enable channel 11 on update trigger
    GTM_TOM0_TGC1_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL11_BIT_LSB_IDX; // enable channel 11 output on update trigger

    GTM_TOM0_CH11_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;         // high signal level for duty cycle
    GTM_TOM0_CH11_CTRL.U |= 0x1 << CLK_BIT_LSB_IDX;        // clock source --> CMU_FXCLK(1) = 6250 KHz
    GTM_TOM0_CH11_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);     // continuous mode enable
    GTM_TOM0_CH11_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX); // TRIG[x] = TRIG[x-1]

    GTM_TOM0_CH11_SR0.U = 12500 - 1; // PWM freq. = 6250 KHz / 12500 = 500 Hz
    GTM_TOM0_CH11_SR1.U = 1250 - 1;  // duty cycle = 1250 / 12500 = 10 % (temporary)

    GTM_TOUTSEL0.U &= ~(0x3 << SEL3_BIT_LSB_IDX); // TOUT3 --> TOM0 Channel 11

    // GTM TOM0 PWM configuration
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL1_BIT_LSB_IDX;    // TOM channel 1 update enablr
    GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL1_BIT_LSB_IDX; // enable channel 1 on update trigger
    GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL1_BIT_LSB_IDX; // enable channel 1 output on update trigger

    GTM_TOM0_CH1_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;         // high signal level for duty cycle
    GTM_TOM0_CH1_CTRL.U |= 0x1 << CLK_BIT_LSB_IDX;        // clock source --> CMU_FXCLK(!)    = 6250kHz
    GTM_TOM0_CH1_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);     // continuous mode enable
    GTM_TOM0_CH1_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX); // TRIG[x]  = TRIG[x-1]

    GTM_TOM0_CH1_SR0.U = 12500 - 1; // PWM freq.    = 6250kHz / 12500 = 500Hz
    GTM_TOM0_CH1_SR1.U = 0;         // duty cycle = 1250 / 12500 = 10% (temporary)

    GTM_TOUTSEL6.U &= ~(0x3 << SEL7_BIT_LSB_IDX); // TOUT103 --> TOM0 channel 1
                                                  // 103 = 16 * 6 + 7

    // GTM TOM0 PWM configuration
    GTM_TOM0_TGC0_GLB_CTRL.U |= 0x2 << UPEN_CTRL2_BIT_LSB_IDX;    // TOM channel 2 update enablr
    GTM_TOM0_TGC0_ENDIS_CTRL.U |= 0x2 << ENDIS_CTRL2_BIT_LSB_IDX; // enable channel 2 on update trigger
    GTM_TOM0_TGC0_OUTEN_CTRL.U |= 0x2 << OUTEN_CTRL2_BIT_LSB_IDX; // enable channel 2 output on update trigger

    GTM_TOM0_CH2_CTRL.U |= 0x1 << SL_BIT_LSB_IDX;         // high signal level for duty cycle
    GTM_TOM0_CH2_CTRL.U |= 0x1 << CLK_BIT_LSB_IDX;        // clock source --> CMU_FXCLK(!)    = 6250kHz
    GTM_TOM0_CH2_CTRL.U &= ~(0x1 << OSM_BIT_LSB_IDX);     // continuous mode enable
    GTM_TOM0_CH2_CTRL.U &= ~(0x1 << TRIGOUT_BIT_LSB_IDX); // TRIG[x]  = TRIG[x-1]

    GTM_TOM0_CH2_SR0.U = 12500 - 1; // PWM freq.    = 6250kHz / 12500 = 500Hz
    GTM_TOM0_CH2_SR1.U = 0;         // duty cycle = 1250 / 12500 = 10% (temporary)

    GTM_TOUTSEL6.U &= ~(0x3 << SEL8_BIT_LSB_IDX); // TOUT103 --> TOM0 channel 1
                                                  // 103 = 16 * 6 + 7
}

void OperationBuzzer(unsigned short duty)
{
    GTM_TOM0_CH11_SR1.U = duty;
}

void Mode2Buzzer(void)
{
    static boolean state = FALSE;

    if (emg_state) {
        OperationBuzzer(3000);
    }
    else if (tuned_distance_state < 10) {
        OperationBuzzer(8000);

    }
    else if (tuned_distance_state < 100)
    {
        if (state)
            OperationBuzzer(8000);
        // OperationBuzzer(tuned_distance_state*5); //potentio_value*100
        else
            OperationBuzzer(0);

        if (tuned_distance_state < time_cnt)
        {
            state = !state;
            time_cnt = 0;
        }
    }
    else
    {
        OperationBuzzer(0);
    }
    /*
    if(tuned_distance_state > 100-25) {   // 25 is offset
        state = !state;

        P10_OUT.U |= (0x1 << P1_BIT_LSB_IDX); // red on
        P10_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX); // blue off
        rgb_en=0;
        time_cnt = 0;
    }

    else if ( ( 50 - tuned_distance_state*0.5) < time_cnt){ //( 50 - potentio_value*5)  // potentio_value high -> rapid beep
        state = !state;
        rgb_en = 1;
        time_cnt = 0;
        P10_OUT.U |= (0x1 << P2_BIT_LSB_IDX); // blue on
        P10_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX); // red off
    }
    */
}