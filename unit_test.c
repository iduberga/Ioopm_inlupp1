/*
Ida Bergman & Daniela Maric
IOOPM Assignment 1 Step 9
2018-10-02
 */

#include "CUnit/Basic.h"
#include "hash_table.h"
#include <string.h>
#include <stdbool.h>

void test_hash_creation()
{
 ioopm_hash_table_t *s = ioopm_hash_table_create();
 CU_ASSERT_PTR_NOT_NULL(s);
 ioopm_hash_table_destroy(s);
}

void test_hash_insertion()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  ioopm_hash_table_insert(s, 1, "foobar");
  CU_ASSERT_EQUAL("foobar", s->buckets[1].next->value);

  ioopm_hash_table_destroy(s);
}

void test_hash_lookup()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  ioopm_option_t option1 = ioopm_hash_table_lookup(s,1);
  CU_ASSERT_EQUAL(NULL, option1.value);
  CU_ASSERT_EQUAL(false, option1.defined);
  
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_option_t option2  = ioopm_hash_table_lookup(s, 1);
  CU_ASSERT_EQUAL("foobar", option2.value);
  CU_ASSERT_EQUAL(true, option2.defined);

  ioopm_hash_table_destroy(s);
}

void test_hash_remove()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  ioopm_hash_table_remove(s, 1);
  CU_ASSERT_EQUAL("helloworld", s->buckets[1].next->value);
  ioopm_hash_table_remove(s, 18);
  CU_ASSERT_EQUAL(NULL, s->buckets[1].next);

  ioopm_hash_table_destroy(s);
}

void test_hash_size()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(0, ioopm_hash_table_size(s));
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  CU_ASSERT_EQUAL(2, ioopm_hash_table_size(s));
  ioopm_hash_table_destroy(s);
}

void test_hash_empty()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(true, ioopm_hash_table_is_empty(s));
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  CU_ASSERT_EQUAL(false, ioopm_hash_table_is_empty(s) );
  ioopm_hash_table_destroy(s);
}

void test_hash_clear()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(true, ioopm_hash_table_is_empty(s));
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  ioopm_hash_table_clear(s);
  CU_ASSERT_EQUAL(true, ioopm_hash_table_is_empty(s));
  ioopm_hash_table_destroy(s);
}

void test_hash_keys()
{
 
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  int *keys = ioopm_hash_table_keys(s);
  CU_ASSERT_EQUAL(0, keys[0]);
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  keys = ioopm_hash_table_keys(s);
  CU_ASSERT_EQUAL(1, keys[0]);
  CU_ASSERT_EQUAL(18, keys[1]);
 
  free(keys);
  ioopm_hash_table_destroy(s);

}

void test_hash_values()
{
 
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  char** values = ioopm_hash_table_values(s);
  CU_ASSERT_EQUAL( NULL, values[0]);
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  values = ioopm_hash_table_values(s);
  CU_ASSERT_EQUAL("foobar", values[0]);
  CU_ASSERT_EQUAL("helloworld", values[1]);
  ioopm_hash_table_destroy(s);
  free(values);
}

void test_hash_has_values()
{
 
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  
  char *searchvalue = "foobar";
  CU_ASSERT_EQUAL( false, ioopm_hash_table_any(s, ioopm_hash_table_has_value, searchvalue));
  ioopm_hash_table_insert(s, 1, searchvalue);
  ioopm_hash_table_insert(s, 18, "helloworld");
  ioopm_hash_table_insert(s, 2, "hi"); 
  CU_ASSERT_EQUAL(true, ioopm_hash_table_any(s, ioopm_hash_table_has_value, searchvalue));
  char *value = s->buckets[1].next->value;
  CU_ASSERT_EQUAL(true, ioopm_hash_table_any(s, ioopm_hash_table_has_value, value));
  ioopm_hash_table_destroy(s);
 
}

void test_hash_has_keys()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  int searchkey = 1;
  CU_ASSERT_EQUAL(false, ioopm_hash_table_any(s, ioopm_hash_table_has_key, &searchkey));
  ioopm_hash_table_insert(s, 1, "foobar");
  ioopm_hash_table_insert(s, 18, "helloworld");
  CU_ASSERT_EQUAL(true, ioopm_hash_table_any(s, ioopm_hash_table_has_key, &searchkey));
  
  ioopm_hash_table_destroy(s);
}

 void test_hash_all()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();
  
  char *searchvalue = "foobar";
  CU_ASSERT_EQUAL( false, ioopm_hash_table_all(s, ioopm_hash_table_has_value, searchvalue));
  ioopm_hash_table_insert(s, 1, searchvalue);
  ioopm_hash_table_insert(s, 18, searchvalue);
  ioopm_hash_table_insert(s, 2, searchvalue); 

  CU_ASSERT_EQUAL(true, ioopm_hash_table_all(s, ioopm_hash_table_has_value, searchvalue));
  char *value = s->buckets[1].next->value;

  CU_ASSERT_EQUAL(true, ioopm_hash_table_all(s, ioopm_hash_table_has_value, value));

  ioopm_hash_table_destroy(s);
  
}

 void test_hash_apply_to_all()
{
  ioopm_hash_table_t *s = ioopm_hash_table_create();


 
  char *setvalue = "foobar";

   char *hej=calloc(1,sizeof(char *));
   strcpy(hej, "hej");
  ioopm_hash_table_insert(s, 1, hej);

   char *hello=calloc(1,sizeof(char *));
   strcpy(hello, "hello");
  ioopm_hash_table_insert(s, 18, hello);

   char *tjenare=calloc(1,sizeof(char *));
   strcpy(tjenare, "tjenare");
  ioopm_hash_table_insert(s, 2, tjenare);
  
  ioopm_hash_table_apply_to_all(s, set_values, setvalue);
  char* foobar = ioopm_hash_table_lookup(s, 1).value;
  
  CU_ASSERT_STRING_EQUAL(setvalue, foobar);
  printf("%s\n", ioopm_hash_table_lookup(s, 1).value);
  printf("%s\n", setvalue);
  ioopm_hash_table_destroy(s);

  free(hej);
  free(hello);
  free(tjenare);
}


int main()
{
 // Initialise
 CU_initialize_registry();
 // Set up suites and tests
 CU_pSuite creation = CU_add_suite("Test creating hash table", NULL, NULL);
 CU_add_test(creation, "Creation", test_hash_creation);
 CU_add_test(creation, "Insertion", test_hash_insertion);
 CU_add_test(creation, "Lookup", test_hash_lookup);
 CU_add_test(creation, "Remove", test_hash_remove);
 CU_add_test(creation, "Size", test_hash_size);
 CU_add_test(creation, "Empty", test_hash_empty);
 CU_add_test(creation, "Clear", test_hash_clear);
 CU_add_test(creation, "Keys", test_hash_keys);
 CU_add_test(creation, "Values", test_hash_values);
 CU_add_test(creation, "Has_keys", test_hash_has_keys);
 CU_add_test(creation, "Has_values", test_hash_has_values);
 CU_add_test(creation, "All", test_hash_all);
 CU_add_test(creation, "Apply_to_all", test_hash_apply_to_all);
 

 // Actually run tests
 CU_basic_run_tests();
 // Tear down
 CU_cleanup_registry();
 return 0;
}
