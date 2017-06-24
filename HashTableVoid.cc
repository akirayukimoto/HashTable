
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
  const char *tmp = key;
  for (int i = 0; i < strlen(tmp); i++) {
  	sum += (i + 1) * tmp[i];
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

HashTableVoid::~HashTableVoid() {
	HashTableVoidEntry *curr;
	HashTableVoidEntry *next;
	for (int i = 0; i < TableSize; i++) {
		curr = _buckets[i];
		while (curr != NULL) {
			next = curr->_next;
			HashTableVoidEntry *temp = curr;
			curr = next;
			free((void *)temp->_key);
			delete temp;
		}
		_buckets[i] = NULL;
	}
	delete _buckets;
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
  //e->_next = _buckets[h];
  //_buckets[h] = e;
  if (_buckets[h] == NULL) {
  	e->_next = NULL;
  }
  else e->_next = _buckets[h];
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
	if (_currentEntry != NULL) {
		if (_currentEntry->_next != NULL) {
			key = _currentEntry->_next->_key;
			data = _currentEntry->_next->_data;
			_currentEntry = _currentEntry->_next;
			return true;
		}
	}
 	int i = _currentBucket + 1;
	int tableSize = 2039;
	while (_hashTable->_buckets[i] == NULL)
		i++;
	if (_hashTable->_buckets[i] != NULL && i < tableSize) {
		_currentEntry = _hashTable->_buckets[i];
		//key = _hashTable->_buckets[i]->_key;
		//data = _hashTable->_buckets[i]->_data;
		key = _currentEntry->_key;
		data = _currentEntry->_data;
		_currentBucket = i;
		return true;
	}
	return false;
}

