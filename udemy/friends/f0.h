#ifndef __F0_H__
#define __F0_H__

#include <string>
using namespace std;

/*
Friendship is not to be taken for granted; ie, friendship must be granted, not taken
Friendship is not symmetric (A => B does not mean B => A)
Friendship is not transitive (A => B and B => C does not mean A => C) 

In the Udemy section 13 code, 
f0 = class Player
f1 = Friend_class
f2 = Other_class
*/

#include "f2.h"
class f1;

class f0{
	//f1 is a friend of f0:
	friend class f1;
	//this method explicitly shares an instance of f0 with f1 
	//(and is not implemented in f0) even though f1 is declared as a friend class.
	//all methods of f1 have access to f0's privates.
	//What if we comment out this method declaration here?
//	friend void sharedFromF0(f0 &f0_obj); 
	//Still works the same. I guess this is just a courtesy, or for clarity
	
	//f2's friendship with f0 is more limited - only a shared method, not shared class, has access 
	//to all private members of f0
	//What if we comment out this method declaration here?
	friend void f2::sharedFromF0(f0 &f0_obj);
	//If this^ is commented out, then lots of stuff breaks
	private:
		static int static_num;
		int priv0;
		string name; //initializing this with {} doesn't work with default compiler settings
	public:
		f0();
		int getPriv0(); 
		string getName();
};

#endif //__F0_H__
