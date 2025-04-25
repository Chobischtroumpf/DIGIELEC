#ifndef MORSE_H
#define MORSE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef enum e_morse_code {
    NONE,
    SHORT,
    LONG,
    END
} morse_code;

morse_code *getMorseCode(char content);


#endif /* MORSE_H */