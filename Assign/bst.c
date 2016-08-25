#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include <string.h>
#include "mylib.h"


struct bstrec{
	char *key;
	bst left;
	bst right;
};

bst bst_insert(bst b, char *str){
	

	if(b->key==NULL){
	b->key=emalloc((strlen(str)+1)*sizeof(char));
	strcpy(b->key,str);
	return b;
	}
	else {
		if( strlen(str) >= strlen(b->key) ){
			if(b->right==NULL){
				b->right=bst_new();
				b->right->key=emalloc((strlen(str)+1)*sizeof(char));
				strcpy((b->right)->key,str);
					
				return b->right;
			}		
			else bst_insert(b->right,str);
		}
		else {
			if(b->left==NULL){
				b->left=bst_new();	
				b->left->key=emalloc((strlen(str)+1)*sizeof(char));
				strcpy((b->left)->key,str);
				return b->left;
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
/*
bst bst_delete(bst b,char *str){
	bst b1;

	if(b==NULL){free(b); return NULL;}
	if(b->key !=NULL){
			
		if( strcmp(b->key,str)==0){
			if(b->left== NULL && b->right==NULL)
			{	
				printf("delete communi\n");
				b->key=NULL;
				free(b->key);
				b=NULL;
				free(b);

				return b;	
			}
			if(b->left ==NULL)
			{
				b1=b;	
				b->key=NULL;		
				free(b->key);
				b=b1->right;
				b1=NULL;
				free(b1);
				return b;
			}
			if(b->right ==NULL){
				b1=b;
				b->key=NULL;
				free(b->key);
			
				b=b1->left;				
				b1=NULL;
				free(b1);
				return b;
			}
			if(b->left !=NULL && b->right !=NULL){
				b1=bst_min(b->right);
				b->key=erealloc(b->key,(strlen(b1->key)+1)*sizeof(char));
				strcpy(b->key,b1->key);
							
				bst_delete(b1,b1->key);
				return b;	
			}

				
		}
		else if( strlen(b->key) <= strlen(str))
			return bst_delete(b->right,str);
		else    return bst_delete(b->left,str); 
	}

	return b;
}

*/

bst bst_delete(bst b,char *str,bst root){
		bst b1;

	if(b==NULL){free(b); return NULL;}

	if(b->key !=NULL){
			
		if( strcmp(b->key,str)==0){
			if(b->left== NULL && b->right==NULL)
			{	
				if(root!=NULL){
				  if(root->left==b) 
				   root->left=NULL;
			          else if(root->right ==b) root->right=NULL;		 
				}
				free(b->key);
				free(b);
				return b;	
			}
			if(b->left ==NULL)
			{
				if(root!=NULL){
				 if(root->left == b){
					root->left=b->right;
					}
				 else if(root->right==b){
					root->right=b->right;
					}	
				
				}
			
				free(b->key);
				free(b);
				return b;
			}
			if(b->right ==NULL){
				if(root!=NULL){
				 if(root->left == b){
					root->left=b->left;
					}
				 else if(root->right==b){
					root->right=b->left;
					}	
				
				}
		
					
				free(b->key);
				free(b);
				return b;
			}
			if(b->left !=NULL && b->right !=NULL){
				b1=bst_min(b->right);
				
				b->key=erealloc(b->key,(strlen(b1->key)+1)*sizeof(char));
				strcpy(b->key,b1->key);
							
				bst_delete(b->right,b1->key,b);
				return b;	
			}

				
		}
		else if( strlen(b->key) <= strlen(str))
			return bst_delete(b->right,str,b);
		else    return bst_delete(b->left,str,b); 
	}

	return b;
}		


bst bst_free(bst b){
	
	if(b!=NULL){
		
	if(b->left !=NULL)
	bst_free(b->left);
	if(b->right !=NULL)
	bst_free(b->right);
	
	if(b->key!=NULL)
	free(b->key);
	
	free(b);
	}
	return b;	
}
void bst_inorder(bst b, void (f)(char *str)){
	
	
	if(b != NULL) {
	
	bst_inorder( (b->left), f);
	
	f(b->key);

        bst_inorder( (b->right), f);
	}

}

bst bst_new(){
	bst b;
        b= emalloc(sizeof( *b));
	b->key= NULL;
	b->left=NULL;
	b->right=NULL;
	return b; 
}

void bst_preorder(bst b, void (f)(char *str)){
	if (b!= NULL){
    	f(b->key);

	bst_preorder((b->left) ,f);
	bst_preorder((b->right),f);
       	}
}

bst bst_min(bst b){
	if(b==NULL) return NULL;
		
	if(b->left !=NULL)
	return bst_min(b->left);
	
	if(b->left==NULL && b->key!=NULL){
		return b;	
		}
	return NULL;
}

bst bst_max(bst b){
	if(b==NULL) return b;
		
	if(b->right !=NULL)
	return bst_max(b->right);
	
	if(b->right==NULL && b->key !=NULL){
	return b;	
		
	}

	return NULL;
}
