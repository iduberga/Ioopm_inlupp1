/*
Ida Bergman & Daniela Maric
IOOPM Assignment 1 Step 9
2018-10-02
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define No_Buckets 17 // amount of buckets in the hash table

typedef struct entry ioopm_entry_t; // new more specific name for struct  entry
typedef struct hash_table ioopm_hash_table_t; // more specific name for hash_table
typedef struct option ioopm_option_t; // new more specific name for struct option
typedef bool(*ioopm_predicate)(int key, char *value, void *extra);
typedef void(*ioopm_apply_function)(int key, char **value, void *extra);


struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  ioopm_entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
 ioopm_entry_t buckets[No_Buckets];  // creates a hash structure with buckets
};


struct option
{
  bool defined;     // whether there is a key is not
  char *value;      // holds the value
};

//brief: creates an empty hash table
//param: void
//return: an empty hash table
ioopm_hash_table_t *ioopm_hash_table_create();

//brief: insert a value and a key into a hash table
//param: a key and a value that is inserted into a hash table
//return: void
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

//brief: look for a value with a certain key
//param: a key and a hash table to look for the key in
//return: an option t, where the bool is whether there is a key or not, and the value at the key
ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

//brief: remove an entry with a certain key from the hash table
//param: a hash table and the key of the entry that is going to be removed
//return: void
void ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);

//brief: destroy the entire hash table
//param: the hash table you want to remove
//return: void
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

int ioopm_hash_table_size(ioopm_hash_table_t *ht);

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

void ioopm_hash_print(ioopm_hash_table_t *ht);

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

char **ioopm_hash_table_values(ioopm_hash_table_t *ht);

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x);

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x);

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function P, void *x);

bool ioopm_hash_table_has_value(int key, char *value, void *x);

bool ioopm_hash_table_has_key(int key, char *value, void *x);

void set_values(int ignore, char** value, void *x);
