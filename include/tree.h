#ifndef _TREE_H_
#define _TREE_H_

typedef struct __M_tree_t__ M_tree_t;

M_tree_t* M_tree_make();
void M_tree_free (M_tree_t* tree);
void M_tree_print(M_tree_t* tree);

#endif //tree_h