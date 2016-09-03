#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"
#include <string.h>
#include "mylib.h"




int LRBranch(char* bstr, char* istr){
/*
	if( strlen(bstr)< strlen(istr))
	return 1;
	else return 0;
*/	
	char key= *bstr;
	char input= *istr;
	int x = key- input;
	if( x < 0 )
	return 1;
	else return 0;
	
		
	
}
struct rbtrec{
	char *key;
	rbt_color color;
	rbt left;
	rbt right;
	rbt parent;
	tree_t type;
};


rbt rbt_insert(rbt b, char *str){
	rbt tmp;
	
	if(b == NULL || str == NULL ) return b;

	if(b->key==NULL){
	b->key=emalloc((strlen(str)+1)*sizeof(char));
	strcpy(b->key,str);

	return find_root(b);

	}
	else {
		if( LRBranch(b->key,str) ){
			
			if(b->right==NULL){
				
				tmp=rbt_new();
				b->right=tmp;
				tmp->parent=b;
				tmp->type=b->type;
				rbt_insert(tmp,str);
				return rbt_fix(b->right);	
				}		
			else rbt_insert(b->right,str);
		}
		else {
				if(b->left==NULL){
			
				tmp=rbt_new();
				b->left=tmp;	
				tmp->parent=b;
				tmp->type=b->type;
				rbt_insert(tmp,str);

				return rbt_fix(b->left);
				
				}
				else rbt_insert(b->left,str);
			}
	}
	return find_root(b);
}

int rbt_search(rbt b, char *str){
	if(b==NULL) return 1;

	if(b->key==NULL) return 1;
	else {
		if( strcmp(b->key,str)==0)
		{	return 0;
		
		}
		else if(LRBranch(b->key,str))
			return rbt_search(b->right,str);
		else    return rbt_search(b->left,str); 
	}		
}

rbt rbt_delete(rbt b,char *str){

	rbt tmp;

	if(b==NULL){ return NULL;}

	if(b->key !=NULL){
			
		if( strcmp(b->key,str)==0){

			if(b->left== NULL && b->right==NULL)
			{	
				free(b->key);
				free(b);
				return b;	
			}
			if(b->left ==NULL)
			{     
				tmp=b;
				b=b->right;
				free(tmp->key);
				free(tmp);

				return b;
			}
			if(b->right ==NULL){
			
				tmp=b;
				b=b->left;
				
				free(tmp->key);
				free(tmp);

				return b;
			}
			if(b->left !=NULL && b->right !=NULL){

				tmp=b;
				b=rbt_min(b->right);			
				free(tmp);
				free(tmp->key);
				rbt_delete(b->right,b->key);
				return b;	
			}

				
		}
		else if( LRBranch(b->key,str))
			b->right=rbt_delete(b->right,str);
		else    b->left=rbt_delete(b->left,str); 
	}

	return b;
}		


rbt rbt_free(rbt b){
	
	if(b!=NULL){
		
	if(b->left !=NULL)
	rbt_free(b->left);
	if(b->right !=NULL)
	rbt_free(b->right);
	
	if(b->key!=NULL)
	free(b->key);
	
	free(b);
	}
	return b;	
}
void rbt_inorder(rbt b, void (f)(rbt_color color, char *str)){
	
	
	if(b != NULL) {
	
	rbt_inorder( (b->left), f);
	f(b->color,b->key);

        rbt_inorder( (b->right), f);
	}

}

void rbt_postorder(rbt b, void (f)(rbt_color color, char *str)){
	
	
	if(b != NULL) {
	
	rbt_postorder( (b->left), f);
	
        rbt_postorder( (b->right), f);
	f(b->color,b->key);

	}

}
rbt find_root(rbt b){
	if(b==NULL)
	return b;
	
	if(b->parent == NULL)
	return b;

	if(b->parent != NULL)
	return find_root(b->parent);

	return NULL;
}

rbt rbt_new(tree_t typet){
	rbt b;
    b= emalloc(sizeof( *b));
	b->key= NULL;
	b->left=NULL;
	b->right=NULL;
	b->parent=NULL;
	b->color=RED;
	b->type= BST;
	b->type = typet;
	return b; 
}

void rbt_preorder(rbt b, void (f)(rbt_color color,char *str)){
	if (b!= NULL){
    	f(b->color,b->key);

	rbt_preorder((b->left) ,f);
	rbt_preorder((b->right),f);
       	}
}

rbt rbt_min(rbt b){
	if(b==NULL) return NULL;
		
	if(b->left !=NULL)
	rbt_min(b->left);
	
	if(b->left==NULL && b->key!=NULL){
		return b;	
		}
	return NULL;
}

rbt rbt_max(rbt b){
	if(b==NULL) return b;
		
	if(b->right !=NULL)
	rbt_max(b->right);
	
	if(b->right==NULL && b->key !=NULL){
	return b;
	}

	return NULL;
}

