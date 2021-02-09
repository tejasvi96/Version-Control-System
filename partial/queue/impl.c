#include "stdio.h"

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

struct Queue {
    node * front, *rear;
};
typedef struct Queue Queue;

Queue * init_queue(){
    Queue *Q=malloc(sizeof(Queue));
    Q->front=Q->rear=NULL;
    return Q;
}
void enqueue(Queue * Q,int key){   
    node * temp=malloc( sizeof(node) );
    Queue *q=malloc(sizeof(Queue));
    
    temp->key=key;
    temp->next=NULL;
    if(Q->front==NULL){
        Q->front=temp;
        Q->rear=Q->front;
    }
    else{
        (Q->rear)->next=temp;
        Q->rear=(Q->rear)->next;
    }
}

int dequeue(Queue *Q){
    int val;
    if(Q->front==NULL){
        printf("Queue is empty");
        exit(0);
    }
    else{
        val=(Q->front)->key;
        Q->front=(Q->front)->next;

        if(Q->front==NULL) Q->rear=Q->front=NULL;
    }
    return val;
}

int empty_queue(Queue Q){
    if (Q.front==NULL) return 1;
    else return 0;
}