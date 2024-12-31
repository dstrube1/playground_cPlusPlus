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
};

#endif //__INH1_H__
