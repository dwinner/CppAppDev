// Records.h
// Defines the types Record_t, IndexEntry_t:

typedef struct { long key;
                 char name[32];
                 /* ... other fields in the record ... */ } Record_t;

typedef struct { long key, pos; } IndexEntry_t;

Record_t *setNewName( FILE *fp, long key, const char *newname);

