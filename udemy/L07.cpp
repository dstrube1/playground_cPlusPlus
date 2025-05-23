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
g++ -std=c++11 -o L07.o L07.cpp
# without -o, outputs to default a.out
# without the -std=c++11, multiple errors for lines with this:
# : str{nullptr} {

# To run:
./L07.o

*/

//Operator overloading
/*
These operators cannot be overloaded:
:: (scope resolution)
:? (conditional)
.* (pointer to member)
. (dot)
sizeof

To make a global operator overload function (ie, not member operator overload function), 
you may* have to declare the implementing class a friend of the class that is being 
affected by the overload. (See lesson 163 for details and example.) This seems a bit limited / contrived to me.
*: If not, then how?
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN Mystring
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mystring{
	//Overloading the extraction operator(>>)
	friend istream &operator>>(istream &is, Mystring &obj);

	private:
		char *str; //C-style string
	public:
		Mystring();
		Mystring(const char *s);
		Mystring(const Mystring &source);
		Mystring( Mystring &&source);
		~Mystring();
		void display() const;
		char* get() const;
		int get_length() const;
		const char *get_str() const {return str;}
	//assignment operator overloading syntax:
	//Type &operator=(const Type rhs);
		//copy assignment
		Mystring &operator=(const Mystring &rhs);
		//move assignment
		Mystring &operator=(Mystring &&rhs);
		//Note, assignment operator must be overloaded as a member function, cannot be friend / nonmember
	//Unary operator overloading (no parameter, unless is friend, in which 1 param):
		Mystring operator-() const;
		Mystring operator+() const;
	//Binary operator overloading (one parameter, unless is friend, in which 2 params):
		bool operator==(const Mystring &rhs) const;
		Mystring operator+(Mystring &rhs) const;
		Mystring &operator+=(Mystring &rhs);
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

char* Mystring::get() const { return str; }

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
	cout << "Mystring unary - operator: negation -> lower case\n";
	char *buff = new char[strlen(str) + 1];
	strcpy(buff, str);
	for (size_t i = 0; i < strlen(buff); i++){
		buff[i] = tolower(buff[i]);
	}
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

Mystring Mystring::operator+() const{
	//Trying my own thing
	cout << "Mystring unary - operator: plus -> upper case\n";
	char *buff = new char[strlen(str) + 1];
	strcpy(buff, str);
	for (size_t i = 0; i < strlen(buff); i++){
		buff[i] = toupper(buff[i]);
	}
	Mystring temp {buff};
	delete [] buff;
	return temp;
}

bool Mystring::operator==(const Mystring &rhs) const{
	cout << "Mystring binary == operator: equality\n";
	if (strcmp(str, rhs.str) == 0) return true;
	return false;
}

Mystring Mystring::operator+(Mystring &rhs) const {
	cout << "Mystring binary + operator: concatenation\n";
	size_t buff_size = strlen(str) + strlen(rhs.str) + 1;
	char *buff = new char[buff_size];
	strcpy(buff, str);
	strcat(buff, rhs.str);
	Mystring temp{buff};
	delete [] buff;
	return temp;
}

Mystring &Mystring::operator+=(Mystring &rhs){
	cout << "Assignment operator overloading: +=\n";
	strcat(str, rhs.str);
	rhs.str = nullptr;
	return *this;
	/*
	alternate implementation:
	*this = *this + rhs; //calls overloaded concatenate operator
	return *this;
	OR maybe this?:
	return *this + rhs;
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END Mystring
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN Number
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Number{
	friend bool operator >=(const Number &lhs, const Number &rhs) /*can't have const in a friend method*/;

	//Overloading the insertion operator(<<)
	friend ostream &operator<<(ostream &os, const Number &obj);
	//trying this as a non-friend didn't work as well

	private:
		int i;
	public:
		Number();
		Number(const int i0);
		~Number();
		int get() const;
	//Unary operator overloading:
		Number operator-() const;
		Number &operator++(); //++i : returns reference
		Number operator++(int /*i0*/); //i++ : returns by value
		//Note that ^this^ is an exception to unary operator overloading taking no parameter
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
	cout << "single param Number constructor...\n";
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
Number Number::operator++(int /*i0*/){ //note, parameter doesn't need to be named, just specified
	cout << "Unary operator overloading: ++(int) (post-increment)\n";
	Number n{*this}; //make a copy
	//i += 1; //or, 
	//i++; //or, even cooler:
	operator++(); //pre-increment the original value, which doesn't get returned
	//note, if implementing this as a friend / nonmember function, first param will be 
	//Number &obj, and at this point, calling pre-increment would be done like this:
	//++obj;
	return n; //return the old copy
}

