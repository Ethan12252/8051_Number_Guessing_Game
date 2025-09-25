#ifndef LED_H
#define LED_H

#include <REG_MPC82G516.H>

// Ports
#define LED_PORT P1

// Led Patterns
#define LED_PATTERN_START 0x18   // 00011000
#define LED_PATTERN_LO 0xFC      // 11111100 
#define LED_PATTERN_HI 0x3F      // 00111111
#define LED_PATTERN_MID 0xE7     // 11100111 
#define LED_PATTERN_ALL 0x00     // 00000000 
#define LED_PATTERN_NONE 0xFF    // 11111111 

#endif // LED_H