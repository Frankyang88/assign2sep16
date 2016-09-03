#ifndef rbt_H_
#define rbt_H_


#define IS_BLACK(x) ((NULL ==(x)) ||(BLACK == (x)->color))
#define IS_RED(x) ((NULL !=(x)) && (RED == (x)->color))

typedef enum {RED,BLACK} rbt_color;
typedef enum {BST,RBT} tree_t;
typedef struct rbtrec *rbt;

extern rbt rbt_delete(rbt b, char *str);
extern rbt rbt_free(rbt b);
extern void rbt_inorder(rbt b, void f(rbt_color color,char *str));
extern rbt rbt_insert(rbt b, char *str);
extern rbt rbt_new();
extern void rbt_preorder(rbt b, void f(rbt_color color,char *str));
extern void rbt_postorder(rbt b, void f(rbt_color color,char *str));
extern int rbt_search(rbt b, char *str);
extern rbt rbt_min(rbt b);
extern rbt rbt_max(rbt b);
extern rbt right_rotate(rbt b);
extern rbt left_rotate(rbt b);
extern rbt rbt_fix(rbt b);
extern int LRBranch(char* bstr, char* istr);
extern rbt find_root(rbt b);
#endif
