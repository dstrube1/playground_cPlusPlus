#include <iostream>
#include <string>
#include <vector>
//#include <cstring> 
//^contains functions for c-style strings like strlen, strcpy, and strcat; 
//but also included in std (or <string>?)

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -std=c++11 -o L7.o L7.cpp
# without -o, outputs to default a.out
# without the -std=c++11, multiple errors for lines with this:
# : str{nullptr} {

# To run:
./L7.o

*/

//Operator overloading
/*
These operators cannot be overloaded:
:: (scope resolution)
:? (conditional)
.* (pointer to member)
. (dot)
sizeof

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN Mystring
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mystring{
	private:
		char *str; //C-style string
	public:
		Mystring();
		Mystring(const char *s);
		Mystring(const Mystring &source);
		Mystring( Mystring &&source);
		~Mystring();
		void display() const;
		int get_length() const;
		const char *get_str() const {return str;}
	//assignment operator overloading syntax:
	//Type &operator=(const Type rhs);
		Mystring &operator=(const Mystring &rhs);
		Mystring &operator=(Mystring &&rhs);
};


Mystring::Mystring() 
	: str{nullptr} {
	//str = "";
	//warning: ISO C++11 does not allow conversion from string literal to 'char *' [-Wwritable-strings]
	str = new char[1];
	*str = '\0';
	cout << "default Mystring constructor" << endl;
}

Mystring::Mystring(const char *s) 
	: str {nullptr} {
	cout << "single param constructor... ";
	if (s == nullptr) {
		str = new char[1];
		*str = '\0';
		cout << "param is null" << endl;
	} else {
		str = new char[strlen(s) + 1];
		strcpy(str, s);
		cout << "param is copied: " << s << endl;
		}
}

Mystring::Mystring(const Mystring &source) 
	: str{nullptr} {
	str = new char[strlen(source.str ) + 1];
	strcpy(str, source.str);
	strcat(str, " copy");
	cout << "copy constructing " << str << endl;
}

Mystring::Mystring( Mystring &&source) 
    :str(source.str) {
        source.str = nullptr;
        cout << "move constructing " << str << endl;
}

Mystring::~Mystring(){
	//Must deallocate memory that's been allocated
	if (get_length() == 0){
		cout << "destructing [empty]" << endl;
	}else{
		cout << "destructing " << str << endl;
	}
	delete [] str;
}

void Mystring::display() const{
	if (get_length() == 0){
		cout << "[empty] : ";
	}else{
		cout << str << " : ";
	}
	cout << get_length() << endl;
}

int Mystring::get_length() const{
	return strlen(str);
}

/*
Weird, compiler doesn't like this implemented here; must be implemented in class declaration.
const char Mystring::*get_str() const{
	return str;
}*/

//Assignment operator overloading - copy
Mystring &Mystring::operator=(const Mystring &rhs){
	//rhs: right-hand-side object
	
	//Check for self assignment
	if (this == &rhs) return *this;
	
	//Deallocate storage for this->str since it's pointing to a string on the heap
	delete [] this->str; //"this->" makes it clearer, but is not required; could just as well do:
	//delete [] str;
	
	//Allocate storage on the heap for deep copy
	str = new char[strlen(rhs.str) + 1]; //+1: space for the string terminator
	
	//Perform the copy
	strcpy(str, rhs.str);
	
	//Return the current reference to allow chain assignment
	return *this;
}

//Assignment operator overloading - move
Mystring &Mystring::operator=(Mystring &&rhs){
	// && : r-value reference
	//used like:
	//Mystring s1 = "Frank";
	//or
	//Mystring s1 = Mystring{"Frank"}
	cout << "Assignment operator overloading - move\n";

	if (this == &rhs) return *this;

	delete [] str;
	str = rhs.str;
	rhs.str = nullptr;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END Mystring
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
/**/
	//These are initializations, not assignments:
	Mystring empty;
	//->		Mystring();
	Mystring original("original");
	//->		Mystring(const char *s);
	Mystring copy {original};
	//->		Mystring(const Mystring &source);
	
	empty.display();
	original.display();
	copy.display();
	
	//also not assignment; same as Mystring s1 {copy}
	Mystring s1 = copy;
	
	s1.display();
	
	//this is assignment:
	cout << "Testing copy assignment...\n";
	s1 = original;
	
	s1.display();
	
	//Before overloading the assignment operator:
	//Creating s1 from copy causes the destructor to fail after both are destroyed; 
	//this is due to the copy constructor being a shallow copier;
	//might be helpful to add a try / catch to the destructor;
	//better solution: override the assignment operator to do a deep copy
	
	cout << "Testing move assignment...\n";
	Mystring s2;
	s2 = "Frank";
	//Getting error here^:
	//zsh: segmentation fault  ./L7.o
	//But no error when compiling running this:
	//cd /Users/dstrube/Downloads/Section14/Mystring-move-assignment
	//g++ -std=c++11 -o main.o main.cpp Mystring.cpp
	//./main.o
	
	//Maybe because we have no move constructor?...
	
	//Mystring s3;
	//s3 = Mystring{"Blah"};

	
	cout << "Done\n";
	
	return empty.get_length();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**/