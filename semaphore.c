
#include "semaphore.h"


uint32_t semaphoreToCMP(semaphore_position pos) {

    // if the position is not in the range of 1 to 7, return 0. Otherwise, calculate angle.
    float angle = (pos >= FIRST && pos <= SEVENTH) ? pos * SEMAPHORE_PWM_ANGLE : 0.0f;

    // convert angle to PWM compare value (black magic tbh)
    return BASE_PWM + (uint32_t)((angle / 180.0f) * SCALE_PWM);

}

semaphore_position getRightSemaphore(char content) {
    
    switch (content) {

        case '1':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'A': return FIRST;

        case '7':
        case 'H':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'B': return SECOND;

        case 'I':
        case 'O':
        case 'T':
        case 'U':
        case 'Y':
        case 'C': return THIRD;

        case '2':
        case '8':
        case 'J':
        case 'V':
        case 'D': return FOURTH;
        
        case '3':
        case '9':
        case ' ':
        case '\0': return FIFTH;
        
        case '4':
        case 'W': return SIXTH;
        
        case '5':
        case 'Z':
        case 'X': return SEVENTH;

        case '6':
        case 'E': 
        case 'F':
        case 'G':
        default: return ZERO;

    }
    
}

semaphore_position getLeftSemaphore(char content) {
    
    switch (content) {
        
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case 'H':
        case 'I': return FIRST;
        
        case '7':
        case '8':
        case '9':
        case '0':
        case '\0':
        case 'O': return SECOND;

        case ' ': return THIRD;

        case 'K':
        case 'P':
        case 'T': return FOURTH;

        case 'E':
        case 'L':
        case 'Q':
        case 'U':
        case 'W':
        case 'X': return FIFTH;

        case 'F':
        case 'J':
        case 'M':
        case 'R':
        case 'Y':
        case 'Z': return SIXTH;

        case 'G':
        case 'N':
        case 'S':
        case 'V': return SEVENTH;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        default: return ZERO;

    }

}

