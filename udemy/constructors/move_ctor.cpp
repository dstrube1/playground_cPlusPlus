#include "move_ctor.h"
#include <iostream>

using namespace std;

/*
	private:
		int *data
*/

move_ctor::move_ctor (){
	data = new int; //allocate storage
	cout << "Move constructor with no params. Leaving privates with their default values." << endl;
	
	int x {100}; //x is an l-value - addressable and named
	int &L_ref = x; //l-value reference
	L_ref = 10; //change x to 10
	
	int &&r_ref = 200; //200 is an r-value; r_ref is an r-value reference
	r_ref = 300; //change r_ref to 300
	
	//int &&x_ref = x; //compiler error
}

void move_ctor::func0(int &num){
	cout << "This function (func0) doesn't do anything except illustrate some of the stuff in the Move Constructor lesson" << endl;
	/*
	int x {100};
	func0(x); //this is fine: x is an l-value
	func0(200); //error - 200 is an r-value
	//cannot bind non-constant l-value reference of type 'int&'to an r-value of type 'int'
	*/
}

void move_ctor::func1(int &&num){
	cout << "This function (func1) doesn't do anything except illustrate some of the stuff in the Move Constructor lesson" << endl;
	/*
	int x {100};
	func1(200); //this is fine: 200 is an r-value
	func1(x); //error: x is an l-value
	//error: rvalue reference to type 'int' cannot bind to lvalue of type 'int'
	*/
}

void move_ctor::func2(int &num){
	cout << "func2 called with an l-value" << endl;
}
void move_ctor::func2(int &&num){
	cout << "func2 called with an r-value" << endl;
}


/*
LEFTOFF=6:23
*/

//Destructor
move_ctor::~move_ctor(){
	delete data;
	cout << "Move destructor \n"; 
}
