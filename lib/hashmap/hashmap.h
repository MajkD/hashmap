// hashmap.h

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

  private:
    char* myKey;
    int myValue;
};

class GrowingHashMap
{
  public:
    GrowingHashMap();
    ~GrowingHashMap();

    void put(char* aKey, int aValue);

    int naive_hash(char* aKey);

  private:

    void grow_by_power_of_two();

    //Util
    void printEntries();

    HashEntry** myEntries;
    int mySize;
    int myNumEntries;

};