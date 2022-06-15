#include "mode_1.h"

extern boolean mode1_status;    // button -> checking mode / Use : [Main]
extern unsigned short mode1_no; // checking scenario no / Use : [Main]
extern unsigned int time_cnt;

void Mode1(void)
{
    if (mode1_status)
    {
        switch (time_cnt)
        {
        case 0:
            ToggleLEDB();
            break;
        case 1:
            ToggleLEDB();
            break;
        case 2:
            ToggleLEDR();
            break;
        case 3:
            ToggleLEDR();
            break;
        case 4:
            OperationRGB(TRUE, 'R');
            break;
        case 5:
            OperationRGB(TRUE, 'G');
            break;
        case 6:
            OperationRGB(TRUE, 'B');
            break;
        case 7:
            OperationRGB(TRUE, 'R');
            break;
        case 8:
            OperationRGB(TRUE, 'G');
            break;
        case 9:
            OperationRGB(TRUE, 'B');
            break;
        case 10:
            OperationRGB(FALSE, 'Z');
            break;
        case 11:
            OperationBuzzer(6000);
            break;
        case 12:
            OperationBuzzer(0);
            break;
        case 13:
            OperationBuzzer(8000);
            break;
        case 14:
            OperationBuzzer(0);
            break;
        case 15:
            OperationBuzzer(11000);
            break;
        case 16:
            OperationBuzzer(0);
            break;
        // Sonic Check
        case 18:
            ToggleLEDB();
            break;
        case 21:
            ResetMode1();
            break;
        default:
            break;
        }
    }
}

void ResetMode1(void)
{
    time_cnt = 0;
    mode1_status = FALSE;
    OpertaionTimer(FALSE, 48828);
    ResetLED();
    ResetRGB();
}
