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
#include "linked_list.h"
#include "keypad.h"

char *handle_keypad_press() {
    static char buffer[2] = {0,0}; // Buffer to store the pressed key
    char *retval = NULL; // Pointer to return the message
    char key = keypadScan(); // Get the pressed key from the keypad
    if (key != 'z') {
        if (buffer[0] == 0) {
            buffer[0] = key; // Store the first key pressed
        } else {
            buffer[1] = key; // Store the second key pressed
        }
    }
    if (buffer[1] != 0 && buffer[1] != '*') {
        //reset buffer if the second key is not '*' and not 0
        buffer[0] = 0; // Reset the first key
        buffer[1] = 0; // Reset the second key
        return retval;
    } else if (buffer[1] == '*') {
        // If the second key is '*', return the string associated to the first key
        // and reset the buffer
        char val = buffer[0];
        buffer[0]=0;
        buffer[1]=0;
        
        if (val == '1') {
            return "SOS";
        } else if (val == '2') {
            return "BEAMS";
        } else if (val == '3') {
            return "PLEASE HELP";
        } else if (val == '4') {
            return "HELP ME";
        } else if (val == '5') {
            return "HELP";
        } else if (val == '6') {
            return "OUT OF FOOD";
        } else if (val == '7') {
            return "IN DANGER";
        } else if (val == '8') {
            return "WERE LOST";
        } else if (val == '9') {
            return "BEP KICKER IS GREAT";
        } else if (val == '0') {
            return "ZERO";
        }        
    }
    return NULL; // Return NULL if no valid key is pressed

}

int main(void)
{
    // CyGlobalIntEnable; /* Enable global interrupts. */

    keypadInit();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */


    for(;;)
    {
        char *message = handle_keypad_press(); // Call the function to handle keypad press
        if (message != NULL) {
            // If a message is returned, we send it to the UART
            // UART_PutString(message);
            // UART_PutCRLF(); // Send a new line after the message
            // then we display it on the LCD
            // LCD_ClearDisplay();
            // LCD_Position(0, 0); // Set the cursor to the first line
            // LCD_PrintString(message); // Print the message on the LCD

            // then, we check if the light is on or off
            // if (PHOTORESISTOR_Read() == 0) {
                // If the light is on, we send the message via DAC (sound)
                //and via semaphore (PWM)
            // else {
                // If the light is off, we send the message via DAC (sound)
                // and via LEDs
        }

        // then we handle the switches:
        if (SWITCH_1_Read() == 0) {
            // If the switch is pressed, we send a bip via DAC as long as the switch is pressed (sound)

            if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a bip via LED
            }
        }
        if (SWITCH_2_Read() == 0) {
            // If the switch is pressed, we send a 250ms bip via DAC (sound)

            if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a 250ms bip via LED
            }
        }
        if (SWITCH_3_Read() == 0) {
            // If the switch is pressed, we send a 750ms bip via DAC (sound)

            if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a 750ms bip via LED
            }
        }
        if (SWITCH_4_Read() == 0) {
            // switch which semaphore to move with the potentiometer
        }
        if (PHOTORESISTOR_Read() == 0) {
            handle_POTENTIOMETER(); // Call the function to handle potentiometer

    }
}

/* [] END OF FILE */
