#include"stdio.h"
#include "stdlib.h"
extern int timecounter;

void updatetime(){
    timecounter++;
}
extern int max_capacity;
extern int latest;
    int mapping[10];
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
stack *root[10];
stack * init_stack(){
    stack *temp=(stack *)malloc(sizeof(stack));
    temp->top=NULL;
    return temp;
}
void add_element_2(stack *l,int key){
    node *temp=(node *)malloc(sizeof(node));
    temp->key=key;
    temp->mods=(logbook *)malloc(sizeof(logbook)*(max_capacity));
    temp->modcounter=0;
    temp->next=NULL;
    int cnt;
    if(l->top==NULL){
        // is it neeeded? 
        temp->bp=NULL;
        l->top=temp;
    }
    else{
        node *it=l->top;
        int flag=0;
        stack *s;
        s=malloc(sizeof(stack));
        s->top=temp;
        temp->next=l->top;
        root[++latest]=s;
        updatetime();
        mapping[latest]=timecounter;
        
    }
}
void push(stack *s,int key){
    node *temp=malloc(sizeof(node));
    temp->key=key;
    temp->next=NULL;
    if(s->top==NULL){
        s->top=temp;
    }
    else{
        temp->next=s->top;
        s->top=temp;
    }
}
int top(stack *s,int t){

}
int isempty(stack *s){
    if(s->top==NULL) return 1;
    else return 0;
}
int pop(stack *s){
    if(isempty(s)) {
        printf("The stack is empty\n");
        return -1;
        }
    // must free here 
        node *it=s->top;
        int value=it->key;
        int flag=0;
        stack *l;
        l=malloc(sizeof(stack));
        it=it->next;
        l->top=it;
        root[++latest]=l;
        updatetime();
        mapping[latest]=timecounter;
        return value;
}
void peek(stack *s, int t){
        stack * it;

    for(int i=latest;i>=0;i--){
        if(t>=mapping[i]){
            it=(root[i]);
        break;
        }
    }
    if(it==NULL)
        printf("empty stack");
    else
    printf("%d",it->top->key);
    // return s->top->key;
}