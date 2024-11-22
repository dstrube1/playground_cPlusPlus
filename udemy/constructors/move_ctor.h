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
		move_ctor (); //no param
		move_ctor(int d); //one param
		move_ctor(const move_ctor &source); //copy constructor
		move_ctor(move_ctor &&source) noexcept; //move constructor
		// what does the noexcept keyword do ^here?
		
		void func_0(int &num);
		void func_1(int &&num);
		//overloaded function so calling it either way will be fine
		void func_2(int &num);
		void func_2(int &&num);

		//not setting or getting the pointer, but rather what it points to, its value
		void set_data(int d);
		int get_data();
		
		//Destructor
		~move_ctor();
};

#endif //__MOVE_CTOR_H__
