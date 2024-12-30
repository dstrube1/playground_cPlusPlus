#include "inh1.h"
#include <iostream>

using namespace std;

inh1::inh1 () 
: i {0}, protectedString{"fails to compile?"}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so name is not accessible here
	cout << "inh1 contructor with no params" << endl;
}

inh1::inh1 (string s) 
: inh0{s}, protectedString{s}, i {0}, protectedString{"fails to compile?"}, protectedInt {1} 
{ //Note, name was declared as private in inh0, not inh1; so name is not accessible here, 
//except as passed along to base constructor
	//Note also, it seems that the s must both be passed to the base constructor AND to inh1's protectedString member
	cout << "inh1 contructor with one param:" << s << endl;
}

void inh1::display(){
	cout << "" << endl;
}

inh1::~inh1 (){
	cout << "inh1 destructor" << endl;
}
