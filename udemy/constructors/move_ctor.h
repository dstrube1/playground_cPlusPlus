#ifndef __MOVE_CTOR_H__
#define __MOVE_CTOR_H__

#include <string>
using namespace std;

class move_ctor{
//Just calling this "move" was ambiguous, according to the compiler

	//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535596#overview
	//Core concepts:
	//Copy elision
	//RVO - Return value optimization
	//r-value references
	//r-value reference operator: &&
	private:
		int *data;
	public:
		move_ctor ();
		
		void func0(int &num);
		void func1(int &&num);
		//overloaded function so calling it either way will be fine
		void func2(int &num);
		void func2(int &&num);
		
		//Destructor
		~move_ctor();
};

#endif //__MOVE_CTOR_H__
