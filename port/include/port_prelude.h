/*
 * Force-included before memory_card.c (port.mk -include).
 * memory_card.c calls strcat before it declares it; GCC 2.7 took the
 * implicit int declaration and the later prototype, clang rejects them.
 */
#ifndef PORT_PRELUDE_H
#define PORT_PRELUDE_H

char *strcat(char *, char *);

#endif /* PORT_PRELUDE_H */
