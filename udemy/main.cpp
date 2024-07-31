#include <iostream>
#include <string>
#include <typeinfo>
#include <climits>
#include <cfloat>

#define bad_const = 5;

using namespace std;

/*
# To compile:
# most basic:
g++ -o main.o main.cpp
# without -o, outputs to default a.out

# show all warnings and compile with c++14:
g++ -Wall -std=c++14 -o main.o main.cpp

# compile verbosely:
g++ -v -o main.o main.cpp

# To run:
./main.o

*/

extern int ex;

int global; // automatically initialized to 0
double global_d;

int main()
{
  /**/
  //Testing assignment at initialization
  string name = "x";
  int local, i; // may or may not be automatically initialized to 0
  string x; 
  double d;
//20 billion
//ticks marks added in C++14
//  int big_number = 20'000'000'000; // -1474836480
//  long big_number = 20'000'000'000; // 20000000000
//  double big_number = 20'000'000'000; // 2e+10

  //cout << "What is your name? ";
  //getline (cin, name);
//alternatively:
  //cin >> name;
  
  //Testing string concatenation in both assignment and output
  name += "1";
  cout << "Hello from cout, " + name << "!\n";

  cerr << "Hello from cerr\n";
  clog << "Hello from clog\n";

  //cout << "Uninitialized global 1: " << global << "; uninitialized global 2: " << global_d << "; uninitialized local 1: " << d << "; uninitialized local 2: " << local << endl;
  //cout << "Here's a big number: " << big_number <<endl;

/*
  short size; //char is better for the range, but not as good for displaying the assigned values
  size = sizeof(char);
  cout << "sizeof(char): " << size << endl;
  size = sizeof(short);
  cout << "sizeof(short): " << size << endl;
  size = sizeof(int);
  int some_var;
  cout << "sizeof(int): " << size << endl;
  size = sizeof some_var;
  cout << "sizeof some_var (int): " << size << endl;
  size = sizeof(some_var);
  cout << "sizeof(some_var)(int): " << size << endl;
  size = sizeof(long);
  cout << "sizeof(long): " << size << endl;
  size = sizeof(long long);
  cout << "sizeof(long long): " << size << endl;
  size = sizeof(float);
  cout << "sizeof(float): " << size << endl;
  size = sizeof(double);
  cout << "sizeof(double): " << size << endl;
  size = sizeof(long double);
  cout << "sizeof(long double): " << size << endl;
  size = sizeof(double long);
  cout << "sizeof(double long): " << size << endl;

  string aString = "a string";
  size = sizeof aString;
  cout << "sizeof aString (string): " << size << endl;

  //These are defined in #include <climits>:
  cout << "CHAR_MAX: " << CHAR_MAX << "; CHAR_MIN: " << CHAR_MIN << "; SHRT_MAX: " << SHRT_MAX << "; SHRT_MIN: " << SHRT_MIN << "; UCHAR_MAX: " << UCHAR_MAX << "; USHRT_MAX: " << USHRT_MAX << endl; 
  cout << "INT_MAX: " << INT_MAX << "; INT_MIN: " << INT_MIN << "; LONG_MAX: " << LONG_MAX << "; LONG_MIN: " << LONG_MIN << endl;
//Unsigned MIN would be dumb
  cout << "UINT_MAX: " << UINT_MAX << "; ULONG_MAX: " << ULONG_MAX << "; LLONG_MAX: " << LLONG_MAX << "; LLONG_MIN: " << LLONG_MIN << endl; 
//LLONG_MAX == LONG_MAX ? 
  
  //These are defined in #include <cfloat>:
  cout << "FLT_MAX: " << FLT_MAX << "; FLT_MIN: " << FLT_MIN << "; DBL_MAX: " << DBL_MAX << "; DBL_MIN: " << DBL_MIN << endl;
  cout << "LDBL_MAX: " << LDBL_MAX << "; LDBL_MIN: " << LDBL_MIN << endl;

  //TODO: test sizeof with arrays and objects
*/

//leftoff: https://gbg.udemy.com/course/beginning-c-plus-plus-programming/learn/lecture/9535372#overview

/*
  cout << "What if I try to take in an int but you enter a non-int?: ";
  cin >> i;
  cout << "I got this for i: " << i << endl; //"blah" == 0; 123x = 123 now, and 0 later; 1.2 = 1 now, 0 later
  cout << "What about chaining cins (first i, then x)?: ";
  cin >> i >> x; //if non int is entered, then this cin is skipped; else it works properly
  cout << "I got this for i: " << i << ", and this for x: " << x << endl;
*/
  //extern ex isn't defined here, or anywhere, so the build throws a linker error, but only if we try to use ex
  //cout << "ex is " << ex << endl;

  //this throws a warning, but not an error
  //int y = 1 / 0;
  //what if I try to print it out?
  //cout << "y is " << y << endl;
  //Floating point exception (core dumped)
  
  /*cout << "Enter an int (10.5): ";
  cin >> i;
  cout << "Enter a float / double: \n";
  cin >> d;
  cout << "i is " << i << " and d is " << d <<endl;

  */
/*   
	//This takes a little while
	int i = 1;
	 int i_p = 0;
	 long count = 0;
	
	while (i_p < i){
		i++;
		i_p++;
		count++;
		if (count % 10000000 == 0)
			printf(".");
			//cout<<".";
	}
	printf("\n");
	printf("Max of int found : %li\n", count);*/

/* auto keyword and typeid
  auto a = 8;
  auto b = 12345678901;
  auto c = 3.14f;
  auto d = 3.14;
  auto e = true;
  auto f = 'd';
  auto g = "hello!";
  
  cout << "type of a: " << typeid(a).name() << "\n"; // i = int
  cout << "type of b: " << typeid(b).name() << "\n"; // x = long
  cout << "type of c: " << typeid(c).name() << "\n"; // f = float
  cout << "type of d: " << typeid(d).name() << "\n"; // d = double
  cout << "type of e: " << typeid(e).name() << "\n"; // b = bool
  cout << "type of f: " << typeid(f).name() << "\n"; // c = char
  cout << "type of g: " << typeid(g).name() << "\n"; // PKc = Pointer to Konstant char, aka, string
*/
	return 0;
}
