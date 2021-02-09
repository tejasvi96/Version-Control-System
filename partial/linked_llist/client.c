#include "stdio.h"
#include "stdlib.h"
#include "header.h"
int timecounter=0;
int max_capacity=2;
int latest=0;
int mapping[10];
list *root[10];

int main(int argc , char **argv){
    // node root=new_node(10,424);

    
    list *l;
    l =malloc(sizeof(list));
    l->head=NULL;
    root[latest]=l;
    mapping[0]=0;
    add_element_2(root[latest],10);
    add_element_2(root[latest],15);
    add_element_2(root[latest],18);
    // delete_element_2(root[latest],25);
    delete_element_2(root[latest],15);
    delete_element_2(root[latest],18);
    add_element_2(root[latest],19);
    delete_element_2(root[latest],10);
    delete_element_2(root[latest],19);
    for(int i=0;i<=timecounter;i++){
        printf("The list \t");
        access_list(root[latest],i);
        printf("\n");
    }
    return 0;
}

// How do we access the list 