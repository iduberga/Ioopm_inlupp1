/*
Ida Bergman & Daniela Maric
IOOPM Assignment 1 Step 9
2018-10-02
 */
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define No_Buckets 17


static ioopm_entry_t *entry_create(int key, char *value, ioopm_entry_t *next)
{
  /// Set the key and value fields to the key and value
  ioopm_entry_t *new_entry = calloc(1, sizeof(ioopm_entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry;
}


ioopm_hash_table_t *ioopm_hash_table_create()
{
  
  ioopm_hash_table_t *hash=calloc(1,sizeof(ioopm_hash_table_t));
 
  return hash;
}

static ioopm_entry_t *find_previous_entry_for_key(ioopm_entry_t *first_entry, int key)
{
 ioopm_entry_t *cursor = first_entry;
 while (cursor->next != NULL)
    {
      if (cursor->next->key == key)
        {
          return cursor; /// Ends the whole function!
        } 

      cursor = cursor->next; /// Step forward to the next entry, and repeat loop
    }
  return cursor;
}

  
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry_create
  int bucket = key % No_Buckets;
  /// Search for an existing entry for a key
  ioopm_entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  ioopm_entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}

ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  ioopm_entry_t *tmp = find_previous_entry_for_key(&(ht->buckets[key %  No_Buckets]), key);
  ioopm_entry_t *next = tmp->next;

    if (next && next->value)
  {
    return (ioopm_option_t) { .defined = true, .value = next->value };
  }
else
  {
    return (ioopm_option_t) { .defined = false };
  }
}

static void entry_destroy(ioopm_entry_t *entry)
{
  free(entry);
}

void ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
 {
  int bucket=key% No_Buckets;
  ioopm_entry_t *previous = find_previous_entry_for_key(&ht->buckets[bucket], key);
  if (previous != NULL && previous->next!=NULL)
    {
      if(previous->next->next == NULL)
        {
        ioopm_entry_t *temp_prev = previous->next;
        previous->next=NULL;
        entry_destroy(temp_prev);
      
      }
      else if ( previous->next->next != NULL)
        { 
          ioopm_entry_t *temp=previous->next->next;
          entry_destroy(previous->next);
          previous->next=temp;
        }
   }
 }

static ioopm_entry_t *bucket_destroy_recursive(ioopm_entry_t *bucket)
{
  if (bucket->next == NULL)
    {
      return bucket;
    }
  else
    {
     entry_destroy(bucket_destroy_recursive(bucket->next));
     return NULL;
      
    }
  
}

/*
static ioopm_entry_t *bucket_destroy_no_tail_recursive(ioopm_entry_t *bucket)
{
  if (bucket->next == NULL)
    {
      return bucket;
    }
  else
    {
      ioopm_entry_t *newentry = bucket->next;
      entry_destroy(bucket_destroy_no_tail_recursive(newentry));
      return NULL;
    }
  
}

static void bucket_destroy_iterative(ioopm_entry_t *bucket)
{
  ioopm_entry_t *temp;
  while(bucket->next!=NULL)
    {
      temp=bucket->next;
      entry_destroy(bucket->next);
      bucket=temp;
    }
  
}
*/

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{  

  for( int i=0; i< No_Buckets; i++)
    {
      bucket_destroy_recursive(&ht->buckets[i]);
    }
  free(ht);
}

void entry_add(ioopm_entry_t *entry, int newkey)
{
  entry->key=newkey;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  int count=0;
  for(int i=0; i<No_Buckets; i++)
    {
      for(ioopm_entry_t *entry = &ht->buckets[i]; entry->next!=NULL; entry=entry->next)
        {
          count++;
        }
    }
  return count;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for(int i=0; i<No_Buckets; i++)
    {
      if(ht->buckets[i].next!=NULL)
        {
          return false;
        }
    }
    return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for(int i=0; i<No_Buckets; i++)
    {
      bucket_destroy_recursive(&ht->buckets[i]);
      ht->buckets[i].next = NULL;
    }
}

