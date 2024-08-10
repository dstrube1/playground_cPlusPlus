#include <iostream>
#include <string>
//#include <typeinfo>
//#include <climits>
//#include <cfloat>
#include <vector>

#define bad_const = 5;

using namespace std;

//compiling and running
/*
# To compile:
# most basic:
g++ -o main.o main.cpp
# without -o, outputs to default a.out

# show all warnings and compile with c++14:
g++ -Wall -std=c++14 -o main.o main.cpp

# compile verbosely:
g++ -v -o main.o main.cpp

# version number specifying is required for some types of array declarations, 
# as described below
g++ -std=c++14 -o main.o main.cpp

# To run:
./main.o

*/

//externs and globals
/*
extern int ex;

int global; // automatically initialized to 0
double global_d;
*/

int main()
{
  cout << boolalpha; //make bools print out as true or false
  //cout << noboolalpha; //default bool outut as 0 or 1

  //initialization, concatenation, cout, cerr, clog, cin
  /*
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
  */

  //local v global, int / long / double printing / overflow
  /*
  int local, i; // may or may not be automatically initialized to 0
  string x; 
  double d;
//20 billion
//ticks marks added in C++14
//  int big_number = 20'000'000'000; // -1474836480
//  long big_number = 20'000'000'000; // 20000000000
//  double big_number = 20'000'000'000; // 2e+10

  //cout << "Uninitialized global 1: " << global << "; uninitialized global 2: " << global_d << "; uninitialized local 1: " << d << "; uninitialized local 2: " << local << endl;
  //cout << "Here's a big number: " << big_number <<endl;
  */

  //sizeof, maxs and mins
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

  //Arrays 
  /* 
  //most of these work on https://cpp.sh/  (except of course arr5), but not when compiling locally on my Mac with just "g++ -o main.o main.cpp", where only arr4 compiles.
  //However, compiling with specifying the c++ version number (like "g++ -std=c++14 -o main.o main.cpp" or "g++ -std=c++17 -o main.o main.cpp") works
  const int size = 2;

  int arr1 [5] {0,1,2,3,4};	//declare and initialize array with literal size
  int arr2 [size] {0,1}; //declare and initialize array with const size
  int arr3 [] {1,2,3}; //initialize array so that size is inferred
  int arr4 [size]; //legal to declare without initializing as long as there is size
  //int arr5 []; //illegal to declare without size AND without initializing
  //if initialize an array with empty braces, then it will be filled with 0s:
  int arrEmpty[size] {};

  for (int i = 0; i < size; i++){
  	arr4[i] = i;
  }
  for (int i = 0; i < size; i++){
  	cout << "arr4[" << i << "] = " << arr4[i] << "; ";
  }
  cout << endl;
  cout << "Testing out of bounds... \n";
  //int test = arr4 [size]; //This gives a warning when compiling, but no error when running
  for (int i = size; i < size * 10; i++){
  	cout << "arr4[" << i << "] = " << arr4[i] << "; ";
  	if (i % 12 == 0) cout << endl;
  }
  cout << endl;
  short size0; 
  size0 = sizeof(arr4);
  cout << "Size of arr4: " << size0 << endl; // 8, 4 * const int size (2)
  int arr5 [100];
  size0 = sizeof(arr5);
  cout << "Size of arr5: " << size0 << endl; // 400, 4 * 100
  //What if I try to cin outside of bounds
  //cout << "Enter a number please: ";
  //cin >> arr4[2]; //no crash, just a warning from the compiler
  int arr2Da [size][size]{{}}; //2x2, filled with 0s
  for (int i = 0; i < size; i++){
  	for(int j = 0; j < size; j++){
  		arr2Da[i][j] = i + j;
  		cout << "arr2Da[" << i << "][" << j <<"] = "<< arr2Da[i][j] << "\n";
  	}
  }
  int test[0];
  */

  //vectors
  /*
  vector <char> vchars {'a', 'e', 'i', 'o', 'u'}; //initializing with values
  vector <int> vints (10); //initializing with size
  vector <int> vints0 (10, 1); //initializing with size & all default values
  //initializing with () & {} is not allowed
  
  int size;
  size = sizeof(vchars);
  cout << "Sizeof empty vector of chars: " << size << endl;
  size = sizeof(vints);
  cout << "Sizeof empty vector of ints: " << size << endl;
  //^both are 24 (bytes?) by default
  
  cout << "Actual size of empty vector of ints: " << vints.size() << endl;
  //from https://cplusplus.com/reference/vector/vector/
  cout << "Max size of empty vector of ints: " << vints.max_size() << endl;
  cout << "Capacity of empty vector of ints: " << vints.capacity() << endl;
  
  for(int i = 0; i < 100; i++){
  	vints[i] = i;
  	//This will halt at the limit of the vector actual size: 10
    //cout << "vints.at("<<i<<"): "<<vints.at(i)<<"\n";
    //This will go as far as you like:
    //cout << "vints["<<i<<"]:"<<vints[i]<<"\n";
    
    //If you put this before calls to at (or even after), then the above limit 
    //won't apply because this actually grows the vector
  	//vints.push_back(i * 2);
  }
  //Testing bounds
  //cout << "Enter a letter: ";
  //cin >> vchars.at(6); //Before the program stops to wait for user input here:
  //"libc++abi: terminating with uncaught exception of type std::out_of_range: vector"

  //using .at() function:
  //This similarly crashes:
  //vints.at(size) = size;
  //size = sizeof(vints);
  //cout << "Size of filled vector of ints: " << size << endl;//no change, still 24
  
  //2D vector
  vector<vector<int>> vints2d
  	{
  		{1,2,3,4},
  		{1,2,3},
  		{1,2,3,5}
  	};
  size = sizeof(vints2d);
  cout << "Sizeof 2d vector of ints: " << size << endl;
  cout << "2d vector of ints.size: " << vints2d.size() << endl;
  cout << "2d vector of ints[0].size: " << vints2d[0].size() << endl;
  cout << "2d vector of ints[1].size: " << vints2d[1].size() << endl;
  cout << "2d vector of ints.max_size: " << vints2d.max_size() << endl;
  */

  //extern, warning, and error
  /*
  //extern ex isn't defined here, or anywhere, so the build throws a linker error, but only if we try to use ex
  //cout << "ex is " << ex << endl;

  //this throws a warning, but not an error
  //int y = 1 / 0;
  //what if I try to print it out?
  //cout << "y is " << y << endl;
  //Floating point exception (core dumped)
  */
  
  //int max via brute force
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
	printf("Max of int found : %li\n", count);
  */

  //auto keyword and typeid
  /* 
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
  
	//Modulo and casting
  /* 
	char f1 = 'y'; //1.5f; //float and double with % => error
	int f2 = 2.0f; //long are fine; char is allowed but may give confusing answers; and bool is allowed but will likely give confusing answers
	float f3 = f1 % f2;
	cout << "f3: " << f3 <<endl;

	//using static_cast
	f3 = static_cast<float> (f1) / f2;
	//old style casting:
	//f3 = (float)f1 / f2; //works, but doesn't do the checking that static_cast does
	cout << "f3: " << f3 <<endl;

	//these are fine, for some reason
	int f0 = 1.5; 
	bool f4 = 3;
	char f5 = 1.5f; 
  */
	
	//Three-way comparison operator, available in c++ 20:
  /* 
	//g++ -std=c++20 -o main.o main.cpp
	int f6 = -1;
	int f7 = 1;
	strong_ordering so = f6 <=> f7;
	cout << "f6 <=> f7 : [can't print a strong_ordering; how to use it? hope to learn this someday...]" << endl;
	//Not compilable on Rocky Linux laptop, but is compilable on Macbook Pro. Still not able to print the strong_ordering variable
  */

	//Logical operators
  /* 
	bool b0 = true;
	bool b1 = !b0;	
	bool b2 = not b0;
	bool b3 = b0 and b1;
	bool b4 = b0 && b1;
	bool b5 = b0 or b1;
	bool b6 = b0 || b1;
	cout << "b1: " << b1 << "; b2: " << b2 << "; b3: " << b3 << "; b4: " << b4 << "; b5: " << b5 << "; b6: " << b6 << endl;
  */

  cout << "Done\n";
  return 0;
}
