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