/*bool Number::operator!() const {
	cout << "Unary operator overloading: !\n";

	//TODO
	return true;
}*/

//Binary operator overloading:
Number Number::operator+(const Number &rhs) const{
	//rhs = right hand side operand
	//this = left side operand
	cout << "Binary operator overloading: +\n";
	Number n{i};
	n.i += rhs.i;
	return n;	
}

Number Number::operator-(const Number &rhs) const{
	cout << "Binary operator overloading: -\n";
	Number n{i};
	n.i -= rhs.i;
	return n;	
}

bool Number::operator==(const Number &rhs) const{
	cout << "Binary operator overloading: ==\n";
	return i == rhs.i;
}

bool Number::operator<(const Number &rhs) const{
	cout << "Binary operator overloading: <\n";
	return i < rhs.i;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END Number
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//trying to overload an operator with a global function
bool operator>(const Number &lhs, const Number &rhs);

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
	
	cout << "empty.display(): ";
	empty.display();
	cout << "original.display(): ";
	original.display();
	cout << "copy.display(): ";
	copy.display();
	
	//also not assignment; same as Mystring s1 {copy}
	Mystring s1 = copy;
	cout << "s1.display(): ";
	s1.display();
	
	//this is assignment:
	cout << "Testing copy assignment...\n";
	s1 = original;
	cout << "s1.display(): ";
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
	
	if (s1 == original) cout << "s1 == original\n";
	else cout << "s1 (" << s1.get() << ") != original (" << original.get() << ")\n";
	
	s3 = +s3;
	cout << "s3.display(): ";
	s3.display();
	
	s3 = -s3;
	cout << "s3.display(): ";
	s3.display();
	
	s3 = s1 + s2;
	cout << "s3.display(): ";
	s3.display();
	
	
/**/
	//Other examples of overloading...
	/**/
	Number n1{100};
	Number n2 = -n1; 	//n1.operator-()
	cout << "n1: " << n1.get() << "; n2: " << n2.get() << endl;
	n2 = ++n1; 			//n1.operator++()
	cout << "n2 (++n1): " << n2.get() << "; n1: " << n1.get() << endl;
	n2 = n1++;			 //n1.operator++(int)
	cout << "n2 (n1++): " << n2.get() << "; n1: " << n1.get() << endl;
	Number n3 = n1 + n2;
	cout << "n3 (n1 + n2): " << n3.get() << endl;
	n3 = n1 - n2;
	cout << "n3 (n1 - n2): " << n3.get() << endl;
	if (n1 == n2){
		cout << "n1 == n2" << endl;
	}
	
	if (n3 < n1){
		cout << "n3 < n1" << endl;
	}
	if (n1 > n3){
		cout << "n1 > n3" << endl;
	}
	if (n1 >= n3){
		cout << "n1 >= n3" << endl;
	}
	
	cout << "n1 = " << n1 << endl;
	
	Mystring x{"123"};
	Mystring y{"456"};
	/*
	cout << "Now input a Mystring: ";
	cin >> x;
	cout << "You inputted; ";
	*/
	x += y;
	x.display();
	
	/**/
	
	cout << "Done\n";
	
	return 0;// empty.get_length();
}

bool operator>(const Number &lhs, const Number &rhs){
	cout << "Binary operator overloading with a global function: >\n";
	//return lhs.i > rhs.i;
	//This function can't access the private member of either lhs or rhs
	//Puzzle: how to declare main as a friend of Number?
	//Workaround: use getter of each
	return lhs.get() > rhs.get();
}

//let's try this with friendship
bool operator >=(const Number &lhs, const Number &rhs){
	//according to Lesson 163 at about 7:00, it's common practice to put the implementation 
	//of this in the implementation of the class (Number.cpp)
	cout << "Binary operator overloading with a global function using friendship: >\n";
	return lhs.i >= rhs.i;
}

ostream &operator<<(ostream &os, const Number &obj){
	cout << "\n(Overloading insertion (<<)...)\n";
	os << obj.i; //if friend function

	//if not friend - doesn't work as well as the friend way:
	//os << obj.get();
	
	//Don't return ostream by value
	return os;
}

//Doing this for Mystring instead, because it's more complicated and interesting
istream &operator>>(istream &is, Mystring &obj){
	char *buff = new char[1000];
	is >> buff;
	obj = Mystring{buff}; //if copy or move assignment is available
	delete [] buff;
	return is;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**/