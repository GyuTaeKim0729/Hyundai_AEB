#include "led.h"

extern unsigned short tuned_distance_state; // rank 0 ~ 100
extern unsigned int time_cnt_rgb;
extern unsigned int potentio_value;
extern unsigned int rgb_en;
extern boolean emg_state;

static void InitGPIO(void);

void InitLED(void)
{
    InitGPIO();
}

static void InitGPIO(void)
{
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX); // reset P10 PC1
    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX); // reset P10 PC2

    P10_IOCR0.U |= 0x10 << PC1_BIT_LSB_IDX; // set P10.1 push-pull general output
    P10_IOCR0.U |= 0x10 << PC2_BIT_LSB_IDX; // set P10.2 push-pull general output
}

void initREDLEDPWM(void)
{
    P10_IOCR0.U &= ~(0x1F << PC1_BIT_LSB_IDX); // reset P10_IOCR0 PC1
    P10_IOCR0.U &= ~(0x1F << PC2_BIT_LSB_IDX); // reset P10_IOCR0 PC2

    P10_IOCR0.U |= 0x11 << PC1_BIT_LSB_IDX; // set P10.1
    P10_IOCR0.U |= 0x11 << PC2_BIT_LSB_IDX; // set P10.1 push-pull general output
}

void ToggleLEDR(void)
{
    P10_OUT.U ^= 0x1 << P1_BIT_LSB_IDX;
}

void ToggleLEDB(void)
{
    P10_OUT.U ^= 0x1 << P2_BIT_LSB_IDX;
}

void ResetLED(void)
{
    P10_OUT.U &= ~(0x1 << P1_BIT_LSB_IDX);
    P10_OUT.U &= ~(0x1 << P2_BIT_LSB_IDX);
}
void Mode2Led(void)
{
    /*
    if( rgb_en & ( (potentio_value*0.2 + 10) < time_cnt_rgb) ){     // potentio_value high -> rgb blink low
        Mode2RGB();
        time_cnt_rgb = 0;
    }
    */
    static boolean state;
    if (emg_state) {
        if (state)
            OperationRGB(FALSE, 'R');
        else
            OperationRGB(TRUE, 'R');
        if (20 < time_cnt_rgb)
        {
            state = !state;
            time_cnt_rgb = 0;
        }
    }
    else if (tuned_distance_state < 10)
    {
        OperationRGB(TRUE, 'R');
    }
    else if ((double)1 / tuned_distance_state * 1200 < time_cnt_rgb)
    {
        Mode2RGB();
        time_cnt_rgb = 0;
    }
}
