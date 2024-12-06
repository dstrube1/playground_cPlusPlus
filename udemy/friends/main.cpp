#include <iostream>
#include <string>
#include "f0.h"
#include "f1.h"
#include "f2.h"
#include "f3.h"

using namespace std;

/*
# To compile:
g++ -o main.o main.cpp f0.cpp f1.cpp f2.cpp f3.cpp

# without -o, outputs to default a.out

# To run:
./main.o

Welcome to the exploration of friends and friendship

- variables_are_named_like_this, unless it's a simple name with a number, like this0
- functionsAreNameLikeThis

f0 - the dungeon master
|_ f1: f0 considers f1 a close personal friend; f1 doesn't recall meeting f0, but will accept f0's invitation to parties; f0 won't think it's at all weird when f1 wants to rummage thru f0's underwear drawer
|_ f2: f0 considers f2 an acquaintance; f2 doesn't recall meeting f0, but will accept f0's invitation to parties; let's see what happens when f2 wants to rummage thru f0's underwear drawer...
|_ f3: f0 doesn't recall meeting f3; When f3 tries to rummage thru f0's underwear drawer, f0 looks into pressing charges
|_ f4: f4 is main's roommate; f0 doesn't recall meeting f4; when f4 tries to rummage thru f0's underwear drawer, f0 seriously questions main's choice in roommates
*/

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN f4
//////////////////////////////////////////////////////////////////////////////////////////
class f4{
	private:
		string name; //initializing this with {} doesn't work with default compiler settings
	public:
		f4 ();
		string getName() { return name; }
		void sharedFromF0(f0 &f0_obj); 
		void doF0Stuff();
};

f4::f4(){
	name = "f4";
	cout << "created an f4" << endl; 
}
void f4::sharedFromF0(f0 &f0_obj){
	cout << __func__ << ": simple: ";
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	
	//NOT ALLOWED
	/**
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f2";
	cout << f0_obj.name << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
	**/
}
void f4::doF0Stuff(){
	cout << __func__ << ": simple: ";
	f0 f0_obj;
	cout << f0_obj.getPriv0() << "; ";
	cout << f0_obj.getName() << endl;
	
	//NOT ALLOWED
	/**
	cout << "complicated: ";
	cout << "priv0: " << f0_obj.priv0 << "; ";
	cout << "++priv0: " << ++f0_obj.priv0 << "; ";
	cout << "name change: "; 
	f0_obj.name = "f0 changed by f2 from "; 
	cout << f0_obj.name << __func__ << endl;
	
	cout << "hardcore: ";
	cout << "static_num: " << f0::static_num << "; ";
	cout << "++static_num: " << ++f0::static_num << endl;
	**/
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END f4
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	f0 f0_obj;
	f1 f1_obj;
	f2 f2_obj;
	f3 f3_obj;
	f4 f4_obj;
	
	cout << "\nTrying to access f0 stuff from f1...\n";
	f1_obj.sharedFromF0(f0_obj);
	cout << "Trying to access f0 stuff from f1 without an outside instance of f0...\n";
	f1_obj.doF0Stuff();
	
	cout << "\nTrying to access f0 stuff from f2...\n";
	f2_obj.sharedFromF0(f0_obj);
	cout << "Trying to access f0 stuff from f2 without an outside instance of f0...\n";
	f2_obj.doF0Stuff();

	cout << "\nTrying to access f0 stuff from f3...\n";
	f3_obj.sharedFromF0(f0_obj);
	cout << "Trying to access f0 stuff from f3 without an outside instance of f0...\n";
	f3_obj.doF0Stuff();

	cout << "\nTrying to access f0 stuff from f4...\n";
	f4_obj.sharedFromF0(f0_obj);
	cout << "Trying to access f0 stuff from f4 without an outside instance of f0...\n";
	f4_obj.doF0Stuff();

	cout << "Done" << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

