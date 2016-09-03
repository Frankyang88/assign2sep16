#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"

int main(void){
hashing_t method=DOUBLE_H;
htable h=htable_new(113,method);
char word[256];
char op;
while(2 ==scanf(" %c %255s",&op,word)){
if('+' ==op){
	htable_insert(h,word);
/*htable_print(h,stdout);*/
	}
	else if('?' == op){
		
		printf("%d %s \n",htable_search(h,word),word);
	}
}

	htable_free(h);

	return 0;
}


