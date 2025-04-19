#include "linked_list.h"
#include <stdint.h>

/*
 * Function to get the Morse code representation of a character.
 * The function returns a pointer to an array of morse_code values.
 * The array is dynamically allocated and should be freed by the caller.
 * morse code is formatted as follows:
 * - SHORT = dot (·), LONG= dash (−), END = end of character (|)
 * - The array is terminated with END.
 */
morse_code *get_morse_code(char content) {
    morse_code *code = (morse_code*) malloc(sizeof(morse_code) * 6);

    switch (content) {
        case 'A':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = END;
            break;
        case 'B':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'C':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'D':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = END;
            break;
        case 'E':
            code[0] = SHORT;
            code[1] = END;
            break;
        case 'F':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'G':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = END;
            break;
        case 'H':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'I':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = END;
            break;
        case 'J':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = END;
            break;
        case 'K':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = END;
            break;
        case 'L':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'M':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = END;
            break;
        case 'N':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = END;
            break;
        case 'O':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = END;
            break;
        case 'P':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = SHORT;
            code[4] = END;
            break;
        case 'Q':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = LONG;
            code[4] = END;
            break;
        case 'R':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = END;
            break;
        case 'S':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = END;
            break;
        case 'T':
            code[0] = LONG;
            code[3] = END;
            break;
        case 'U':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = END;
            break;
        case 'V':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = LONG;
            code[3] = END;
            break;
        case 'W':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = END;
            break;
        case 'X':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = LONG;
            code[4] = END;
            break;
        case 'Y':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = END;
            break;
        case 'Z':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = END;
            break;
        case '1':
            code[0] = SHORT;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = LONG;
            code[5] = END;
            break;
        case '2':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = LONG;
            code[5] = END;
            break;
        case '3':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = LONG;
            code[4] = LONG;
            code[5] = END;
            break;
        case '4':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = LONG;
            code[5] = END;
            break;
        case '5':
            code[0] = SHORT;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = SHORT;
            code[5] = END;
            break;
        case '6':
            code[0] = LONG;
            code[1] = SHORT;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = SHORT;
            code[5] = END;
            break;
        case '7':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = SHORT;
            code[3] = SHORT;
            code[4] = SHORT;
            code[5] = END;
            break;
        case '8':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = SHORT;
            code[4] = SHORT;
            code[5] = END;
            break;
        case '9':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = SHORT;
            code[5] = END;
            break;
        case '0':
            code[0] = LONG;
            code[1] = LONG;
            code[2] = LONG;
            code[3] = LONG;
            code[4] = LONG;
            code[5] = END;
            break;
        case ' ':
            code[0] = NONE;
            code[1] = NONE;
            code[2] = NONE;
            code[3] = NONE;
            code[5] = END;
            break;
        default:
            break;
    }
    return code;
}

/*
 * function to get the morse array size
 */
size_t get_morse_array_size(char *input) {
    size_t max_size = 0;
    for (size_t i = 0; input[i] != '\0'; i++) {
        uint8_t size = 0;
        morse_code *char_morse = lstget(input[i])->m_char;
        if (char_morse == NULL) { continue; }
        while (char_morse[size] != END) { size++; }
        max_size += size + 3; // +1 for the separator
    }
}

/*
 * Function to convert a string to Morse code.
 * The function takes a string as input and returns a pointer to an array of morse_code values.
 * The array is dynamically allocated and should be freed by the caller.
 * The array is terminated with END.
*/
morse_code *to_morse(const char *input) {
    
    if (input == NULL) { return NULL; }

    // +1 for the last END
    morse_code *morse_array = (morse_code *)malloc(sizeof(morse_code) * (get_morse_array_size(input) + 1));
    if (morse_array == NULL) {
        // alocation failed, might wanna throw something but atm we just return NULL
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; input[i] != '\0'; i++) {

        morse_code *char_morse = lstget(input[i])->m_char;
        if (char_morse == NULL) { continue; }

        for (size_t j = 0; char_morse[j] != END; j++) {
            morse_array[index++] = char_morse[j];
            // j < max_size in all cases
        }

        // adding the separator between characters
        morse_array[index++] = NONE;
        morse_array[index++] = NONE;
        morse_array[index++] = NONE;
    }

    morse_array[index] = END;

    return morse_array;

}
