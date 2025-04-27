/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

#include "keypad.h"
#include "morse.h"
#include "semaphore.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>


void handleMorse(char *message, bool use_leds) {

    size_t message_length = strlen(message);
    for (size_t i = 0; i < message_length; i++) {
        
        morse_code* morseCode = getMorseCode(message[i]);
        int j = 0;

        while (morseCode[j] != END) {
            
            if (morseCode[j] != NONE) {
                if (use_leds) { writeToLeds(1); } // Turn on LEDs
                
                if (morseCode[j] == LONG) {
                    UART_1_PutString("- ");
                    useVDAC(LONG_BEEP); // Use VDAC for long beep
                } else if (morseCode[j] == SHORT) {
                    UART_1_PutString(". ");
                    useVDAC(SHORT_BEEP); // Use VDAC for short beep
                }

                if (use_leds) { writeToLeds(0); } // Turn off LEDs

            } else {
                // pass (none)
                UART_1_PutChar(' ');
            }

            // Standard transition delay for morse code
            CyDelay(SHORT_BEEP);

            j++;

        }

        CyDelay(LONG_BEEP); // Delay between characters
        free(morseCode); // Free the allocated memory for morse code

    }

    UART_1_PutCRLF(' ');

}

void handleSemaphore(char *message) {

    // send the message via semaphore (PWM)
    for (size_t i = 0; i < strlen(message); i++){

        uint32_t r_cmp_val = semaphoreToCMP(getRightSemaphore(message[i]));
        uint32_t l_cmp_val = semaphoreToCMP(getLeftSemaphore(message[i]));

        writeToServo(r_cmp_val, SEVRO_RIGHT);
        writeToServo(l_cmp_val, SEVRO_LEFT);

        CyDelay(1000);

    }

}

void handleUARTReceive(uint32_t val_adc_phot) {
    
    char message[9] = {0};
    int index = 0;

    while (UART_1_GetRxBufferSize() != 0 && index < 8) {
        char RxData = UART_1_GetChar();
        strncat(message, &RxData, 1);
        index++;
    }

    if (strlen(message) != 0) {

        LCD_Char_1_ClearDisplay();
        LCD_Char_1_Position(0, 0);
        LCD_Char_1_PrintString(message);
        
        if (isLightOn(val_adc_phot)) {
            // If the light is on, we send the message via DAC (sound)
            // and via semaphore (PWM)
            handleMorse(message, false);
            handleSemaphore(message);
        } else {
            // If the light is off, we send the message via DAC (sound)
            // and via LEDs
            handleMorse(message, true);
        }

    }

}


int main(void) {
    
    CyGlobalIntEnable;  // Enable global interrupts.
    
    UART_1_Start();
    VDAC_Start();
    VDAC_Sleep();
    MORSE_TIMER_Start();
    LCD_Char_1_Start();
    keypadInit();
    uint16_t pwm_period = 48000;
    PWM_DROITE_Start();
    timer_clock_1_Start();
    PWM_GAUCHE_Start();
   
    PWM_DROITE_WritePeriod(pwm_period);
    PWM_GAUCHE_WritePeriod(pwm_period);
    Mux_Start();
    ADC_POTENTIOMETRE_Start();
    uint8_t current_servo = 0;
    uint32_t val_adc_pot = 0;
    uint32_t val_adc_phot = 0;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */


    for(;;)
    {
        getAdcValue(&val_adc_pot, &val_adc_phot);
        char *message = handleKeypadPress(); // Call the function to handle keypad press
        if (message != NULL) {
            // If a message is returned, we send it to the UART
            // then we display it on the LCD
            LCD_Char_1_ClearDisplay();
            LCD_Char_1_Position(0, 0); // Set the cursor to the first line
            LCD_Char_1_PrintString(message); // Print the message on the LCD

            // then, we check if the light is on or off
            if (isLightOn(val_adc_phot)) {
                // If the light is on, we send the message via DAC (sound)
                //and via semaphore (PWM)
                handleMorse(message, false);
                handleSemaphore(message);
            } else {
                // If the light is off, we send the message via DAC (sound)
                // and via LEDs
                handleMorse(message, true);
            }
        }

        handleUARTReceive(val_adc_phot);
        
        // then we handle the switches:
        if (SWITCH_1_Read() == 1) {
            // If the switch is pressed, we send a bip via DAC as long as the switch is pressed (sound)
            while (SWITCH_1_Read() == 1) {
                if (isLightOn(val_adc_phot)==0) {
                    writeToLeds(1);
                }
                useVDAC(100);
            }
            writeToLeds(0);
        }
        
        if (SWITCH_2_Read() == 1) {
            // If the switch is pressed, we send a 250ms bip via DAC (sound)
            if (isLightOn(val_adc_phot)==0) {
                writeToLeds(1);
            }
            useVDAC(SHORT_BEEP);
            if (isLightOn(val_adc_phot)==0) {    
                writeToLeds(0);
            }
        }
        if (SWITCH_3_Read() == 1) {
            // If the switch is pressed, we send a 750ms bip via DAC (sound)
            if (isLightOn(val_adc_phot)==0) {
                writeToLeds(1);
            }
            useVDAC(LONG_BEEP);
            if (isLightOn(val_adc_phot)==0) {
                writeToLeds(0);
            }
        }
        if (SWITCH_4_Read() == 1) {
            // switch which semaphore to move with the potentiometer
            current_servo = 1 - current_servo;
            CyDelay(200);
        }
        if (isLightOn(val_adc_phot)) {
            // read the pototiometer value and use it to position the current servo
            uint32_t val_cmp = (((val_adc_pot /(float)0xFFFF)*4) + 1 ) * BASE_PWM; 
            writeToServo(val_cmp, current_servo);
        }
        CyDelay(500);
    }
}

/* [] END OF FILE */
