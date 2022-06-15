#include "timer.h"

static void InitCCU60(void);

extern unsigned int time_cnt;

void InitTimer(void)
{
    InitCCU60();
}

static void InitCCU60(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    CCU60_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable CCY
    

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    //-------------------

    while ((CCU60_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0)
        ; // wait until CCU60 module enabled

    //-------------------

    /*
    CCU60_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX); // f_T12 = f_CCU6 / prescaler
    CCU60_TCTR0.U |= 0x2 << T12CLK_BIT_LSB_IDX; // f_CCU6 = 50 Mhz, prescaler = 1024
    CCU60_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX; // f_T12 = 48,828 Hz

    CCU60_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX); // T12 auto reset when period match (PM) occuer

    CCU60_T12PR.U = 24414 - 1; // 0.5s // PM Interrupt freq. = f_T12 / (T12PR + 1)
    // CCU60_T12PR.U = 765 - 1; // 0.01s // PM Interrupt freq. = f_T12 / (T12PR + 1) 
    CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX; // load T12PR from shadow register

    CCU60_T12.U = 0; // clear T12 Counter Register

    //-------------------

    // CCU60 T12 PM(Period Match) interrupt setting
    CCU60_INP.U &= ~(0x3 << INPT12_BIT_LSB_IDX); // service request output 500 selected
    CCU60_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX; // enable T12 PM interrupt

    //-------------------
    
    // CCU60 T12 Counting Start
    // CCU60_TCTR4.U |= 0x1 << T12RS_BIT_LSB_IDX; // T12 Start Counting;
    */

    CCU60_TCTR0.U &= ~(0x7 << T12CLK_BIT_LSB_IDX); // f_T12 = f_CCU6 / prescaler
    CCU60_TCTR0.U |= 0x2 << T12CLK_BIT_LSB_IDX;    // f_CCU6 = 50 MHz, prescaler = 1024
    // CCU60_TCTR0.U |= 0x1 << T12PRE_BIT_LSB_IDX;                 // f_T12 = 48,828Hz PRE(1/256)is not used. = 12.5MHz

    CCU60_TCTR0.U &= ~(0x1 << CTM_BIT_LSB_IDX); // T12 auto reset when period match (PM) occur

    // CCU60_T12PR.U   = 24414 - 1;                                // PM interrupt freq. f_T12 / (T12PR + 1) 0.5초마다
    CCU60_T12PR.U = 125 - 1;
    CCU60_TCTR4.U |= 0x1 << T12STR_BIT_LSB_IDX; // load T12PR from shadow register

    CCU60_TCTR2.B.T12SSC = 0x1; // Single shot control

    CCU60_T12.U = 0; // clear T12 counter register

    // CCU60 T12 PM interrupt setting
    CCU60_INP.U &= ~(0x3 << INPT12_BIT_LSB_IDX); // setting request output SR0 selected
    CCU60_IEN.U |= 0x1 << ENT12PM_BIT_LSB_IDX;   // load T12PR from shadow register

    // SRC Setting for CCU60
    SRC_CCU6_CCU60_SR0.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR0.U |= 0x0D << SRPN_BIT_LSB_IDX; // set Priority 0x0B
    
    SRC_CCU6_CCU60_SR0.U &= ~(0x3 << TOS_BIT_LSB_IDX); // CPU0 service 12 PM interrupt

    SRC_CCU6_CCU60_SR0.U |= 0x1 << SRE_BIT_LSB_IDX; // SR0 enabled

    /////////////////////////////////////////////
    // CCU T13 //////////////////////////////////
    /////////////////////////////////////////////

    CCU60_TCTR0.U &= ~(0x7 << T13CLK_BIT_LSB_IDX); // f_T12 = f_CCU6 / prescaler
    CCU60_TCTR0.U |= 0x2 << T13CLK_BIT_LSB_IDX; // f_CCU6 = 50 Mhz, prescaler = 1024
    CCU60_TCTR0.U |= 0x1 << T13PRE_BIT_LSB_IDX; // f_T12 = 48,828 Hz

    CCU60_T13PR.U = 24414 - 1; // 0.5s // PM Interrupt freq. = f_T12 / (T12PR + 1)
    CCU60_TCTR4.U |= 0x1 << T13STR_BIT_LSB_IDX; // load T12PR from shadow register

    CCU60_T13.U = 0; // clear T12 Counter Register

    //-------------------

    // CCU60 T12 PM interrupt setting
    CCU60_INP.U &= ~(0x3 << INPT13_BIT_LSB_IDX); // setting request output SR0 selected
    CCU60_INP.U |= 0x1 << INPT13_BIT_LSB_IDX;
    CCU60_IEN.U |= 0x1 << ENT13PM_BIT_LSB_IDX;   // load T13PR from shadow register

    //-------------------

    // SRC Setting for CCU60
    SRC_CCU6_CCU60_SR1.U &= ~(0xFF << SRPN_BIT_LSB_IDX);
    SRC_CCU6_CCU60_SR1.U |= 0x0A << SRPN_BIT_LSB_IDX; // set Priority 0x0C
    SRC_CCU6_CCU60_SR1.U &= ~(0x3 << TOS_BIT_LSB_IDX); // CPU0 service 12 PM interrupt

    SRC_CCU6_CCU60_SR1.U |= 0x1 << SRE_BIT_LSB_IDX; // SR0 enabled

    // CCU60 T13 Counting Start
    // CCU60_TCTR4.U |= 0x1 << T13RS_BIT_LSB_IDX; // T13 Start Counting;
}

void OpertaionTimer(boolean state, unsigned int freq)
{
    if (state){
        CCU60_TCTR4.U &= ~(0x3); // T13 Clear
        time_cnt = 0;
        CCU60_T13PR.U = freq - 1;                  // 1s // PM Interrupt freq. = f_T12 / (T12PR + 1)
        CCU60_TCTR4.U |= 0x1 << T13STR_BIT_LSB_IDX; // load T13PR from shadow register

        CCU60_TCTR4.U |= 0x1 << T13RS_BIT_LSB_IDX; // T13 Start Counting;
    }
    else {
        CCU60_TCTR4.U |= 0x1 << T13RR_BIT_LSB_IDX; // T13 Stop Counting;
    }
}

