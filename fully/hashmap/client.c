#include "stdio.h"
#include "stdlib.h"
#include "header.h"
int *latest;
int timecounter;

int max_capacity;
int **mapping;
struct entry;
typedef struct entry entry;
int size;


int main(int argc,char **argv){
    hmap *h;
    h=malloc(sizeof(hmap));
    int n=10;
    init(h,n);
    for(int i=0;i<n;i++){
        latest[i]=0;
        mapping[i][0]=0;
    }
    insert(h,0,"#include<stdio.h>",timecounter,1);
    insert(h,20,"int main(int argc,char**argv){",timecounter,1);
    insert(h,0,"printf(Hello World)}",timecounter,1);
    insert(h,2,"printf(Hi there)}",timecounter,1);
    insert(h,13,"printf(Extra line)",timecounter,1);
    removekey(h,2,timecounter);
    insert(h,3,"printf(Gone in the past for the Extra line)",3,1);
    entry *e=findkey(*h,10,1);
    if(e!=NULL) printf("found key 10\n");
    
    e=findkey(*h,0,7);
    if(e!=NULL) printf("found key 0\n");
        for(int i=0;i<=timecounter;i++){
            printf("AT time %d\n",i);
             printhmap(*h,n,i);
        }
    return 0;

    }