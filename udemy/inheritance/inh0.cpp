#include "inh0.h"
#include <iostream>

using namespace std;

inh0::inh0 (): name {"inh0"}, protectedString {"protectedString-inh0"} {
	cout << "inh0 contructor with no params" << endl;
}

inh0::inh0(string s) : name{s}, protectedString {"protectedString-inh0"}  {
	cout << "inh0 contructor with 1 param: " << s << endl;
}

string inh0::getName(){
	return name;
}

string inh0::getProtectedString(){
	return protectedString;
}

inh0::~inh0 (){
	cout << "inh0 destructor" << endl;
}

