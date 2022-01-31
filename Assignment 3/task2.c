#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int n=110470;
int A[110470],b=-1,i=0,inserts=0;
float comparisons, searches;
struct Tree_Node
{
    int doc_id;
    char *name;
    int word_count;
    int height;
    struct Tree_Node *left;
    struct Tree_Node *right;
}*root=NULL;


int findMax(int p, int q)
{
  return (p >= q)? p: q;
}

int height(struct Tree_Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

void randomize ( int a[], int n )
{
    srand(time(NULL));
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        if(a[i]!=a[j])
        {
              int t = a[i];
              a[i] = a[j];
             a[j] = t;
        }
    }
}

void tree_print_sorted(struct Tree_Node *root)
{
    if (root != NULL)
    {
        tree_print_sorted(root->left);
        printf("%d %s %d %d\n", root->word_count,root->name,root->doc_id,++i);
        tree_print_sorted(root->right);
    }
}

struct Tree_Node *rightRotate(struct Tree_Node *y)
{
    struct Tree_Node *x = y->left;
    struct Tree_Node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = findMax(height(y->left), height(y->right))+1;
    x->height = findMax(height(x->left), height(x->right))+1;
 
    return x;
}

struct Tree_Node *leftRotate(struct Tree_Node *x)
{
    struct Tree_Node *y = x->right;
    struct Tree_Node *z = y->left;
 
    y->left = x;
    x->right = z;
 
    x->height = findMax(height(x->left), height(x->right))+1;
    y->height = findMax(height(y->left), height(y->right))+1;
 
    return y;
}

int getBalanceFactor(struct Tree_Node *bal)
{
    if (bal == NULL)
        return 0;
    return height(bal->left) - height(bal->right);
}

struct Tree_Node* create_bst (int doc_id, char *name, int word_count, int height){
    struct Tree_Node *temp =  (struct Tree_Node *)malloc(sizeof(struct Tree_Node));
    if(temp != NULL){
        temp->doc_id = doc_id;
        temp->name = name;
        temp->word_count = word_count;
        temp->height = 1;
        temp->left = temp->right = NULL;
        inserts++;
    }
    return temp;
}

struct Tree_Node* tree_insert(struct Tree_Node* node, char* name, int doc_id, int word_count)
{
    if (node == NULL)
    {
        node = create_bst(doc_id, name,  word_count, 1);
        return node;
    }
 
    else
    {
        if (doc_id < node->doc_id)
            node->left  = tree_insert(node->left, name,doc_id,word_count);
        else if(doc_id > node->doc_id)
            node->right = tree_insert(node->right, name,doc_id,word_count);
        else  return node;
    }
    
    node->height = 1 + findMax(height(node->left),height(node->right));
    int balance = getBalanceFactor(node);
 
    // Left Left Case
    if (balance >= 2 && doc_id < node->left->doc_id)
        return rightRotate(node);
 
    // Right Right Case
    if (balance <= -2 && doc_id > node->right->doc_id)
        return leftRotate(node);
 
    // Left Right Case
    if (balance >= 2 && doc_id > node->left->doc_id)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance <= -2 && doc_id < node->right->doc_id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

int bst_check(struct Tree_Node *tree,struct Tree_Node *l,struct Tree_Node *r)
{
    if (tree == NULL)
        return 0;
    if (l != NULL && tree->doc_id < l->doc_id)
        return -1;
    if (r != NULL && tree->doc_id > r->doc_id)
        return -1;
    return bst_check(tree->left, l, tree) && bst_check(tree->right, tree, r);
}

int balanced_tree(struct Tree_Node *root)
{
   int lh,rh;
   if(root == NULL)
    return 1;
 
   lh = height(root->left);
   rh = height(root->right);
 
   if( abs(lh-rh) <= 1 &&  balanced_tree(root->left) &&  balanced_tree(root->right))
       return 1;

   return 0;
}

int countNodes (struct Tree_Node* root)
{
    if (root == NULL)
        return 0;
    return countNodes (root->left) + countNodes (root->right) + 1;
}

int bstdb_init ( void )
{
    for(int i = 0; i<n; i++)
        A[i] = i;
    randomize(A,n);
    return 1;
}

int bstdb_add ( char *name, int word_count )
{
    root=tree_insert(root,name,A[++b],word_count);
    return A[b];
}

int bstdb_get_word_count ( int doc_id )
{
    struct Tree_Node *p = root;
    while (1)
    {
        comparisons++;
        if (p == NULL){
            comparisons++;
            return -1;
        }
        else if (doc_id==p->doc_id){
            searches++;
            comparisons++;
            return p->word_count;
        }
        else if (doc_id<p->doc_id)
            p = p->left;
        else
            p = p->right;
    }
}
char* bstdb_get_name ( int doc_id )
{
    struct Tree_Node *p = root;
    while (1)
    {
        comparisons++;
        if (p == NULL){
            comparisons++;
            return NULL;
        }
        else if (doc_id==p->doc_id){
            searches++;
            comparisons++;
            return p->name;
        }
        else if (doc_id<p->doc_id)
            p = p->left;
        else
            p = p->right;
    }
}
void bstdb_stat ( void ) {
    printf("\nSome stats are as follows\n");
    
    printf("\nAvg comparisons per search: %f",(comparisons/searches));
    printf("\nList size matches expected?: ");
    if(inserts==countNodes(root))
        printf("Yes\n");
    else
        printf("No\n");
    
    printf("\nIs it a Binary Search Tree?\n");
    if(bst_check(root,NULL,NULL)==0)
        printf("It is a binary search tree with unique values.\n");
    else
        printf("It is not a binary search tree\n");
    
    printf("\nIs the tree balanced\n");
    if(balanced_tree(root))
        printf("Yes, the tree is balanced\n");
    else
        printf("No, the tree isn't balanced\n");
    
    printf("\nHeight of the tree is %d\n",height(root));
    printf("\nNumber of nodes are %d\n",countNodes(root));
}
void bstdb_quit ( void )
{
    //
}
