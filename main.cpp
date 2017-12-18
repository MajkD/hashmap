//main.cpp

#include <stdio.h>
#include <string>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib/hashmap/hashmap.h"

void traceHandler(int sig)
{
  void *array[10];
  size_t size;
  size = backtrace(array, 10);
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

void test_hash(std::string aString, GrowingHashMap* aHashMap)
{
  printf("Hashing string: '%s' ----> value: '%u'\n", &aString[0], aHashMap->hash(&aString[0]));
}

void testHashfunc() 
{
  GrowingHashMap* hashmap = new GrowingHashMap(32);

  test_hash(std::string("ab"), hashmap);
  test_hash(std::string("test_string"), hashmap);
  test_hash(std::string("foobar"), hashmap);
  test_hash(std::string("lalalalalalal"), hashmap);
  test_hash(std::string("hello there, this is a cool key...."), hashmap);
  test_hash(std::string("hello there, this is a cool key...."), hashmap);
  test_hash(std::string("hello there, this is a cool key...."), hashmap);
  test_hash(std::string("hello there, this is a cool key...."), hashmap);
  test_hash(std::string("hello there, this is a cool key....d"), hashmap);
  test_hash(std::string("hello there, this is a cool key....that it veeeeery long!!!!"), hashmap);
  test_hash(std::string("hello there, this is a cool key....that it veeeeery long!!!!"), hashmap);
  test_hash(std::string("hello there, this is a dsakey....that it adeery long!!!!"), hashmap);
  test_hash(std::string("hello there, thgf cool key....that it veeeeery long!!!!"), hashmap);
  test_hash(std::string("hello there, this is agfy....that it veeeeery long!!!!"), hashmap);

  delete hashmap;
}

void testPut()
{
  GrowingHashMap* hashmap = new GrowingHashMap(2);

  std::string fool = "fool";
  hashmap->put(&fool[0], 123);
  std::string bar = "barsa";
  hashmap->put(&bar[0], 456);
  std::string baz = "bazorxz";
  hashmap->put(&baz[0], 789);
  std::string foobara = "foobara";
  hashmap->put(&foobara[0], 158);
  std::string dsadsad = "foobaradsadas";
  hashmap->put(&dsadsad[0], 158);

  hashmap->printEntries();

  delete hashmap;
}

int main(void) 
{
  signal(SIGSEGV, traceHandler);

  // testHashfunc();
  testPut();

  // --- TODO ---
  // Impl & test collided
  // Collided deletes linked items
  //Test insert many

  return 0;
}