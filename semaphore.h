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
    float angle = 22.5;
    switch (pos){
    case FIRST:
        angle*=1;
        break;
    case SECOND:
        angle*=2;
        break;
    case THIRD:
        angle*=3;
        break;
    case FOURTH:
        angle*=4;
        break;
    case FIFTH:
        angle*=5;
        break;
    case SIXTH:
        angle*=6;
        break;
    case SEVENTH:
        angle*=7;
        break;
    case ZERO:
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
