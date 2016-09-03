#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

void print_key(rbt_color color,char *s){
if(color==RED)
printf("red:%s\n",s);
else if(color== BLACK)
printf("black:%s\n",s);

}


int main(void){
rbt b=rbt_new(RBT);


b=rbt_insert(b,"h");
b=rbt_insert(b,"l");
b=rbt_insert(b,"i");
b=rbt_insert(b,"f");
b=rbt_insert(b,"j");
b=rbt_insert(b,"g");
b=rbt_insert(b,"k");
b=rbt_insert(b,"d");
b=rbt_insert(b,"a");
b=rbt_insert(b,"e");
b=rbt_insert(b,"b");
b=rbt_insert(b,"c");


/*
rbt_insert(b,"abcdefgh",NULL);
rbt_insert(b,"abcdefghijkl",NULL);
rbt_insert(b,"abcdefghi",NULL);
rbt_insert(b,"abcdef",NULL);
rbt_insert(b,"abcdefghij",NULL);
rbt_insert(b,"abcdefg",NULL);
rbt_insert(b,"abcdefghijk",NULL);
rbt_insert(b,"abcd",NULL);
rbt_insert(b,"a",NULL);
rbt_insert(b,"abcde",NULL);
rbt_insert(b,"ab",NULL);
rbt_insert(b,"abc",NULL);

if(!rbt_search(b,"abc")  && !rbt_search(b,"abcde") && !rbt_search(b,"abcdefg"))
printf("find!\n");
*/


rbt_preorder(b,print_key);

printf("-----------------\n");
rbt_preorder(b,print_key);

/*
rbt_delete(b,"a");
rbt_preorder(b,print_key);
*/
printf("-----------------\n");
b=rbt_insert(b,"x");

rbt_preorder(b,print_key);


rbt_free(b);

return 0;
}

