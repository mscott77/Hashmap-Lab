#include "Hashmap.h"
#include <string>

using namespace std;

int main()
{
    Hashmap mymap;

    cout << "------------------------TEST 1 - basic inserting, and inserting a duplicate key------------------------ \n \n";
    mymap.insert("mason",23);
    cout << endl << mymap.toString() << endl;
    mymap.insert("mason",666);
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    cout << "\n ---------------------TEST 2 - inserting multiple (non-duplicates) in the same bucket--------------- \n \n";

    mymap.insert("nosam",123);
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;
    mymap.insert("samno",456);
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    cout << "------------------------TEST 3 - clearing the Map, and adding new elements------------------------ \n \n";

    mymap.clear();
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    mymap.insert("chicken",5);
    mymap.insert("lettuce",7);
    mymap.insert("beluga wale",25);
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;




}