rbt right_rotate(rbt b){
	
	if(NULL==b || NULL==b->left)
	return b;
	else{
		rbt tmp=b;
		b=b->left;
		
		b->parent=tmp->parent;

		if(b->right!=NULL){
		tmp->left=b->right;
		b->right->parent=tmp;
		}
		else {

		tmp->left = NULL;
		}
		b->right=tmp;
		tmp->parent=b;
		
		return b;
		
		}
}

rbt left_rotate(rbt b){

 	if(NULL==b || NULL==b->right)
	return b;
	else{
		rbt tmp=b;

		b=b->right;
		b->parent=tmp->parent;
		if(b->left!=NULL){
		tmp->right=b->left;
		b->left->parent=tmp;
		}
		else {
		tmp->right =  NULL;
		}
	
		b->left=tmp;
		tmp->parent=b;	
		return b;
		}
}

rbt rbt_fix(rbt b){
	rbt new_root1;
	rbt new_root2;

	if(b->type == RBT){

			if(b== NULL){
				printf("error occur\n");
			}

			if(b->parent == NULL){
				b->color = BLACK;
				return b;
			}
			else if(b->parent->parent==NULL){
			b->parent->color = BLACK;
			return b->parent;
			}
			else {

				if(  ( b->parent->parent->left == b->parent && b->parent->left == b   ) &&  IS_RED(b->parent) && IS_RED(b->parent->left)){
		
					if(IS_BLACK(b->parent->parent->right)){
			
						rbt R = b->parent->parent->parent;

						new_root1=right_rotate(b->parent->parent);

						if(R != NULL && R->left == new_root1->right)
						R->left = new_root1;		
						else if(R!=NULL && R->right== new_root1->right)
						R->right = new_root1;
	
						new_root1->color=BLACK;
						new_root1->right->color=RED;
	
						return rbt_fix(new_root1);
			
					}
		
					if(IS_RED(b->parent->parent->right)){
					  b->parent->parent->color= RED;
					  b->parent->parent->left->color= BLACK;
					  b->parent->parent->right->color=BLACK;
					  return rbt_fix(b->parent->parent);
					}
			}
	
			if( ( b->parent->parent->left == b->parent && b->parent->right == b  )  && IS_RED(b->parent) && IS_RED(b->parent->right)){
				if(IS_RED(b->parent->parent->right)){
					b->parent->parent->color= RED;
					b->parent->parent->left->color= BLACK;
					b->parent->parent->right->color=BLACK;
					return rbt_fix(b->parent->parent);
				}
				if(IS_BLACK(b->parent->parent->right)){

					rbt R1 = b->parent->parent;
					rbt R2 = b->parent->parent->parent;
			
					new_root1=left_rotate(b->parent);
					R1->left = new_root1;
			
					new_root2=right_rotate(R1);
			
					if(R2 != NULL && R2->left == new_root2->right)
					R2->left = new_root1;		
					else if(R2!=NULL && R2->right== new_root2->right)
					R2->right = new_root1;
		

			
					new_root2->color=BLACK;
					new_root2->right->color=RED;	
					return rbt_fix(new_root2);	
				}
			}

			if( (  b->parent->parent->right == b->parent && b->parent->left == b   ) && IS_RED(b->parent) && IS_RED(b->parent->left)){
				if(IS_RED(b->parent->parent->left)){
					b->parent->parent->color= RED;
					b->parent->parent->left->color= BLACK;
					b->parent->parent->right->color=BLACK;
					return rbt_fix(b->parent->parent);
				}
				if(IS_BLACK(b->parent->parent->left)){
			
					rbt R1 = b->parent->parent;
					rbt R2 = b->parent->parent->parent;

					new_root1=right_rotate(b->parent);
					R1->right = new_root1;

					new_root2=left_rotate(R1);

					if(R2 != NULL && R2->left == new_root2->left)
					R2->left = new_root1;		
					else if(R2!=NULL && R2->right== new_root2->left)
					R2->right = new_root1;

					new_root2->color=BLACK;
					new_root2->left->color=RED;

					return rbt_fix(new_root2);		
				}
			}

			if( ( b->parent->parent->right == b->parent && b->parent->right == b  ) && IS_RED(b->parent) && IS_RED(b->parent->right)){

		
			  if(IS_RED(b->parent->parent->left)){
				b->parent->parent->color= RED;
				b->parent->parent->left->color= BLACK;
				b->parent->parent->right->color=BLACK;
				return rbt_fix(b->parent->parent);
			  }
			  if(IS_BLACK(b->parent->parent->left)){

				rbt R = b->parent->parent->parent;

				new_root1=left_rotate(b->parent->parent);
			
				if(R != NULL && R->left == new_root1->left)
				  R->left = new_root1;		
				else if(R!=NULL && R->right== new_root1->left)
				  R->right = new_root1;

				new_root1->color=BLACK;
				new_root1->left->color=RED;	
				return rbt_fix(new_root1);	
			  }
			}


		}

		return find_root(b);
	}
	else {	find_root(b);}

	return find_root(b);
}
