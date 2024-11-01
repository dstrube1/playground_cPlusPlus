#include <iostream>
#include <string>
#include <vector>

using namespace std;

//compiling and running
/*
# To compile:
# most basic:
g++ -o main.o main.cpp
# without -o, outputs to default a.out

# show all warnings and compile with c++14:
g++ -Wall -std=c++14 -o main.o main.cpp

#just compile with c++14:
g++ -std=c++14 -o main.o main.cpp

# compile verbosely:
g++ -v -o main.o main.cpp

# version number specifying is required for some types of array declarations, 
# as described below
g++ -std=c++14 -o main.o main.cpp

# To run:
./main.o

*/

int main()
{

	
  cout << "Done\n";
  return 0;
}

/* 
//TODO: revisit lesson 148 at 4:21
Shallow::Shallow(const Shallow &source) : data(source.data) {
	cout << "Copy constructor - shallow" << endl;
	//Shallow copy - only the pointer is copied - not what it is pointing to.
	//source and the newly created object both point to the same data area.
	//When a copied pointer goes out of scope, it is destroyed.
	//When the copy pointer is destroyed, the source pointer is no longer valid
}

int main(){
	Shallow obj{100};
	display_shallow(obj); //crash here?
	// obj's data has been released
	obj.set_data(1000); //or here?
	Shallow obj0 {obj}; //or here?
	cout << "Still alive?" << endl;
	return 0;
}

//TODO: revisit lesson 149 at 1:37
Deep::Deep(const Deep &source){
	data = new int;
	*data = *source.data;
	cout << "Copy constructor - deep" << endl;
}

//Deep copy constructor - delegating constructor
Deep:Deep(const Deep &source) : Deep{*source.data} {
	cout << "Copy constructor - deep & delegated" << endl;
}

//TODO: make folder "constructors" to explore lessons 148-150
Also, in lesson 150, around 14:50 - noexcept? Was this explained, and if so when?
https://en.cppreference.com/w/cpp/language/noexcept
https://stackoverflow.com/questions/10787766/when-should-i-really-use-noexcept
*/
