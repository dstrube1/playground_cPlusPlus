#ifndef __F3_H__
#define __F3_H__

#include <string>
#include "f0.h"

using namespace std;

class f3{
	private:
		string name; //initializing this with {} doesn't work with default compiler settings
	public:
		f3 ();
		string getName() { return name; }
		void sharedFromF0(f0 &f0_obj); 
		void doF0Stuff();
};

#endif //__F3_H__
