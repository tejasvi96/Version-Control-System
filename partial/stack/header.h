    struct node;
//Actually the value that can be variable sized based on the diffetent types that are modified
// valueobj updatevalue(int type,void *)

//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
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
struct stack{
    node *top;
};
typedef struct stack stack;
void add_element_2(stack *l,int key);
void push(stack *s,int key);
int pop(stack *s);
stack * init_stack();
void peek(stack *s, int t);