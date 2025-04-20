#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "linked_list.h"

/*
 * Return the right flag position of the semaphore representation of a character.
 * 
 * @param content The character to convert (letter or digit).
 * @return the corresponding right flag semaphore position.
 * 
*/
semaphore_position get_rsemaphore(char content);

/*
 * Return the left flag position of the semaphore representation of a character.
 * 
 * @param content The character to convert (letter or digit).
 * @return the corresponding left flag semaphore position.
 * 
*/
semaphore_position get_lsemaphore(char content);

/**
 * Converts a input string into a dynamically allocated array of
 * semaphore_position.
 *
 * For each character in the input string, this function retrieves the corresponding
 * right and left semaphore positions. These positions
 * are stored sequentially in an array (two per character [right, left, right, left, ...]).
 *
 * @param input the string to convert
 * @return A pointer to the array of `semaphore_position`.
 *
 * The caller is responsible for freeing the returned array.
 */
semaphore_position *to_semaphore(const char *input);

#endif /* SEMAPHORE_H */