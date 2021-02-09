#include "stdio.h"
#include "stdlib.h"
int *latest;
extern int timecounter;
void updatetime(){
    timecounter++;
}
extern int max_capacity;
int **mapping;
struct entry;
typedef struct entry entry;
int size;
union valueobj{
	  int tag;
    struct {
        int tag;
        int val;
    } int_;
    struct {
        int tag;
        float val;
    } float_;
	    struct {
        int tag;
        char* val;
    } char_;
};
typedef union valueobj valueobj;
enum type {INT ,STRING,FLOAT};
//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
    struct entry   *ptr;
};
typedef struct logbook logbook;

struct entry{
    int key;
    valueobj value;
    struct entry *next;
    logbook *mods;
    int modcounter;
    entry *bp;
};

struct entrylist{
    entry *head;
};
typedef struct entrylist entrylist;

struct map{
    // int hashkey;
    entrylist * head;
};
typedef struct map map;
struct hmap{
    // int size;
    map *head;
};
typedef struct hmap hmap;
typedef struct hhmap hhmap;

void init(hmap *h,int n){
    timecounter=0;
    max_capacity=10;
    size=n;
    int len;
    len = sizeof(int *) * n + sizeof(int) * n * n; 
    mapping = (int **)malloc(sizeof(int*)*n); 
    latest=(int *)malloc(sizeof(int)*n);
        h->head=malloc(sizeof(map*)*n);
        
    for(int i=0;i<n;i++){
        h->head[i].head=malloc(sizeof(entrylist *)*n);
        for(int j=0;j<n;j++)
            h->head[i].head[j].head=NULL;
    }
    // mapping=(int *)malloc(n*n*sizeof(int));
    for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
        *(mapping+i)=(int*)malloc(sizeof(int)*n);
    }
}
int keyequals(int key1,int key2){
    if(key1==key2){
        return 1;
    }
    else return 0;
}

void * getfield(entry *it,char *field,int version){
    int cnt=it->modcounter;
    // printf("cnt %d \t",cnt);
    void *p;
    int flag=0;
    while(--cnt>=0 ){
        if( it->mods[cnt].version>version)continue;
        if(it->mods[cnt].field==field){
            flag=1;
            if(field=="next"){
                 p=(entry *)it->mods[cnt].ptr;
            }

            break;
        }
    }
    if (flag==1) return p;
    else {
        if(field=="key"){
            return((int *)it->key);
        }
        else if(field=="next")
        {
            return (it->next);
        }
        
    }
}

// latest for each must be tracked
void recurse(hmap *h,entry *parent,entry *child,char *field){
    entry *next;
    int keyval;
    if(parent==NULL){
            int hash=(child->key)%size;
            // printf("reached a root\n");
            if(child!=NULL){
            child->bp=NULL;
            int hash=(child->key)%size;
            }

            h->head[hash].head[++latest[hash]].head=child;    
            updatetime();
            mapping[(child->key)%size][latest[(child->key)%size]]=timecounter;
            // printf("Root has now key as %d\n",cnode->key);
            return;
    }
    else{
        int cnt=parent->modcounter;
        if(cnt==max_capacity){
            // printf("log is full case\n");    
            // Must update the time here somehow for the version
            next=getfield(parent,"next",timecounter);
			//keyval=getfield(parent,"key",timecounter);
            entry *temp=(entry *)malloc(sizeof(entry));
            temp->key=parent->key;
            temp->value=parent->value;
            temp->modcounter=0;
            temp->mods=(logbook *)malloc(sizeof(logbook)*max_capacity);
            temp->bp=parent->bp;
            
            if(field=="next"){
                temp->next=child;
            }
            // if(temp->bp==NULL &&)
            recurse(h,temp->bp,temp,field);
        }
        else{
            updatetime();
            parent->mods[cnt].field=field;
            parent->mods[cnt].version=timecounter;
            parent->mods[cnt].ptr=child;
            if(child!=NULL)
                child->bp=parent;
            (parent->modcounter)++;
        }


    }
}

void newhmap(hmap *h,int size){
    // hmap *temp=malloc(sizeof(hmap));
    // temp->size=0;
    // h->size=0;
    h->head=(map *)malloc(sizeof(map*)*size);
    // for(int i=0;i<size;i++) (h->head[i]).hash[]=NULL;
}

