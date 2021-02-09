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

void init(hmap *h,int n);
int removekey(hmap *h,int key,int version);
void insert(hmap *h,int key,char *value,int version,int type);
void printhmap(hmap h,int n,int version);
entry *findkey(hmap h,int key,int version);