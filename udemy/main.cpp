#include <iostream>
#include <string>
//
#include <vector>
#include <iomanip>
#include <cstring> //strcpy, strcat, strlen, strcmp
#include <cctype> //character-bsaed functions
#include <cmath> //required for sqrt() & abs()
#include <cstdlib> //required for rand(), converting c-style strings to numbers
#include <ctime> //required for time()

using namespace std;

//compiling and running
/*
# To compile:
# most basic:
g++ -o main.o main.cpp
# without -o, outputs to default a.out

# show all warnings and compile with c++14:
g++ -Wall -std=c++14 -o main.o main.cpp

#just compile with c++14:
g++ -std=c++14 -o main.o main.cpp

# compile verbosely:
g++ -v -o main.o main.cpp

# version number specifying is required for some types of array declarations, 
# as described below
g++ -std=c++14 -o main.o main.cpp

# To run:
./main.o

*/

//void pass_by_ref(int &num);
//void pass_vec_by_ref(const vector<int> &v);
//void static_test();
inline int add(int a, int b) { return a + b; }
//unsigned long long factorial(unsigned long long n);
//double a_penny_doubled_everyday(int days, double total_amount );
//void double_target(int *ptr);
//int *largest(int *ptr1, int *ptr2);
//int *make_array(size_t size, int initial_value = 0); //default parameter


int main()
{
	//This requires #include <iomanip>
	cout << fixed << setprecision(2);
	
	cout << boolalpha; //make bools print out as true or false
	//cout << noboolalpha; //default bool outut as 0 or 1

	//Pointers
	int i = 10;
	int *i_ptr = &i; //&: address; *: declare pointer
	//interesting, when compiling on Mac, this gives a compiler error:
	//int *i_ptr {&i};
	cout << "value of i: " << i << endl;
	cout << "address of i: " << &i << endl;
	cout << "value of i (from i_ptr): " << *i_ptr << endl; //*: dereference pointer
	cout << "address of i (from i_ptr): " << i_ptr << endl;
	(*i_ptr)++;
	cout << "i after (*i_ptr)++ (must use parentheses) : " << i << endl;
	
  cout << "Done\n";
  return 0;
}

