#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>

static const float SEMAPHORE_PWM_ANGLE = 22.5f;
static const uint32_t BASE_PWM = 1200;
static const uint32_t SCALE_PWM = 4800;

typedef enum e_semaphore {
    ZERO = 0,
    FIRST = 1,
    SECOND = 2,
    THIRD = 3,
    FOURTH = 4,
    FIFTH = 5,
    SIXTH = 6,
    SEVENTH = 7
} semaphore_position;

/*
 * Map a semaphore position to a PWM compatible value.
 */
uint32_t semaphoreToCMP(semaphore_position pos);

semaphore_position getRightSemaphore(char content);
semaphore_position getLeftSemaphore(char content);

#endif /* SEMAPHORE_H */
