#include <iostream>
#include <string>
#include "shallow.h"
#include "deep.h"
#include "move_ctor.h"
#include <vector>

using namespace std;

/*
# To compile:
g++ -o main.o -std=c++14 main.cpp shallow.cpp deep.cpp move_ctor.cpp

# without -o, outputs to default a.out
# without -std=c++14, builtin copy constructor fails to compile, as well as class method implementations outside the class

# To run:
./main.o

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN clazz 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//If not defined in another file (and referenced like "#include "blah.h"), then this must be declared above the main function
class clazz{
	private:
		int priv0;
		string priv1 {"initial value"};
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
		void setPriv0(int p0);

		//Destructor
		~clazz();//{ };
};

//Constructor initialization lists are more efficient than old fashioned constructor initialization
clazz::clazz (int p0, string p1) : priv0 {p0}, priv1 {p1} {cout << "Constructor with 2 parameters : "<< p0 << "," << p1 << "\n";} 

//Delegating constructor
clazz::clazz () : clazz{0, "default"} { cout << "Default constructor, no parameters, delegating to constructor with params. (The constructor this is delegated to does its stuff before this is printed.)\n";} 

int clazz::getPriv0() {
	return priv0;
}

void clazz::setPriv0(int p0){
	priv0 = p0;
}

//Destructor
clazz::~clazz(){
	cout << "clazz destructor of " << priv1 << "\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END clazz
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN shallow_without_pointer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class shallow_without_pointer{
	private:
		int priv0; 								//<-not a pointer
		string priv1 {"shallow_without_pointer initial value"};
	public:
		//Standard constructor declarations
		shallow_without_pointer (int p0, string p1);
		shallow_without_pointer ();

		int getPriv0();
		void setPriv1(string p1);

		//Copy constructor
		shallow_without_pointer (const shallow_without_pointer &source);

		//Destructor
		~shallow_without_pointer();
};

shallow_without_pointer::shallow_without_pointer (){
	cout << "Shallow_without_pointer contructor with no params. Leaving privates with their default values." << endl;
}

shallow_without_pointer::shallow_without_pointer (int p0, string p1){
	priv0 =  p0;
	priv1 = p1;
	cout << "Shallow_without_pointer contructor with 2 params." << endl;
}

//Copy constructor
shallow_without_pointer::shallow_without_pointer (const shallow_without_pointer &source)
: priv0 {source.priv0}, priv1 {source.priv1 + " copied"} { 
	cout << "Copy constructor of shallow_without_pointer " << source.priv1 << endl;
}

/*
Shallow copy: 
- memberwise copy
- each data member is copied from the source object
- pointer is copied, NOT what it points to
	problem: when we release the storage in the destructor, the other object still refers to the released storage
		best case scenario: this is discovered when the program crashes in the development stage
*/

int shallow_without_pointer::getPriv0() {
	cout << "getPriv0 called by " << priv1 << endl;
	return priv0;
}

//Destructor
shallow_without_pointer::~shallow_without_pointer(){
	cout << "shallow_without_pointer destructor of " << priv1 << "\n"; 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END shallow_without_pointer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Declaring locally defined method that will use a shallow_without_pointer object, passed in by value, 
//but should not cause a blow up
void display_shallow_without_pointer(shallow_without_pointer swop);

//Explore shallow vs deep copying
void shallow_vs_deep();

void non_clazz_method(clazz c);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
/**/
	move_ctor m{};
	int x {100};
	m.func_0(x); //this is fine: x is an l-value
	//m.func_0(200); //error - 200 is an r-value
	
	m.func_1(200); //this is fine: 200 is an r-value
	//m.func_1(x); //error: x is an l-value
	
	//overloaded method
	m.func_2(x); 
	m.func_2(200);
/**/

	vector<move_ctor> vec {};
	//pushing unnamed temporary objects, i.e., r-values; compiler will use the copy constructor to make them
	for(int i = 10; i <= 80; i+=10){
		vec.push_back(move_ctor{i});
	}
	//Note: vector makes copies of the objects behind the scenes as well as it grows
	//Does this also call the destructor now or later?
	//cout << "move_ctor destructor called yet?" << endl; //no, not yet

	cout << "Done. Automatically calling destructors now" << endl;
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_shallow_without_pointer(shallow_without_pointer swop){
	cout << "swop.getPriv0() called from method declared and implemented outside the swop class: ";
	cout << swop.getPriv0() << endl; //output: getPriv0 called by swop1 copied copied
	//Interesting, seems to be getting double copied
}

void shallow_vs_deep(){
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

	cout << "Creating s1, shallow object with initialization:" << endl;
	shallow s1 {1, "s1"};

	cout << "Creating s2, via shallow copy of s1:" << endl;
	shallow s2 {s1};

	cout << "Calling getPriv0 from s2:" << endl;
	s2.getPriv0(); 
//when calling getPriv0 with s1, a copy is made for getPriv0
//when that method is done, the copy goes out of scape and is automatically destroyed, 
//which will cause a problem for s1
	cout << "Still alive after calling getPriv0 from s2?" << endl;
//	If this is not included in the default constructor, then No: segmentation fault:
//priv0 = new int; //allocate storage
//If this ^ is included in the default constructor, then it won't fail here, but will fail later (when destructor is called?) 
	/**/
	
	//shallow_without_pointer
	cout << "\nTrying shallow_without_pointer copy constructor" << endl;
	shallow_without_pointer swop0;
	shallow_without_pointer swop1{7, "swop1"};
	//Harmless shallow copy?
	shallow_without_pointer swop2{swop1};
	int result = swop1.getPriv0();
	cout << "Result of swop1.getPriv0(): " << result << endl;
	display_shallow_without_pointer(swop2);
	//Key takeaway- shallow copy seems to be safe as long as it's done without a pointer,
	//but that may be contrived

////////////////
//deep
////////////////
	/**/
	cout << "\nCreating d0, deep object with no initialization:" << endl;
	deep d0;

	cout << "Creating d1, deep object with initialization:" << endl;
	deep d1 {1,"d1"};

	cout << "Creating d2, via deep copy of d1:" << endl;
	deep d2 {d1};

	cout << "Calling getPriv0 from d2:" << endl;
	d2.getPriv0();
	
	//Try the alternate deep copy constructor- it uses delegation
	/**/

////////////////
//the end
////////////////
	cout << "\nDone. Destructors get called automatically after this." << endl;
	
	/*
	If shallow s0 and s1 are left intact, then when destructors are called the program ends like this:
main.o(62977,0x11458d600) malloc: *** error for object 0x280: pointer being freed was not allocated
main.o(62977,0x11458d600) malloc: *** set a breakpoint in malloc_error_break to debug
	*/
}

void non_clazz_method(/*const*/clazz /*&*/c){ //TODO - try with the const modifier and pointer indicator (&) in the param list- it may build here but compiler fail when it calls the method
	//testing to see at what point does this fail when a const clazz is passed in
	cout << "Did this even build?\n";
	c.setPriv0(0);
	cout << "After setPriv0\n";
	c.getPriv0();
	cout << "After getPriv0\n";

}
