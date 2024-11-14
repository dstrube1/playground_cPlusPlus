#include "shallow_without_pointer.h"
#include <iostream>

using namespace std;

/*
This comment is just here to remind you of what the privates are for this class, 
not an accidentally commented out declaration :-p
	private:
		int priv0 		//not a pointer
		string priv1
*/

//Public method implementations

shallow_without_pointer::shallow_without_pointer (){
	cout << "Shallow_without_pointer contructor with no params. Leaving privates with their default values." << endl;
}

shallow_without_pointer::shallow_without_pointer (int p0, string p1){
	priv0 =  p0;
	priv1 = p1;
	cout << "Shallow_without_pointer contructor with 2 params." << endl;
}

//Copy constructor
shallow_without_pointer::shallow_without_pointer (const shallow_without_pointer &source)
: priv0 {source.priv0}, priv1 {source.priv1 + " copied"} { 
	cout << "Copy constructor of shallow_without_pointer " << source.priv1 << endl;
}

/*
Shallow copy: 
- memberwise copy
- each data member is copied from the source object
- pointer is copied, NOT what it points to
	problem: when we release the storage in the destructor, the other object still refers to the released storage
		best case scenario: this is discovered when the program crashes in the development stage
*/

int shallow_without_pointer::getPriv0() {
	cout << "getPriv0 called by " << priv1 << endl;
	return priv0;
}

//Destructor
shallow_without_pointer::~shallow_without_pointer(){
	cout << "shallow_without_pointer destructor of " << priv1 << "\n"; 
}

