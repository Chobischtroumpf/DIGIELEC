
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "project.h"

#include "keypad.h"
#include "morse.h"
#include "semaphore.h"


#define SEVRO_RIGHT 0
#define SEVRO_LEFT 1

#define LIGHT_THRESHOLD 0.3  // Low light bar (0 to 1)

#define LONG_BEEP 750
#define SHORT_BEEP 250
#define MORSE_FREQUENCY 128
#define VDAC_DIFF 2

#define LIGHT_ON 1
#define LIGHT_OFF 0


void useVDAC(uint16_t ms);
int isLightOn(uint32_t val_adc_phot);
void writeToLeds(int tw);
void writeToServo(uint32_t val, uint8_t servo_idx);
bool updateKeyBuffer(char key, char *buffer);
char *handleKeypadPress(void);
static uint32_t readAdcChannel(uint8_t channel);
void getAdcValue(uint32_t *pot, uint32_t *phot);


#endif /* UTILS_H */