#include "move_ctor.h"
#include <iostream>

using namespace std;

/*
	private:
		int *data
*/

move_ctor::move_ctor (){
	data = new int; //allocate storage
	cout << "move_ctor constructor with no params. Leaving privates with their default values." << endl;
	
	int x {100}; //x is an l-value - addressable and named
	int &L_ref = x; //l-value reference
	L_ref = 10; //change x to 10
	
	int &&r_ref = 200; //200 is an r-value; r_ref is an r-value reference
	r_ref = 300; //change r_ref to 300
	
	//int &&x_ref = x; //compiler error
}

move_ctor::move_ctor (int d){
	data = new int; //allocate storage
	cout << "move_ctor constructor with one param." << endl;
	*data = d;
}

move_ctor::move_ctor(const move_ctor &source){ //copy constructor
	cout << "move_ctor deep copy constructor of " << *source.data << endl;
	data = new int;
	*data = *source.data; 
}

//A move constructor is like a deep copy constructor, except after copying the address of the resource from the source to the current ojbect, we then null out the pointer in the source pointer - very efficient
//no const qualifier for the paramater source- this way we can null out its pointer
/*move_ctor::move_ctor(move_ctor &&source) noexcept : data {source.data} {
	//no need for deep copy; shallow copy is safe here because of the immediate nulling
	source = nullptr;
	//TODO - try the vector pushes with and without this move constructor
}*/

void move_ctor::func_0(int &num){
	//TODO code to get method name? this is possible in Java. Is it possible in C++?
	cout << "This function (func_0) doesn't do anything except illustrate some of the stuff in the Move Constructor lesson" << endl;
	/*
	int x {100};
	func_0(x); //this is fine: x is an l-value
	func_0(200); //error - 200 is an r-value
	//cannot bind non-constant l-value reference of type 'int&'to an r-value of type 'int'
	*/
}

void move_ctor::func_1(int &&num){
	cout << "This function (func_1) doesn't do anything except illustrate some of the stuff in the Move Constructor lesson" << endl;
	/*
	int x {100};
	func_1(200); //this is fine: 200 is an r-value
	func_1(x); //error: x is an l-value
	//error: rvalue reference to type 'int' cannot bind to lvalue of type 'int'
	*/
}

void move_ctor::func_2(int &num){
	cout << "func_2 called with an l-value" << endl;
}
void move_ctor::func_2(int &&num){
	cout << "func_2 called with an r-value" << endl;
}

//not setting or getting the pointer, but rather what it points to, its value
void move_ctor::set_data(int d) {*data = d;}
int move_ctor::get_data() {return *data; }


/*
LEFTOFF=6:23
*/

//Destructor
move_ctor::~move_ctor(){
	if (data == nullptr) cout << "Move destructor for nullptr \n";  
	else cout << "Move destructor for: " << *data << " \n"; 

	delete data;
}
