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
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum e_semaphore {
    ZERO,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH,
    SIXTH,
    SEVENTH,
} semaphore_position;

typedef enum e_morse_code {
    NONE,
    SHORT,
    LONG,
    END
} morse_code;

typedef struct s_list
{
	char    character;
    morse_code *m_char;
    semaphore_position left_semaphore;
    semaphore_position right_semaphore;
    struct  s_list *next;
} t_charlist;

semaphore_position get_lsemaphore(char content);
semaphore_position get_rsemaphore(char content);
morse_code *get_morse_code(char content);

/* [] END OF FILE */
#endif /* LINKED_LIST_H */