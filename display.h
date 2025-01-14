#ifndef DISPLAY_H
#define DISPLAY_H

// Used: timer0

// Imports
#include <REG_MPC82G516.H>
#include "int.h"

// Letters
#define LETTER_DASH 10
#define LETTER_L    11
#define LETTER_O    12
#define LETTER_H    13
#define LETTER_I    14
#define NONE 15

// Timer values
#define TIMER0_VAL_LOW  0x00
#define TIMER0_VAL_HIGH 0xff

// Ports
#define DISP_DATA_PORT  P0
#define DISP_DRIVE_PORT P4

// functions
void initDispUpdate(void);
void setDisplayBuffer(uint8 D3, uint8 D2, uint8 D1, uint8 D0); // Set the values for display, D3 is the leftmost one
void displayNumber(uint16 num); // Display a 4 digits decimal number
void rightShiftDisp(void);  // RS display, clears the leftmost digit to 0 
void leftShiftDisp(void);   // LS display, clears the rightmost digit to 0 
void setDispBuffer0(uint8 val);
uint16 getDispBuffer(void);

#endif // DISPLAY_H