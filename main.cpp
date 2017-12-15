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
  printf("Hashing string: '%s' ----> value: '%i'\n", &aString[0], aHashMap->naive_hash(&aString[0]));
}

int main(void) 
{
  signal(SIGSEGV, traceHandler);

  GrowingHashMap* hashmap = new GrowingHashMap();

  std::string test = "foo";
  hashmap->put(&test[0], 123);

  // test_hash(std::string("test_string"), hashmap);
  // test_hash(std::string("foobar"), hashmap);
  // test_hash(std::string("lalalalalalal"), hashmap);
  // test_hash(std::string("hello there, this is a cool key...."), hashmap);

  delete hashmap;
  return 0;
}