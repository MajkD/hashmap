// hashmap.cpp

#include "hashmap.h"

#include <stdio.h>

//HashEntry

HashEntry::HashEntry(char* aKey, int aValue)
{
  printf("created HashEntry\n");
  myValue = aValue;
}

HashEntry::~HashEntry()
{
  printf("removed HashEntry\n");
}

int HashEntry::getValue()
{
  return myValue;
}

//GrowingHashMap

GrowingHashMap::GrowingHashMap()
{
  mySize = 2;
  myNumEntries = 2;

  myEntries = new HashEntry*[mySize];
  myEntries[0] = new HashEntry(NULL, 1);
  myEntries[1] = new HashEntry(NULL, 12);
}

GrowingHashMap::~GrowingHashMap()
{
}

void GrowingHashMap::put(char* aKey, int aValue)
{
  printEntries();
  if(myNumEntries >= mySize) grow_by_power_of_two();
  printEntries();
}

int GrowingHashMap::naive_hash(char* aKey)
{
  unsigned short result = 0;
  while(*aKey != '\0')
  {
    result += *aKey;
    aKey++;
  }
  return result;
}

void GrowingHashMap::grow_by_power_of_two()
{
  int oldSize = mySize;
  mySize = mySize * mySize;

  HashEntry** newEntries = new HashEntry*[mySize];
  for(int index = 0; index < mySize; index++) {
    if (index < oldSize) {
      newEntries[index] = myEntries[index];
    } else {
      newEntries[index] = NULL;
    }
  }

  delete myEntries;
  myEntries = newEntries;
}

void GrowingHashMap::printEntries()
{
  for(int index = 0; index < mySize; index++) {
    if(myEntries[index] != NULL) {
      printf("hash entry inxed: %i value: %i\n", index, myEntries[index]->getValue());
    } else {
      printf("hash entry inxed: %i NULL\n", index);
    }
  }
}