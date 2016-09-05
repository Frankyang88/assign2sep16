#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>
#include "mylib.h"




int LRBranch(char* bstr, char* istr){
	/*
	if( strlen(bstr)<= strlen(istr))
	return 1;
	else return 0;
	*/

	char key= *bstr;
	char input= *istr;
	int x=0;
	if(key!='\0' && input != '\0')
	x = key-input;
	else if(key=='\0' && input !='\0')
	return 1;
	else if(key!='\0' && input == '\0')
	return 0;
	
	if(key=='\0' && input=='\0')
	printf("exception!\n");
	
	
	
	if( x < 0 )
	return 1;
	else if(x>0)
	return 0;
	else return LRBranch(bstr+1,istr+1); 
		
	
}
struct treerec{
	char *key;
	tree_color color;
	tree left;
	tree right;
	tree parent;
	tree_t type;
	int frequency;
};


tree tree_insert(tree b, char *str){
	tree tmp;
	
	if(b == NULL || str == NULL ) return b;

	if(b->key==NULL){
	b->key=emalloc((strlen(str)+1)*sizeof(char));
	strcpy(b->key,str);
	b->frequency = 0;
	return find_root(b);

	}
	else {
		if(strcmp(b->key,str)==0){
			b->frequency +=1;
			return find_root(b);		
		}
		if( LRBranch(b->key,str) ){
			
			if(b->right==NULL){
				
				tmp=tree_new();
				b->right=tmp;
				tmp->parent=b;
				tmp->type=b->type;
				tree_insert(tmp,str);
				if(b->type == RBT)
				return tree_fix(b->right);
				else return find_root(b);	
				}		
			else tree_insert(b->right,str);
		}
		else {
				if(b->left==NULL){
			
				tmp=tree_new();
				b->left=tmp;	
				tmp->parent=b;
				tmp->type=b->type;
				tree_insert(tmp,str);
				if(b->type == RBT)
				return tree_fix(b->left);
				else return find_root(b);
				}
				else tree_insert(b->left,str);
			}
	}
	return find_root(b);
}

int tree_search(tree b, char *str){
	if(b==NULL) return 1;

	if(b->key==NULL) return 1;
	else {
		if( strcmp(b->key,str)==0)
		{	return 0;
		
		}
		else if(LRBranch(b->key,str))
			return tree_search(b->right,str);
		else    return tree_search(b->left,str); 
	}		
}

int tree_depth(tree b){
	int depthl=0;
	int depthr=0;
	if(b == NULL) return 0;
	else{
		if(b->left ==NULL && b->right==NULL)
		return 1;
	
		if(b->left !=NULL)	
		depthl =  tree_depth(b->left)+1;	

		if(b->right!=NULL)
		depthr =  tree_depth(b->right)+1;
	
		if(depthl>depthr)
		return depthl;
		else return depthr;
	}
}


tree tree_delete(tree b,char *str){

	tree tmp;

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
				b=tree_min(b->right);			
				free(tmp);
				free(tmp->key);
				tree_delete(b->right,b->key);
				return b;	
			}

				
		}
		else if( LRBranch(b->key,str))
			b->right=tree_delete(b->right,str);
		else    b->left=tree_delete(b->left,str); 
	}

	return b;
}		


tree tree_free(tree b){
	
	if(b!=NULL){
		
	if(b->left !=NULL)
	tree_free(b->left);
	if(b->right !=NULL)
	tree_free(b->right);
	
	if(b->key!=NULL)
	free(b->key);
	
	free(b);
	}
	return b;	
}
void tree_inorder(tree b, void (f)(tree_color color, char *str)){
	
	
	if(b != NULL) {
	
	tree_inorder( (b->left), f);
	f(b->color,b->key);

        tree_inorder( (b->right), f);
	}

}

void tree_postorder(tree b, void (f)(tree_color color, char *str)){
	
	
	if(b != NULL) {
	
	tree_postorder( (b->left), f);
	
        tree_postorder( (b->right), f);
	f(b->color,b->key);

	}

}
tree find_root(tree b){
	if(b==NULL)
	return b;
	
	if(b->parent == NULL)
	return b;

	if(b->parent != NULL)
	return find_root(b->parent);

	return NULL;
}

tree tree_new(tree_t typet){
	tree b;
   	 b= emalloc(sizeof( *b));
	b->key= NULL;
	b->left=NULL;
	b->right=NULL;
	b->parent=NULL;
	b->color=RED;
	b->type= BST;
	b->type = typet;
	b->frequency = 0;
	return b; 
}

void tree_preorder(tree b, void (f)(tree_color color,char *str)){
	if (b!= NULL){
    	f(b->color,b->key);

	tree_preorder((b->left) ,f);
	tree_preorder((b->right),f);
       	}
}

