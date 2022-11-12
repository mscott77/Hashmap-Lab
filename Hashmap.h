// The only changes you can make to this file:
//  1) Adding additional private methods
//     You are not required to add additional private methods, but you may if you wish
//  2) You can also change the BUCKETS value to see how it changes the distribution of keys
//     10-1000 is a good range for this lab
#pragma once
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <queue>
#include "HashmapInterface.h"
#define BUCKETS 10

using namespace std;

class Hashmap: public HashmapInterface
{
private:
	/*
	 * Node struct for bucket chaining
	 * Nodes make a doubly-linked list where each buckets[i] is a head pointer
	 */
	struct Node
	{
		string key;
		int value;
		Node* next;
		Node* prev;

		// make a constructor so it's easier to assign new values upon creation
		Node(const string& user_key, const int& user_value, Node* user_next_val = NULL, Node* user_prev_val = NULL){
			key = user_key;
			value = user_value;
			next = user_next_val;
			prev = user_prev_val;
		}

	};

	/*
	 * Compare struct to be used for sorting nodes
	 * Nodes with different values should sort by greater values first
	 * Nodes with the same values should sort alphabetically (a-z) by key
	 */
	struct NodeCompare
	{
		bool operator ()(Node* a, Node* b)
		{
			if(a->value != b->value)
				return a->value < b->value;
			else
				return a->key > b->key;
		}
	};

	/*
	 * Array of linked lists used for bucket chaining
	 * Bucket index for a value should be calculated using hash function
	 * Each Node* in buckets should be initialized to NULL
	 * The first Node* placed in a bucket becomes the head pointer of a doubly-linked list
	 * There is no tail pointer
	 */
	Node* buckets[BUCKETS];

	/*
	 * Number of nodes (key/value pairs) in map
	 */
	int mapSize;

	/*
	 * Return a hash code (bucket index) for a given key
	 *  Must return a value >= 0 and < BUCKETS
	 *  This can be done by generating a hash code and returning "hashcode % BUCKETS"
	 *  Try to make your hash function so that the distribution is uniform over all buckets
	 */
	unsigned int hash(string key) const;
public:
	Hashmap();
	~Hashmap();
	void insert(string key, int value);
	bool contains(string key) const;
	int get(string key) const;
	int& operator [](string key);
	bool remove(string key);
	void clear();
	string toString() const;
	int size() const;

	/*
	 * Get string representation of all keys and related values
	 *  Sort by values in descending order
	 *   For nodes that have the same value, sort alphabetically by key in ascending order.
	 *   You should use the NodeCompare struct to sort nodes.
	 *  Because a hashmap cannot sort items, you will have to use a different data structure
	 *   to do the sorting. Use a priority queue to do a heapsort.
	 *  Each key/value pair in the map should be on its own line with no leading or trailing spaces:
	 *
	 *  key => value
	 *
	 * For example:
	 *  bob => 13
	 *  alice => 9
	 *  eve => 3
	 *  steve => 3
	 *  nancy => 1
	 *  tom => 1
	 */
	string toSortedString() const;
};
