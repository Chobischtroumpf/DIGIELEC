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
#include "semaphore.h"

#define LIGHT_THRESHOLD 0.3  // Low light bar (0 to 1)
#define LONG_BEEP 750
#define SHORT_BEEP 250
#define MORSE_FREQUENCY 128
#define LIGHT_ON 1
#define LIGHT_OFF 0
#define SEVRO_RIGHT 0
#define SEVRO_LEFT 1


// utils

void use_VDAC(uint16_t ms){

    // Set the VDAC value to MORSE_FREQUENCY for ms milliseconds
    int overflows = 0;
    
    VDAC_Wakeup();
    while(overflows < ms + 1) {

        // Timer overflows in 1ms intervals, meaning ms overflows will last ms milliseconds
        if ((0x80 & MORSE_TIMER_ReadStatusRegister()) != 0) {
            overflows += 1;    
            if (overflows%2)
                VDAC_SetValue(MORSE_FREQUENCY);
            else
                VDAC_SetValue(MORSE_FREQUENCY+2);
        }

    }

    VDAC_Sleep();
}

int check_light(uint32_t val_adc_phot) {

    // Check if the light is on or off based on the ADC value
    // The light is considered on if the ADC value is above the threshold
    // and off if it is below the threshold

    float norm_val_phot = (val_adc_phot / (float) 0xFFFF);
    return LIGHT_ON ? LIGHT_OFF : norm_val_phot < LIGHT_THRESHOLD;

}

void write_leds(int tw) {

    // Set the LEDs to the given value (0 or 1)

    LED_1_Write(tw);
    LED_2_Write(tw);
    LED_3_Write(tw);
    LED_4_Write(tw);

}

void set_servo_pos(uint32_t val, uint8_t servo_idx) {

    // Set the position of the servo based on the given value and servo number
    // 0 = right servo, 1 = left servo

    switch (servo_idx) {

        case SEVRO_RIGHT:
            // Set the right servo position
            PWM_DROITE_WriteCompare(val);
            break;

        case SEVRO_LEFT:    
            // Set the left servo position
            PWM_GAUCHE_WriteCompare(val);
            break;
        
        default:
            break;
    }

}

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
            return "YVES DE SHMET";
        }        
    }

    return NULL; // Return NULL if no valid key is pressed
    
}

void get_adc_val(uint32_t *val_adc_pot, uint32_t *val_adc_phot) {

    Mux_Select(0);
    CyDelay(10);
    ADC_POTENTIOMETRE_StartConvert();
    if (ADC_POTENTIOMETRE_IsEndConversion(ADC_POTENTIOMETRE_WAIT_FOR_RESULT)){
        *val_adc_pot = ADC_POTENTIOMETRE_GetResult32();
    }

    Mux_Select(1);
    CyDelay(10);
    ADC_POTENTIOMETRE_StartConvert();
    if(ADC_POTENTIOMETRE_IsEndConversion(ADC_POTENTIOMETRE_WAIT_FOR_RESULT)){
        *val_adc_phot = ADC_POTENTIOMETRE_GetResult32();
    }
    
}



// handlers

void handle_morse(char *message, bool use_leds) {

    size_t message_length = strlen(message);
    for (size_t i = 0; i < message_length; i++) {
        
        morse_code* morseCode = get_morse_code(message[i]);
        int j = 0;

        while (morseCode[j] != END) {
            
            if (morseCode[j] != NONE) {

                if (use_leds) { write_leds(1); } // Turn on LEDs
                
                if (morseCode[j] == LONG) {
                    use_VDAC(LONG_BEEP); // Use VDAC for long beep
                } else if (morseCode[j] == SHORT) {
                    use_VDAC(SHORT_BEEP); // Use VDAC for short beep
                }

                if (use_leds) { write_leds(0); } // Turn off LEDs

            } else {
                // pass (none)
            }

            // Standard transition delay for morse code
            CyDelay(SHORT_BEEP);

            j++;

        }
        
        CyDelay(LONG_BEEP); // Delay between characters
        free(morseCode); // Free the allocated memory for morse code

    }

}

void handle_semaphore(char *message) {

    // Send the message via semaphore (PWM)
    for (size_t i = 0; i < strlen(message); i++){

        semaphore_position r_sem = get_rsemaphore(message[i]);
        semaphore_position l_sem = get_lsemaphore(message[i]);

        uint32_t r_cmp_val = sem_pos_to_cmp(r_sem);
        set_servo_pos(r_cmp_val, 0);    // 0 = right servo
        uint32_t l_cmp_val = sem_pos_to_cmp(l_sem);
        set_servo_pos(l_cmp_val, 1);    // 1 = left servo
        CyDelay(1000);

    }

}




void handle_UART_receive(uint32_t val_adc_phot) {
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
    handle_morse(message, val_adc_phot);
    
    // then, we check if the light is on or off
    if (check_light(val_adc_phot) == 0) {
        //If the light is on, we send the message via semaphore (PWM)
        handle_semaphore(message);
    }
    else {
        // otherwise we send it via LEDs
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
        get_adc_val(&val_adc_pot, &val_adc_phot);
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
            if (check_light(val_adc_phot) == 0) {
                // If the light is on, we send the message via DAC (sound)
                //and via semaphore (PWM)
                handle_morse(message, val_adc_phot);
                handle_semaphore(message);
            }
                
            else {
                // If the light is off, we send the message via DAC (sound)
                // and via LEDs
                handle_morse(message, val_adc_phot);
            }
        }

        handle_UART_receive(val_adc_phot);
        
        // then we handle the switches:
        if (SWITCH_1_Read() == 0) {
            // If the switch is pressed, we send a bip via DAC as long as the switch is pressed (sound)

            if (check_light(val_adc_phot) != 0) {
                // If the light is off, we send a bip via LED
            }
        }
        if (SWITCH_2_Read() == 0) {
            // If the switch is pressed, we send a 250ms bip via DAC (sound)

            if (check_light(val_adc_phot) != 0) {
                use_VDAC(SHORT_BEEP);
                // If the light is off, we send a 250ms bip via LED
            }
        }
        if (SWITCH_3_Read() == 0) {
            // If the switch is pressed, we send a 750ms bip via DAC (sound)
            use_VDAC(LONG_BEEP);
            if (check_light(val_adc_phot) != 0) {
                // If the light is off, we send a 750ms bip via LED
            }
        }
        if (SWITCH_4_Read() == 1) {
            // switch which semaphore to move with the potentiometer
            current_servo = 1 - current_servo;
            CyDelay(200);
        }
        if (check_light(val_adc_phot) == 0) {
            // read the pototiometer value and use it to position the current servo
            uint32_t val_cmp = (((val_adc_pot /(float)0xFFFF)*4) + 1 ) * 1200; 
            set_servo_pos(val_cmp, current_servo);
        }
        CyDelay(500);
    }
}

/* [] END OF FILE */
