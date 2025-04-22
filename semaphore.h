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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
    
#include "linked_list.h"
#include <stdint.h>
    
    /*
* Map a semaphore position to a PWM compatible value.
*/
uint32_t sem_pos_to_cmp(semaphore_position pos){
    uint32_t cmp_val;
    uint16_t angle;
    switch (pos){
    case ZERO:
        angle = 270/2; 
        break;
    case FIRST:
        angle = 225/2; 
        break;
    case SECOND:
        angle = 180/2;
        break;
    case THIRD:
        angle = 135/2;
        break;
    case FOURTH:
        angle = 90/2;
        break;
    case FIFTH:
        angle = 45/2;
        break;
    case SIXTH:
        angle = 360/2;
        break;
    case SEVENTH:
        angle = 315/2;
        break;
    default:
        angle = 0;
        break;
    }
    
    // 1200 + 1*4800 = 6000, 1200 + 0*4800 = 1200
    cmp_val = 1200+(angle/180)*4800;
    return cmp_val;
}

#endif /* SEMAPHORE_H */
/* [] END OF FILE */
