// hashmap.cpp

#include "hashmap.h"
#include <stdio.h>

//HashEntry

HashEntry::HashEntry(char* aKey, int aValue)
{
  myKey = aKey;
  myHashedKey = -1;
  myValue = aValue;
  myNextItem = NULL;
}

//GrowingHashMap

GrowingHashMap::GrowingHashMap(int size)
{
  if (size < 2) {
    printf("Warning GrowingHashMap size too small, defaulting to 2");
    mySize = 2;
  } else {
    mySize = size;
  }
  myNumEntries = 0;
  myEntries = new HashEntry*[mySize];
  for(int index = 0; index < mySize; index++){
    myEntries[index] = NULL;
  }
}

GrowingHashMap::~GrowingHashMap()
{
  for(int index = 0; index < mySize; index++) {
    HashEntry* current = myEntries[index];
    if (current != NULL) {
      do {
        HashEntry* next = current->myNextItem;
        delete current;
        current = next;
      } while(current != NULL);
      myEntries[index] = NULL;
    }
  }
  delete myEntries;
  myEntries = NULL;
}

void GrowingHashMap::put(char* aKey, int aValue)
{
  if(myNumEntries >= mySize) growByPowerOfTwo();
  insert(new HashEntry(aKey, aValue));
}

int GrowingHashMap::get(char* aKey)
{
  HashEntry* entry = myEntries[hash(aKey)];
  while(entry && entry->myKey != aKey) {
    entry = entry->myNextItem;
  }
  if(entry != NULL) {
    return entry->myValue;
  }
  printf("Warning: Accessed hashmap with non-existing key...\n");
  return 0;
}

//Insert by order of generated key
void GrowingHashMap::insert(HashEntry* aNewEntry)
{
  unsigned int hashedKey = hash(&aNewEntry->myKey[0]);
  // printf("-- inserting Entry: %i with key: %i -- my size: %i \n",aNewEntry->myValue, hashedKey, mySize);
  if(myEntries[hashedKey] != NULL) {
    insertCollided(aNewEntry, myEntries[hashedKey]);
  } else {
    myEntries[hashedKey] = aNewEntry;
  }
  aNewEntry->myHashedKey = hashedKey;
  myNumEntries++;
}

void GrowingHashMap::insertCollided(HashEntry* aNewEntry, HashEntry* anExistingEntry)
{
  // printf("-- insertCollided -- \n");
  HashEntry* current = anExistingEntry;
  while(current->myNextItem != NULL) {
    current = current->myNextItem;
  }
  current->myNextItem = aNewEntry;
}

unsigned int GrowingHashMap::hash(char* aKey)
{
  unsigned int length = 0;
  unsigned int hashValue = DJBHash(aKey, strlen(aKey));
  // Fit hashed value into the current size
  while(hashValue >= mySize) {
    hashValue = hashValue / 10;
  }
  return hashValue;
}

// Written by: Professor Daniel J. Bernstein
unsigned int GrowingHashMap::DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

// Bitwise hash function written by Justin Sobel
unsigned int GrowingHashMap::JSHash(const char* str, unsigned int length)
{
  unsigned int hash = 1315423911;
  unsigned int i    = 0;

  for (i = 0; i < length; ++str, ++i)
  {
    hash ^= ((hash << 5) + (*str) + (hash >> 2));
  }
  return hash;
}

void GrowingHashMap::growByPowerOfTwo()
{
  // printf("growing...\n");
  int oldSize = mySize;
  mySize = mySize * mySize;

  HashEntry** oldEntries = myEntries;
  delete myEntries;
  myEntries = new HashEntry*[mySize];
  for(int index = 0; index < mySize; index++) {
    myEntries[index] = NULL;
  }
  myNumEntries = 0;
  rehash(oldEntries, oldSize);
}

void GrowingHashMap::rehash(HashEntry** oldEntries, int oldSize)
{
  for(int index = 0; index < oldSize; index++) {
    if(oldEntries[index] != NULL) {
      HashEntry* current = oldEntries[index];
      do {
        HashEntry* next = current->myNextItem;
        current->myNextItem = NULL;
        insert(current);
        current = next;
      } while (current != NULL);
    }
  }
}

void GrowingHashMap::printEntries(HashEntry** someEntries, int size)
{
  for(int index = 0; index < size; index++) {
    if(someEntries[index] != NULL) {
      printf("\nEntry: %i", index);
      HashEntry* cur = someEntries[index];
      do {
        printf(" [Value: %i]", cur->myValue);
        cur = cur->myNextItem;
      } while(cur != NULL);
    } else {
      printf("\nEntry: %i NULL", index);
    }
  }
  printf("\n");
}

void GrowingHashMap::printEntries()
{
  for(int index = 0; index < mySize; index++) {
    if(myEntries[index] != NULL) {
      printf("\nEntry: %i", index);
      HashEntry* cur = myEntries[index];
      do {
        printf(" [Value: %i]", cur->myValue);
        cur = cur->myNextItem;
      } while(cur != NULL);
    } else {
      printf("\nEntry: %i NULL", index);
    }
  }

  printf("\n");
  printf("mySize: %i\n", mySize);
  printf("myNumEntries: %i\n", myNumEntries);
}