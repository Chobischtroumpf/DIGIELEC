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

typedef enum e_morse_code {
    NONE,
    SHORT,
    LONG,
    END
} morse_code;

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

typedef struct s_list
{
	char    character;
    morse_code *m_char;
    semaphore_position left_semaphore;
    semaphore_position right_semaphore;
    struct  s_list *next;
} t_charlist;

void	lstadd(t_charlist **alst, t_charlist *new);
t_charlist	*ft_lstnew(char content);
semaphore_position get_lsemaphore(char content);
semaphore_position get_rsemaphore(char content);
morse_code *get_morse_code(char content);
morse_code *to_morse(const char *str);

/* [] END OF FILE */
