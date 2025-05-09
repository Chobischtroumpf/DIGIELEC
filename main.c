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

void play_sound(uint16_t ms){
   int overflows=0;
   while(overflows < ms+1){
       if ((0x80 & MORSE_TIMER_ReadStatusRegister()) != 0){
        overflows  += 1;    
        }
    VDAC_SetValue(128);
    }
    
}

void short_bip(){
    play_sound(250);
}

void long_bip(){
    play_sound(1000);
}

void handle_morse(char *message){
   
    morse_code * morse_array = to_morse(message);
    size_t i =0;
    while(morse_array[i] != END){
       if(morse_array[i] == NONE){CyDelay(250);}
       else if (morse_array[i]  == LONG){ long_bip();}
       else if (morse_array[i] == SHORT){ short_bip();}
       i++;
    }
}

/*
* Set the position of the given servo.
*/
void set_servo_pos(uint32_t val, uint8_t servo_nb) {
    if (servo_nb == 0) {
        PWM_DROITE_WriteCompare(val);
    } else if (servo_nb == 1) {
        PWM_GAUCHE_WriteCompare(val);
    }
}

/*
* Converts a text message into semaphore positions and controls the servos accordingly.
*/
void msg_to_semaphore(char *message){
    for (size_t i=0; i<strlen(message); i++){
        semaphore_position r_sem = lstget(message[i])->right_semaphore;
        semaphore_position l_sem = lstget(message[i])->left_semaphore;
        uint32_t r_cmp_val = sem_pos_to_cmp(r_sem);
        set_servo_pos(r_cmp_val, 0);    // 0 = right servo
        uint32_t l_cmp_val = sem_pos_to_cmp(l_sem);
        set_servo_pos(l_cmp_val, 1);    // 1 = left servo
        CyDelay(1000);
    }
}


int check_light(uint32_t *val_adc_phot) {
    float norm_val_phot = (*val_adc_phot /(float)0xFFFF);
    if (norm_val_phot > LIGHT_THRESHOLD) {
        // Light is on
        return 0;
    } else {
        // Light is off
        return 1;
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

void handle_UART_receive(uint32_t *val_adc_phot) {
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
    handle_morse(message);
    
    // then, we check if the light is on or off
    if (check_light(val_adc_phot) == 0) {
        //If the light is on, we send the message via semaphore (PWM)
        msg_to_semaphore(message);
    }
    else {
        // otherwise we send it via LEDs
    }
}


void get_adc_val(uint32_t* val_adc_pot, uint32_t* val_adc_phot){
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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    VDAC_Start();
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
            if (check_light(&val_adc_phot) == 0) {
                // If the light is on, we send the message via DAC (sound)
                //and via semaphore (PWM)
                handle_morse(message);
                msg_to_semaphore(message);
            }
                
            else {
                // If the light is off, we send the message via DAC (sound)
                // and via LEDs
                handle_morse(message);
            }
        }

        handle_UART_receive(&val_adc_phot);
        
        // then we handle the switches:
        if (SWITCH_1_Read() == 0) {
            // If the switch is pressed, we send a bip via DAC as long as the switch is pressed (sound)

            if (check_light(&val_adc_phot) != 0) {
                // If the light is off, we send a bip via LED
            }
        }
        if (SWITCH_2_Read() == 0) {
            // If the switch is pressed, we send a 250ms bip via DAC (sound)

            if (check_light(&val_adc_phot) != 0) {
                play_sound(250);
                // If the light is off, we send a 250ms bip via LED
            }
        }
        if (SWITCH_3_Read() == 0) {
            // If the switch is pressed, we send a 750ms bip via DAC (sound)
            play_sound(750);
            if (check_light(&val_adc_phot) != 0) {
                // If the light is off, we send a 750ms bip via LED
            }
        }
        if (SWITCH_4_Read() == 1) {
            // switch which semaphore to move with the potentiometer
            current_servo = 1 - current_servo;
            CyDelay(200);
        }
        if (check_light(&val_adc_phot) == 0) {
            // read the pototiometer value and use it to position the current servo
            uint32_t val_cmp = (((val_adc_pot /(float)0xFFFF)*4) + 1 ) * 1200; 
            set_servo_pos(val_cmp, current_servo);
        }
        CyDelay(500);
    }
}

/* [] END OF FILE */