void old_tests(){
	
	//for loops
	/*
	//this is valid and endless:
	//for(;;){cout<<".";}
	
	//what about just initialization (1st) and change (3rd), no 2nd step (test)?
	//Yes:
	for (int i = 1;;i++){
		//Remember: must compile with c++14 to get tick marks in numbers
	
		//this doesn't seem to overflow and is endless unless there's a break within
		if (i % 10'000'000 == 0) {
			// this batches up a while and then prints out a bunch at once
			cout<<".";
		}
		
		if (i % 100'000'000 == 0) {		
			break; 
		}
	}
	cout<<"Broke out\n";
	
	//range-based for loop
	int arr[] = {1,2,3};
	for (auto i : arr){
		cout << i << " ";
	}
	cout << endl;
	
	vector <int> vints {1,2,3,4};
	for (auto i : vints){
		cout << i << " ";
	}
	cout << endl;
	
	//also works on collections of characters, aka strings
	string str = "test";
	for(auto c : str){
		cout << c << " ";
	}
	cout << endl;
	*/	

	//Letter Pyramid 
	/*string input {};
	cout << "Enter some string: ";
	getline(cin, input);
	for(int i=0; i < input.length(); i++){
		for(int j = 1; j < input.length() - i; j++)
			cout << " ";
		for(int k = 0; k <= i; k++)
			cout << input.at(k);
		if(i > 0){
			for (int h = i - 1; h >= 0; h--)
				cout << input.at(h);
		}
		cout << endl;
	}*/

	//C-style string
	/*
	//char ok[]; //is it okay to declare a c style string with no size specified and no initialization? no
	char ok[] = "okay"; //what about no size specified and initialization? yes
	cout << "size of ok[] ''okay'': " << sizeof(ok) << endl;
	size_t size = sizeof(ok); //the proper datatype of sizes
	//https://en.cppreference.com/w/cpp/types/size_t
	char ok0[size]; //is this okay? yes
	char test [8];
	cout << "test before assignment:'" << test << "'" << endl;
	//test="blah";//error: incompatible types in assignment of ‘const char [5]’ to ‘char [8]’
	//test = "blah123";//same size, still error: invalid array assignment
	strcpy(test, "blah");//OK; defined here: #include <cstring>
//	strcpy(test, "blahblahblah");//copying to out of bounds (with compiler warning) - works but potentially dangerous

	strcat(test, "12345"); //concatenate
	cout << "test:'" << test << "'" << endl;
	int length = strlen(test); //concatenating can safely affect length
	cout << "length: " << length << endl;
	int compare = strcmp(test, "test"); // compare
	cout << "compared to 'test': " << compare << endl;
	char line[4];
	cout << "enter some text for line[4] (using getline(line,5)): ";
	cin.getline(line,5); //getline's 2nd parameter specifies the length it will get up to; 
	//if the value of the 2nd parameter is greater than the size of the cstyle string, it will stop at the size of the cstyle string
	//just using 'cin >> line' stops reading at whitespace; getline does not stop at whitespace
	cout << "you entered: " << line << endl;
	*/

	//C++ String
	/*
 	string s = "test";
	s = s.substring(start_index, length);
	int i = s.find(s1);
	int j = s.find(s1, start_index);
	int k = s.rfind(...
	cout << "in string s ('test'), index of '': " << s.find("") << endl; //0
	cout << "string::npos: " << string::npos << endl; // 18446744073709551615, or 18,446,744,073,709,551,615, ~18 quintillion
	//s.erase(start_index, length);
	//s.clear(); //empties the string
	string s0 = {s, 1, 2};
	s = s + "def"; //ok
	//s = "123" + "456" + s; //compiler error
	s = s + "123" + "456"; //no compiler error

	cout << "s: " << s << endl;
	cout << "s0: " << s0 << endl;
 	*/
	
	//pretty sure this'll crash:
	//char crash[string::npos];
	//nope, won't even build: error: size of array ‘crash’ is negative
	//todo: char crash[math.abs(string::npos)];

	//Maths
	/*cout << "sqrt(400.0): " << sqrt(400.0) << endl;
	
	long double nposLD = string::npos; 
	cout << "absolute value of string::npos as long double: " << abs(nposLD) << endl; //1.84467e+19

	long long int nposLLI = string::npos; 
	cout << "absolute value of string::npos as long long int: " << abs(nposLLI) << endl; // = 1

	long long unsigned nposLLU = string::npos; 
	cout << "string::npos as long long unsigned: " << nposLLU << endl; 
	cout << "abs(string::nposLLU): error: call of overloaded ‘abs(long long unsigned int&)’ is ambiguous" << endl; 
	
	//just declaring this doesn't seem to do any harm
	short arr[nposLLU];

	int a = -1;
	int b = -1;
	cout << "-1 + -1 = " << a + b << endl;*/

	//more getline stuff:
	//getline(cin, s); //read line from cin stream into s until \n
	//getline(cin, s, 'x'); //read line until \n or 'x'

	//Random and time
	/*
//#include <cstdlib> //required for rand()
//#include <ctime> //required for time()
	cout << "RAND_MAX here is: " << RAND_MAX << endl; // 2,147,483,647 =~ 2 billion; guaranteed to be at least 32,767
	const int min = 1; //lower bound (inclusive)
	const int max = 100; //upper bound (inclusive)
	int random_number;
	const int count = 10;
	//seed the random number generator
	srand(time(nullptr));
	cout << "time(nullptr): " << time(nullptr) << endl;
	cout << count << " random numbers: ";
	for (int i=0; i < count; i++){
		random_number = rand() % max + min;
		cout << random_number << " ";
	}
	cout << endl;
	*/
	
	/*int i = 0;
	cout << "i before passByRef: " << i << endl;
	pass_by_ref(i);
	cout << "i after passByRef: " << i << endl;

	static_test();
	//cout << "is i0 accessible here?" << i0; no
	static_test();*/

	/*
 	cout << "52! = " << factorial(52) << endl; // 9994050523088551936 = 9,994,050,523,088,551,936 = almost 10 quintillion; but maybe not:
	cout << "53! = " << factorial(53) << endl; // 13175843659825807360
	cout << "54! = " << factorial(54) << endl; // 10519282829630636032
	cout << "55! = " << factorial(55) << endl; // 6711489344688881664
	for (unsigned long long i = 0; i < 100; i++){
		cout << i << "! = " << factorial(i) << endl; 
	} //https://zeptomath.com/calculators/factorial.php?number=52&hl=en

	int days = 25; 
	double total_amount = 0.01;
	//total_amount = a_penny_doubled_everyday(days, total_amount);
	//cout << "total_amount = " << total_amount << endl;

*/

	//Pointers and references
	/*
 	int i1 = 1;
	int i2 = 2;
	int *ptr1 {&i1};
	int *ptr2 {&i2};
	//two ways to swap two pointers without using a 3rd variable:
	//1:
	*ptr1 = *ptr1 + *ptr2;
	*ptr2 = *ptr1 - *ptr2;
	*ptr1 = *ptr1 - *ptr2;
	//2:
	std::swap(*ptr1, *ptr2);

	//pointer to a constant: cannot change the value of the thing pointed to, but can change what the pointer points to
	const int *ptr3 {&i1};
	//*ptr3 = 3; //compiler error
	ptr3 = &i2; //OK
	//const pointer:
	int *const ptr4 {&i1};
	//ptr4 = &i2; //compiler error
	*ptr4 = 3; //OK
	//const pointer to a constant:
	const int *const ptr5 {&i1};
	//ptr5 = &i2; //compiler error
	//*ptr5 = 3; //compiler error
	
	cout << "Before doubling: " << i1 << endl;
	double_target(&i1); // pass in the address of the target, i.e. pass by reference
	cout << "After doubling: " << i1 << endl;

	int *largest_ptr = {nullptr};
	largest_ptr = largest(&i1, &i2);
	cout << "Returning a pointer from a function: " << *largest_ptr << endl;

	int *my_arr;
	my_arr = make_array(10);
	//use it, then
	delete [] my_arr;

	int *test_ptr {nullptr};
	//delete test_ptr; //what happens? nothing
	//what about this instead?:
	//cout << "dereferenced null pointer: " << *test_ptr << endl; // = Segmentation fault (core dumped)

	//References - like a pointer, but different: must be initialized at creation, and cannot be null, like a constant pointer that is automatically dereferenced
	vector<string> test {"1","2","3"};
	for (auto str : test) str = "4";
	for (auto str : test) cout << str << " ";
	cout << endl; //no change
	for (auto &str : test) str = "4";
	for (auto str : test) cout << str << " ";
	cout << endl; //all changed
	//for (auto const &str : test) str = "4"; //<- compiler error; this is good if only displaying the contents without incurring the cost of copying each element into a temp variable
	//references must be assigned to l-values, cannot be assigned to r-values
	//int &ref = 100; //compiler error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
	//same if function f is expecting a reference- cannot pass in an r-value
 
 */

}

