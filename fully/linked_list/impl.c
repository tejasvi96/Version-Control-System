#include "stdio.h"
#include "stdlib.h"

extern int timecounter;
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

// The linked list in list based implementation 
struct list{
    node *head;
};

typedef struct list list;
    list *root[10];

void updatetime(){
    
        timecounter++;
}
// Acts like a consructor for a new node 
node * new_node(int key){
    node* temp =(node*)malloc(sizeof(node));
    temp->next=NULL;
    temp->mods=malloc(sizeof(logbook)*(max_capacity));
    temp->modcounter=0;
    return temp;
}
// Modify what to do if we reached parent 
void * getfield(node *it,char *field,int version){
    int cnt=it->modcounter;
    // printf("cnt %d \t",cnt);
    void *p;
    int flag=0;
    while(--cnt>=0 ){
        if( it->mods[cnt].version>version)continue;
        if(it->mods[cnt].field==field){
            flag=1;
            if(field=="next"){
                 p=(node *)it->mods[cnt].ptr;
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
void recurse(node *parent,node *child,int field){
    node *next;
    int keyval;
			
    if(parent==NULL){
            list *l;
					
            l=(list *)malloc(sizeof(list));
            l->head=child;
            if(child!=NULL)
                child->bp=NULL;
            root[++latest]=l;
            updatetime();
            // versionobj.time=timecounter;
            mapping[latest]=timecounter;
            // printf("Root has now key as %d\n",cnode->key);
            return;
    }
    else{
        int cnt=parent->modcounter;
        if(cnt==max_capacity){
            next=(node *)getfield(parent,"next",timecounter);
            //right=(node *)getfield(parent,"right",timecounter);
            keyval=(int)getfield(parent,"key",timecounter);
            node *temp=new_node(parent->key);
            //temp->type=parent->type;
            temp->key=parent->key;
			temp->next=child;	
            temp->bp=parent->bp;
            if(child!=NULL)
            child->bp=temp;								  
            recurse(temp->bp,temp,field);												  
        }

        else{
            updatetime();
            parent->mods[cnt].field="next";
            parent->mods[cnt].version=timecounter;
            parent->mods[cnt].ptr=child;
            if(child!=NULL)
                child->bp=parent;
            (parent->modcounter)++;
        }

    }
}

void add_element_2(list *l,int key,int version){
    node *temp=(node *)malloc(sizeof(node));
    temp->key=key;
    node *prev=NULL;
    temp->mods=malloc(sizeof(logbook)*(max_capacity));
    temp->modcounter=0;
    temp->next=NULL;
    list *head;
    int cnt;
                for(int k=latest;k>=0;k--)
            {
                if(version>=mapping[k]){
                        
                     head=root[k];
                     break;
                }        
            }
    if(head->head==NULL){
        root[++latest]=head;
          updatetime();
        mapping[latest]=timecounter;
        temp->bp=NULL;
        head->head=temp;
      
    }
    else{
                if(version!=timecounter){
        root[++latest]=head;
        mapping[latest]=timecounter+1;
            }

        node *it=head->head;
        int flag=0;
        
        while(it!=NULL){
            prev=it; 
                     it=getfield(it,"next",version);
                     
            if(version!=timecounter &&it!=NULL){
                int cnt=prev->modcounter;
                prev->mods[cnt].field="next";
                prev->mods[cnt].version=timecounter+1;
                prev->mods[cnt].ptr=it;
                prev->modcounter++;
            }
        }
        recurse(prev,temp,"next");
      
    }
}
void delete_element_2(list *l,int key,int version){
    node *prev=NULL;
    int keyval;
     int flag=0;
     int cnt;
         list *head;
     for(int k=latest;k>=0;k--)
            {
                if(version>=mapping[k]){
                        
                     head=root[k];
                     break;
                }        
            }
     node *it=head->head;
         node *next=NULL;
    if(it==NULL){
        printf("Nothing to delete");
    }
    else{
      next=(node *)getfield(head->head,"next",version);
        prev=head->head;
            // if(temp==NULL) return -1;
            if(head->head->key==key){
                flag=1;
                // printf("Found a match");
                if(next==NULL){
                    // printf("root node case \n");
                    list *l;
                    l->head=next;
                    root[++latest]=l;    
            // roots[(child->key)%size][++latest[(child->key)%size]]=l;
            updatetime();
            // versionobj.time=timecounter;
            mapping[latest]=timecounter;
            // return 1;
                }
                else
                recurse(prev->bp,next,"next");
                // h->head[hash].=(h->head[hash].locn)->next;
                // return 1;
            }
            else{
                if(version!=timecounter){
                     list *l;
                    l->head=next;
        root[++latest]=head;
        mapping[latest]=timecounter+1;
            }
                node *temp=head->head;
                while(temp!=NULL){


            if(temp->key==key){
                // printf("Fodund a match");
               
                next=(node *)getfield(temp,"next",version);
                 recurse(prev,next,"next");
                //  timecounter--;
                 flag=1;
                 break;
                // prev->next=temp->next;
                // return 1;
            }
            prev=temp;
            temp=(node *)getfield(temp,"next",version);
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
            for(int k=latest;k>=0;k--)
            {
                //copying that times version
                if(version>=mapping[k]){
                    // Will have to update inside these nodes also 
                    // i.e set the next appropriately 
                     list *l=root[k];
                     node *it=l->head;
                     while(it!=NULL){
                         int cnt=it->modcounter;
                         node *next=getfield(it,"next",version);
                         it->mods[cnt].field="next";
                         it->mods[cnt].version=timecounter-1;
                         it->mods[cnt].ptr=next;
                         it->modcounter++;

                         it=next;
                     }
                     break;
                }
                   
                    
            }
            
        }

    }
    }
  
  
    }


void access_list(list *l,int t){
    // Must maintain an array of root pointers otherwise 
    node * it;

    for(int i=latest;i>=0;i--){
        if(t>=mapping[i]){
            it=(root[i])->head;
        break;
        }
    }
    while(it!=NULL){
        printf("%d\t",it->key);
        it=getfield(it,"next",t);
    }
}
