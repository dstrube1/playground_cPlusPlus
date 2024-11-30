#ifndef __F2_H__
#define __F2_H__

#include <string>
using namespace std;

class f0;

class f2{
	private:
		string name; //initializing this with {} doesn't work with default compiler settings
	public:
		f2 ();
		string getName() { return name; }
		//also declared in f0.h, but not implemented in f0.cpp
		void sharedFromF0(f0 &f0_obj);
		void doF0Stuff();
};

#endif //__F2_H__
