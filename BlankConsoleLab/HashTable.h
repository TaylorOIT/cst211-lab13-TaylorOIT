#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iterator>
#include <cctype>
#include <iostream>
using std::string;
using std::list;
using std::pair;
using std::cout;
using std::endl;

struct Book {
	string m_title;
	string m_author;
	int m_pages;
};

template <typename K, typename V>
class HashTable {
public:
	HashTable(); // default ctor
	HashTable(int value); // one param ctor
	HashTable(const HashTable<K, V>& copy); //copy constructor
	HashTable(HashTable<K, V>&& copy); // move constructor
	HashTable& operator =(const HashTable<K, V>& rhs); // copy assignment
	HashTable& operator =(HashTable<K, V>&& rhs); // move assignment
	~HashTable(); // destructor

	const int GetNxtIncr(); // getter for the nxt_incr variable
	const int GetCapacity(); // getter for the capacity variable
	const int GetBucketSize(); // getter for the BUCKETSIZE variable

	int setHash(K key); // returns the element where the list item will be inserted
	void Insert(K key, V value); // inserts the object into the bucket
	V operator [](K key); // returns the value depending on the key (operator array index)
	void Delete(K key); // deletes the list given a key
	void Purge(); // deletes the entire 
	void Traverse(V value); // traverses the hashtable to find the object value that matches the input and output title, author,
							// and pages
	void PrintHashTable(); // prints the entire hash table. For testing purposes.
private:
	list <pair<K, V> >* bucketlist;
	int BUCKETSIZE; // size of the hash table
	int nxt_incr; // used in the operator array index method.
	int capacity; // total capacity of the hash table. Used in the reHash function.
	void reHash(); // resizes the hash table depending if the load factor is equal/above 0.5
};

template<typename K, typename V>
inline HashTable<K, V>::HashTable()
{
	nxt_incr = 0;
	capacity = 0;
	this->BUCKETSIZE = 5;
	bucketlist = new list <pair<K, V>>[BUCKETSIZE];
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(int value)
{
	nxt_incr = 0;
	capacity = 0;
	this->BUCKETSIZE = value;
	bucketlist = new list <pair<K, V>>[BUCKETSIZE];
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable<K, V>& copy)
{
	if (this != &copy)
	{
		int index = 0;
		nxt_incr = copy.nxt_incr;
		capacity = copy.capacity;
		BUCKETSIZE = copy.BUCKETSIZE;
		bucketlist = new list <pair<K, V>>[BUCKETSIZE];

		for (int i = 0; i < BUCKETSIZE; i++)
		{
			for (auto list : copy.bucketlist[i])
			{
				index = setHash(list.first);
				pair<K, V> str_object_pair = make_pair(list.first, list.second);
				bucketlist[index].push_back(str_object_pair);
			}
		}
	}
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(HashTable<K, V>&& copy)
{
	if (this != &copy) {
		int index = 0;
		nxt_incr = copy.nxt_incr;
		capacity = copy.capacity;
		BUCKETSIZE = copy.BUCKETSIZE;
		bucketlist = new list <pair<K, V>>[BUCKETSIZE];

		for (int i = 0; i < BUCKETSIZE; i++)
		{
			for (auto list : copy.bucketlist[i])
			{
				index = setHash(list.first);
				pair<K, V> str_object_pair = make_pair(list.first, list.second);
				bucketlist[index].push_back(str_object_pair);
			}
		}

		copy.Purge();
	}
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable<K, V>& rhs)
{
	if (this != &rhs)
	{
		int index = 0;
		nxt_incr = rhs.nxt_incr;
		capacity = rhs.capacity;
		BUCKETSIZE = rhs.BUCKETSIZE;
		bucketlist = new list <pair<K, V>>[BUCKETSIZE];

		for (int i = 0; i < BUCKETSIZE; i++)
		{
			for (auto list : rhs.bucketlist[i])
			{
				index = setHash(list.first);
				pair<K, V> str_object_pair = make_pair(list.first, list.second);
				bucketlist[index].push_back(str_object_pair);
			}
		}
	}
	return *this;

}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(HashTable<K, V>&& rhs)
{
	if (this != &rhs)
	{
		int index = 0;
		nxt_incr = rhs.nxt_incr;
		capacity = rhs.capacity;
		BUCKETSIZE = rhs.BUCKETSIZE;
		bucketlist = new list <pair<K, V>>[BUCKETSIZE];

		for (int i = 0; i < BUCKETSIZE; i++)
		{
			for (auto list : rhs.bucketlist[i])
			{
				index = setHash(list.first);
				pair<K, V> str_object_pair = make_pair(list.first, list.second);
				bucketlist[index].push_back(str_object_pair);
			}
		}

		rhs.Purge();
	}
	return *this;
}

template<typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
	Purge();
}

template<typename K, typename V>
inline const int HashTable<K, V>::GetNxtIncr()
{
	return nxt_incr;
}

template<typename K, typename V>
inline const int HashTable<K, V>::GetCapacity()
{
	return capacity;
}

template<typename K, typename V>
inline const int HashTable<K, V>::GetBucketSize()
{
	return BUCKETSIZE;
}

template<typename K, typename V>
inline int HashTable<K, V>::setHash(K key)
{
	int hash = 0;
	int index;
	index = key.length();

	for (int i = 0; i < key.length(); i++)
		hash = hash + (int)key[i];

	index = hash % BUCKETSIZE;

	return index;
}

template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	int index = setHash(key);

	pair<K, V> str_object_pair = make_pair(key, value);

	bucketlist[index].push_back(str_object_pair);

	reHash();
}

