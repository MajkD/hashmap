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

void gen_random_string(std::string& string, const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        string[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    string[len] = 0;
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

  hashmap->put(&std::string("fool")[0], 123);
  hashmap->put(&std::string("barsa")[0], 456);
  hashmap->put(&std::string("bazorxz")[0], 789);
  hashmap->put(&std::string("foobara")[0], 158);
  hashmap->put(&std::string("foobaradsadas")[0], 555);
  hashmap->put(&std::string("LALALAL")[0], 1337);
  hashmap->put(&std::string("foobarzorz")[0], 787878);
  hashmap->put(&std::string("lll")[0], 65);
  hashmap->put(&std::string("Test")[0], 42);
  hashmap->put(&std::string("TESTA")[0], 98);

  hashmap->printEntries();

  delete hashmap;
}

void testGet() {

  GrowingHashMap* hashmap = new GrowingHashMap(2);

  hashmap->put(&std::string("fool")[0], 123);
  hashmap->put(&std::string("barsa")[0], 456);
  hashmap->put(&std::string("bazorxz")[0], 789);
  hashmap->put(&std::string("foobara")[0], 158);
  hashmap->put(&std::string("foobaradsadas")[0], 555);
  hashmap->put(&std::string("LALALAL")[0], 1337);
  hashmap->put(&std::string("foobarzorz")[0], 787878);
  hashmap->put(&std::string("lll")[0], 65);
  hashmap->put(&std::string("Test")[0], 42);
  hashmap->put(&std::string("TESTA")[0], 98);

  hashmap->printEntries();

  printf("Get: %i\n", hashmap->get(&std::string("fool")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("barsa")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("bazorxz")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("foobara")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("foobaradsadas")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("LALALAL")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("foobarzorz")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("lll")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("Test")[0]));
  printf("Get: %i\n", hashmap->get(&std::string("TESTA")[0]));

  // should log warning
  printf("Get: %i\n", hashmap->get(&std::string("does not exist")[0]));

  delete hashmap;
}

void testMany() {
  while (true) {
    GrowingHashMap* hashmap = new GrowingHashMap(2);

    hashmap->put(&std::string("fool")[0], 123);
    hashmap->put(&std::string("barsa")[0], 456);
    hashmap->put(&std::string("bazorxz")[0], 789);
    hashmap->put(&std::string("foobara")[0], 158);
    hashmap->put(&std::string("foobaradsadas")[0], 555);
    hashmap->put(&std::string("LALALAL")[0], 1337);
    hashmap->put(&std::string("foobarzorz")[0], 787878);
    hashmap->put(&std::string("lll")[0], 65);
    hashmap->put(&std::string("Test")[0], 42);
    hashmap->put(&std::string("TESTA")[0], 98);

    delete hashmap;
  }
}

void testGrowBig() {

  GrowingHashMap* hashmap = new GrowingHashMap(2);

  for(int index = 0; index < 1000000; index++) {
    int randomValue = (rand() % 1000) + 1;
    std::string key;
    gen_random_string(key, 10);
    hashmap->put(&key[0], randomValue);
  }

  printf("map size: %i\n", hashmap->getSize());
  printf("map num entries: %i\n", hashmap->getNumEntries());
  delete hashmap;
}

void testMemory() {

  int count = 0;

  while(true) {
    GrowingHashMap* hashmap = new GrowingHashMap(2);

    for(int index = 0; index < 1000000; index++) {
      int randomValue = (rand() % 1000) + 1;
      std::string key;
      gen_random_string(key, 10);
      hashmap->put(&key[0], randomValue);
    }

    delete hashmap;

    printf("iteration: %i\n", count);
    count++;
  }
}

int main(void) 
{
  signal(SIGSEGV, traceHandler);

  // testHashfunc();
  // testPut();
  // testMany();
  // testGet();
  // testGrowBig();
  testMemory();

  // --- TODO ---
  // Implement remove
  // Determine when it whould grow
  // 'Templatize' value

  return 0;
}