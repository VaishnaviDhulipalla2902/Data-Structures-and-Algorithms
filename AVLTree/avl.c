// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
 
// An AVL tree node
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

//fucntion to search for a node in the tree
int search(struct Node* node, int num)
{
    if(node==0) return 0;
    if(node->key==num) return 1;
    if(node->key>num) return search(node->left, num);
    return search(node->right, num);
}
 
// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}

struct Node* zigzag1(struct Node *z)
{
    struct Node* y = z->right;
    struct Node* x = y->left;
    struct Node* T3 = x->right;
    struct Node* T2 = x->left;
    x->right = y;
    x->left = z;
    z->right = T2;
    y->left = T3;

    //update heights
    y->height = max(height(T3),height(y->right)) + 1;
    z->height = max(height(T2),height(z->left)) + 1;
    x->height = max(height(z),height(y)) + 1;

    return x;
}

struct Node* zigzag2(struct Node *z)
{
    struct Node* y = z->left;
    struct Node* x = y->right;
    struct Node* T2 = x->left;
    struct Node* T3 = x->right;
    x->left = y;
    x->right = z;
    y->right = T2;
    z->left = T3;

    //update heights
    y->height = max(height(y->left),height(T2)) + 1;
    z->height = max(height(T3),height(z->right)) + 1;
    x->height = max(height(z),height(y)) + 1;

}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *zigzig1(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *zigzig2(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return zigzig1(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return zigzig2(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        return zigzag2(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        return zigzag1(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
int findRank(struct Node* root, int x)
{
    int r = 1;
    struct Node* node = root;
    while(node)
    {
        if(node->key==x) 
        {
            if(node->right!=0)return(node->right->num+r);
            else return r;
        }
        else if(node->key > x)
        {
            r = r + 1 + node->right->num;
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return 0;
}

// A utility function to do inorder traversal of BST
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

int main(){
    int q,temp,n;
    struct Node *root = NULL;
    scanf("%d\n",&q);
    for(int j = 0;j < q;j++){
        scanf("%d %d",&n,&temp);
        if(n == 1){
           root = insert(root,temp);
        }
        if(n == 2){
            if(search(root,temp) != 1){
                printf("no\n");
            }
            else{
                inorder(root);
                printf("%d\n",findRank(root, num));
            }
        }
    }    
    return 0;
}