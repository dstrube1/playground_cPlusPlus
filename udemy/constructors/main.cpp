#include <iostream>
#include <string>
#include "shallow.h"
//#include "deep.h"

using namespace std;

/*
# To compile:
# most basic:
g++ -o main.o -std=c++14 main.cpp shallow.cpp deep.cpp
# without -o, outputs to default a.out
# without -std=c++14, builtin copy constructor fails to compile, as well as class method implementations outside the class

# To run:
./main.o

*/

//If not defined in another file (and referenced like "#include "blah.h"), then this must be declared above the main function
class clazz{
	private:
		int priv0;
		string priv1 {"can be declared with initial value"};
	public:
		clazz (int p0, string p1);
		clazz ();
		//If implemented in class, the constructors would look like this:
		/*
		//Constructor initialization lists are more efficient than old fashioned constructor initialization
		clazz (int p0, string p1) : priv0 {p0}, priv1 {p1} {cout << "Construcctor with 2 parameters : "<< p0 << "," << p1 << "\n";} 
		//Delegating constructor
		clazz () : clazz{0, ""} { cout << "Default construcctor, no parameters, delegating to constructor with params\n";} 
		//Alternatively: Constructor with default values, making other constructors superfluous:
		//clazz (int p0 = 0, string p1 = "a");
		*/
		//But better to implement them outside the class (instead we'll just declare them), along with other methods, like this one:
		int getPriv0();

		//Destructor
		~clazz();//{ };
};

//Constructor initialization lists are more efficient than old fashioned constructor initialization
clazz::clazz (int p0, string p1) : priv0 {p0}, priv1 {p1} {cout << "Constructor with 2 parameters : "<< p0 << "," << p1 << "\n";} 

//Delegating constructor
clazz::clazz () : clazz{0, "default"} { cout << "Default constructor, no parameters, delegating to constructor with params. (The constructor this is delegated to does its stuff before this is printed.)\n";} 

int clazz::getPriv0() {
	cout << "getPriv0 called by " << priv1 << endl;
	return priv0;
}

//Destructor
clazz::~clazz(){
	cout << "clazz destructor of " << priv1 << "\n";
}

int main()
{
////////////////
//clazz
////////////////
	cout << "Creating c0, clazz object with no initialization:" << endl;
	clazz c0;

	cout << "\nCreating pointer to object with 2 params:" << endl;
	clazz *c1 = new clazz(1, "c1");

	cout << "\nCreating object with 2 params:" << endl;
	clazz c2 {2,"c2"};

	cout << "\nCalling class method with an object:" << endl;
	c2.getPriv0();

	cout << "\nCalling with an object pointer, weird way:" << endl;
	(*c1).getPriv0();

	cout << "\nCalling with an object pointer, normal way:" << endl;
	c1->getPriv0();

	cout << "\nDeleting c1:" << endl;
	delete c1;
	
//while still using clazz, this is technically a shallow copy
	cout << "\nInitializing c3 with {c0} using the builtin copy constructor" << endl;
	clazz c3 {c0};

////////////////
//shallow
////////////////
	/**/
	cout << "\nCreating s0, shallow object with no initialization:" << endl;
	shallow s0;

	cout << "\nCreating s1, via shallow copy of s0:" << endl;
	shallow s1 {s0};

	cout << "\nCalling getPriv0 from s1:" << endl;
	s1.getPriv0();
	/**/

////////////////
//deep
////////////////
	/**
//TODO - flesh this out / fix this / etc
	cout << "\nCreating d0, deep object with no initialization:" << endl;
	deep d0;

	cout << "\nCreating d1, via deep copy of d0:" << endl;
	deep d1 {d0};

	cout << "\nCalling getPriv0 from d1:" << endl;
	d1.getPriv0();
	/*/

////////////////
//the end
////////////////
	cout << "\nDone. Destructors get called automatically after this." << endl;
	
	return 0;
}

