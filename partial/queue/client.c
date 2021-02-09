#include "stdio.h"
#include "header.h"
int timecounter=0;
int max_capacity=2;
int latest=0;
int mapping[10];

int main(int argc, char**argv){
    Queue *q=init_queue();
    enqueue(q,10);
    enqueue(q,45);
    enqueue(q,67);
    printf("The value dequeued is %d \n",dequeue(q));
    printf("The value dequeued is %d \n",dequeue(q));
    printf("The value dequeued is %d \n",dequeue(q));
    return 0;
}