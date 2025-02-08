#include <iostream>
#include <string>
#include "inh0.h"
#include "inh1.h"
#include "inh2.h"
#include "IPrintable.h"
#include "PrintMe.h"
#include <vector>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o main.o main.cpp inh0.cpp inh1.cpp inh2.cpp IPrintable.cpp PrintMe.cpp

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
TODO: inh2: Derived from inh0 and inh1?

See also: UML class diagrams

Is-a relationship (vs has-a): e.g., Circle (sub) *is-a* Shape (parent)
Composition: has-a; e.g, Person has-a Account, Circle has-a Location; also allows re-use of existing classes, but is not inheritance; see also aggregation & association
Generalization: combine similar classes into single general class based on common attributes
Specialization: new classes with specialized attributes

*/

void call_from_reference(inh0 &i0);
void doStuff(vector<inh0 *> &vec);

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
/**/
	inh0 i0a;
	inh0 i0b("i0b");
	
	cout << "i0a.getName(): " << i0a.getName() << endl;
	cout << "i0a.getProtectedString(): " << i0a.getProtectedString() << endl;
	
	inh1 i1a;
	inh1 i1b("i1b");
	
	//Not allowed:
	//i1a.protectedInt = 1;
	
	//Note, if not declared and implemented in ih1, getName is still callable from i1a
	cout << "i1a.getName(): " << i1a.getName() << endl;
	
	cout << "i1a.getProtectedString(): " << i1a.getProtectedString() << endl;
	
	cout << "i1b.display(): ";
	i1b.display();

	//static binding example
	cout << endl << "static binding example: \n";
	inh0 *inh0_ptr = new inh1();
	//The following calls inh0 getName, not inh1's:
	cout << "Even though inh0_ptr is assigned to a new inh1, it calls inh0's getName:\n";
	cout << "inh0_ptr getName(): " << inh0_ptr->getName() << endl; 
	//Good practice to always delete pointers when you're done with them
	delete inh0_ptr;

	//run-time polymorphism example
	cout << endl << "run-time polymorphism example: \n";
	inh1 i1c;
	call_from_reference(i1c);
/**/
	//another example of run-time polymorphism, using smart pointer:
	cout << endl << "run-time polymorphism via smart pointer example: \n";
	std::unique_ptr<inh0> smart_ptr = std::make_unique<inh1>();
	smart_ptr->virtualMethod();
	//We don't have to delete smart pointers.
	//Note, this automatically calls the inh0 destructor, 
	//but interestingly doesn't seem to call the inh1 destructor
	
	cout << endl << "run-time polymorphism via array example: \n";
	inh0 *i0 = new inh0();
	inh0 *i1 = new inh1();
	inh0 *i2 = new inh2();
	inh0 *arr [] = {i0, i1, i2};
	for (auto i=0; i < 3; ++i){
		arr[i]->virtualMethod();
	}

	cout << endl << "run-time polymorphism via vector example: \n";
	vector<inh0 *> vec {i0, i1, i2};
	for (auto vec_ptr : vec){
		vec_ptr->virtualMethod();
	}
	cout << "pass a vector of pointers as a reference:\n";
	doStuff(vec);
	cout << "deleting inh0 pointer to inh0\n";
	delete i0;
	cout << "deleting inh0 pointer to inh1\n";
	delete i1;
	cout << "deleting inh0 pointer to inh2\n";
	delete i2;
	
	cout << endl << "using base class references:\n";
	cout << "(declaring inh1 i1_origin)\n";
	inh1 i1_origin;
	cout << "(declaring inh0 &i1_ref and initializing it to inh1 i1_origin)\n";
	inh0 &i1_ref = i1_origin;
	cout << "(calling virtualMethod from i1_ref)\n";
	i1_ref.virtualMethod();

	//Trying to instantiate an abstract base class:
	cout << endl << "interface example:\n";
	//IPrintable p; //error: variable type 'Printable' is an abstract class
	//IPrintable *p0 = new IPrintable(); //error: allocating an object of abstract class type 'Printable'
	IPrintable *p1 = new PrintMe();
	cout << "Calling print as a function:\n";
	p1->print(cout);
	cout << "Testing use of IPrintable / PrintMe p1 with cout:\n";
	cout << *p1;
	delete p1;

	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void call_from_reference(inh0 &i0){
	cout << "inh0 reference's call to getProtectedString() (where getProtectedString is not a virtual method): " << i0.getProtectedString()<< endl;
	
	//Example of run-time polymorphism, as opposed to compile-time polymorphism
	cout << "inh0 reference's call to virtualMethod() (where the inh0 is actually an inh1): "<< endl;
	i0.virtualMethod();
	
	//Shouldn't matter whether the virtual method is void or actually returns something
}

//to pass a vector of pointers as a reference (so as to not copy anything):
void doStuff(vector<inh0 *> &vec){
	for(const auto i : vec){
		i->virtualMethod();
	}
}



