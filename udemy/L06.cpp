#include <iostream>
#include <string>
#include <vector>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -std=c++11 -o L06.o L06.cpp
# without -o, outputs to default a.out
# without -std=c++11, get errors just declaring private data members(?!):
function definition does not declare parameters

# To run:
./L06.o

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN clazz 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class clazz{
	private:
		int priv0 {3};
		string priv1 {"initial value"};
		const static int constStaticPriv {2}; 
		static int staticPriv; //C++ forbids in-class initialization of non-const static members
	public:
		//Without this, get the follow error:
		//default initialization of an object of const type 'const clazz' without a user-provided default constructor
		clazz ();
		int getPriv0(); 
		void setPriv0(int p0);
		void constMethod() const;

		static int staticPublic;
		int nonStaticPublic;
		static int getStaticPriv();
};

//Default constructor
clazz::clazz (){ cout << "Default constructor, no parameters\n";} 

//initialize private static data
int clazz::staticPriv = 1;

int clazz::getPriv0() {
	//NOte: __func__ predefined identifier
	cout << __func__ << " called where priv 1 = " << priv1 << endl;
	//return priv0;
	//Does this work as well? Yes
	return this->priv0;
}

void clazz::setPriv0(int priv0){
	this->priv0 = priv0;
	//If param name is the same as the data member, then must use 'this' here 
	//because otherwise it's ambiguous and scope rules say that the parameter would just assign the value to itself
}

void clazz::constMethod() const { cout << "constMethod doesn't really do anything except illustrate how to call a method with a const object\n";}

/*static*/ int clazz::getStaticPriv(){
	return staticPriv;
	//Called like this: cout << clazz::getStaticPriv();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END clazz
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN struct
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct struckd { //members are public by default (members of classes are private by default)
	int i; //default initial value might be 1, or 0, or some garbage 
	int get_i() { return i;}
/*
Use struct for passive objects with public access
Don't declare methods in struct (why? is private not possible in struct? or are structs inefficient?)
Use class for active objects with private access

*/
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END struct
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//Const, struct, static, this, and __func__
	/**/
	struckd s;
	cout << "s.i: " << s.i << endl;
	cout << "s.get_i(): " << s.get_i() << endl;
	
 	//Next, testing const stuff
	const clazz c0;

	//these fail to compile
	//c0.setPriv0(0);
	//c0.getPriv0();
	//but this works
	c0.constMethod();

	//Testing __func__ predefined identifier
	clazz c1;
	cout << "Calling getPriv0 returns this: " << c1.getPriv0() << endl;

 /**/

	
  cout << "Done\n";
  return 0;
}


/**/