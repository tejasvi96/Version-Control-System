#include"stdio.h"
#include "stdlib.h"
#include "header.h"

int timecounter=0;
int max_capacity=2;
int latest=0;
stack *root[10];
int mapping[10];

int main(int argc,char **argv){
    stack *s=init_stack();

        stack *l;
    l =malloc(sizeof(stack));
    s->top=NULL;
    // add_element(&l,12,426);

    // int latest=0;
    root[latest]=l;
    mapping[0]=0;
    add_element_2(root[latest],10);
    add_element_2(root[latest],20);
    add_element_2(root[latest],40);
    printf("VAlue popped out is %d\t",pop(root[latest]));
    // print_stack(s);
    
    printf("VAlue popped out is %d\t",pop(root[latest]));
    
    printf("VAlue popped out is %d\t",pop(root[latest]));
     printf("VAlue popped out is %d\t",pop(root[latest]));
    // print_stack(s);
    printf("\n");
      for(int i=0;i<timecounter;i++){
        peek(root[i],i);
        printf("\n");
    }
    return 0;
}