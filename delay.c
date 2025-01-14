#include <REG_MPC82G516.H>
#include "delay.h"

void delay(uint16 val)
{
    while (val != 0) 
        val--;
}