tree tree_min(tree b){
	if(b==NULL) return NULL;
		
	if(b->left !=NULL)
	tree_min(b->left);
	
	if(b->left==NULL && b->key!=NULL){
		return b;	
		}
	return NULL;
}

tree tree_max(tree b){
	if(b==NULL) return b;
		
	if(b->right !=NULL)
	tree_max(b->right);
	
	if(b->right==NULL && b->key !=NULL){
	return b;
	}

	return NULL;
}

tree right_rotate(tree b){
	
	if(NULL==b || NULL==b->left)
	return b;
	else{
		tree tmp=b;
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

tree left_rotate(tree b){

 	if(NULL==b || NULL==b->right)
	return b;
	else{
		tree tmp=b;

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

tree tree_fix(tree b){
	tree new_root1;
	tree new_root2;

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
						tree R = b->parent->parent->parent;
						new_root1=right_rotate(b->parent->parent);
						if(R != NULL && R->left == new_root1->right)
						R->left = new_root1;		
						else if(R!=NULL && R->right== new_root1->right)
						R->right = new_root1;
						new_root1->color=BLACK;
						new_root1->right->color=RED;
						return tree_fix(new_root1);
					}
					if(IS_RED(b->parent->parent->right)){
					  b->parent->parent->color= RED;
					  b->parent->parent->left->color= BLACK;
					  b->parent->parent->right->color=BLACK;
					  return tree_fix(b->parent->parent);
					}
				}
			if( ( b->parent->parent->left == b->parent && b->parent->right == b  )  && IS_RED(b->parent) && IS_RED(b->parent->right)){
				if(IS_RED(b->parent->parent->right)){
					b->parent->parent->color= RED;
					b->parent->parent->left->color= BLACK;
					b->parent->parent->right->color=BLACK;
					return tree_fix(b->parent->parent);
					}
				if(IS_BLACK(b->parent->parent->right)){

					tree R1 = b->parent->parent;
					tree R2 = b->parent->parent->parent;
			
					new_root1=left_rotate(b->parent);
					R1->left = new_root1;
			
					new_root2=right_rotate(R1);
			
					if(R2 != NULL && R2->left == new_root2->right)
					R2->left = new_root1;		
					else if(R2!=NULL && R2->right== new_root2->right)
					R2->right = new_root1;
		

			
					new_root2->color=BLACK;
					new_root2->right->color=RED;	
					return tree_fix(new_root2);	
					}
				}

			if( (  b->parent->parent->right == b->parent && b->parent->left == b   ) && IS_RED(b->parent) && IS_RED(b->parent->left)){
				if(IS_RED(b->parent->parent->left)){
					b->parent->parent->color= RED;
					b->parent->parent->left->color= BLACK;
					b->parent->parent->right->color=BLACK;
					return tree_fix(b->parent->parent);
				}
				if(IS_BLACK(b->parent->parent->left)){
			
					tree R1 = b->parent->parent;
					tree R2 = b->parent->parent->parent;

					new_root1=right_rotate(b->parent);
					R1->right = new_root1;

					new_root2=left_rotate(R1);

					if(R2 != NULL && R2->left == new_root2->left)
					R2->left = new_root1;		
					else if(R2!=NULL && R2->right== new_root2->left)
					R2->right = new_root1;

					new_root2->color=BLACK;
					new_root2->left->color=RED;

					return tree_fix(new_root2);		
				}
			}

			if( ( b->parent->parent->right == b->parent && b->parent->right == b  ) && IS_RED(b->parent) && IS_RED(b->parent->right)){

		
			  if(IS_RED(b->parent->parent->left)){
				b->parent->parent->color= RED;
				b->parent->parent->left->color= BLACK;
				b->parent->parent->right->color=BLACK;
				return tree_fix(b->parent->parent);
			  }
			  if(IS_BLACK(b->parent->parent->left)){

				tree R = b->parent->parent->parent;

				new_root1=left_rotate(b->parent->parent);
			
				if(R != NULL && R->left == new_root1->left)
				  R->left = new_root1;		
				else if(R!=NULL && R->right== new_root1->left)
				  R->right = new_root1;

				new_root1->color=BLACK;
				new_root1->left->color=RED;	
				return tree_fix(new_root1);	
			  }
			}


		}

		return find_root(b);

	return find_root(b);
}

/* -*- mode:c -*- */

/* These functions should be added to your tree.c file */

/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
   fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
   tree_output_dot_aux(t, out);
   fprintf(out, "}\n");
}

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
void tree_output_dot_aux(tree t, FILE *out) {
   if(t->key != NULL) {
      fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
              t->key, t->key, t->frequency,
              (RBT == t->type  && RED == t->color) ? "red":"black");
   }
   if(t->left != NULL) {
      tree_output_dot_aux(t->left, out);
      fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
   }
   if(t->right != NULL) {
      tree_output_dot_aux(t->right, out);
      fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
   }
}

