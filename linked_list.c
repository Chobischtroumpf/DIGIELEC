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

#include "linked_list.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

semaphore_position get_rsemaphore(char content) {
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

semaphore_position get_lsemaphore(char content) {
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
            code[4] = END;

        default:
            break;
    }
    return code;
}

/*
 * Function to convert a string to Morse code.
 * The function takes a string as input and returns a pointer to an array of morse_code values.
 * The array is dynamically allocated and should be freed by the caller.
 * The array is terminated with END.
*/
morse_code *to_morse(const char *input) {
    
    if (input == NULL) { return NULL; }

    size_t max_size = strlen(input) * 6;
    // +1 for the END marker ^w^
    morse_code *morse_array = (morse_code *)malloc(sizeof(morse_code) * (max_size + 1));
    if (morse_array == NULL) {
        // alocation failed, might wanna throw something but atm we just return NULL
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; input[i] != '\0'; i++) {

        morse_code *char_morse = get_morse_code(input[i]);
        if (char_morse == NULL) { continue; }

        for (size_t j = 0; char_morse[j] != END; j++) {
            morse_array[index++] = char_morse[j];
            // j < max_size in all cases
        }

        // adding a separator between characters
        morse_array[index++] = NONE;

        free(char_morse); // free the temporary morse code array
    }

    // finally I think replacing the last NONE with END is a good idea
    if (index > 0 && morse_array[index - 1] == NONE) { index--; }
    morse_array[index] = END;

    return morse_array;

}

/*
 * Function to create a new node in the linked list
 * with the given character and its Morse code representation
 * and semaphore positions.
 * The new node points to itself as the next node.
 * Returns a pointer to the new node.
 */
t_charlist	*ft_lstnew(char content) {
	t_charlist	*lst;

	if (!(lst = (t_charlist *)malloc(sizeof(t_charlist))))
		return (0);
	lst->character = content;
    lst->m_char = get_morse_code(content);
    lst->left_semaphore = get_lsemaphore(content);
    lst->right_semaphore = get_rsemaphore(content);
	lst->next = lst;
	return (lst);
}

/*
 * Function to add a new node to the linked list.
 * The new node is added after the head of the list.
 * The head pointer is updated to point to the new node.
 */
void	lstadd(t_charlist **alst, t_charlist *new) {
    t_charlist *ptr = *alst;

    new->next = ptr->next;
    ptr->next = new;
}

/*
 * Function to get the element of the linked list
 * that contains the specified character.   
 * The function iterates through the linked list and returns the
 * semaphore position of the node containing the character.
 */
t_charlist *lstget(t_charlist **alst, char content) {
    t_charlist *ptr = *alst;

    while (ptr != NULL) {
        if (ptr->character == content) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

t_charlist *init_list(void) {
    t_charlist *head = ft_lstnew('A');
    t_charlist *current = head;

    for (char c = 'B'; c <= 'Z'; c++) {
        lstadd(&current, ft_lstnew(c));
    }
    for (char c = '0'; c <= '9'; c++) {
        lstadd(&current, ft_lstnew(c));
    }
    lstadd(&current, ft_lstnew(' ')); // Adding space character
    lstadd(&current, ft_lstnew('\0')); // Adding null character
    return head;
}
/* [] END OF FILE */