template<typename K, typename V>
inline V HashTable<K, V>::operator[](K key)
{

	int index = setHash(key);
	for (int i = 0; i < BUCKETSIZE; i++) {
		auto begin = bucketlist[i].begin();
		auto nxt = std::next(begin, 0);

		if (bucketlist[i].size() > 1 && index == i)
		{
			nxt = std::next(begin, nxt_incr);
			++nxt_incr;
			if (nxt_incr == bucketlist[i].size())
				nxt_incr = 0;
			return (*nxt).second;
		}
		else if (index == i)
		{
			return (*nxt).second;
		}
	}
}

template<typename K, typename V>
inline void HashTable<K, V>::Delete(K key)
{
	int index = setHash(key);
	for (int i = 0; i < BUCKETSIZE; i++)
	{
		if (index == i) {
			cout << "Deleting Element: " << i;
			for (auto list : bucketlist[i]) {
				cout << " --> " << list.first << ", " << list.second.m_title;
				--capacity;
			}
			bucketlist[i].clear();
		}
	}
	cout << endl;
}

template<typename K, typename V>
inline void HashTable<K, V>::Purge()
{
	delete[] bucketlist;

	bucketlist = nullptr;
	BUCKETSIZE = 0;
	nxt_incr = 0;
	capacity = 0;
}

template<typename K, typename V>
inline void HashTable<K, V>::Traverse(V value)
{
	for (int i = 0; i < BUCKETSIZE; i++) {
		for (auto list : bucketlist[i])
			if (value.m_title == list.second.m_title)
				cout << list.second.m_title << ", " << list.second.m_author << ", " << list.second.m_pages << endl;
	}
	cout << endl;
}

template<typename K, typename V>
inline void HashTable<K, V>::PrintHashTable()
{
	if (BUCKETSIZE > 0) {
		cout << "\nHash Table:\n";
		cout << "------------------------------------\n";
		for (int i = 0; i < BUCKETSIZE; i++) {
			cout << i;
			for (auto list : bucketlist[i])
				cout << " --> " << list.first << ", " << list.second.m_title;
			cout << endl;
		}
		cout << "------------------------------------\n\n";
	}
	else
		cout << "Hash Table is empty.\n";
}

template<typename K, typename V>
inline void HashTable<K, V>::reHash()
{
	int index = 0;
	capacity = 0;
	double load_factor;

	for (int i = 0; i < BUCKETSIZE; i++)
	{
		for (auto list : bucketlist[i]) {
			++capacity;
		}
	}

	load_factor = (double)capacity / (double)BUCKETSIZE;

	if (load_factor >= 0.5)
	{
		list <pair<K, V> >* temp_bkt_list;
		temp_bkt_list = new list <pair<K, V>>[BUCKETSIZE * 2];

		for (int i = 0; i < BUCKETSIZE; i++)
		{
			for (auto list : bucketlist[i]) {
				index = setHash(list.first);
				pair<K, V> str_object_pair = make_pair(list.first, list.second);
				temp_bkt_list[index].push_back(str_object_pair);
			}
		}
		delete[] bucketlist;
		bucketlist = temp_bkt_list;
		BUCKETSIZE = BUCKETSIZE * 2;

		cout << "Load Factor is above 0.5. Table size is now: " << BUCKETSIZE << endl;
	}
}

#endif
