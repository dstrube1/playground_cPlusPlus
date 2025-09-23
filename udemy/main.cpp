#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

void intDivsionTest();
void carriageReturnTest();
void functionWithNoParams(void);
//void functionWithNoParams0(void, int);
void bitwiseTest();

int main()
{
	intDivsionTest();
	//carriageReturnTest();
	//functionWithNoParams();
	//bitwiseTest();
	
	cout << "\nDone\n";
	return 0;
}

void intDivsionTest(){
	int i = 3;
	int j = 2;
	int k = i / j;
	cout << "int 3 / 2 = " << k << endl; //round down: 1.5 => 1
	
	//What does a divide by zero error look like?
	//j = 0;
	//k = i / j;
	//Surprisingly quiet:
	//zsh: floating point exception  ./main.o
	
	//Also surprising that the compiler allowed it to compile without having to be tricky
}

void carriageReturnTest(){
	cout << "Example of \\r:\n";
	cout << "1\r2 \n";
	cout << "There was a 1 there before the \\r returned carriage (return carriaged?) and overwrote it\n";
}

void functionWithNoParams(){ //void in param list here is optional even if it was included in the function declaration before main
	//from https://en.wikipedia.org/wiki/Compatibility_of_C_and_C%2B%2B
	cout << "\nA function with no parameters can be specified as such using a void param\n";
}

/*void functionWithNoParams0(void x, int y){
	cout << "Is this possible? No, of course not, silly rabbit!" << endl;
	// error: 'void' must be the first and only parameter if specified
}*/

/* 
In lesson 150, around 14:50 - noexcept? Was this explained, and if so when?
https://en.cppreference.com/w/cpp/language/noexcept
https://stackoverflow.com/questions/10787766/when-should-i-really-use-noexcept
^Explored in noexceptTest.cpp, new and currently one dir up

*/

//2025-06-13: While brushing up on Go, saw something weird about Go's bitwise operators.
//This is a test to confirm that it doesn't work in C++ like it does in Go
void bitwiseTest(){
	int i = 1;
	cout << "i before bitwise shift (<< 2): " << i << endl;
	i = i << 2;
	cout << "i after bitwise shift: " << i << endl;
}