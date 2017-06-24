
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
  //int len = strlen(key);
  //for (int i = 0; i < len; i++) {
  //	sum += (i + 1) * key[i];
  //}
  while (*key != '\0') {
  	sum++;
	key++;
  }
  return sum % TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
  // Add implementation here
  _buckets = new HashTableVoidEntry*[TableSize];
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
  HashTableVoidEntry *entry = _buckets[h];
  while (entry != NULL) {
  	if (strcmp(key, entry->_key) == 0) {
		entry->_data = data;
		return true;
	}
  	entry = entry->_next;
  }
  HashTableVoidEntry *e = new HashTableVoidEntry();
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
  int h = hash(key);
  HashTableVoidEntry *entry = _buckets[h];
  while (entry != NULL) {
  	if (strcmp(key, entry->_key) == 0) {
		*data = entry->_data;
		return true;
	}
	entry = entry->_next;
  }
  return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
  // Add implementation here
  int h = hash(key);
  HashTableVoidEntry *entry = _buckets[h];
  HashTableVoidEntry *prev = NULL;
  while (entry != NULL) {
  	if (strcmp(key, entry->_key) == 0) {
		if (prev != NULL) prev = entry->_next;
		else _buckets[h] = entry->_next;
		free((void *)entry->_key);
		delete entry;
		return true;
	}
	prev = entry;
	entry = entry->_next;
  }
  return false;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
  // Add implementation here
	_currentBucket = 0;
	_currentEntry = NULL;
	_hashTable = hashTable;
  
}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)
{
  // Add implementation here
 	int i = _currentBucket;
	int tableSize = 2039;
	i++;
	while (_hashTable->_buckets[i] == NULL)
		i++;
	if (_hashTable->_buckets[i] != NULL && i < tableSize) {
		_currentEntry = _hashTable->_buckets[i];
		key = _hashTable->_buckets[i]->_key;
		data = _hashTable->_buckets[i]->_data;
		_currentBucket = i;
		return true;
	}
	else return false;
}

