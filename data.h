typedef struct _hash_entry_ {
  char *string;
  char *val;

  struct _hash_entry_ *next;
} hash_entry;

typedef struct _hash_table_ {
  int size;           /* the size of the table */
  hash_entry **table; /* the table elements */
} hash_table;
