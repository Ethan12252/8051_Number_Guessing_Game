#include <REG_MPC82G516.H>
#include "int.h"
#include "pushbutton.h"

/* 
const uint8 code keyCodeTable[]
    = {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

uint8 getKeyValue()
{
    uint8 i;
    uint8 keyHigh = KEYPORT_HIGHER;
    uint8 keyLow = KEYPORT_LOWER ;
    for(i=0;i<8;i++)
    {
        if(keyHigh == keyCodeTable[i])
            return i+8;
        if(keyLow == keyCodeTable[i])
            return i;
    }
    return NO_BUTTON;
}
*/

uint8 getKeyValue(void)
{
    uint16 KEY_CD = 0x8000;
    uint8 key_value1 = 15;
    uint16 key_code1 = 0;
    key_code1 = (uint16)KEYPORT_HIGHER;
    key_code1 <<= 8;
    key_code1 |= (uint16)KEYPORT_LOWER;
    key_code1 = ~key_code1;
    while ((key_code1 != KEY_CD) && (KEY_CD != 0)) {
        key_value1--;
        KEY_CD >>= 1;
    }
    if (KEY_CD == 0)
        key_value1 = NO_BUTTON;
    return key_value1;
}
