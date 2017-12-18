// hashmap.h

#include <string>

// TEST IMPL HASHMAP (WIP)

#ifndef HASH_MAP_H
#define HASH_MAP_H
#endif

class HashEntry
{
  public:
    HashEntry(char* aKey, int aValue);
    ~HashEntry();

    int getValue();
    char* getKey();
    void setKeyIndex(int aKeyIndex);
    int getKeyIndex();

  private:
    std::string myKey;
    int myValue;
    int myKeyIndex;
};

class GrowingHashMap
{
  public:
    GrowingHashMap(int size);
    ~GrowingHashMap();

    void put(char* aKey, int aValue);

    unsigned int hash(char* aKey);

    //Debug
    void printEntries();
    HashEntry** getEntries() { return myEntries; }

  private:

    void growByPowerOfTwo();
    void insert(HashEntry* anEntry);
    void insertCollided(HashEntry* anEntry, HashEntry* anExistingEntry);

    // http://www.partow.net/programming/hashfunctions/
    unsigned int JSHash(const char* str, unsigned int length);
    unsigned int DJBHash(const char* str, unsigned int length);

    HashEntry** myEntries;
    int mySize;
    int myNumEntries;

};