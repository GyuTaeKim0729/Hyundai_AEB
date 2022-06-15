#include "led.h"

extern unsigned int time_cnt;
extern unsigned int potentio_value; // delete

static void InitGPIO(void);

void InitRGB(void)
{
    InitGPIO();
}

static void InitGPIO(void)
{
    P02_IOCR4.B.PC7 = 0x0; // Clear
    P10_IOCR4.B.PC5 = 0x0; // Clear
    P10_IOCR0.B.PC3 = 0x0; // Clear

    P02_IOCR4.B.PC7 |= 0x10; // Set
    P10_IOCR4.B.PC5 |= 0x10; // Set
    P10_IOCR0.B.PC3 |= 0x10; // Set
}

void PowerRGB(boolean state, char color)
{
    switch (color)
    {
    case 'R':
        if (state)
            P02_OUT.B.P7 = 0x1;
        else
            P02_OUT.B.P7 = 0x0;
        break;
    case 'G':
        if (state)
            P10_OUT.B.P5 = 0x1;
        else
            P10_OUT.B.P5 = 0x0;
        break;
    case 'B':
        if (state)
            P10_OUT.B.P3 = 0x1;
        else
            P10_OUT.B.P3 = 0x0;
        break;
    }
}

void OperationRGB(boolean state, char color)
{
    if (!state)
        color = 'Z';

    switch (color)
    {
    case 'R':
        PowerRGB(TRUE, 'R');
        PowerRGB(FALSE, 'G');
        PowerRGB(FALSE, 'B');
        break;
    case 'M':
        PowerRGB(TRUE, 'R');
        PowerRGB(FALSE, 'G');
        PowerRGB(TRUE, 'B');
        break;
    case 'Y':
        PowerRGB(TRUE, 'R');
        PowerRGB(TRUE, 'G');
        PowerRGB(FALSE, 'B');
        break;
    case 'G':
        PowerRGB(FALSE, 'R');
        PowerRGB(TRUE, 'G');
        PowerRGB(FALSE, 'B');
        break;
    case 'B':
        PowerRGB(FALSE, 'R');
        PowerRGB(FALSE, 'G');
        PowerRGB(TRUE, 'B');
        break;
    case 'C':
        PowerRGB(FALSE, 'R');
        PowerRGB(TRUE, 'G');
        PowerRGB(TRUE, 'B');
        break;
    case 'W':
        PowerRGB(TRUE, 'R');
        PowerRGB(TRUE, 'G');
        PowerRGB(TRUE, 'B');
        break;
    default:
        PowerRGB(FALSE, 'R');
        PowerRGB(FALSE, 'G');
        PowerRGB(FALSE, 'B');
        break;
    }
}

void ResetRGB(void) {
    PowerRGB(FALSE, 'R');
    PowerRGB(FALSE, 'G');
    PowerRGB(FALSE, 'B');
}

void Mode2RGB(void)
{
    static uint8 cnt = 0;
    
    switch (cnt)
    {
    case 0:
        OperationRGB(TRUE, 'R');
        break;
    case 1:
        OperationRGB(TRUE, 'G');
        break;
    case 2:
        OperationRGB(TRUE, 'B');
        break;
    default:
        break;
    }
    cnt++;
    if (cnt > 2)
        cnt = 0;
}
