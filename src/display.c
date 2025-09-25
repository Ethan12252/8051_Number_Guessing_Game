#include <REG_MPC82G516.H>
#include "display.h"
#include "int.h"

uint8 data dispBuffer[4];

// Display data table
static uint8 code dispDataTable[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, // 0~9
    0xbf,                                                       // dash
    0xc7,                                                       // L
    0xa3,                                                       // o
    0x89,                                                       // H
    0xef,                                                       // i
    0xff                                                        // None
};

// Display drive Table
static const uint8 code dispDriveTable[] = {
	0xF7,  // D3
	0xFB,  // D2
	0xFD,  // D1
	0xFE   // D0
}; 


void dispUpdate_ISR(void) interrupt 1 using 2
{
    static uint8 dispUpdateCnt = 0;
    TR0 = 0;
    TL0 = TIMER0_VAL_LOW;
    TH0 = TIMER0_VAL_HIGH;
    TR0 = 1;
    dispUpdateCnt++;
    if (dispUpdateCnt == 4)
        dispUpdateCnt = 0;
    DISP_DATA_PORT = dispDataTable[dispBuffer[dispUpdateCnt]];
    DISP_DRIVE_PORT = dispDriveTable[dispUpdateCnt];
}

void initDispUpdate(void)
{
    // Timer0 mode1 (16bit timer)
    TMOD &= 0xf0;
    TMOD |= 0x01;
    TL0 = TIMER0_VAL_LOW;
    TH0 = TIMER0_VAL_HIGH;
    TF0 = 0;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void displayNumber(uint16 num)
{
    // Display a 4 digits decimal number
    // Up to 9999 (4 digits)
    dispBuffer[0] = num % 10; // ones
    num = num / 10;           // Left shift

    dispBuffer[1] = num % 10; // tens
    num = num / 10;

    dispBuffer[2] = num % 10; // hundreds
    num = num / 10;

    dispBuffer[3] = num % 10; // thousands
}

void leftShiftDisp(void)
{
    uint8 i;
    for (i = 3; i > 0; i--)
        dispBuffer[i] = dispBuffer[i - 1];
    dispBuffer[0] = 0;
}

void rightShiftDisp(void)
{
    uint8 i;
    for (i = 0; i < 3; i++) {
        dispBuffer[i] = dispBuffer[i + 1];
    }
    dispBuffer[3] = 0;
}

// Set the values for display, D3 is the leftmost one
void setDisplayBuffer(uint8 D3, uint8 D2, uint8 D1, uint8 D0)
{
    dispBuffer[3] = D3;
    dispBuffer[2] = D2;
    dispBuffer[1] = D1;
    dispBuffer[0] = D0;
}

void setDispBuffer0(uint8 val)
{
	dispBuffer[0] = val;
}

uint16 getDispBuffer(void)
{
    // get the dispBuffer in the form of decimal number
    int8 i;
    uint16 result = 0;
    for (i = 3; i >= 0; i--) {
        if (dispBuffer[i] <= 9)
            result = result * 10 + dispBuffer[i];
    }
    return result;
}