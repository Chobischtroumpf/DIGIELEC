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
 * Function to create a new node in the linked list
 * with the given character and its Morse code representation
 * and semaphore positions.
 * The new node points to itself as the next node.
 * Returns a pointer to the new node.
 */
t_charlist	*lstnew(char content) {
	t_charlist	*lst;

	if (!(lst = (t_charlist *)malloc(sizeof(t_charlist))))
		return (0);
	lst->character = content;
    lst->m_char = get_morse_code(content);
    lst->left_semaphore = get_lsemaphore(content);
    lst->right_semaphore = get_rsemaphore(content);
	lst->next = NULL;
	return (lst);
}

/*
 * Function to add a new node to the linked list.
 * The new node is added after the head of the list.
 * The head pointer is updated to point to the new node.
 */
void	lst_addback(t_charlist **alst, t_charlist *new) {
    t_charlist *ptr = *alst;

    if (ptr == NULL) {
        *alst = new;
        return;
    }
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = new;
    new->next = NULL;

}

/*
 * Function to get the element of the linked list
 * that contains the specified character.   
 * The function iterates through the linked list and returns the
 * semaphore position of the node containing the character.
 */
t_charlist *lstget(char content) {
    t_charlist *ptr = get_charlist();
    t_charlist *head = ptr;
    if (ptr == NULL) {
        return NULL;
    }

    while (head != NULL) {
        if (head->character == content) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

t_charlist *init_list(void) {
    t_charlist *head = lstnew('A');
    t_charlist *current = head;

    for (char c = 'B'; c <= 'Z'; c++) {
        lst_addback(&current, lstnew(c));
    }
    for (char c = '0'; c <= '9'; c++) {
        lst_addback(&current, lstnew(c));
    }
    lst_addback(&current, lstnew(' ')); // Adding space character
    lst_addback(&current, lstnew('\0')); // Adding null character
    while (current->next != NULL) {
        current = current->next;
    }

    return head;
}

/*
 * Function to get the head of the linked list.
 * If the list is not initialized, it initializes a new static list.
 * Returns a pointer to the head of the linked list.
 * mimics a singleton pattern to ensure only one instance of the list exists.
 */
t_charlist *get_charlist(void) {
    static t_charlist head;
    if (head.next == NULL) {
        head = *init_list();
    }
    return &head;
}
/* [] END OF FILE */