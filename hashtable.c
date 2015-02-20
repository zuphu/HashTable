/*********************************
AUTHOR: Anthony Guevara
Date: February 17, 2015
PURPOSE: Hash table in C
Help from: http://www.sparknotes.com/cs/searching/hashtables/section3.rhtml
*********************************/

/* INCLUDES */
/* Standard C libs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Custom structs */
#include "data.h"
/* Hash functions */
#include "hash.h"

/* CONSTANTS */
#define TABLE_SIZE 20
#define ALREADY_EXISTS 2

/* FUNCTION PROTOTYPES */
hash_table *create_hash_table(int size);
int add_string(hash_table *hashtable, char *str, char *val);
hash_entry *lookup_key(hash_table *hashtable, char *str);
int iterate_table(hash_table *hashtable);
void free_table(hash_table *hashtable);

/*
  Description: Create a hash table, add some key value pairs, iterate through hash table
*/
int main () {
  /* Create a hash table */
  hash_table *hash_table = create_hash_table(TABLE_SIZE);

  /* Ensure table was created successfully */
  if (hash_table) {
    /* Add item(s) to table: key       value */
    add_string(hash_table, "Hello"  , "World");
    add_string(hash_table, "Colour" , "Red");
    add_string(hash_table, "Candy"  , "TimTam");
    add_string(hash_table, "Answer" , "42");
    add_string(hash_table, "Animal" , "Badger");
    add_string(hash_table, "Hungry" , "true");
  
    /* Iterate through all items in hash table */
    iterate_table(hash_table);
    free_table(hash_table);
  }
  else return 0; /* Error creating table */
}

/*
  Description: Create a new hash table
  Parameters:
  int table_size: size of hash table, greater than 1
*/
hash_table *create_hash_table(int table_size) {
  hash_table *new_hash_table;
    
  if (table_size < 1) {
    fprintf(stderr, "Table size must be greater than 0.");
    return NULL; /* Invalid size for table */
  }

  /* Allocate memory for hash table structure */
  new_hash_table = (hash_table*) malloc(sizeof(hash_table));
  if (!new_hash_table) return NULL;
    
  /* Allocate memory for the hash table entries based on the size */
  new_hash_table->table = (hash_entry**) malloc(sizeof(hash_entry *) * table_size);
  if (!new_hash_table->table) return NULL;

  /* Clear the table */
  for (int i=0; i < table_size; ++i) new_hash_table->table[i] = NULL;

  /* Set table size */
  new_hash_table->size = table_size;

  return new_hash_table;
}

/*
  Description: Lookup keys in the hash table, NULL if key does not exist
  Parameters:
  int hashtable: the hash table to search for keys
  char *str: string to search for in the hashtable
*/
hash_entry *lookup_key(hash_table *hashtable, char *str)
{
  hash_entry *list;
  unsigned int hash_value = hash(TABLE_SIZE, str);

  /* Search the hashtable for a string match */
  for (list = hashtable->table[hash_value]; list != NULL; list = list->next) {
    if (strcmp(str, list->string) == 0) return list;
  }
  
  return NULL;
}

/*
  Description: Add a string to a hash table, returns -1 if unable to allocate memory, -2 if key already exists
  Parameters:
  int hashtable: the hash table to add key value pairs to
  char *str: the key to add to the hash table
  char *val: the value to add to the hash table
*/
int add_string(hash_table *hashtable, char *str, char *val) 
{
  hash_entry *new_list;
  hash_entry *current_list;
  unsigned int hashval = hash(TABLE_SIZE, str);

  /* Allocate memory for list */
  new_list = (hash_entry *) malloc(sizeof(hash_entry));
  if (new_list == NULL) return -1;

  /* Check if item exists */
  current_list = lookup_key(hashtable, str);

  /* if item exists,return */
  if (current_list != NULL) return ALREADY_EXISTS;

  /* Allocate memory into new list */
  new_list->string = strdup(str);
  new_list->val = strdup(val);
  new_list->next = hashtable->table[hashval];
  hashtable->table[hashval] = new_list;

  return 0;
}

/*
  Description: Clear memory on heap
  Parameters:
  hash_table *hashtable: the hash table to free from the heap
*/
void free_table(hash_table *hashtable) {
  int i;
  hash_entry *list, *temp;

  if (hashtable == NULL) return;

  for (i=0; i < hashtable->size; ++i) {
    list = hashtable->table[i];
    while(list != NULL) {
      temp = list;
      list = list->next;
      free(temp->string);
      free(temp->val);
      free(temp);
    }
  }

  /* Free the hashtable and the structure */
  free(hashtable->table);
  free(hashtable);
}

/*
  Description: Iterate through a hashtable printing all the key value and hash integers
  Parameters:
  int hashtable: the hash table to free from the heap
*/
int iterate_table(hash_table *hashtable) {
  hash_entry *list, *temp;
  printf("|Key\t\t|Value\t\t|Hash\t|\n");
  printf("================================================\n");
    
  for(int i=0; i < hashtable->size; i++) {
    list = hashtable->table[i];
    while(list != NULL) {
      temp = list;
      list = list->next;
      int hashval;
      hashval = hash(TABLE_SIZE, temp->string);
      printf("|%s\t\t|%s\t\t|%d\n", temp->string, temp->val, hashval);
    }
  }
  
  return 0;
}
