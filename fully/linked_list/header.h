struct node;
//Actually the value that can be variable sized based on the diffetent types that are modified
// valueobj updatevalue(int type,void *)

//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
    struct node *ptr;
    // valueobj value;
};
typedef struct logbook logbook;

// It is the fat node which will store the data and values for us 
struct node{
    int key;
    struct node * next;
    logbook *mods;
    int modcounter;
    struct node *bp;
};
typedef struct node node;

// The linked list in list based implementation 
struct list{
    node *head;
};

typedef struct list list;
void delete_element_2(list *l,int key,int version);
void access_list(list *l,int t);
void add_element_2(list *l,int key,int version);