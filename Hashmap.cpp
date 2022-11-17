#include <stdexcept>
#include <sstream>
#include <iostream>
#include <queue>
#include <utility>
#include <stack>


#include "Hashmap.h"

using namespace std;

//-----------------------------------------------------------CONSTRUCTOR--------------------------------------------------------(done)
Hashmap :: Hashmap()
{
    //initialize each Node object pointer in the buckets array to be NULL
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        buckets[i] = NULL;
        mapSize = 0;
    }

}
//-------------------------------------------------------------DESTRUCTOR------------------------------------------------------(done)
Hashmap :: ~Hashmap()
{
    cout << "deleting all elements in the HashMap \n";
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // you'll be deletinig the head of the list, so save the address of the next guy in the list so you don't lose him!
            Node* next2Del = current->next;
            //delete the current Node
            delete current;
            // reassign current to be the next node that you saved earlier,
            current = next2Del;
        }
    }
}
//------------------------------------------------------------HASH FUNCTION----------------------------------------------------(done)
unsigned int Hashmap :: hash(string key) const
{
    int count = 0;
    for(int i = 0; i < key.size() ; i++)
    {
        count += key[i];
    }
    return (count % BUCKETS);
}
//---------------------------------------------------------------INSERT---------------------------------------------------------(done)
void Hashmap :: insert(string key, int value)
{
    cout << "In insert() \n";
    // first, generate the hash index for the given key
    int hashIndex = hash(key);
    cout << "hash index for the key " << key << " is " << hashIndex << endl;
    // dude, why did you find the hash index, but then not use it to go to the correct bucket? look at the commentary for the contains function!

    // then, search all buckets for a duplicate key // NO! only search the one bucket that you found with your hash function!
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
        buckets[hashIndex] = new Node(key,value,NULL,NULL); // (the pointer is already made, just assign it memory on heap with new)
        mapSize++;
    }
    //FIXME: have  case for when there's already something in the bucket
    else
    {
        Node* current = buckets[hashIndex]; 
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // once you find the last element, add a new node after it and return from the function
            if (current->next == NULL) // if the next item is NULL, you're on the last item
            {
                Node* newNode = new Node(key,value,NULL,current);
                current->next = newNode;
                mapSize++;
                return;
            }

            // then increment the 'counter'
            current = current->next;
        }
    }


}
//------------------------------------------------------------CONTAINS------------------------------------------------------------(done)
bool Hashmap :: contains(string key) const
{
    // I just realized this is reduntant, why loop through all the each bucket 
    // when you can just go directly to the correct bucket using the key and hashmap function??
    // if the key you're looking for does or does not exist, there's only bucket it would go in anyways so why loop through all the buckets...
    // I'm too lazy to fix it though and it technically works so here's to laziness. *makes a toast*
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // do stuff to the current link 
            if ((current->key) == key) // if there is an item with matching key, just reassign that keys value to the new value
            {
                return true;
            }
            // then increment the 'counter'
            current = current->next;
        }
    }
    return false;
}
//-----------------------------------------------------------GET-------------------------------------------------------------(done)
int Hashmap :: get(string key) const
{
    int hashIndex = hash(key);

    cout << "In get(), the key you entered is in bucket [" << hashIndex << "] \n searching through the bucket for your item \n";

    Node* current = buckets[hashIndex];
    while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
    {
        // do stuff to the current link 
        if ((current->key) == key) // if there is an item with matching key, just reassign that keys value to the new value
        {
            cout << "your key was found! \n";
            return current->value;
        }
        // then increment the 'counter'
        current = current->next;
    }

    cout << "your key was not found :/ \n";
    throw invalid_argument("key does not yet exist in the HashMap");

}
//-----------------------------------------------------------REMOVE-------------------------------------------------------------(done)
bool Hashmap :: remove(string key)
{
    int hashIndex = hash(key);

    cout << "In remove(), \nthe key " << key <<  " should be in bucket [" << hashIndex << "] \n searching through the bucket for your item \n";

    Node* current = buckets[hashIndex];
    while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
    {
        // do stuff to the current link 
        if ((current->key) == key) // if there is an item with matching key, just reassign that keys value to the new value
        {
            cout << "valid key, the associated Node is being removed\n";

            // special case if it's the ONLY item in the list
            if ( (current == buckets[hashIndex]) && (current->next == NULL))
            {
                cout << "the item to be removed was the ONLY item in the list! \n";
                buckets[hashIndex] = current->next;
                delete current;
                mapSize--;
                //buckets[hashIndex] == NULL;
                return true;
            }
            // special case if it's the first Node in the list (to avoid segFault)
            else if (current == buckets[hashIndex])
            {
                cout << "the item to be removed was the first in the list! \n";
                buckets[hashIndex] = current->next; // just point the buckets[hashIndex] to the next item instead
                current->next->prev = NULL;
                delete current;
                current = NULL;
                mapSize--;
                return true;
            }
            // special case if it's the last Node in the list
            else if(current->next == NULL)
            {
                cout << "the item to be removed was the last in the list! \n ";
                current->prev->next = NULL;
                delete current;
                current = NULL;
                mapSize--;
                return true;
            }
            // case if it's not the first or last node
            else
            {
                cout << "the item to be removed was not the first or last item but somewhere in the middle \n";
                current->prev->next = current->next; // point to previous Node's 'next' pointer to the next Node
                current->next->prev = current->prev; // point the next Node's 'prev' pointer to the previous Node
                delete current;
                current = NULL;
                mapSize--;
                return true;
            }
        }
        // then increment the 'counter'
        current = current->next;
    }
    cout << "there is no item associated with the given key, no Nodes were deleted\n";
    return false;
}
//-------------------------------------------------------CLEAR-----------------------------------------------------------------(done)
void Hashmap :: clear()
{
    cout << "deleting all elements in the HashMap \n";
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // you'll be deletinig the head of the list, so save the address of the next guy in the list so you don't lose him!
            Node* next2Del = current->next;
            //delete the current Node
            delete current;
            // reassign current to be the next node that you saved earlier,
            current = next2Del;
        }
        buckets[i] = NULL;
    }
    mapSize = 0;
}
//-------------------------------------------------------TO STRING-----------------------------------------------------------------(done)
string Hashmap :: toString() const
{
    cout << "in toString, printing the current HashMap \n";
    stringstream ss;

    for (int i = 0 ; i < BUCKETS ; i++)
    {
        // print out the bucket number
        ss << "[" << i << "]"; 
        // print contents, if there are any
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // do stuff to the current link 
            ss << " " << current->key << " => " << current->value;
            if (current->next != NULL)
            {
                ss << ", ";
            }
            // then increment the 'counter'
            current = current->next;
        }
        //end with a newline
        ss << endl;
    }

    
    return ss.str();
}
//--------------------------------------------------------TO SORTED STRING-----------------------------------------------------
string Hashmap :: toSortedString() const
{
    stringstream ss;
    // create a pair for the key and value since we can't put a Node into a queue
    priority_queue< pair<int,string> > mypq; // default ordering for a pair is by the first element, so lets put the value in the first element to make things easy

    // iterate through the hashmap and add each Node's key and value to a pair, then put that pair into a priority queue
    for (int i = 0 ; i < BUCKETS ; i++)
    {
        Node* current = buckets[i];
        while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
        {
            // do stuff to the current link 
            pair <int,string> tempPair (current->value, current->key); // make a temporary pair and initialize it!
            mypq.push(tempPair); // add the temporary pair to the ordered queue of pairs
            
            // then increment the 'counter'
            current = current->next;
        }
    }

    // iterate through the priority queue, adding each pair to the stringstream (with formatting) and then popping it off the queue
    while(!mypq.empty())
    {
        // setup a temporary PQ and integer to store this rounds info
        priority_queue<string> tempPQ;
        int tempInt = mypq.top().first;
        // keep doing this stuff if the value is getting repeated and while there's still items in the list
        while ( (!mypq.empty()) && (mypq.top().first == tempInt))
        {
                // add the current top of the lists's *KEY* to the temporary priority queue
                tempPQ.push(mypq.top().second);
                // now that it has been saved you can get rid of it and look at the next one
                mypq.pop();
        }
        // once you stop getting repeat values, you can exit the loop and print out the temppq, which is automatically ordered by string!
        // oh wait but we're not ready yet, priority queue sorts the highest value on top, but we want alphabetical order, 
        // or the "lowest" values first.. so we need to put tempPQ into a stack first, and then pop the stack off the top
        // the top of the stack will be the bottom of the PQ, or the lowest value item so it will work just how we want it!
        stack<string> tempStack;
        while(!tempPQ.empty())
        {
            tempStack.push(tempPQ.top());
            tempPQ.pop();
        }
        while(!tempStack.empty())
        {
            ss << tempStack.top() << " => " << tempInt << endl;
            tempStack.pop();
        }
        // now that we've printed off all keys with matching values, as long as the mainpq is still not empty, we'll do 
        // another round with a new tempInt and a new tempPQ
    }


    return ss.str();
}
//--------------------------------------------------------SIZE----------------------------------------------------------------(done)
int Hashmap :: size() const
{
    return mapSize;
}
//--------------------------------------------------------OPERATOR []----------------------------------------------------------------
int& Hashmap :: operator [](string key)
{
    //first, find the Node (if it exists)
    int hashIndex = hash(key);

    cout << "attempting to access the value of " << key << " in bucket [" << hashIndex << "] \n searching through the bucket for your item \n";

    Node* current = buckets[hashIndex];
    while(current != NULL) // loop through all Nodes in the bucket (this will be skipped if the first item is NULL)
    {
        // do stuff to the current link 
        if ((current->key) == key) // if there is an item with matching key, just reassign that keys value to the new value
        {
            cout << "your key was found! \n";
            return current->value;
        }
        // then increment the 'counter'
        current = current->next;
    }

    cout << "your key was not found, creating a new node with the given key for you to access \n";

    insert(key,0);
    // no need to increment mapSize, because the insert function already does that for us!
    return this->operator[](key);
}
