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
    static char buffer[3] = {0,0,0}; // Buffer to store the pressed key
    char *retval = NULL; // Pointer to return the message
    char key = keypadScan(); // Get the pressed key from the keypad
    if (key != 'z') {
        if (buffer[0] == 0) {
            buffer[0] = key; // Store the first key pressed
        } else {
            buffer[1] = key; // Store the second key pressed
        }
        
    } else {
        return NULL;
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
            return "PLEASE";
        } else if (val == '4') {
            return "HELP ME";
        } else if (val == '5') {
            return "HELP";
        } else if (val == '6') {
            return "OUT OF FOOD";
        } else if (val == '7') {
            return "IN DANGER";
        } else if (val == '8') {
            return "LOST";
        } else if (val == '9') {
            return "KICKER LOVE";
        } else if (val == '0') {
            return "ZERO";
        }        
    }
    return NULL; // Return NULL if no valid key is pressed
}

void handle_UART_receive() {
    char message[9] = {0};
    int index = 0;
    while (UART_1_GetRxBufferSize() != 0 && index <8)
    {
        char RxData = UART_1_GetChar();
        strncat(message, &RxData, 1);
        index++;
    }
    if (strlen(message) != 0){
        LCD_Char_1_ClearDisplay();
        LCD_Char_1_Position(0, 0);
        LCD_Char_1_PrintString(message);
    }
    // we send the message via DAC (sound)
    
    // then, we check if the light is on or off
    // if (PHOTORESISTOR_Read() == 0) {
        //If the light is on, we send the message via semaphore (PWM)
    // else {
        // otherwise we send it via LEDs
    // }
}

/*
* Init both servo and the potentiometre.
*/
void init_servo_and_pot(){
    uint16_t pwm_period = 48000;
    PWM_DROITE_Start();
    timer_clock_1_Start();
    PWM_GAUCHE_Start();
    timer_clock_2_Start();
    PWM_DROITE_WritePeriod(pwm_period);
    PWM_GAUCHE_WritePeriod(pwm_period);
    ADC_POTENTIOMETRE_Start();
    ADC_POTENTIOMETRE_StartConvert();
}


/*
* Read and return the value of the potentiometre.
*/
uint32_t get_pot_val(){
    uint32_t val_adc;
    uint32_t val_cmp;
    if (ADC_POTENTIOMETRE_IsEndConversion(ADC_POTENTIOMETRE_RETURN_STATUS)){
        val_adc = ADC_POTENTIOMETRE_GetResult32();
        val_cmp = ((val_adc /(float)0xFFFF) + 1 ) * 2400;
    }
    return val_cmp;
}


/*
* Set the position of the given servo.
*/
void set_servo_pos(uint32_t compare_value, uint8_t servo_nb) {
    if (servo_nb == 0) {
        PWM_DROITE_WriteCompare(compare_value);
    } else if (servo_nb == 1) {
        PWM_GAUCHE_WriteCompare(compare_value);
    }
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    LCD_Char_1_Start();
    keypadInit();
    init_servo_and_pot();
    uint8_t current_servo = 0;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */


    for(;;)
    {
        char *message = handle_keypad_press(); // Call the function to handle keypad press
        if (message != NULL) {
            // If a message is returned, we send it to the UART
            UART_1_PutString(message);
            UART_1_PutCRLF(' '); // Send a new line after the message
            // then we display it on the LCD
            LCD_Char_1_ClearDisplay();
            LCD_Char_1_Position(0, 0); // Set the cursor to the first line
            LCD_Char_1_PrintString(message); // Print the message on the LCD

            // then, we check if the light is on or off
            // if (PHOTORESISTOR_Read() == 0) {
                // If the light is on, we send the message via DAC (sound)
                //and via semaphore (PWM)
            // } else {
                // If the light is off, we send the message via DAC (sound)
                // and via LEDs
            // }
        }

        handle_UART_receive();
        
        // then we handle the switches:
        if (SWITCH_1_Read() == 0) {
            // If the switch is pressed, we send a bip via DAC as long as the switch is pressed (sound)

            //if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a bip via LED
          //  }
        }
        if (SWITCH_2_Read() == 0) {
            // If the switch is pressed, we send a 250ms bip via DAC (sound)

            //if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a 250ms bip via LED
            //}
        }
        if (SWITCH_3_Read() == 0) {
            // If the switch is pressed, we send a 750ms bip via DAC (sound)

            //if (PHOTORESISTOR_Read() != 0) {
                // If the light is off, we send a 750ms bip via LED
            //}
        }
        if (SWITCH_4_Read() == 0) {
            // switch which semaphore to move with the potentiometer
            current_servo = 1 - current_servo;
            CyDelay(200);
        }
        //if (PHOTORESISTOR_Read() == 0) {
            //handle_POTENTIOMETER(); // Call the function to handle potentiometer
        CyDelay(500);
    }
    uint32_t pot_value = read_pot_val();
    set_servo_pos(pot_value, current_servo);
}

/* [] END OF FILE */
