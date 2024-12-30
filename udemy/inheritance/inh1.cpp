#include "inh1.h"
#include <iostream>

using namespace std;

inh1::inh1 () 
: i {0}, protectedString{"fails to compile?"}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so not accessible here
	cout << "inh1 contructor with no params" << endl;
}

inh1::inh1 (string s) 
: inh0(s), i {0}, protectedString{"fails to compile?"}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so not accessible here
	cout << "inh1 contructor with no params" << endl;
}

void inh1::display(){
	cout << "" << endl;
}

inh1::~inh1 (){
	cout << "inh1 destructor" << endl;
}
