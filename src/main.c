#include <REG_MPC82G516.H>
#include "int.h"
#include "random.h"
#include "display.h"
#include "led.h"
#include "pushbutton.h"
#include "delay.h"

enum GameState {
    STATE_INIT = 0,
    STATE_NEW_GAME,
    STATE_INPUT,
    STATE_CHECK,
    STATE_WIN
};

void main()
{
    uint16 answer;
	uint8 key;
    uint16 numTries = 0;
    uint16 guessedNumber = 0;
    uint8 dispClearFlag = 0;
    uint8 ansSpace = 4; // Space For the user to input (4 max)
    enum GameState gameState = STATE_INIT;

    initRandom();
    initDispUpdate();

    while (1) {
        // Read push button
        key = NO_BUTTON;
        if (KEY_PRESSED) {  // debounce
            delay(500);
            if (KEY_PRESSED) {
                key = getKeyValue();
            }
        }

        // State Machine
        switch (gameState) {
            case STATE_INIT: {
                LED_PORT = LED_PATTERN_START;
                setDisplayBuffer(LETTER_DASH, LETTER_DASH, LETTER_DASH, LETTER_DASH);
                if (key == NEW_BUTTON)
                    gameState = STATE_NEW_GAME;
                break;
            }

            case STATE_NEW_GAME: {
                LED_PORT = LED_PATTERN_MID;
                answer = genRandomNum() % 10000;  // for  0 ~ 9999
                guessedNumber = numTries = 0;
                ansSpace = 4;
                setDisplayBuffer(LETTER_O, LETTER_O, LETTER_O, LETTER_O);
                gameState = STATE_INPUT;
                break;
            }

            case STATE_INPUT: {
                if (dispClearFlag && key != NO_BUTTON) {
					LED_PORT = LED_PATTERN_NONE;
                    setDisplayBuffer(0, 0, 0, 0);
                    dispClearFlag = 0;
                }

                // Read key
                if (key >= 0 && key <= 9) {       // key0 ~ KEY9
                    LED_PORT = LED_PATTERN_NONE;
					if (ansSpace <= 4 && ansSpace > 0) {
                        leftShiftDisp();
						setDispBuffer0(key);
						ansSpace--;
                    }
                } else if (key == BACK_BUTTON) {  // backspace
                    LED_PORT = LED_PATTERN_NONE;
					if (ansSpace <= 4) {
                        rightShiftDisp();
                        ansSpace++;
                    }
                } else if (key == CHECK_BUTTON) {  // check
					LED_PORT = LED_PATTERN_NONE;
                    gameState = STATE_CHECK;
                }
                break;
            }
            case STATE_CHECK: {
                numTries++;
                guessedNumber = getDispBuffer(); // retrieve guessed number from dispBuffer[]
                ansSpace = 4;

                if (guessedNumber == answer) {
                    // Correct
                    LED_PORT = LED_PATTERN_ALL;
                    displayNumber(numTries);
                    gameState = STATE_WIN;
                } else if (guessedNumber < answer) {
                    // Too Low
                    LED_PORT = LED_PATTERN_LO;
                    setDisplayBuffer(LETTER_L, LETTER_O, NONE, NONE);
                    dispClearFlag = 1;
                } else {
                    // Too High
                    LED_PORT = LED_PATTERN_HI;
                    setDisplayBuffer(LETTER_H, LETTER_I, NONE, NONE);
                    dispClearFlag = 1;
                }

                if (key != CHECK_BUTTON && key != NO_BUTTON)
                    gameState = STATE_INPUT;

                break;
            }

            case STATE_WIN: {
                // If any button pressed, go back to initial state
                if (key != NO_BUTTON)
                    gameState = STATE_INIT;
                break;
            }
        }

        // Wait for the button to be released
        while (getKeyValue() != NO_BUTTON)
            delay(100);
    }
}