/* 
void pass_by_ref(int &num){
	num++;
}

void pass_vec_by_ref(const vector<int> &v){
	//pass collections by reference because they're not all small
	for(auto i : v){}
}
void static_test(){
	static int i0 = 0;
	cout << "i0 before increment: " << i0 << endl;
	i0++;
	cout << "i0 after increment: " << i0 << endl;
}

//recursive function #1
unsigned long long factorial(unsigned long long n){
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

//recursive function #2
double a_penny_doubled_everyday(int days, double total_amount) {    
	cout << "day " << days << ", total amount = " << total_amount << endl;
    if (days <= 1) return total_amount;
    total_amount = total_amount * 2;
    total_amount += a_penny_doubled_everyday(--days, total_amount);
    return total_amount;
 }

 //passing a pointer to a function
void double_target(int *ptr){
	*ptr *= 2;
	//no need to return anything
}

//returning a pointer from a function
int *largest(int *ptr1, int *ptr2){
	if (*ptr1 > *ptr2) return ptr1;
	else return ptr2;
}

//returning dynamically allocated memory from the heap
int *make_array(size_t size, int initial_value){
	int *new_arr {nullptr};
	new_arr = new int[size];
	for (size_t i = 0; i < size; i++){
		*(new_arr + i) = initial_value;
		//or use subscript notation like this:
		//new_arr[i] = initial_value;
	}
	return new_arr;
}

//TODO: revisit lesson 148 at 4:21
Shallow::Shallow(const Shallow &source) : data(source.data) {
	cout << "Copy constructor - shallow" << endl;
	//Shallow copy - only the pointer is copied - not what it is pointing to.
	//source and the newly created object both point to the same data area.
	//When a copied pointer goes out of scope, it is destroyed.
	//When the copy pointer is destroyed, the source pointer is no longer valid
}

int main(){
	Shallow obj{100};
	display_shallow(obj); //crash here?
	// obj's data has been released
	obj.set_data(1000); //or here?
	Shallow obj0 {obj}; //or here?
	cout << "Still alive?" << endl;
	return 0;
}

//TODO: revisit lesson 149 at 1:37
Deep::Deep(const Deep &source){
	data = new int;
	*data = *source.data;
	cout << "Copy constructor - deep" << endl;
}

//Deep copy constructor - delegating constructor
Deep:Deep(const Deep &source) : Deep{*source.data} {
	cout << "Copy constructor - deep & delegated" << endl;
}

//TODO: make folder "constructors" to explore lessons 148-150
Also, in lesson 150, around 14:50 - noexcept? Was this explained, and if so when?
https://en.cppreference.com/w/cpp/language/noexcept
https://stackoverflow.com/questions/10787766/when-should-i-really-use-noexcept
*/

