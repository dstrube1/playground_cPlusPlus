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
/**/
	
	try{
		int i = 1;
		int j = 0;
		cout << "before assigning k...\n";
		throw 0; //without this, the exception isn't caught
		double k = i/j;
		cout << k;
	}
	catch(exception e){
		cout << "caught exception 1" << endl;
	}
	catch(int &ex){
		cout << "caught exception 1.1" << endl;
	}
/**/
	
	for (int i = 0; i < 2; i++){
		try{
			cout << "before throwsExceptions" << endl;
			throwsExceptions(i);
			cout << "after throwsExceptions" << endl;
		}
		catch(exception e){
			cout << "caught exception 3" << endl;
		}/*Multiple types of exceptions*/
		catch(int &ex){
			cout << "caught exception 2" << endl;
		}/**/
	}
	
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