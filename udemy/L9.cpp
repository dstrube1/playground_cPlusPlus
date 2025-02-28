#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L9.o L9.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L9.o

Exceptions & exception handling

Exceptions are caused by:
* insufficient resources (out of diskspace or RAM)
* missing resources (nonexistent file)
* invalid operations ()
* range violations ()
* underflows and overflows
* illegal data
* etc

exception handling should not be used for asynchronous code

std:exception
what()

*/

class SomeClass{
	private:
		string name;
	public:
		SomeClass(){cout << "SomeClass default ctor\n"; name = "default";}
		SomeClass(string n){name = n; cout << "SomeClass " << name << " ctor\n";}
		void method(string type){cout<<"method from SomeClass with " << type << " pointer\n";}
		void setName(string n){name = n;}
		string getName(){return name;}
		~SomeClass(){cout<<"SomeClass destructor for " << name << "\n";}
};

class MyException : public exception{
	public:
		MyException() noexcept = default;
		~MyException() = default;
		virtual const char *what() const noexcept{ return "MyException"; }
};
//In diagram of C++ standard library exception class hierarchy (L10.jpeg),
// the ones in orange are c++17 additions

void throwsExceptions(int i);
MyException returnsMyException();
void overflow_underflow();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//First pass at exception throwing
	int m = 1;
	int g = 0;
	cerr << "This is the error stream\n";
	cout << "m: " << m << "; g: " << g << endl;
	cout << "static_cast<double> (m)/g:" << (static_cast<double> (m)/g) << endl; //inf
	cout << "static_cast<double> (-m)/g:" << (static_cast<double> (-m)/g) << endl; //-inf
	cout << "static_cast<double> (0)/g:" << (static_cast<double> (0)/g) << endl; //nan
	
	try{
		//program crashes with the following if m=1 and g=0, even with the "catch (...)":
		//cout << "m/g:" << (m/g) << endl; //zsh: floating point exception 
		//1:
		//https://stackoverflow.com/questions/56729866/i-cannot-catch-and-handle-floating-point-exception
		//"Floating point exception" is the name of a signal instead of exception.
		//"Integer divide by zero" is not an exception in standard C++.
		//2:
		//https://stackoverflow.com/questions/6121623/catching-exception-divide-by-zero

		//This led me down this rabbit hole:
		overflow_underflow();

		if (g == 0)
		{
			throw 0;
		//All subsequent code in this block will be skipped over, 
		//and outside this block, c++ will look for a catch of what is thrown;
		//Without try/catch:
		//libc++abi: terminating with uncaught exception of type int
		}
		if (g < 0 && g > -2){ //g == -1
			throw string{"Can throw a string"};
		}
		if (g < -1 && g > -3) //g == -2
		{
			throw "If thrown is not cast as string, must be caught as const char *";
		}
		int g0 = 0;
		//Interesting: this exception throwing / program crashing line isn't executed 
		//if it comes after the above exception throwings in the same block
		double mpg0 = m/g0; //zsh: floating point exception 

	}catch(const int &caught){ //best practice: throw by value, catch by reference or const
		//throw object, not primitive
		//Can throw from a constructor, especially since they don't return a boolean to indicate an error
		//Do not throw exceptions from destructors
		cerr << "Caught this int: " << caught << endl; //g == 0
	}
	catch (string &s){
		cerr << "Caught this string: " << s << endl; //g == -1
	}
	catch (const char *s){
		cerr << "Caught this const char *: " << s << endl; //g == -2
	}
	catch (...){//catch anything else, allegedly
		cerr << "Caught unknown exception." << endl; //not actually caught by the mpg0 calculation
	}
/**/
	
	for (int i = 0; i <= 2; i++){
		try{
			cout << "before throwsExceptions" << endl;
			throwsExceptions(i);
			cout << "after throwsExceptions" << endl;
		}
		catch(const exception &e){
			cerr << "caught exception 3; what(): " << e.what() << endl;
			// virtual const char *what() const noexcept is implemented by every concrete child of std::exception
		} /* Multiple types of exceptions */
		catch(int &ex){
			cerr << "caught exception 2" << endl;
		}
	}/**/
	
	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void throwsExceptions(int i) {
	cout << "before throw; i = " << i << endl;
	if (i==0) {
		throw exception();//1
	}
	else if (i==1) {
		throw returnsMyException(); //2
	}
	else {
		throw 0;
	}
	cout << "after throw" << endl;
}

MyException returnsMyException(){
	//could return a pointer to an exception, but that's not what is thrown in best practice
	return MyException();
}

void overflow_underflow(){
	cout << "Testing overflow and underflow: " << endl;
	float largeNumber = numeric_limits<float>::max();
	float result = largeNumber * 2; // overflow: inf
	cout << "Overflow result: " << result << endl;
	
	float smallNumber = numeric_limits<float>::min();
    result = smallNumber / largeNumber; //underflow: 0
	cout << "Underflow result: " << result << endl;
}