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
	//Wacky overloading:
		Mystring operator-() const;
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
	cout << "single param Mystring constructor... ";
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
	if (/*str == nullptr or */get_length() == 0){
		cout << "destructing [empty]" << endl;
	}else{
		cout << "destructing " << str << endl;
	}
	
	//Lesson learned: be careful calling get_length() or str here.
	//After move assignment, str of source is null
	//Solution 1: test first for str == nullptr before get_length() == 0
	//Solution 2: (better): add nullptr check to get_length()
	
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
	if (str == nullptr) return 0;
	
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
	
	cout << "Assignment operator overloading - copy\n";

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

Mystring Mystring::operator-() const{
	//lesson 162 @2:20
	//Not optimized, but drawn out to be clear
	//TODO - test this
	char *buff = new char[strlen(str) + 1];
	strcpy(buff, str);
	for (size_t i = 0; i < strlen(buff); i++){
		buff[i] = tolower(buff[i]);
	}
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END Mystring
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN Number
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Number{
	private:
		int i;
	public:
		Number();
		Number(const int i0);
		//Mystring(const Mystring &source);
		//Mystring( Mystring &&source);
		~Number();
		//void display() const;
		int get() const;
	//Unary operator overloading:
		Number operator-() const;
		Number &operator++();
		Number &operator++(int i0);
		bool operator!() const;
	//Binary operator overloading:
		Number operator+(const Number &rhs) const;
		Number operator-(const Number &rhs) const;
		bool operator==(const Number &rhs) const;
		bool operator<(const Number &rhs) const;
};


Number::Number() 
	: i{0} {
	cout << "default Number constructor" << endl;
}

Number::Number(const int i0) 
	: i {0} {
	cout << "single param Number constructor... ";
	i = i0;
}

Number::~Number(){
	cout << "Number destructor: " << i << "\n";
}


int Number::get() const{	
	return i;
}

//Unary operator overloading: - (negation)
Number Number::operator-() const {
	cout << "Unary operator overloading: - (negation)\n";
	Number n{i};
	n.i = -n.i;
	return n;
}

//Unary operator overloading: ++ (pre-increment)
Number &Number::operator++(){
	cout << "Unary operator overloading: ++ (pre-increment)\n";
	i = i + 1;
	return *this;
}

//Unary operator overloading: ++(int) (post-increment)
Number &Number::operator++(int i0){
	cout << "Unary operator overloading: ++(int) (post-increment)\n";
	//TODO
	return *this;
}

bool Number::operator!() const {
	cout << "Unary operator overloading: !\n";

	//TODO
	return true;
}

//Binary operator overloading:
Number operator+(const Number &rhs) const{
	//rhs = right hand side operand
	//this = left side operand
	Number n{i};
	n.i = -n.i;
	return n;	
}
Number operator-(const Number &rhs) const{
	//TODO
	return nullptr;
}
bool operator==(const Number &rhs) const{
	//TODO
	return true;
}
bool operator<(const Number &rhs) const{
	//TODO
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END Number
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
	//Was getting an error here^:
	//zsh: segmentation fault  ./L7.o
	//But no error when compiling running this:
	//cd /Users/dstrube/Downloads/Section14/Mystring-move-assignment
	//g++ -std=c++11 -o main.o main.cpp Mystring.cpp
	//./main.o
	
	//Maybe because we have no move constructor?...
	//No, the cause / solution was in the destructor
	
	Mystring s3;
	s3 = Mystring{"Blah"};

	//Other examples of overloading...
	Number n1{100};
	Number n2 = -n1; 	//n1.operator-()
	n2 = ++n1; 			//n1.operator++()
	n2 = n1++;			 //n1.operator++(int)
	Number n3 = n1 + n2;
	n3 = n1 - n2;
	if (n1 == n2){}
	
	cout << "Done\n";
	
	return empty.get_length();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**/