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
    node *right;
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


// To actually print the complete list  /
// helper funtion to print the list of fields in the node 
void add_element_2(list *l,int key){
    node *temp=(node *)malloc(sizeof(node));
    temp->key=key;
    node *prev;
    temp->mods=malloc(sizeof(logbook)*(max_capacity));
    temp->modcounter=0;
    temp->next=NULL;
    int cnt;
    if(l->head==NULL){
        temp->bp=NULL;
        l->head=temp;
        updatetime();
    }
    else{
        node *it=l->head;
        int flag=0;
        
        
        while(it!=NULL){
            prev=it;
            it=getfield(it,"next",timecounter);
        }
        cnt=prev->modcounter;
        recurse(prev,temp,1);
        // if(cnt==max_capacity){
        //     recurse(prev->bp,prev,1);
        // }
        // else{
        //     temp->bp=prev;
        //     updatetime();
        //     // printf("inserting before %d",prev->key);
        //     prev->mods[cnt].version=timecounter;
        //     prev->mods[cnt].field="next";
    
        //     prev->mods[cnt].ptr=temp;
        //     prev->modcounter++;
        // }
    }
}
void delete_element_2(list *l,int key){
    node *prev=NULL;
    int keyval;
     int flag[2]={0,0};
     int cnt;
     node *it=l->head;
         node *next=NULL;
    if(it==NULL){
        printf("Nothing to delete");
    }
    else{
        
    
        while(it!=NULL){
				next=getfield(it,"next",timecounter);
                 if(it->key==key){
					recurse(prev,next,1);
                    break;
				 }
				 
				 prev=it;
				 it=next;
                 
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
    // int key;
    // int tot=0;
    // long int lkey;
    // node * next;
    //     for(int i=latest;i>=0;i--){
    //     if(t>=mapping[i]){
    //         it=(root[i])->head;
    //     break;
    //     }
    // }
    // // printf("\n  Accessing the list \n");
    // while(it!=NULL){
    //     tot=0;
    //     // CAnt directly print must search in the log for the value here
    //          int flag[3]={0,0,0}; 
    //     if(it->modcounter!=0){
    //         // printf("modcounter  u[dated\t");
    //            int cnt=it->modcounter; 
              
    //                      while(--cnt>=0){
    //                          if(t>=it->mods[cnt].version){
    //                             //  printf("found an older version\t");
    //                              if(it->mods[cnt].field=="next" && flag[0]!=1){
    //                                 //found the latest next pointer
    //                                 // printf("Found the match for next ponter \t");
    //                                 tot++;
    //                                 next=it->mods[cnt].ptr;
    //                                 flag[0]=1;

    //                              }
    //                              else if(it->mods[cnt].field=="key" && flag[1]!=1){
    //                                  tot++;
    //                                 //  printf("Found the match for key \t");
    //                                 key=it->key;
    //                                  flag[1]=1;
    //                              }
    //                              else if(it->mods[cnt].field=="lkey" && flag[2]!=1){
    //                                  tot++;
    //                                     //must modify this afterwards
    //                                 lkey=it->key;
    //                                  flag[2]=1;
    //                              }
    //                              if(tot==3) break;
    //                          }
    //                      }

                            
    //                     }
    //                         if(tot!=3){
    //                             next=flag[0]?next:(unsigned int)it->next;
    //                             key=flag[1]?key:it->key;
    //                             lkey=flag[2]?lkey:it->lkey;
    //                         }
                    
    //                 printf("%d  \t",(key));
    //                 it=(node *)next;
          
    //     }
        // else{


}
