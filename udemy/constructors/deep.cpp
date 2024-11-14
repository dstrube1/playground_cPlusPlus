#include "deep.h"
#include <iostream>

using namespace std;

/*
	private:
		int *priv0;
		string priv1 {"can be declared with initial value"};
*/

deep::deep (){
	priv0 = new int; //allocate storage
	cout << "Deep contructor with no params. Leaving privates with their default values." << endl;
}

deep::deep (int p0, string p1){
	priv0 = new int; //allocate storage
	*priv0 = p0;
	priv1 = p1;
	cout << "Deep contructor with 2 params." << endl;
}

//Copy constructor
/**/
deep::deep (const deep &source)
{ 
	//Deep copy - create new storage and copy values
	priv0 = new int; //allocate storage
	*priv0 = *source.priv0;
	priv1 = source.priv1 + " deep copy";
	cout << "Deep copy constructor of " << source.priv1 << endl;
}
/**/

//Alternative copy constructor - delegate to parameterized constructor - try this too:
//Copy constructor
/**
deep::deep (const deep &source) : deep{*source.priv0, source.priv1 + " copy"}
{ 
	cout << "Deep copy constructor of " << source.priv1 << " using delegation" << endl;
}
**/

int deep::getPriv0() {
	cout << "getPriv0 called by " << priv1 << endl;
	return *priv0;
}

//Destructor
deep::~deep(){
	delete priv0;
	cout << "Deep destructor of " << priv1 << "\n"; 
}
