#include <stdio.h>
#include <stdlib.h>
#ifndef HTABLE_H_
#define HTABLE_H_

typedef enum hashing_e {LINEAR_P, DOUBLE_H} hashing_t;

typedef struct htablerec *htable;

extern void htable_free(htable h);
extern int htable_insert(htable h, char *str);
extern htable htable_new(int capacity, hashing_t method);
extern void htable_print(htable h, FILE *stream);
extern int htable_search(htable h, char *str);

#endif
