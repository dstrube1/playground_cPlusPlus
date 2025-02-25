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
what() //?

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

void throwsExceptions(int i);
exception *returnsException();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//First pass at exception throwing
	int m = 1;
	int g = -3;
	//double mpg = m/g; //zsh: floating point exception 
	//double mpg = static_cast<double> (m)/g; //inf
	//double mpg = static_cast<double> (-m)/g; //-inf
	double mpg = static_cast<double> (0)/g; //nan
	cout << "mpg: " << mpg << endl; 
	cerr << "This is the error stream\n";
	try{
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
		double mpg0 = m/g0; //zsh: floating point exception 

	}catch(int &caught){ //best practice: catch by reference
		cout << "Caught this: " << caught << endl; //g == 0
	}
	catch (string &s){
		cout << "Caught this: " << s << endl; //g == -1
	}
	catch (const char *s){
		cout << "Caught this: " << s << endl; //g == -2
	}
	catch (...){//catch anything else, allegedly
		cerr << "Caught unknown exception." << endl; //not actually caught by the mpg0 calculation
	}
/** /
	
	for (int i = 0; i < 2; i++){
		try{
			cout << "before throwsExceptions" << endl;
			throwsExceptions(i);
			cout << "after throwsExceptions" << endl;
		}
		catch(exception e){
			cout << "caught exception 3" << endl;
		}/*Multiple types of exceptions* /
		catch(int &ex){
			cout << "caught exception 2" << endl;
		}
	}/**/
	
	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void throwsExceptions(int i){
	cout << "before throw" << endl;
	if(i==0)
		throw new exception;//1
	else if (i==1)
		throw returnsException(); //2
	else 
		throw 0;
	cout << "after throw" << endl;
}

exception *returnsException(){
	return new exception;
}