#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"

int main(void){

htable h=htable_new(18143);

char word[256];
while (getword(word, sizeof word, stdin) != EOF) {
	htable_insert(h, word);
}
printf("hello world\n");
htable_print(h, stdout);
htable_free(h);

return EXIT_SUCCESS;

}
