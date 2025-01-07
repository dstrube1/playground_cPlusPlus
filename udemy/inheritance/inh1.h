#ifndef __INH1_H__
#define __INH1_H__

#include <string>
#include "inh0.h"

using namespace std;

/*
*/

class inh1: /*access specifier:*/ /**/public/**/ /** /protected/ **/ /** /private/ **/ inh0 {
	//public inheritance: is-a
	//private and protected inheritance: has-a; 
	//	^beyond the scope of this course: https://gbg.udemy.com/course/beginning-c-plus-plus-programming
	//If protected inheritance, then method that was public in parent is protected in child
	//If private inheritance, then method that was public in parent is private in child
	private:
		int i; 
	protected:
		string protectedString; //Seems like this should fail on compile, 
		//since protectedString was already declared in inh0
		int protectedInt; //TODO: accessible from main?
	public:
		inh1(); //constructors are not inherited from base class by derived class
		//Therefore, if both base and derived have a constructor with a param, but only base implements it,
		//then compile will fail. TODO - test this; 
		//also if there is a base constructor with a param, it must be called from derived constructor with a param
		inh1(string);
		void display();
		~inh1();
		//When a class derives from a parent, constructor / destructor order is this:
		// Base constructor, derived constructor, derived destructor, base destructor
/*
inh: see also https://gbg.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535664#overview
176. Copy/Move Constructors and Operator = with Derived Classes

redefine method from base class:
inh1::getName(){
	cout << "inh1's getName calls inh0's getName\n";
	return inh0::getName();
}

also: 
//static binding example
inh0 *inh0_ptr = new inh1();
inh0_ptr->getName(); //TODO: Confirm: calls inh0 getName, not inh1 ?
delete *inh0_ptr;

also:
overloaded functions and overloaded operators are compile-time polymorphism (aka, early-binding polymorphism and static binding polymorphism), as opposed to run-time polymorphism
run-time polymorphism requires inheritance
try this, in main:
void call_from_reference(inh0 &i0){
	i0.getProtectedString();
}
implement getProtectedString() in ih1, then :
inh0 i0 = new inh1();
i0.getProtectedString();
and 
inh1 i1 = new inh1();
i1.getProtectedString();
see what happens

then make new method in inh0: public virtual void test();
and declared and implemented in inh1: public void test();

smart pointer:
std::unique_ptr<inh0> ptr = std::make_unique<inh1>();
ptr->test();
//don't have to delete smart pointers

*/
};

#endif //__INH1_H__
