#include "potentiometer.h"

extern unsigned int potentio_value;

void InitPotentio(void)
{
    InitVADC();
}

void OperationPotentio(void)
{
    static unsigned int adc_result;
    VADC_startConversion();
    adc_result = VADC_readResult();
    CalculateRotation(&adc_result);
}

void CalculateRotation(const int *adc_result)
{
    potentio_value = *adc_result*((double)1000/4096); // rank 1000
}

void OperationPotentio_FREQ(void)
{
    VADC_startConversion();
    OpertaionTimer(TRUE, VADC_readResult()*((double)1000/4096));
}

static void InitVADC(void)
{
    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to clear ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) & ~(1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    VADC_CLC.U &= ~(1 << DISR_BIT_LSB_IDX); // enable VADC

    // Password Access to unlock SCU_WDTSCON0
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) & ~(1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) != 0)
        ; // wait until unlocked

    // Modify Access to ENDINIT
    SCU_WDTCPU0_CON0.U = ((SCU_WDTCPU0_CON0.U ^ 0xFC) | (1 << LCK_BIT_LSB_IDX)) | (1 << ENDINIT_BIT_LSB_IDX);
    while ((SCU_WDTCPU0_CON0.U & (1 << LCK_BIT_LSB_IDX)) == 0)
        ; // wait until locked

    // VDC Configurations
    while ((VADC_CLC.U & (1 << DISS_BIT_LSB_IDX)) != 0)
        ; // wait until VADC Module enabled

    VADC_G4_ARBPR.U |= 0x3 << PRIO0_BIT_LSB_IDX;   // highest priority for Request Source 0
    VADC_G4_ARBPR.U &= ~(0x1 << CSM0_BIT_LSB_IDX); // Wait-for-Start mode
    VADC_G4_ARBPR.U |= 0x1 << ASEN0_BIT_LSB_IDX;   // Arbitration Source Input 0 enable

    VADC_G4_QMR0.U &= ~(0x3 << ENGT_BIT_LSB_IDX); // Clear
    VADC_G4_QMR0.U |= 0x1 << ENGT_BIT_LSB_IDX;    // enable Conversion Request
    VADC_G4_QMR0.U |= 0x1 << FLUSH_BIT_LSB_IDX;   // Clear ADB queue

    VADC_G4_ARBCFG.U |= 0x3 << ANONC_BIT_LSB_IDX; // ADC Normal Operation

    VADC_G4_ICLASS0.U &= ~(0x7 << CMS_BIT_LSB_IDX); // Class 0 Standard Conversion (12-bits)

    VADC_G4_CHCTR7.U |= 0x1 << RESPOS_BIT_LSB_IDX;    // result right-aligned
    VADC_G4_CHCTR7.U &= ~(0xF << RESREG_BIT_LSB_IDX); // Store Result @ Result Register G4RES0
    VADC_G4_CHCTR7.U &= ~(0x3 << ICLSEL_BIT_LSB_IDX); // Class 0

    VADC_G4_CHASS.U |= 0x1 << ASSCH7_BIT_LSB_IDX;
}

static void VADC_startConversion(void)
{
    VADC_G4_QINR0.U |= 0x07;                   // no. of Request Channel = 7
    VADC_G4_QMR0.U |= 0x1 << TREV_BIT_LSB_IDX; // Generate Conversion start Trigger event
}

static unsigned int VADC_readResult(void)
{
    unsigned int result;

    while ((VADC_G4_RES0.U & (0x1 << VF_BIT_LSB_IDX)) == 0)
        ; // wait until read available
    result = VADC_G4_RES0.U & (0xFFF << RESULT_BIT_LSB_IDX);

    return result;
}
