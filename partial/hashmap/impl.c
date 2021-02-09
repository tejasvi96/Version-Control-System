#include "stdio.h"
#include "stdlib.h"
int *latest;
extern int timecounter;
void updatetime(){
    timecounter++;
}
int max_capacity;
int **mapping;
struct entry;
typedef struct entry entry;
extern int size;
//It is the actual log which is stored in each of the node
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
void init(hmap *h,int n){
   
    timecounter=0;
    max_capacity=2;
    size=n;		
    int len;
    len = sizeof(int *) * n + sizeof(int) * n * n; 
    mapping = (int **)malloc(sizeof(int*)*n); 			  
    latest=(int *)malloc(sizeof(int)*n);
    // mapping=(int *)malloc(n*n*sizeof(int));

    h->head=malloc(sizeof(map*)*n);
    for(int i=0;i<n;i++){
        h->head[i].head=malloc(sizeof(entrylist *)*n);
        for(int j=0;j<n;j++)
            h->head[i].head[j].head=NULL;
    }	 
    for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++)
        *(mapping+i)=(int*)malloc(sizeof(int)*n);
			
    }
//     roots=(map*)malloc(sizeof(map*)*n);
									  
	for(int i=0;i<n;i++){
        latest[i]=0;
        mapping[i][0]=0;
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
                // printf("found a left node");
                 p=(entry *)it->mods[cnt].ptr;
            }
           
            // else
            // {
            //     // printf("Found a right node");
            //     p=(node *)it->mods[cnt].value.ptr;
            // }
            break;
        }
        // cnt--;
    }
    if (flag==1) return p;
    else {
        if(field=="key"){
            return(it->key);
        }
        else if(field=="next")
        {
            return (it->next);
        }
        // else
        // {
        //     return (it->right);
        // }
        
    };
}

// latest for each must be tracked
void recurse(hmap *h,entry *parent,entry *child,char *field){
    entry *next;
    int keyval;
    if(parent==NULL){
            // map *l;
            // l=malloc(sizeof(map));
            // l->head=child;
            // entry *e=malloc(sizeof(entry));
            int hash=(child->key)%size;
            printf("reached a root\n");
            if(child!=NULL){
            child->bp=NULL;
            int hash=(child->key)%size;
            }

            h->head[hash].head[++latest[hash]].head=child;    
            // roots[(child->key)%size][++latest[(child->key)%size]]=l;
            updatetime();
            // versionobj.time=timecounter;
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
            entry *temp=(entry*)malloc(sizeof(entry));
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


 valueobj get(hmap *h,int key){
    int hash=key%size;
    if(h->head[hash].head[latest[hash]].head==NULL){
        printf("not found\n");
        valueobj v;
        v.tag=-1;
        return v;
    }
        
        entry *temp=h->head[hash].head[latest[hash]].head;
        while(temp!=NULL){
            if(temp->key==key){
                return temp->value;
            }
            temp=temp->next;
        }    
        
}
int removekey(hmap *h,int key){
    int hash=key%size;
        if(h->head[hash].head[latest[hash]].head==NULL)
        return -1;
            entry *temp=h->head[hash].head[latest[hash]].head;
            entry *next=(entry *)getfield(temp,"next",timecounter);
            entry *prev=temp;
            // if(temp==NULL) return -1;
            if(temp->key==key){
                // printf("Found a match");
                if(next==NULL){
                    // printf("root node case \n");
                    h->head[hash].head[++latest[hash]].head=next;    
            // roots[(child->key)%size][++latest[(child->key)%size]]=l;
            updatetime();
            // versionobj.time=timecounter;
            mapping[(temp->key)%size][latest[(temp->key)%size]]=timecounter;
            return 1;
                }
                else
                recurse(h,prev->bp,next,"next");
                // h->head[hash].=(h->head[hash].locn)->next;
                return 1;
            }
        while(temp!=NULL){
            
            if(temp->key==key){
                // printf("Fodund a match");
               
                next=(entry *)getfield(temp,"next",timecounter);
                 recurse(h,prev,next,"next");
                // prev->next=temp->next;
                return 1;
            }
            prev=temp;
            temp=(entry *)getfield(temp,"next",timecounter);
        } 
        return -1;   
}
void insert(hmap *h,int key,void *value,int tag){
    // WE must work on the latest head of the current key 
    int hash=key%size;
    entry *t=(entry *)malloc(sizeof(entry));
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
    t->key=key;
    t->value=v1;
    t->bp=NULL;
    // updatetime();
    t->modcounter=0;
    t->mods=malloc(sizeof(logbook)*max_capacity);
    t->next=NULL;
    
    if(h->head[hash].head[latest[hash]].head==NULL){
        // map *temp=malloc(sizeof(map));
        // temp->hashkey=hash;
        // temp->locn=t;
        // h->head[hash].hashkey=hash;
         updatetime();
        h->head[hash].head[++latest[hash]].head=t;
        mapping[hash][latest[hash]]=timecounter;
        // roots[hash][latest[hash]]=
    
        // latest[hash]++;
        
    }
    else{
        // Will need to check if the keys of the hashmap are equal 

        entry *temp=h->head[hash].head[latest[hash]].head;
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
                 recurse(h,prev,t,"next");
                flag=1;
                break;
            }
            prev=temp;


            temp=getfield(temp,"next",timecounter);
        }
        if(flag==0){
            // printf("key not present already");
            recurse(h,prev,t,"next");
        }
        // prev->next=t;
    }
    
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
entry *search(entry *e,int key,int version){
    // e=h.head[hash].head[];
    while(e!=NULL &&e->key!=key){
        e=(entry *)getfield(e,"next",version);
    }
    if(e==NULL) return NULL;
    else return e;
}