void ioopm_hash_print(ioopm_hash_table_t *ht)
{
  for(int i=0; i<No_Buckets; i++ )
    {
      if(ht->buckets[i].next!=NULL)
        {
          for(ioopm_entry_t *entry = ht->buckets[i].next; entry!=NULL; entry=entry->next)
            {
              printf("%s\n", entry->value );
            }
         }
    }
}

int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  int *keys = calloc(ioopm_hash_table_size(ht), sizeof(int));
  int *startkeys = keys;
  int countkeys = 0;
   for(int i=0; i<No_Buckets; i++ )
    {
      if(ht->buckets[i].next!=NULL)
        {
          for(ioopm_entry_t *entry = ht->buckets[i].next; entry!=NULL; entry=entry->next)
            {
              keys[countkeys]=entry->key;
              countkeys++;
            }
         }
    }
  return startkeys;
}


char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  char **values = calloc(ioopm_hash_table_size(ht)+1, sizeof(int));
  int countvalues=0;
  for(int i=0; i<No_Buckets; i++ )
    {
      if(ht->buckets[i].next!=NULL)
        {
          for(ioopm_entry_t *entry = ht->buckets[i].next; entry!=NULL; entry=entry->next)
            {
              values[countvalues]=entry->value;
              countvalues++;
            }
         }
    }
  values[countvalues]=NULL;
  return values;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate P, void *x)
 {
   int size = ioopm_hash_table_size(ht);
   int *keys = ioopm_hash_table_keys(ht);
   char **values = ioopm_hash_table_values(ht);
   bool result = true;
   if(size==0)
     {
       return false;
     }
   for (int i = 0; i < size && result; ++i)
     {
       result = result && P(keys[i], values[i], x);
     }

   free(keys);
   free(values);
   return result;
 }


bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate P, void *x)
{
   int size = ioopm_hash_table_size(ht);
   int *keys = ioopm_hash_table_keys(ht);
   char **values = ioopm_hash_table_values(ht);
   bool result = false;
   for (int i = 0; i < size && result!=true; ++i)
     {
       result = result ||  P(keys[i], values[i], x);
     }

   free(keys);
   free(values);
   return result;
 }

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function P, void *x)
{
  int size = ioopm_hash_table_size(ht);
  int *keys = ioopm_hash_table_keys(ht);
  char **values = ioopm_hash_table_values(ht);

  
  for(int i=0; i<size; i++)
    {
      P(keys[i], &values[i], x);
    }

  free(keys);
  free(values);
}


bool ioopm_hash_table_has_key(int key, char *ignore, void *x)
{
  int *searchkey = x;
  return (key == *searchkey);
}

bool ioopm_hash_table_has_value( int ignore, char *value, void *x)
{
  char *searchvalue = x;
  return (value == searchvalue);
}

void set_values(int ignore, char** value, void *x)
{
  char *setvalue=x;
  strcpy(*value, setvalue);
}

/*

int main()
{
  ioopm_hash_table_t *hash = ioopm_hash_table_create();
  ioopm_hash_table_insert(hash, 1, "kjnkjnjn");
   ioopm_hash_print(hash);
  // printf("%d\n", hash->buckets[1].key);
  //entry_add(&hash->buckets[1], 17);
  //printf("%d\n", hash->buckets[1].key);
  ioopm_hash_table_insert(hash, 18, "khejhå");
  ioopm_hash_table_insert(hash, 35, "hallå");
   ioopm_hash_print(hash);
  for(int i=0; i<3; i++)
    {
      int key = (ioopm_hash_table_keys(hash)[i]);
      printf("%d\n",key);
    }  
  ioopm_hash_table_insert(hash, 18, "hello");
  //ioopm_hash_table_remove(hash, 1);
  char* searchvalue = "hallo";
  ioopm_hash_print(hash);
  ioopm_hash_table_any(hash, ioopm_hash_table_has_value, searchvalue);

  
  ioopm_hash_table_destroy(hash);


  
  return 0;
  
  }

*/

