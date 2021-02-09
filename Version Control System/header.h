struct entry;
typedef struct entry entry;
int size;
//It is the actual log which is stored in each of the node
struct logbook{
    int version;
    char *field;
    struct entry   *ptr;
};
typedef struct logbook logbook;

struct entry{
    int key;
    char *value;
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
void menu_program(hmap *h);
void init(hmap *h,int n);
void init_samplecode(hmap *h);
int removekey(hmap *h,int key,int version);
void insert(hmap *h,int key,char *value,int version);
void printhmap(hmap h,int n,int version);
entry *findkey(hmap h,int key,int version);
void merge(hmap *h,int v1,int v2);