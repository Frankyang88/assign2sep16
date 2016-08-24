#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>



struct bst{
	char *key;
	bst left;
	bst right;
};

bst bst_insert(bst b, char *str){
	

	if(b->key==NULL){
	b->key=str;
	return b;
	}
	else {
		if( strlen(str) >= strlen(b->key) ){
			if(b->right==NULL){
				b->right=bst_new();
				(b->right)->key=str;
					
				return b;
			}		
			else bst_insert(b->right,str);
		}
		else {
			if(b->left==NULL){
				b->left=bst_new();	
				(b->left)->key=str;
				return b;
			}
			else bst_insert(b->left,str);
			}
		return b;
	}
	
	
	
}

int bst_search(bst b, char *str){
	if(b==NULL) return 1;

	if(b->key==NULL) return 1;
	else {
		if( strcmp(b->key,str)==0)
		{	return 0;
		
		}
		else if( strlen(b->key) <= strlen(str))
			return bst_search(b->right,str);
		else    return bst_search(b->left,str); 
	}		
}

bst bst_delete(bst b,char *str){
	
	if(b==NULL) return NULL;
	if(b->key !=NULL){
			
		if( strcmp(b->key,str)==0){
			if(b->left== NULL && b->right==NULL)
			{	printf("free1\n");
				b->key=NULL;
				b=NULL;
				free(b);
				return b;	
			}
			if(b->left ==NULL)
			{	bst b1=b->right;	
				b->key=b1->key;
				b->right=b1->right;
				b->left=b1->left;
				free(b1);
				return b;
			}
			if(b->right==NULL){
				bst b1=b->left;
				b->key=b1->key;
				b->left=b1->left;
				b->right=b1->right;
				
				free(b1);
				
				return b;
			}
			if(b->left !=NULL && b->right !=NULL){
				bst b1=bst_min(b->right);
				b->key=b1->key;
				bst_delete(b->right,b1->key);	
				
				
			}
		}
		else if( strlen(b->key) <= strlen(str))
			return bst_delete(b->right,str);
		else    return bst_delete(b->left,str); 
	}

	return b;
}

bst bst_free(bst b){
	if(b==NULL) free(b);	
	
	if(b->left !=NULL)
	bst_free(b->left);
	if(b->right !=NULL)
	bst_free(b->right);
	free(b);

	return b;	
}
void bst_inorder(bst b, void (f)(char *str)){
	
	
	if(b != NULL) {
	
	bst_inorder( (b->left), f);
	
	if(b->key != NULL)
	f(b->key);

        bst_inorder( (b->right), f);
	}

}

bst bst_new(){
	bst b;
        b=(struct bst*) malloc(sizeof(struct bst));
	b->key= NULL;
	b->left=NULL;
	b->right=NULL;
	return b; 
}

void bst_preorder(bst b, void (f)(char *str)){
	if (b!= NULL){

	if(b->key!= NULL)
    	f(b->key);

	bst_preorder((b->left) ,f);
	bst_preorder((b->right),f);
       	}
}

bst bst_min(bst b){
	if(b==NULL) return NULL;
		
	if(b->left !=NULL)
	bst_min(b->left);
	
	if(b->left==NULL && b->key!=NULL){
		return b;	
		}
	return NULL;
}

bst bst_max(bst b){
	if(b==NULL) return b;
		
	if(b->right !=NULL)
	bst_max(b->right);
	
	if(b->right==NULL && b->key !=NULL){
	return b;	
		
	}

	return NULL;
}
