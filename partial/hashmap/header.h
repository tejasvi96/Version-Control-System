struct entry;
typedef struct entry entry;
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
void init(hmap *h,int n);
int removekey(hmap *h,int key);
void insert(hmap *h,int key,void *value,int tag);
void printhmap(hmap h,int n,int version);
entry *findkey(hmap h,int key,int version);