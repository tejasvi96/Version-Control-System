#include "stdio.h"
#include "stdlib.h"
extern int timecounter;
void updatetime(){
    timecounter++;
}
extern int max_capacity;
extern int latest;
    int mapping[10];
    struct node;
//Actually the value that can be variable sized based on the diffetent types that are modified
union valueobj{
    int key;
    struct node    *ptr;
};
typedef union valueobj valueobj;

// valueobj updatevalue(int type,void *)

//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
    valueobj value;
};
typedef struct logbook logbook;

// It is the fat node which will store the data and values for us 
struct node{
    int key;
    struct node * left;
    struct node * right;
    logbook *mods;
    int modcounter;
    struct node *bp;
    int type;
};
typedef struct node node;

// type =0 root, type=1 left, type=2 right
struct treelist {
    node* head;
};
typedef struct treelist treelist;

treelist *roots[10];
node * new_node(int key){
    node *temp=(node*)malloc(sizeof(node));
    temp->left=NULL;
    temp->right=NULL;
    temp->key=key;
    temp->mods=(logbook *)malloc(sizeof(logbook)*(max_capacity));
    temp->modcounter=0;
    temp->bp=NULL;
    return temp;
}
void * getfield(node *it,char *field,int version){
    int cnt=it->modcounter;
    // printf("cnt %d \t",cnt);
    void *p;
    int flag=0;
    while(--cnt>=0 ){
        if( it->mods[cnt].version>version)continue;
        if(it->mods[cnt].field==field){
            flag=1;
            if(field=="key"){
                int val=it->mods[cnt].value.key;
                p=&val;
            }
                // p=
            else if(field=="left"){
                // printf("found a left node");
                 p=(node *)it->mods[cnt].value.ptr;
            }
           
            else
            {
                // printf("Found a right node");
                p=(node *)it->mods[cnt].value.ptr;
            }
            break;
        }
        // cnt--;
    }
    if (flag==1) return p;
    else {
        if(field=="key"){
            return(it->key);
        }
        else if(field=="left")
        {
            return (it->left);
        }
        else
        {
            return (it->right);
        }
        
    };
}

void recurse(node *parent,node *child,char *field){
    node *left;
    node *right;
    int keyval;
    if(parent==NULL){
            treelist *l;
            l=(treelist *)malloc(sizeof(treelist));
            l->head=child;
            if(child!=NULL)
                child->bp=NULL;
            roots[++latest]=l;
            updatetime();
            // versionobj.time=timecounter;
            mapping[latest]=timecounter;
            // printf("Root has now key as %d\n",cnode->key);
            return;
    }
    else{
        int cnt=parent->modcounter;
        if(cnt==max_capacity){
            left=(node *)getfield(parent,"left",timecounter);
            right=(node *)getfield(parent,"right",timecounter);
            keyval=(int)getfield(parent,"key",timecounter);
            node *temp=new_node(parent->key);
            temp->type=parent->type;
            if(field=="right"){
                temp->right=child;
                temp->left=left;
            }
            else if(field=="left"){
                temp->left=child;
                temp->right=right;
            }
            else{
                // printf("key to be modified");
                temp->key=child->key;
                temp->left=left;
                temp->right=right;
            }
            temp->bp=parent->bp;
            if(child!=NULL && field!="key")
            child->bp=temp;
            if(temp->type==1)field="left";
            else if(temp->type==2)field="right";
            // else{
            //     // rootnode
            //     printf("reached root");
            // }
            recurse(temp->bp,temp,field);
        }
        else{
            updatetime();
            parent->mods[cnt].field=field;
            parent->mods[cnt].version=timecounter;
            if(field=="key")
                parent->mods[cnt].value.key=child->key;
            parent->mods[cnt].value.ptr=child;
            if(child!=NULL)
                child->bp=parent;
            (parent->modcounter)++;
        }


    }
}
void insert(node *root,int key){
    if(root!=NULL){
        if(root->key>key){
            node *left=(node*)getfield(root,"left",timecounter);
            if(left==NULL){
                // updatetime();
                node *temp=new_node(key);
                temp->type=1;
                if(root->modcounter==max_capacity){
                    recurse(root,temp,"left");
                    // printf("node is full\n");
                }
                else{
                    updatetime();
                temp->type=1;
                temp->bp=root;
                int cnt=root->modcounter;
                root->mods[cnt].field="left";
                root->mods[cnt].value.ptr=temp;
                root->mods[cnt].version=timecounter;
                (root->modcounter)++;
                // root->left=NULL;
               
                }
                  return;
            }
            else{
                insert(left,key);
                // return;
            }
           
        }
        else{
                
                node *right=(node*)getfield(root,"right",timecounter);
                if(right==NULL ){
                    node *temp=new_node(key);
                    temp->type=2;
                    if(root->modcounter==max_capacity) {
                        // printf("node is full\n");
                        recurse(root,temp,"right");
                    }
                    else{
                    node *temp=new_node(key);
                    updatetime();
                    temp->bp=root;
                    temp->type=2;
                int cnt=root->modcounter;
                root->mods[cnt].field="right";
                root->mods[cnt].value.ptr=temp;
                root->mods[cnt].version=timecounter;
                (root->modcounter)++;
                }

                return;
                // root->right=NULL;
            }
            else{
                insert(right,key);
                // right->key=100;
                // return;
            }
        }
    }
}


