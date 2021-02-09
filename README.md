# Persistent Data Structures
Implemented a library of fully and partially persistent data structures using node path copying for partial persistence and fat node for fully persistence.
Linked List, Queue, Stack, BST, Hashmap were implemented for both persistent and fully persistent data structures.

# Version Control System-
We consider the problem of version control systems which we use to store the different code versions. We have a master version of the code which we initially load in repository and this has limited write access . So the different developers fork out the code out of the repository and work on the individual components of the code independently. Each user can access different versions of the code. Here we consider the problem when we have to merge the changes made by the users in the code. Let’s consider the merging of two versions of code. Clearly this is a problem where we have a source and a target version of the code and a baseline version of the code out of which the both codes were essentially forked out.
# Approach-
Thus we can solve this problem using persistent associative maps whose values are arrays of characters or let’s say, each line is represented as an index of the sorted associative array and different versions of the array are stored using persistence. This will basically require a fully persistent associative map because a user may fork out of any version of the code. But at the time of merging we must produce a version efficiently where the conflicts are basically identified if the changes are made in the same lines of code but if the same line numbers have same versions in both the copies to be merged , we copy it directly. For Collision resolution user will be asked which copy to keep and which one to discard while producing the merged version. Thus we can make use of the associative maps to model this problem.

# Implementation Details-
An integer based hashmap which has the keyvalue as the line numbers and the value pointed by them is the actual code that is stored in that line.

`struct logbook{
int version;
char *field;
struct entry *ptr;
};`
It is the modification node which stores the field name as well as the corresponding value and time version as well. Here the field the next which is of entry type.


`struct entry{
int key;
char *value;
struct entry *next;
logbook *mods;
int modcounter;
entry *bp;
};`
It is the actual node which stores the key ,value as well as the mods array which logs all the modifications done on the node. It is the actual slot pointed to by the hashbucket which forms a chained structure of hashing.

`struct entrylist{
entry *head;
};`
It is actually the bucket which points to a node of entry type which is the head of the chained structure of the corresponding hashvalue.

`struct map{
// int hashkey;
entrylist * head;
};`
It is actually the hashmap which points to the beginning of the first bucket of the hashtable.

`struct hmap{
// int size;
map *head;
};`
It stores the location of the map which is the head of the first bucket of the hashtable.

# Operations Involved-

`int removekey(hmap *h,int key,int version)`- It simply is equivalent to removing a specific line of code from a specific point of time at saving it as the new version.

`void insert(hmap *h,int key,char *value,int version)`- It simply is equivalent to adding new line of code or modifying the existing line of code.

`void printhmap(hmap h,int n,int version)`-It simply displays how our code file looks at a specific point of time.

`entry *findkey(hmap h,int key,int version)`- It is simply used to determine whether a particular line of code exists or not.

`void merge(hmap *h,int v1,int v2)`- It is the major operation which drives this application. It takes two versions of the code and merges them directly if different lines of code exists in both the versions but asks for user input if a conflict is there.
