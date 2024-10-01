#include <iostream>
#include <string>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

//TODO: 
//1- Verify this still builds and runs
//2- Remove this code from main.cpp

#define bad_const = 5;

using namespace std;

//compiling and running
/*
# To compile:
# most basic:
g++ -o L0.o L0.cpp

# To run:
./L0.o

*/

//externs and globals
/*
extern int ex;

int global; // automatically initialized to 0
double global_d;
*/


int main()
{
    //initialization, concatenation, cout, cerr, clog, cin
  /**/
  //Testing assignment at initialization
  string name = "x";
  //cout << "What is your name? ";
  //getline (cin, name);
  //alternatively:
  //cin >> name;

  //Testing string concatenation in both assignment and output
  name += "1";
  cout << "Hello from cout, " + name << "!\n";

  cerr << "Hello from cerr\n";
  clog << "Hello from clog\n";
  
  cout << "Enter an int (10.5): ";
  cin >> i;
  cout << "Enter a float / double: \n";
  cin >> d;
  cout << "i is " << i << " and d is " << d <<endl;

  cout << "What if I try to take in an int but you enter a non-int?: ";
  cin >> i;
  cout << "I got this for i: " << i << endl; //"blah" == 0; 123x = 123 now, and 0 later; 1.2 = 1 now, 0 later
  cout << "What about chaining cins (first i, then x)?: ";
  cin >> i >> x; //if non int is entered, then this cin is skipped; else it works properly
  cout << "I got this for i: " << i << ", and this for x: " << x << endl;
  /**/

  //local v global, int / long / double printing / overflow
  /**/
  int local, i; // may or may not be automatically initialized to 0
  string x; 
  double d;
//20 billion
//ticks marks added in C++14
int big_number = 20'000'000'000; // -1474836480
long big_number_L = 20'000'000'000; // 20000000000
double big_number_D = 20'000'000'000; // 2e+10

  cout << "Uninitialized global 1: " << global << "; uninitialized global 2: " << global_d << "; uninitialized local 1: " << d << "; uninitialized local 2: " << local << endl;
  cout << "Here's a big number: " << big_number_L <<endl;
  cout << "Here's another big number: " << big_number_D <<endl;
  /**/

  //sizeof, maxs and mins
  /**/
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

	int i;
	cout << "Int input overflow test: enter a ridiculously big number, like 3 billion: ";
	cin >> i; // 3 billion = 2'147'483'647
	cout << "You entered " << i << endl;
	
  //TODO: test sizeof with arrays and objects
/**/
  cout << "Done\n";
  return 0;
}