valueobj get(hmap *h,int key){
    int hash=key%size;
    if(h->head[hash].head[latest[hash]].head==NULL){
        valueobj v1;
        v1.tag=-1;
        printf("Value not found\n");
        return v1;
    }
        entry *temp=h->head[hash].head[latest[hash]].head;
        while(temp!=NULL){
            if(temp->key==key){
                return temp->value;
            }
            temp=temp->next;
        }    
        
}
int removekey(hmap *h,int key,int version){
    int hash=key%size;
    int flag=0;

        entry *temp;
                        for(int k=latest[hash];k>=0;k--)
            {
                if(version>=mapping[hash][k]){
                        
                     temp=(h->head[hash]).head[k].head;
                     break;
                }        
            }
                    if(temp==NULL)
        return 0;
            // entry *temp=h->head[hash].head[latest[hash]].head;
            entry *next=(entry *)getfield(temp,"next",version);
            entry *prev=temp;
            // if(temp==NULL) return -1;
            if(temp->key==key){
                flag=1;
                // printf("Found a match");
                if(next==NULL){
                    // printf("root node case \n");
                    h->head[hash].head[++latest[hash]].head=next;    
            // roots[(child->key)%size][++latest[(child->key)%size]]=l;
            updatetime();
            // versionobj.time=timecounter;
            mapping[hash][latest[hash]]=timecounter;
            // return 1;
                }
                else
                recurse(h,prev->bp,next,"next");
                // h->head[hash].=(h->head[hash].locn)->next;
                // return 1;
            }

            else{
                        if(version!=timecounter){
        h->head[hash].head[++latest[hash]].head=temp;
        mapping[hash][latest[hash]]=timecounter+1;
            }

                while(temp!=NULL){


            if(temp->key==key){
                // printf("Fodund a match");
               
                next=(entry *)getfield(temp,"next",version);
                 recurse(h,prev,next,"next");
                //  timecounter--;
                 flag=1;
                 break;
                // prev->next=temp->next;
                // return 1;
            }
            prev=temp;
            temp=(entry *)getfield(temp,"next",version);
            if(version!=timecounter &&temp!=NULL){
                int cnt=prev->modcounter;
                prev->mods[cnt].field="next";
                prev->mods[cnt].version=timecounter+1;
                prev->mods[cnt].ptr=temp;
                prev->modcounter++;
            }
            
        } 
   
            }
             if(flag==1){

        
          if(version!=timecounter-1){
        for(int i=0;i<10;i++){
                    if(i==hash)continue;
            for(int k=latest[i];k>=0;k--)
            {
                //copying that times version
                if(version>=mapping[i][k]){
                    // Will have to update inside these nodes also 
                    // i.e set the next appropriately 
                     h->head[i].head[++latest[i]].head=(h->head[i]).head[k].head;
                     entry *it=(h->head[i]).head[k].head;
                     while(it!=NULL){
                         int cnt=it->modcounter;
                         entry *next=getfield(it,"next",version);
                         it->mods[cnt].field="next";
                         it->mods[cnt].version=timecounter-1;
                         it->mods[cnt].ptr=next;
                         it->modcounter++;

                         it=next;
                     }
                     mapping[i] [latest[i]]=timecounter;
                     break;
                }
                   
                    
            }
            
        }

    }
        }
        return 1;   
}
void insert(hmap *h,int key,char *value,int version,int tag){
    // WE must work on the latest head of the current key 
    int hash=key%size;
    entry *t=(entry *)malloc(sizeof(entry));
    t->key=key;
	valueobj v1;
	v1.tag=tag;
	switch(tag){
	
	case 0:
		{
			v1.int_.tag=0;
			v1.int_.val=(int)(*(int *)(value));
            break;
		}
		
	case 1:
		{
			v1.char_.tag=1;
			v1.char_.val=(char *)value;
            break;
		}
		
	case 2:
		{
			v1.float_.tag=2;
			v1.float_.val=(float)(*(float *)(value));
            
        }
		
	}
    t->value=v1;
    t->bp=NULL;
    // updatetime();
    t->modcounter=0;
    t->mods=(logbook *)malloc(sizeof(logbook)*max_capacity);
    t->next=NULL;
    entry *e=NULL;
    // int hash=i%size;
            for(int k=latest[hash];k>=0;k--)
            {
                if(version>=mapping[hash][k]){
                        
                     e=(h->head[hash]).head[k].head;
                     break;
                }        
            }
    //calucalte latest hash based on the version

    if(e==NULL){
         updatetime();
        h->head[hash].head[++latest[hash]].head=t;
        mapping[hash][latest[hash]]=timecounter;
    }
    else{
        // Will need to check if the keys of the hashmap are equal 
        if(version!=timecounter){
        h->head[hash].head[++latest[hash]].head=e;
        mapping[hash][latest[hash]]=timecounter+1;
            }

        entry *temp=e;
        entry*prev=NULL;
        int flag=0;
        while(temp!=NULL){
            if(temp->key==key){
                t->bp=temp->bp;
                t->modcounter=temp->modcounter;
                for(int l=temp->modcounter-1;l>=0;l--){
                    t->mods[l].field=temp->mods[l].field;
                    t->mods[l].version=temp->mods[l].version;
                    t->mods[l].ptr=temp->mods[l].ptr;
                    if(t->mods[l].ptr!=NULL){
                        t->mods[l].ptr->bp=t;
                    }
                }
                //  if(prev==NULL){

                //  }   
                 recurse(h,prev,t,"next");
                // printf("need to take care of modification of the key\n");
                flag=1;
                break;
            }
            prev=temp;

            
            temp=getfield(temp,"next",version); 
            if(version!=timecounter &&temp!=NULL){
                int cnt=prev->modcounter;
                prev->mods[cnt].field="next";
                prev->mods[cnt].version=timecounter+1;
                prev->mods[cnt].ptr=temp;
                prev->modcounter++;
            }
        }
        if(flag==0){
            // printf("key not present already");
            recurse(h,prev,t,"next");
        }
        // prev->next=t;
    }
    if(version!=timecounter-1){
        for(int i=0;i<10;i++){
                    if(i==hash)continue;
            for(int k=latest[i];k>=0;k--)
            {
                //copying that times version
                if(version>=mapping[i][k]){
                    // Will have to update inside these nodes also 
                    // i.e set the next appropriately 
                     h->head[i].head[++latest[i]].head=(h->head[i]).head[k].head;
                     entry *it=(h->head[i]).head[k].head;
                     while(it!=NULL){
                         int cnt=it->modcounter;
                         entry *next=getfield(it,"next",version);
                         it->mods[cnt].field="next";
                         it->mods[cnt].version=timecounter-1;
                         it->mods[cnt].ptr=next;
                         it->modcounter++;

                         it=next;
                     }
                     mapping[i] [latest[i]]=timecounter;
                     break;
                }
                   
                    
            }
            
        }

    }
    // return 1;
    
}
void printhmap(hmap h,int n,int version){
    for(int i=0;i<n;i++){
        // for(int j=0;j<n;j++){
            // entry *e=(h.head[i]).head[j].head;
            entry *e=NULL;
            int hash=i%size;
            for(int k=latest[hash];k>=0;k--)
            {
                if(version>=mapping[hash][k]){       
                     e=(h.head[i]).head[k].head;
                     break;
                }               
    }
        // printf("%d\t",i);
            while(e!=NULL)
            {
				switch (e->value.tag){
					case  0:
					printf("%d %d\t",e->key,e->value.int_.val);
                    break;
				case 1:
					printf("%d %s\t",e->key,e->value.char_.val);
                    break;
				case 2:
					printf("%d %f\t",e->key,e->value.float_.val);
				
				}
         
                e=(entry *)getfield(e,"next",version);
                // e=e->next;
            }
            printf("\n");
        // }
        // printf("\n");
    }
}


entry *search(entry *e,int key,int version){
    // e=h.head[hash].head[];
    while(e!=NULL &&e->key!=key){
        e=(entry *)getfield(e,"next",version);
    }
    if(e==NULL) return NULL;
    else return e;
}
entry *findkey(hmap h,int key,int version){
    int hash=key%size;
    entry *e;
                for(int k=latest[hash];k>=0;k--)
            {
                if(version>=mapping[hash][k]){
                        
                     e=(h.head[hash]).head[k].head;
                     break;
                }
                   
                    
    }
    // e=h.head[hash].head[];
    while(e!=NULL &&e->key!=key){
        e=(entry *)getfield(e,"next",version);
    }
    if(e==NULL) return NULL;
    else return e;
}