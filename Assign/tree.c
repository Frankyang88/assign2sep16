#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>
#include "mylib.h"


/*tree structure*/
struct treerec{
	char *key;
	tree_color color;
	tree left;
	tree right;
	tree parent;
	tree_t type;
	int frequency;
};


/*static method declaration*/
static void tree_output_dot_aux(tree t, FILE *out); 

/*LRBranch:decide the key's position in left or right branch
 * this is in alphabetic order
 * do comparison from letter to letter*/
int LRBranch(char* bstr, char* istr){
	char key= *bstr;
	char input= *istr;
	int x=0;
	if(key!='\0' && input != '\0')
	x = key-input;
	else if(key=='\0' && input !='\0')
	return 1;
	else if(key!='\0' && input == '\0')
	return 0;
	
	/*special cases: it shouldnot happen
 	*an exception case*/
	if(key=='\0' && input=='\0')
	printf("exception in selecting left/right subtrees!\n");
	
	
	/*compare the first letter, if they are the same letter
 	*do recursive operation to the next letter*/
	if( x < 0 )
	return 1;
	else if(x>0)
	return 0;
	else return LRBranch(bstr+1,istr+1); 
		
	
}
/*tree insert:
 * insert a string into tree
 * if the root(node) is null then return
 * if the current node is not null but its key is null then insert into this node and return root node
 * if the current node is not null and it has already placed a key
 * then check its left or right branch
 * if the left/right branch is null, create a node and insert string into this node
 * otherwise do recursion on that branch(Whether it go to left or right is decided by LRBranch function)
 * after insertion, if it is a red black tree do tree fix and tree fix will return the new root node
 * if it is a bst, if return the root of the tree*/
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


/*tree search:
 * search string in the tree, similar to tree insert operation 
 * in the process of finding a cell,
 *if it find the input string in tree, it will return 0
 * otehrwise, it return 1*/
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

/*tree depth:
 * return the depth of tree
 * recursive operation,it go through all the subtrees
 * and return the maximum height of all nodes as its height*/
int tree_depth(tree b){
	int depthl=0;
	int depthr=0;
	if(b == NULL) return 0;
	else{

		if(b->left ==NULL && b->right==NULL)
		return 0;
	
		if(b->left !=NULL)	
		depthl =  tree_depth(b->left)+1;	

		if(b->right!=NULL)
		depthr =  tree_depth(b->right)+1;
	
		if(depthl>depthr)
		return depthl;
		else return depthr;
	}
}

/*tree free:
 * free the tree nodes and the string memory
 * recursive operation on both left and right children of the current nodes*/
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
/*tree inoder:
 * inorder traverse,print tree node in inorder*/
void tree_inorder(tree b, void (f)(tree_color color, char *str)){
	
	
	if(b != NULL) {
	
	tree_inorder( (b->left), f);
	f(b->color,b->key);

        tree_inorder( (b->right), f);
	}

}

/*tree postorder:
 * postorder traverse,print tree node in post order*/
void tree_postorder(tree b, void (f)(tree_color color, char *str)){
	
	
	if(b != NULL) {
	
	tree_postorder( (b->left), f);
	
        tree_postorder( (b->right), f);
	f(b->color,b->key);

	}

}
/*find root
 * return the root node of the tree
 * if the node's parent is null, then return it*/
tree find_root(tree b){
	if(b==NULL)
	return b;
	
	if(b->parent == NULL)
	return b;

	if(b->parent != NULL)
	return find_root(b->parent);

	return NULL;
}

/*tree new:
 * create a new tree with type typet*/
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
/*tree preorder:
 * print the tree node in preorder*/
void tree_preorder(tree b, void (f)(tree_color color,char *str)){
	if (b!= NULL){
    	f(b->color,b->key);

	tree_preorder((b->left) ,f);
	tree_preorder((b->right),f);
       	}
}
/*tree min:
 * find the minimum node in the tree
 * go down recursive to the left most child*/
tree tree_min(tree b){
	if(b==NULL) return NULL;
		
	if(b->left !=NULL)
	tree_min(b->left);
	
	if(b->left==NULL && b->key!=NULL){
		return b;	
		}
	return NULL;
}
/*tree max:
 * find the maximum node in the tree
 * go down recursively to the right most child*/
tree tree_max(tree b){
	if(b==NULL) return b;
		
	if(b->right !=NULL)
	tree_max(b->right);
	
	if(b->right==NULL && b->key !=NULL){
	return b;
	}

	return NULL;
}
/*right rotate:
 * make the left child of root to be the new root
 * make the old root to be new right child of the new root
 * then if the new root's has an old right child,make the old right child to be the left child of the old root
 * if the new root has no old right child, make the old root's left child to be null
 * then fix up all the pointer of parents
 * the new root get the parent of the old root
 * then set the old root's parent to be new root*/
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
/*left rotate:
 * make the right child of root to be the new root
 * make the old root to be new left child of the new root
 * then if the new root's has an old left child,make the old left child to be the right child of the old root
 * if the new root has no old left child, make the old root's right child to be null
 * then fix up all the pointer of parents
 * the new root get the parent of the old root
 * then set new root as the old root's parent*/

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
/*tree fix:
 * recursive operation from the current to the top nodes
 * exactly the same operation as that in the labbook
 * add some code to fix the pointer problems that may break the tree's link
 * it fix the 'root' recursively 
 * if grandparent does not exist and parent exist, just repaint parent black
 * if parent doesnot exist, repaint itself black
 * */
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
static void tree_output_dot_aux(tree t, FILE *out) {
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

