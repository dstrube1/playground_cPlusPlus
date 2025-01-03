#include <iostream>
#include <string>
#include "inh0.h"
#include "inh1.h"

using namespace std;

/*
# To compile:
g++ -std=c++14 -o main.o main.cpp inh0.cpp
g++ -o main.o main.cpp inh0.cpp inh1.cpp
g++ -o main.o main.cpp inh0.cpp inh1.cpp inh2.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./main.o

Welcome to the exploration of inheritance, 
the process of creating new classes from existing classes
Single inheritance: new class created from another single class
Multiple inheritance: new class created from two or more classes

inh0: Base / super / parent class
inh1: Derived from inh0 - child / sub class
TODO: inh2: Derived from inh0 and inh1

See also: UML class diagrams

Is-a relationship (vs has-a): e.g., Circle (sub) *is-a* Shape (parent)
Composition: has-a; e.g, Person has-a Account, Circle has-a Location; also allows re-use of existing classes, but is not inheritance; see also aggregation & association
Generalization: combine similar classes into single general class based on common attributes
Specialization: new classes with specialized attributes

*/

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	inh0 i0a;
	inh0 i0b("i0b");
	
	cout << "i0a.getName(): " << i0a.getName() << endl;
	cout << "i0a.getProtectedString(): " << i0a.getProtectedString() << endl;
	
	inh1 i1a;
	inh1 i1b("i1b");
	
	cout << "i1a.getName(): " << i1a.getName() << endl;
	
	cout << "i1a.getProtectedString(): " << i1a.getProtectedString() << endl;
	
	cout << "i1b.display(): ";
	i1b.display();

	cout << "Done" << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////




