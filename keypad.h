#ifndef KEYPAD_H
#define KEYPAD_H

#include "project.h"
#include <stdint.h>

#define KBD_DELAY 5


void keypadInit(void);
uint8_t keypadScan(void);
const char *getMessageFromKey(char key);


#endif /* KEYPAD_H */
