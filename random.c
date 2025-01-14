#include <REG_MPC82G516.H>
#include "random.h"

void randomNumberTimer_ISR(void) interrupt 3
{
    // Reload timer
    TR1 = 0;
    TL1 = TH1 = 0;
    TR1 = 1;
}

void initRandom(void)
{
    // Timer1 mode1
    TMOD &= 0x0f;
    TMOD |= 0x10;
    TL1 = TH1 = 0;
    TF1 = 0;
    ET1 = 1;
    EA = 1;
    TR1 = 1;
}

uint16 genRandomNum(void)
{
    uint16 val;
    TR1 = 0;
    val = TH1;
    val = (val << 8) | TL1;
    TR0 = 1;
    return val;
}