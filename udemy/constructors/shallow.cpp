#include "shallow.h"
#include <iostream>

using namespace std;

/*
	private:
		int priv0
		string priv1
*/

int shallow::getPriv0() {
	cout << "getPriv0 called by " << priv1 << endl;
	return priv0;
}

shallow::shallow (){
	cout << "Shallow contructor with no params. Leaving privates with their default values." << endl;
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

//Destructor
shallow::~shallow(){
	cout << "shallow destructor of " << priv1 << "\n"; 
}
