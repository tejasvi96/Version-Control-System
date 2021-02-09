#include "stdio.h"
#include "stdlib.h"
#include "header.h"
int *latest;
int timecounter;
int max_capacity;
int **mapping;

int size;
int main(int argc,char **argv){
    hmap *h;

    // newhmap(&h,50);
    h=(hmap *)malloc(sizeof(hmap));
    int n=10;
    init(h,n);

				   
	int p=100;
	char *ch="Helooo";
	float fp=3.14;
    insert(h,0,&p,0);
    insert(h,10,ch,1);
    insert(h,20,&fp,2);		   
    insert(h,31,"thirty one",1);
    removekey(h,20);
    insert(h,50,"fifty",1);
    insert(h,0,"Zerooo",1);
    removekey(h,10);
        for(int i=0;i<=timecounter;i++){
            printf("AT time %d\n",i);
             printhmap(*h,n,i);
        }
    return 0;

    }