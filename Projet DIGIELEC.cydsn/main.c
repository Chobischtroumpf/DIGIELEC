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

void setAngle(uint8_t angle, uint8_t servo_nb) {
    uint16_t pulseWidth = 1200 + ((angle*1200)/180);
    if (servo_nb == 0) {
        uint16_t compareValue = (pulseWidth * PWM_DROITE_ReadPeriod())/24000;
        PWM_DROITE_WriteCompare(compareValue);
    } else if (servo_nb == 1) {
        uint16_t compareValue = (pulseWidth * PWM_GAUCHE_ReadPeriod())/24000;
        PWM_GAUCHE_WriteCompare(compareValue);
    }
    
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    PWM_DROITE_Start();
    timer_clock_1_Start();
    PWM_GAUCHE_Start();
    timer_clock_2_Start();
    TIMER_Start();
    LCD_Char_1_Start();
    ADC_POTENTIOMETRE_Start();
    uint8_t current_servo = 0;
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        ADC_POTENTIOMETRE_StartConvert();
        while (!ADC_POTENTIOMETRE_IsEndConversion(ADC_POTENTIOMETRE_WAIT_FOR_RESULT));
        uint16_t potValue = ADC_POTENTIOMETRE_GetResult16();
        LCD_Char_1_Position(0,0);
        LCD_Char_1_PrintString("Pot=");
        LCD_Char_1_PrintNumber(potValue);
        uint8_t angle = (uint8_t)((potValue * 180) / 1023);
        if (SWITCH_4_Read() == 1) {
            LED_1_Write(1 - current_servo);
            current_servo = 1 - current_servo;
            CyDelay(200);
        }
        setAngle(angle, current_servo);
        CyDelay(50);
    }
}
/* [] END OF FILE */
