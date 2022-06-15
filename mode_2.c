#include "mode_2.h"

extern boolean mode2_status;
extern unsigned int time_cnt;
extern unsigned short mode2_no;

static void TimeSec(void);

static unsigned int time_s;

void Mode2(void)
{
    if (mode2_status)
    {
        switch (mode2_no)
        {
        case 0:
            TimeSec();
            switch (time_s)
            {
            case 0:
                OperationBuzzer(0);
                OperationBuzzer(4000);
                ToggleLEDB();
                ToggleLEDR();
                break;
            case 1:
                OperationBuzzer(0);
                ToggleLEDB();
                ToggleLEDR();
                break;
            case 2:
                OperationBuzzer(4000);
                break;
            case 3:
                OperationBuzzer(0);
                ToggleLEDB();
                mode2_no++;
                break;
            default:
                break;
            }
            break;
        case 1:
            OperationPotentio(); // potentiometer -> potentio_value 변경
            GetDistance(); // ultrasonic + potentio_value -> distance 변경
            Mode2Buzzer();
            Mode2Led();
            break;
        default:
            break;
        }
    }
}

static void TimeSec(void)
{
    if(time_cnt >= 80){ // 10ms * 100 = 1sec
        time_s++;    
        time_cnt = 0;
    }
}

void ResetMode2(void)
{
    time_cnt = 0;
    mode2_no = 0;
    mode2_status = FALSE;
    time_s = 0;
    ResetLED();
    ResetRGB();
    OperationBuzzer(0);
    OpertaionTimer(FALSE, 48828);
}