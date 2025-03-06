#include <iostream>
#include <typeinfo>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -std=c++20 -o L02.o L02.cpp
# without -o, outputs to default a.out
# without -std=c++20, errors from strong_ordering and three-way comparison operator

# To run:
./L02.o

*/

int main()
{
  //auto keyword and typeid
  /* */
  auto a = 8;
  auto b = 12345678901;
  auto c = 3.14f;
  auto d = 3.14;
  auto e = true;
  auto f = 'd';
  auto g = "hello!";
  auto h = string::npos; // 18446744073709551615, or 18,446,744,073,709,551,615, ~18 quintillion
  
  cout << "type of a: " << typeid(a).name() << "\n"; // i = int
  cout << "type of b: " << typeid(b).name() << "\n"; // x = long
  cout << "type of c: " << typeid(c).name() << "\n"; // f = float
  cout << "type of d: " << typeid(d).name() << "\n"; // d = double
  cout << "type of e: " << typeid(e).name() << "\n"; // b = bool
  cout << "type of f: " << typeid(f).name() << "\n"; // c = char
  cout << "type of g: " << typeid(g).name() << "\n"; // PKc = Pointer to Konstant char, aka, string
  cout << "type of h: " << typeid(h).name() << "\n"; //m?
  /**/
  
	//Modulo and casting
  /**/ 
	char f1 = 'y'; //1.5f; //float and double with % => error
	int f2 = 2.0f; //long are fine; char is allowed but may give confusing answers; and bool is allowed but will likely give confusing answers
	float f3 = f1 % f2;
	cout << "f3: " << f3 <<endl;

	//using static_cast
	f3 = static_cast<float> (f1) / f2;
	cout << "f3: " << f3 <<endl;
	//old style casting:
	f3 = (float)f1 / f2; //works, but doesn't do the checking that static_cast does
	cout << "f3: " << f3 <<endl;

	//these are fine, for some reason
	int f0 = 1.5; 
	bool f4 = 3;
	char f5 = 1.5f; 
  /**/
	
	//Three-way comparison operator, available in c++ 20:
  /**/ 
	//g++ -std=c++20 -o main.o main.cpp
	int f6 = -1;
	int f7 = 1;
	strong_ordering so = f6 <=> f7;
	cout << "f6 <=> f7 : [can't print a strong_ordering; how to use it? hope to learn this someday...]" << endl;
	//Not compilable on Rocky Linux laptop, but is compilable on Macbook Pro. Still not able to print the strong_ordering variable
  /**/

	//Logical operators
  /* */
	bool b0 = true;
	bool b1 = !b0;	
	bool b2 = not b0;
	bool b3 = b0 and b1;
	bool b4 = b0 && b1;
	bool b5 = b0 or b1;
	bool b6 = b0 || b1;
	cout << "b1: " << b1 << "; b2: " << b2 << "; b3: " << b3 << "; b4: " << b4 << "; b5: " << b5 << "; b6: " << b6 << endl;
  /**/

	//Compound assignment
	/**/
	int a7 = 1;
	int b7 = 2;
	int c7 = 3;
	a7 *= b7 + c7; // == a7 = a7 * (b7 + c7) == 1 * (2 + 3) == 1 * 5 == 5
	cout<<"a(1) *= b(2) + c(3) = " << a7 << endl;
	/**/
	
	//Prefix vs postfix
	/**/
	int a8 = 1;
	int b8 = 1;
	int aPrefix = ++a8;
	int bPostfix = b8++;
	cout << "a(1) prefix increment: (++a): " << aPrefix << endl;
	cout << "b(1) postfix increment: (b++): " << bPostfix << endl;
	/**/
	
	//setprecision(2)
	/**/
	double a9 = 1;
	double b9 = 3;
	double c9 = a / b;
	double d9 = 1/3;
	cout << "with cout << fixed << setprecision(2): " << endl; //0.33
	cout << "c = a(1) / b(3): " << c9 << endl; //0.00
	cout << "d = 1/3: " << d9 << endl;
	/**/

	//Fall thru switch and enumeration
	/**/
	enum Color {red,blue,green};
	Color color = green;
	switch (color) {
		case green: cout << "color could be green\n";
		case blue: cout << "color could be blue\n";
			break;
		case red: cout << "color could be red\n";
		//case black: cout << "color could be black\n";
		//^ error: use of undeclared identifier 'black'
		default: cout << "color isn't red, blue, green, or black \n";
		
	}
	//Case expressions must be constant expressions 
	//that evaluate to integer or integer literal(?)

	//So no switch(string) case "hello":... ?
	//Chars evaluate to integers, but
	//no switch(float) case 1.5:...?
	string s = "hey";
	/*
	switch (s) {
		case "hi": cout<< s <<endl; break;
		case "hello": cout<< s <<endl; break;
		case "howdy": cout<< s <<endl; break;
		default: cout<< s <<endl; break;
	}
	//^ error: statement requires expression of integer type ('std::string' (aka 'basic_string<char, char_traits<char>, allocator<char> >') invalid)

	//note: typo in error: mismatched ()s

	float f = 0.1;
	switch (f) {
		case 0.2: cout<< f <<endl; break;
		case 0.3: cout<< f <<endl; break;
		case 0.4: cout<< f <<endl; break;
		default: cout<< f <<endl; break;
	}
	//^ similar error
	*/
	
  cout << "Done\n";
  return 0;
}