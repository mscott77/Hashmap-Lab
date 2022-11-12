#include <stdexcept>
#include <sstream>
#include <iostream>
#include <queue>

#include "Hashmap.h"

using namespace std;

//-----------------------------------------------------------CONSTRUCTOR-------------------------------------------------------------
Hashmap :: Hashmap()
{
    //initialize each Node object pointer in the buckets array to be NULL
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        buckets[i] = NULL;
        mapSize = 0;
    }

}
//-------------------------------------------------------------DESTRUCTOR-----------------------------------------------------------
Hashmap :: ~Hashmap()
{

}
//------------------------------------------------------------HASH FUNCTION--------------------------------
unsigned int Hashmap :: hash(string key) const
{
    int count = 0;
    for(int i = 0; i < key.size() ; i++)
    {
        count += key[i];
    }
    return (count % BUCKETS);
}
//---------------------------------------------------------------INSERT---------------------------------------------------------
void Hashmap :: insert(string key, int value)
{
    cout << "In insert() \n";
    // first, generate the hash index for the given key
    int hashIndex = hash(key);
    cout << "hash index for the key " << key << " is " << hashIndex << endl;

    // then, search all buckets for a duplicate key
    cout << "searching the array/lists for duplicate keys... \n";
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // do stuff to the current link 
            if ((current->key) == key) // if there is an item with matching key, just reassign that keys value to the new value
            {
                cout << "duplicate key found, reassigning duplicate key's value to new value \n";
                current->value = value; // reassign the duplicate key's value to the new value 
                return; // no new item were added, exit the function
            }
            // then increment the 'counter'
            current = current->next;
        }
    }

    // if it was not a duplicate, insert a new node in the correct bucket
    // if it is the first item in the bucket just replace the buckets[hashIndex] Node, no need to worry about chaning pointers around
    if (buckets[hashIndex] == NULL)
    {
        buckets[hashIndex] = new Node(key,value,NULL,NULL); // (the pointer is already made, just assign it memory on heap with new
    }
    //FIXME: have  case for when there's already something in the bucket



}
//------------------------------------------------------------------------------------------------------------------------
bool Hashmap :: contains(string key) const
{
    return false;
}
//------------------------------------------------------------------------------------------------------------------------
int Hashmap :: get(string key) const
{
    return 666;
}
//------------------------------------------------------------------------------------------------------------------------
bool Hashmap :: remove(string key)
{
    return false;
}
//------------------------------------------------------------------------------------------------------------------------
void Hashmap :: clear()
{

}
//-------------------------------------------------------TO STRING-----------------------------------------------------------------
string Hashmap :: toString() const
{
    return "returning toString \n";
}
//------------------------------------------------------------------------------------------------------------------------
int Hashmap :: size() const
{
    return 666;
}
//------------------------------------------------------------------------------------------------------------------------
int& Hashmap :: operator [](string key)
{
}
