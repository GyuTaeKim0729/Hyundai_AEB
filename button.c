
#include "button.h"

static void InitERU(void);

void InitButton(void)
{
    InitERU();
}

static void InitERU(void)
{
    // ----- Button 1 --------
    P02_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX); // reset P02 PC1
    P02_IOCR0.U |= 0x02 << PC1_BIT_LSB_IDX;    // set P02.1 push-pull general output

    SCU_EICR1.U &= ~(0x7 << EXIS0_BIT_LSB_IDX); // Clear
    SCU_EICR1.U |= 0x2 << EXIS0_BIT_LSB_IDX;    // Set ERS2`s EXIS0`s P02.1 (001)               *********************************

    SCU_EICR1.U |= 0x1 << FEN0_BIT_LSB_IDX; // Falling edge enable
    SCU_EICR1.U |= 0x1 << REN0_BIT_LSB_IDX; // Rising edge enable                              **********************************
    // SCU_EICR1.U |= 0x1 << (FEN0_BIT_LSB_IDX + 1);     // Falling edge enable

    SCU_EICR1.U |= 0x1 << EIEN0_BIT_LSB_IDX; // Trigger event is enabled

    SCU_EICR1.U &= ~(0x7 << INP0_BIT_LSB_IDX); // Input Node Pointer -> trigger output OGU0 (000)

    SCU_IGCR0.U &= ~(0x3 << IGP0_BIT_LSB_IDX); // Clear
    SCU_IGCR0.U |= 0x1 << IGP0_BIT_LSB_IDX;    // Set IGP0`s IOUT (01)

    SRC_SCU_SCU_ERU0.U &= ~(0xFF << SRPN_BIT_LSB_IDX); // Clear
    SRC_SCU_SCU_ERU0.U |= 0x0C << SRPN_BIT_LSB_IDX;    // Service Request Priority Number

    SRC_SCU_SCU_ERU0.U &= ~(0x3 << TOS_BIT_LSB_IDX); // Type of Service Control

    SRC_SCU_SCU_ERU0.U |= 1 << SRE_BIT_LSB_IDX; // Service Request Enable
    
    // ----- Button 2 --------
    P02_IOCR0.U &= ~(0x1F << PC0_BIT_LSB_IDX); // reset P02 PC0
    P02_IOCR0.U |= 0x02 << PC0_BIT_LSB_IDX;    // set P02.0 push-pull general output

    SCU_EICR1.U &= ~(0x7 << EXIS1_BIT_LSB_IDX); // Clear
    SCU_EICR1.U |= 0x2 << EXIS1_BIT_LSB_IDX;    // Set ERS3`s EXIS0`s P02.0 (001)

    SCU_EICR1.U |= 0x1 << FEN1_BIT_LSB_IDX; // Falling edge enable
    // SCU_EICR1.U |= 0x1 << (FEN1_BIT_LSB_IDX + 1);     // Falling edge enable

    SCU_EICR1.U |= 0x1 << EIEN1_BIT_LSB_IDX; // Trigger event is enabled

    SCU_EICR1.U &= ~(0x7 << INP1_BIT_LSB_IDX); // Input Node Pointer
    SCU_EICR1.U |= 0x1 << INP1_BIT_LSB_IDX; // trigger output OGU1 (001)

    SCU_IGCR0.U &= ~(0x3 << IGP1_BIT_LSB_IDX); // Clear
    SCU_IGCR0.U |= 0x1 << IGP1_BIT_LSB_IDX;    // Set IGP1`s IOUT (01)

    SRC_SCU_SCU_ERU1.U &= ~(0xFF << SRPN_BIT_LSB_IDX); // Clear
    SRC_SCU_SCU_ERU1.U |= 0x0B << SRPN_BIT_LSB_IDX;    // Service Request Priority Number

    SRC_SCU_SCU_ERU1.U &= ~(0x3 << TOS_BIT_LSB_IDX); // Type of Service Control

    SRC_SCU_SCU_ERU1.U |= 1 << SRE_BIT_LSB_IDX; // Service Request Enable
    
}
