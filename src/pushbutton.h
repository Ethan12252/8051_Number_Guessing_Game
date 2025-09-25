#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <REG_MPC82G516.H>
#include "int.h"

// Ports
#define KEYPORT_LOWER  P2
#define KEYPORT_HIGHER P3

// Buttons
#define NO_BUTTON    16
#define BACK_BUTTON  11
#define CHECK_BUTTON 12
#define NEW_BUTTON   15

// check if any key is pressed
#define KEY_PRESSED  ((KEYPORT_LOWER != 0xff) || (KEYPORT_HIGHER != 0xff))

uint8 getKeyValue(void);

#endif // PUSHBUTTON_H