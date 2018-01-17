// hashmap.h

#include <string>

#ifndef HASH_MAP_H
#define HASH_MAP_H
#endif

struct HashEntry
{
    HashEntry(char* aKey, int aValue);
    ~HashEntry() {};

    std::string myKey;
    int myValue;
    int myHashedKey;
    HashEntry* myNextItem;
};

class GrowingHashMap
{
  public:
    GrowingHashMap(int size);
    ~GrowingHashMap();

    void put(char* aKey, int aValue);
    int get(char* aKey);

    //Debug
    unsigned int hash(char* aKey);
    void printEntries();
    void printEntries(HashEntry** someEntries, int size);
    HashEntry** getEntries() { return myEntries; }
    int getSize() { return mySize; }
    int getNumEntries() { return myNumEntries; }

  private:

    void growByPowerOfTwo();
    void insert(HashEntry* aNewEntry);
    void insertCollided(HashEntry* aNewEntry, HashEntry* anExistingEntry);
    void rehash(HashEntry** oldEntries, int oldSize);

    // http://www.partow.net/programming/hashfunctions/
    unsigned int JSHash(const char* str, unsigned int length);
    unsigned int DJBHash(const char* str, unsigned int length);

    HashEntry** myEntries;
    int mySize;
    int myNumEntries;

};