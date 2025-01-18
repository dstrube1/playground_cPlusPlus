#include "inh1.h"
#include <iostream>
#include <string>

using namespace std;

inh1::inh1 () 
: i {0}, protectedString{"fails to compile?"}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so name is not accessible here
	cout << "inh1 contructor with no params" << endl;
}

/**/inh1::inh1 (string s) 
: inh0{s}, protectedString{s}, i {0}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so name is not accessible here, 
//except as passed along to base constructor
	//Note also, it seems that the s must both be passed to the base constructor AND to inh1's protectedString member
	cout << "inh1 contructor with one param:" << s << endl;
}/**/

//'final' specifier is not allowed outside a class definition
void inh1::display() const /*final*/{
	cout << "protectedString: " << protectedString;
	cout << "; protectedInt: " << protectedInt << "; i: " << i << endl;
}

//redefine method from base class
string inh1::getName(){
	cout << "inh1's getName calls inh0's getName by redefining it: ";
	return inh0::getName();
}

string inh1::getProtectedString(){
	protectedString = "protectedString from inh1";
	cout << "getProtectedString from inh1: ";
	return protectedString;
}

//'virtual' can only be specified inside the class definition
//'override' specifier is not allowed outside a class definition
/*virtual*/ void inh1::virtualMethod() const /*override*/{
	cout << "virtualMethod from inh1\n";
}

inh1::~inh1 (){
	cout << "inh1 destructor" << endl;
}
