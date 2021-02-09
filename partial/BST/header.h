    struct node;
//Actually the value that can be variable sized based on the diffetent types that are modified
union valueobj{
    int key;
    struct node    *ptr;
};
typedef union valueobj valueobj;

// valueobj updatevalue(int type,void *)

//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
    valueobj value;
};
typedef struct logbook logbook;

// It is the fat node which will store the data and values for us 
struct node{
    int key;
    struct node * left;
    struct node * right;
    logbook *mods;
    int modcounter;
    struct node *bp;
    int type;
};
typedef struct node node;

// type =0 root, type=1 left, type=2 right
struct treelist {
    node* head;
};
typedef struct treelist treelist;
node* delete_time(node *root,int key);
node *predecessor_time(node *root,int key,int version);
node *successor_time(node *root,int key,int version);
node *search_time(node *root,int key,int version);
void preorder(node *root,int version);
void inorder(node *root,int version);
void insert(node *root,int key);
node * new_node(int key);
