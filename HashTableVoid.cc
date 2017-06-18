
//
// CS251
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
  // Add implementation here
  int sum = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
  	sum += (i + 1) * key[i];
  }
  return sum % TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
  // Add implementation here
  for (int i = 0; i < TableSize; i++) {
  	_buckets[i] = NULL;
  }
}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data)
{
  // Add implementation here
  int h = hash(key);
  HashTableVoidEntry *e = _buckets[h];
  while (e != NULL) {
  	if (strcmp(key, e->_key)) {
		e->_data = data;
		return true;
	}
  	e = e->_next;
  }
  e = new HashTableVoidEntry();
  e->_key = strdup(key);
  e->_data = data;
  e->_next = _buckets[h];
  _buckets[h] = e;
  return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
  // Add implementation here
  return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
  // Add implementation here
  return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
  // Add implementation here

}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)
{
  // Add implementation here
  return false;
}

