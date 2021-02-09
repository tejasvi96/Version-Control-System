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
node * new_node(int key);
void add_element_2(list *l,int key);
void delete_element_2(list *l,int key);
void access_list(list *l,int t);