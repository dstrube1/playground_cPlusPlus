#include "shallow.h"
#include <iostream>

using namespace std;

/*
This comment is just here to remind you of what the privates are for this class, 
not an accidentally commented out declaration :-p
	private:
		int *priv0 		//pointer
		string priv1
*/

//Public method implementations

shallow::shallow (){
	priv0 = new int; //allocate storage
	cout << "Shallow contructor with no params. Leaving privates with their default values." << endl;
}

shallow::shallow (int p0, string p1){
	priv0 = new int; //allocate storage
	*priv0 = p0;
	priv1 = p1;
	cout << "Shallow contructor with 2 params." << endl;
}

//Copy constructor
shallow::shallow (const shallow &source)
: priv0 {source.priv0}, priv1 {source.priv1 + " copied"} { 
	//^Alternatively, can delegate from copy constructor to another construtor, like Constructor initialization lists, like so:
	//: shallow (source.priv0, source.priv1 + " copied") { 
	cout << "Copy constructor of shallow " << source.priv1 << endl;
	//Note 1: copy constructor is provided by the compiler by default if not explicitly made
	//Note 2: any method of shallow that uses a shallow object will call the copy constructor first
}

/*
Shallow copy: 
- memberwise copy
- each data member is copied from the source object
- pointer is copied, NOT what it points to
	problem: when we release the storage in the destructor, the other object still refers to the released storage
		best case scenario: this is discovered when the program crashes in the development stage
*/

int shallow::getPriv0() {
	cout << __func__ << " called by " << priv1 << endl;
	return *priv0;
}

//Destructor
shallow::~shallow(){
	delete priv0;	//free storage
	cout << "shallow destructor of " << priv1 << "\n"; 
}

