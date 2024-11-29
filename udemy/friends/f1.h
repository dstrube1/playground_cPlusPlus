#ifndef __F1_H__
#define __F1_H__

#include <string>
#include "f0.h"

using namespace std;

class f1{
	private:
		string name; //initializing this with {} doesn't work with default compiler settings
	public:
		f1 ();
		string getName() { return name; }
		
		//the following method was also declared in f0.h, but not implemented in f0.cpp; 
		//I later commented it out in f0.h:
		void sharedFromF0(f0 &f0_obj); 
		//note, when the function name was sharedFromF0ForF1, this wasn't required here:
		//#include "f0.h"
		//Seems if the function name is unique, then it's not ambiguous, & the compiler is 
		//smart enough to not require the include
		
		void doF0Stuff();
};

#endif //__F1_H__