void inorder(node *root,int version){
    // was working here 
    // need to somehow send the latest root first time only 
    // And only that should be sent 

    if(root!=NULL){
        inorder((node*)getfield(root,"left",version),version);
        printf("%d\t",(int)getfield(root,"key",version),version);
        inorder((node*)getfield(root,"right",version),version);
    }

}
void preorder(node *root,int version){
    if(root!=NULL){
        
        printf("%d\t",root->key);
        preorder((node*)getfield(root,"left",version),version);
        preorder((node*)getfield(root,"right",version),version);

    }
}
node *getroot(int version){
        node *it;
        for(int i=latest;i>=0;i--){
        if(version>=mapping[i]){
            it=roots[i]->head;
        break;
        }
    }
    return it;
}

node *search_time(node *root,int key,int version){

    // root is evaluated first
    if(root==NULL || root->key==key) return root;
    if(root->key>key){
               
        search_time((node*)getfield(root,"left",version),key,version);
    }
    else if(root->key<key) 
        search_time((node*)getfield(root,"right",version),key,version);

}
node *successor_time(node *root,int key,int version){
    node *it=search_time(root,key,version);
    if(it==NULL) return NULL;
    node *right=(node*)getfield(it,"right",version);
    if(right==NULL) return NULL;
    // printf("how\n");
    it=right;
    node *prev;
    while(it!=NULL){
        prev=it;
        it=(node*)getfield(it,"left",version);
    }
    return prev;
}
node *predecessor_time(node *root,int key,int version){
       
    node *it=search_time(root,key,version);

    if(it==NULL)return NULL;
    node * left=(node*)getfield(it,"left",version);
    if(left==NULL)return NULL;
    it=left;
    node *prev;
    while(it!=NULL){
        prev=it;
        it=(node*)getfield(it,"right",version);
    }
    return prev;
}
void handle_delete(node *root,node *succ);
node* delete_time(node *root,int key){
    if(root==NULL) return NULL;
    if(root->key>key){
        node *left=(node *)getfield(root,"left",timecounter);
        if(left==NULL) return NULL;
        delete_time(left,key);
        // root->left=delete(root->left,key);
    }
    else if(root->key<key){
        node *right=(node *)getfield(root,"right",timecounter);
        if(right==NULL) return NULL;
        delete_time(right,key);
        // root->right=delete(root->right,key);
    }
    else{
        // Value is equal found the key
         node *right=(node *)getfield(root,"right",timecounter);
         node *left=(node *)getfield(root,"left",timecounter);
        printf("here\n");
    if(left==NULL && right==NULL){
        // root=NULL;
        if (root->type==0){
            treelist *t=(treelist *)malloc(sizeof(treelist));
            t->head=NULL;
            roots[++latest]=t;
            updatetime();
            // versionobj.time=timecounter;
            mapping[latest]=timecounter;
            printf("root is getting deletedd\n");
        }
        else if(root->type==1){
            // left child
            recurse(root->bp,NULL,"left");
        }
        else if(root->type==2){
            printf("right child\n");
             recurse(root->bp,NULL,"right");
        }
        // free(root);
        printf("a leaf node\n");
       
    }
    else if(left==NULL){
        char *field;
        if(root->type==1)
            field="left";
        else if(root->type==2)
        field="right";
        else{
            printf("root");
        }    
        recurse(root->bp,right,field);
    }
    else if(right==NULL){
        char *field;
        if(root->type==1)
            field="left";
        else if(root->type==2)
        field="right";
        else{
            printf("root");
        }    
        recurse(root->bp,left,field);
    }
    else{
        printf("both children present\n");
        node *temp=successor_time(getroot(timecounter),key,timecounter);
        if(temp!=NULL) {
            int value=temp->key;
            printf("Found a successor %d\n",value);
            handle_delete(root,temp);
            return root;
         }
        }
    }
    // Must return this recursively
    return root;
}

void handle_delete(node *root,node *succ){
    node *left=getfield(root,"left",timecounter);
    node *right=getfield(root,"right",timecounter);
    node *it=new_node(succ->key);
    it->bp=root->bp;
    it->type=root->type;
    it->left=left;
    it->right=right;
    left->bp=it;
    right->bp=it;
    char *field;
    if(it->type==1){
        field="left";
    }
    else if(it->type==2) field="right";
    recurse(it->bp,it,field);
    timecounter--;
    delete_time(right,succ->key);
}