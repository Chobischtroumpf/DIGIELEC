
#include "utils.h"


/*
 * Function to use the VDAC for a given duration in milliseconds.
 * The VDAC value is set to MORSE_FREQUENCY +- VDAC_DIFF to make a morse sound.
*/
void useVDAC(uint16_t ms) {

    // Set the VDAC value to MORSE_FREQUENCY for ms milliseconds
    int overflows = 0;
    VDAC_Wakeup();

    while (overflows < ms + 1) {

        // Timer overflows in 1ms intervals, meaning ms overflows will last ms milliseconds
        if ((0x80 & MORSE_TIMER_ReadStatusRegister()) != 0) {
            
            overflows += 1;

            // Set the VDAC value to MORSE_FREQUENCY + VDAC_DIFF or MORSE_FREQUENCY - VDAC_DIFF
            if (overflows % 2 == 0) { VDAC_SetValue(MORSE_FREQUENCY + VDAC_DIFF); }
            else { VDAC_SetValue(MORSE_FREQUENCY - VDAC_DIFF); }
                
        }

    }

    // Set the VDAC to sleep mode
    VDAC_Sleep();

}

/*
 * Function to check if the light is on or off based on the ADC value.
 * The light is considered on if the ADC value is above the threshold
 * and off if it is below the threshold.
*/
int isLightOn(uint32_t val_adc_phot) {

    // Check if the light is on or off based on the ADC value
    // The light is considered on if the ADC value is above the threshold
    // and off if it is below the threshold
    
    float norm_val_phot = val_adc_phot / (float)0xFFFF;
    return (norm_val_phot < LIGHT_THRESHOLD) ? LIGHT_OFF : LIGHT_ON;

}

/*
 * Function to write the LEDs to a given value (0 or 1).
 * The LEDs are turned on or off based on the value passed to the function.
*/
void writeToLeds(int tw) {

    // Set the LEDs to the given value (0 or 1)
    LED_1_Write(tw); LED_2_Write(tw);
    LED_3_Write(tw); LED_4_Write(tw);

}

/*
 * Function to set the position of the servo based on the given value and servo number.
 * The value is a PWM compatible value (0 to ...) and the servo number is either 0 (right) or 1 (left).
*/
void writeToServo(uint32_t val, uint8_t servo_idx) {

    switch (servo_idx) {

        case SEVRO_RIGHT:
            PWM_DROITE_WriteCompare(val);  // Set the right servo position
            break;

        case SEVRO_LEFT:    
            PWM_GAUCHE_WriteCompare(val);  // Set the left servo position
            break;
        
        // Default case to handle invalid servo index (not expected to happen)
        default: break;

    }

}

/*
 * Function to update the key buffer with the key pressed.
 * The function returns true in all case beside if the key is 'z'.
*/
bool updateKeyBuffer(char key, char *buffer) {

    if (key == 'z') { return false; }  // 'z' is used to exit the function

    if (buffer[0] == 0) { buffer[0] = key; }
    else { buffer[1] = key; }

    return true;

}

/*
 * Function to handle the keypad press and return the corresponding message.
 * The function returns a string corresponding to the key pressed.
*/
char *handleKeypadPress(void) {

    static char buffer[3] = {0, 0, 0}; // buffer to store the key pressed
    char key = keypadScan();

    // if the key is 'z', we exit the function
    if (!updateKeyBuffer(key, buffer)) {
        return NULL;
    }

    // if the second key is not '0' or '*', we reset the buffer and return NULL
    if (buffer[1] != 0 && buffer[1] != '*') {
        buffer[0] = 0;
        buffer[1] = 0;
        return NULL;
    }

    // if the second key is '*', we get the message from the first key
    if (buffer[1] == '*') {
        char result_key = buffer[0];
        buffer[0] = 0;
        buffer[1] = 0;
        return (char *)getMessageFromKey(result_key);
    }

    return NULL;

}

/*
 * Function to read the ADC value from a given channel.
*/
static uint32_t readAdcChannel(uint8_t channel) {
    
    // select the channel to read from and start the ADC conversion
    Mux_Select(channel);
    CyDelay(10);
    ADC_POTENTIOMETRE_StartConvert();

    // wait for the conversion to finish and return the result
    if (ADC_POTENTIOMETRE_IsEndConversion(ADC_POTENTIOMETRE_WAIT_FOR_RESULT)) {
        return ADC_POTENTIOMETRE_GetResult32();
    }

    return 0;  // fallback value in case of error

}

/*
* Function to get the ADC value from the potentiometer and phototransistor.
* The function takes two pointers as arguments to store the ADC values.
* The first pointer is used to store the ADC value from the potentiometer
* and the second pointer is used to store the ADC value from the phototransistor.
*/
void getAdcValue(uint32_t *pot, uint32_t *phot) {
    
    // read the ADC value from the potentiometer and phototransistor
    if (pot) { *pot = readAdcChannel(0); }
    if (phot) { *phot = readAdcChannel(1); }

}


