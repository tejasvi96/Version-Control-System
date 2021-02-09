#include "stdio.h"
#include "stdlib.h"
#include "header.h"
int *latest;
int timecounter;
int max_capacity;
int **mapping;

int main(int argc,char **argv){
    hmap *h;
    h=malloc(sizeof(hmap));
    
    // Number of buckets in hashmap
    
    int n=50;
    init(h,n);
    init_samplecode(h);
    
    // merge(h,4,7);
    while(1){
        menu_program(h);
    }
    entry *e=findkey(*h,10,1);
    if(e!=NULL) printf("found key 10\n");
    
    e=findkey(*h,0,7);
    if(e!=NULL) printf("found key 0\n");
        for(int i=0;i<=timecounter;i++){
            printf("AT time %d\n",i);
             printhmap(*h,10,i);
        }
    return 0;

    }