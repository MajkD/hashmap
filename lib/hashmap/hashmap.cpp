// hashmap.cpp

#include "hashmap.h"
#include <stdio.h>

//HashEntry

HashEntry::HashEntry(char* aKey, int aValue)
{
  myKey = aKey;
  myValue = aValue;
  myKeyIndex = 0;
}

HashEntry::~HashEntry()
{
}

char* HashEntry::getKey()
{
  return &myKey[0];
}

int HashEntry::getValue()
{
  return myValue;
}

void HashEntry::setKeyIndex(int aKeyIndex)
{
  myKeyIndex = aKeyIndex;
}

int HashEntry::getKeyIndex()
{
  return myKeyIndex;
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
    delete myEntries[index];
  }
  delete myEntries;
}

void GrowingHashMap::put(char* aKey, int aValue)
{
  if(myNumEntries >= mySize) growByPowerOfTwo();
  HashEntry* newEntry = new HashEntry(aKey, aValue);
  insert(newEntry);
}

//Insert by order of generated key
void GrowingHashMap::insert(HashEntry* aNewEntry)
{
  unsigned int hashedKey = hash(aNewEntry->getKey());
  if(myEntries[hashedKey] != NULL) {
    insertCollided(aNewEntry, myEntries[hashedKey]);
  } else {
    myEntries[hashedKey] = aNewEntry;
    myNumEntries++;
  }
}

void GrowingHashMap::insertCollided(HashEntry* anEntry, HashEntry* anExistingEntry)
{
  printf("insertCollided() - not implemented yet, skipping insertion...\n");
  // TODO
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
  // unsigned int hash = 1315423911;
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
      printf("hash entry index: %i value: %i\n", index, myEntries[index]->getValue());
    } else {
      printf("hash entry index: %i NULL\n", index);
    }
  }

  printf("mySize: %i\n", mySize);
  printf("myNumEntries: %i\n", myNumEntries);
}