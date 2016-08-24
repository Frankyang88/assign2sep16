#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void print_key(char *s){
printf("%s\n",s);
}


int main(void){
bst b=bst_new();

bst_insert(b,"talentyang2");
bst_insert(b,"new information");
bst_insert(b,"string");
bst_insert(b,"string1111");
bst_insert(b,"string111");
bst_insert(b,"string55");
bst_insert(b,"string5");
bst_insert(b,"hello world1");
bst_insert(b,"communication123");

if(!bst_search(b,"string")  && !bst_search(b,"string5") && !bst_search(b,"string55"))
printf("find!\n");

bst_inorder(b,print_key);
bst_preorder(b,print_key);

bst_delete(b,"communication123");


bst_inorder(b,print_key);
bst_preorder(b,print_key);



bst_free(b);

return 0;
}

