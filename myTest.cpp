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

    cout << "------------------------TEST 4 - test the get function for existing and non-existing keys------------------------ \n \n";

    mymap.clear();
    mymap.insert("waffle",7);
    mymap.insert("donkey",60);

    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    int donkeyVal = mymap.get("donkey");
    cout << "\nthe value of donkey is: " << donkeyVal << endl << endl;

    /*the following line will give you an error and end the program*/
    //mymap.get("DonCarlos");

    cout << "------------------------TEST 5 test the contains() function------------------------ \n \n";

    cout << "is \'waffle\' in the HashMap? " << mymap.contains("waffle") << endl;
    cout << "is \'le poissont\' in the HashMap? " << mymap.contains("le poissont") << endl << endl;


    cout << "------------------------TEST 6 test the remove function------------------------ \n \n";

    mymap.clear();

    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    mymap.insert("asdf",1);
    mymap.insert("fdsa",2);
    mymap.insert("afsd",3);
    mymap.insert("fads",4);
    mymap.insert("fasd",5);
    mymap.insert("afds",6);
    
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    mymap.remove("asdf");
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    mymap.remove("afds");
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

    mymap.remove("fads");
    cout << endl << mymap.toString() << endl;
    cout << "current number of items in map is: " << mymap.size() << endl << endl;

}