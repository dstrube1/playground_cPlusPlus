#include "inh2.h"
#include <iostream>

using namespace std;

inh2::inh2 () { 
	cout << "inh2 contructor with no params" << endl;
}

//'virtual' can only be specified inside the class definition
//'override' specifier is not allowed outside a class definition
/*virtual*/ void inh2::virtualMethod() const /*override*/{
	cout << "virtualMethod from inh2\n";
}

inh2::~inh2 (){
	cout << "inh2 destructor" << endl;
}
