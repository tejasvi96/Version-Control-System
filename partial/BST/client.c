#include "stdio.h"
#include "stdlib.h"
#include "header.h"

int timecounter=0;
int max_capacity=2;
int latest=0;
int mapping[10];
treelist *roots[10];

int main(int argc,char **argv){
    treelist *t;
    // Inserting the root node 
    t->head=new_node(5);
    mapping[0]=0;
    latest=0;
    roots[latest]=t;
    node * temp=NULL;
    insert(roots[latest]->head,10);
    insert(roots[latest]->head,2);
    insert(roots[latest]->head,1);
    insert(roots[latest]->head,4);
    insert(roots[latest]->head,3);
    
    temp=delete_time(roots[latest]->head,5);
    for(int i=0;i<=timecounter;i++){
        inorder(getroot(i),i);
        printf("\n");
        preorder(getroot(i),i);
        printf("\n\n");
    }
        printf("\n");
    return 0;
}