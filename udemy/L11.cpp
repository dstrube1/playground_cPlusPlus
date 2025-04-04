#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric> //required for accumulate
#include <utility> //required for std::pair
#include <list>
#include <map>
#include <set>
#include <cctype> //for ::toupper

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L11.o L11.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L11.o

Standard Template Library
Developed in 1994 by Alexander Stepanov
Containers, iterators, and algorithms (also functors and allocators, not covered here)
Containers:
	Sequence Containers (maintain ordering of elements):
		Array
		Vector
		List & forward list
		Deque
	Associative Containers:
		Set & multi set
		Map & multi map
	Container adapters (don't suport iterators, can't be used with STL <algorithm>):
		Stack & queue
		Priority queue
Iterators: forward, reverse, by value, by reference, constant, etc
Types of Iterators: input, output, forward, bi-directional, random access (subscript)
Algorithms (~60): find, max, count, accumulate (sum), sort, etc
Generic programming / meta-programming:
	preprocessor macros - be careful, especially with macros that take arguments; used more in C code
	function templates
	class templates
Macros:
	be careful, especially with macros that take arguments; 
	used more in C code
	example of a macro: #define PI 3.14159
	preprocessor first removes the macro at its definition and then replaces all instances of it in the program (not including instances in string literals); for example, this:
		#define PI 3.14159
		float p = PI;
	becomes this:
		//#define PI 3.14159
		float p = 3.14159;
	constants are better because they're typed (ie have a specified data type) and are known to the compiler
*/

//	example of a macro that take arguments:
#define MAX(a,b) ((a > b) ? a : b)
//example of macro that take arguments going wrong:
#define SQUARE(a) a * a
#define BETTER_SQUARE(a) (a * a)

void algorithmExamples();
void macroExamples();

void functionTemplateExamples();
//The following can also use 'class' instead of 'typename' - "essentially equivalent":
template <typename T> 
T maxFunctionTemplate(T a, T b){
	//this function is good for any type that supports the > operator, 
	//either natively or overloaded
	return (a > b) ? a : b;
}

//This can use more than 1 type
template <typename T1, typename T2> 
void typeTest(T1 a, T2 b){
	cout << "typeTest, where a is type " << typeid(a).name() << " and b is " << typeid(b).name() << endl;
}

void classTemplateExamples();

/*
Make this class generic so that value can be an int or double
Can't overload classes with the same name in the same namespace
class Item{
	private:
		int value;
		string name;
	public:
		Item(string name, int value) 
			: name{name}, value {value}
			{}
		int get_value() const {return value;}
		string get_name() const {return name;}
};
*/

template <typename T> 
class Item{
	//Note, template classes are usually completely contained in header (.h) files, no .cpp
	private:
		T value;
		string name;
	public:
		Item(string name, T value) 
			: name{name}, value {value}
			{}
		T get_value() const {return value;}
		string get_name() const {return name;}
};

//similarly for a struct:
template <typename T1, typename T2> 
struct TemplatedStruct {
	T1 first;
	T2 second; //can be the same or different type
};

template <typename T, int N> 
class GATC{ //Generic Array Template Class
	//initialized like this:
	//GATC<N> gatc;, where N is the size, not the type; this will be a non-type templated class
	//This is just for an example; if really need something like this, use std::array
	int size {N};
	T values[N];
	friend ostream &operator<<(ostream &os, const GATC<T, N> &arr){
		os << "[";
		for(const auto &val : arr.values){
			os << val << " ";
		}
		os << "]" << endl;
		return os;
	}
	public:
		GATC() = default;
		GATC(T init_val){
			for(auto &item : values) item = init_val;
		}
		void fill(T val){ for(auto &item : values) item = val; }
		int get_size() const { return size; }
		//overloaded subscript operator
		T &operator[](int index){ //is 'index' a reserved keyword?
			return values[index];
			//Usage: nums[i] 
			//which is(?) equivalent to: nums.operator[](i)
		}
};

void containersExamples();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	algorithmExamples();
	//macroExamples();
	//functionTemplateExamples();
	//classTemplateExamples();
	//containersExamples();
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

struct Square_Functor {
	void operator()(int x){ //overload () operator
		cout << x * x << " ";
	}
};

void square_function_pointer(int x){
	cout << x * x << " ";
}

void algorithmExamples(){
	//Simple example:
	vector<int> vec {1,5,3};
	cout << "vector before sorting:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	//Sort from beginning to end:
	sort(vec.begin(), vec.end());
	//Sort works on not just vectors
	//Also, can specify how to sort, like sort account objects by balance
	
	cout << "vector after sorting:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	//Reverse
	reverse(vec.begin(), vec.end());
	cout << "vector after reversing:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	//Accumulate - requires #include <numeric>
	int sum = std::accumulate(vec.begin(), vec.end(), 0);
	cout << "sum of vector:\n" << sum << endl;		
	
	//More:
	//https://en.cppreference.com/w/cpp/algorithm
	
	//All STL algorithms expect at least one iterator
	
	//The possibility of iterator invalidation is something to be aware of. For example:
	//while iterating over a collection, call clear(). Then what? 
	//Undefined; iterator will be unknowingly invalid, so be careful.
	
	//Find
	auto loc = find(vec.begin(), vec.end(), 3);
	if (loc != vec.end()) {//found it!
		cout << "found " << *loc << endl; 
		//find returns iterator pointing to the first found instance...
		//but where? loc is not the index, it's a pointer to the value
	}
	//This works for any container of objects that have '==' defined.
	//If using find on a container of custom objects of class C, then C must override operator==
	
	//for_each - applies function to each element
	//function must be provided as:
	//	functor (function object),
	//	function pointer,
	//	or lambda 
	Square_Functor square_functor;
	cout << "Squaring with a functor (aka function object): ";
	for_each(vec.begin(), vec.end(), square_functor);
	cout << endl;
	
	cout << "Squaring with a function pointer: ";
	for_each(vec.begin(), vec.end(), square_function_pointer);
	cout << endl;

	//Lambda - introduced in C++11, aka closure, block, and anonymous function
	cout << "Squaring with a lambda: ";
	for_each(vec.begin(), vec.end(), 
		[](int x) {cout << x * x << " ";}  //lambda
		);
	cout << endl;

	cout << "Original vector is unchanged: ";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	//Count
	int lookFor = 3;
	int num = count(begin(vec), end(vec), lookFor);
	cout << "Found '" << lookFor << "' " << num << " time(s)\n";
	lookFor = 4;
	num = count(begin(vec), end(vec), lookFor);
	cout << "Found '" << lookFor << "' " << num << " time(s)\n";
	
	//Count if (if some condition is met), using a lambda
	int num_evens = count_if(begin(vec), end(vec), [](int x){return x % 2 == 0;});
	int num_odds = count_if(begin(vec), end(vec), [](int x){return x % 2 != 0;});
	cout << "Found " << num_evens << " evens and " << num_odds << " odds\n";
	
	//Replace - affects container in place, replaces all found
	vec.push_back(1);
	replace(begin(vec), end(vec), 1, 2);
	cout << "Vector with 1 added, then replace 1 with 2: ";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	//all_of: returns true if the lambda function returns true for all elements
	bool allLessThan100 = all_of(begin(vec), end(vec), [](int x){return x < 100;});

	//transform - apply passed in function to all elements
	//3rd param is where to start the transformation
	string s = "this is a test";
	cout << "Before transform: " << s << endl;
	transform(begin(s), end(s), begin(s), ::toupper);
	cout << "After transform: " << s << endl;
}

void macroExamples(){
	cout << "Macro examples:\n";
	//Parameterized macro 
	cout << "MAX(10,20): " << MAX(10,20) << endl;
	cout << "MAX(2.4,3.5): " << MAX(2.4,3.5) << endl;
	cout << "MAX('A','C'): " << MAX('A','C') << endl;
	
	//example of macro that take arguments going wrong:
	int result = SQUARE(5); //expect 25
	cout << "SQUARE(5): " << result << endl; //get 25, good
	result = 100 / SQUARE(5); //expect 100 / 25 = 4
	cout << "100 / SQUARE(5): " << result << endl; //get 100 / 5 * 5 = 100, bad
	//fix 1:
	result = 100 / (SQUARE(5)); //expect 100 / 25 = 4
	cout << "100 / (SQUARE(5)): " << result << endl; //get 100 / (5 * 5) = 4
	//fix 2:
	result = 100 / BETTER_SQUARE(5); //expect 100 / 25 = 4
	cout << "100 / BETTER_SQUARE(5): " << result << endl; //get 100 / (5 * 5) = 4
	//even better solution: don't use macros with arguments; use function templates instead
}

//example of something more complex that a primitive (structs) that can be passed to a function template:
struct Test{
	string s;
	int i;
};

struct BetterTest{
	string s;
	int i;
	//overload > operator:
	bool operator>(const BetterTest &rhs) const{
		return this->i > rhs.i;
	}
};
//overload <<
ostream &operator<<(ostream &os, const BetterTest &bt){
	os << bt.s;
	return os;
}

void functionTemplateExamples(){
	//Type checking is done at compile time, not run time like other languages
	//Type checking at compile time = better performance
	//No code is generated until the user uses a specialized version of the template
	cout << "Function template examples:\n";

	cout << "maxFunctionTemplate(10,20): " << maxFunctionTemplate(10,20) << endl;
	cout << "maxFunctionTemplate(2.4,3.5): " << maxFunctionTemplate(2.4,3.5) << endl;
	cout << "maxFunctionTemplate('A','C'): " << maxFunctionTemplate('A','C') << endl;
	//optionally can specify the type of the parameter(s) like so:
	cout << "maxFunctionTemplate<int>(10,20): " << maxFunctionTemplate<int>(10,20) << endl;
	
	int a{};
	float b{};
	typeTest(a,b);
	
	cout << "Can they be the same type?...\n";
	int c{};
	typeTest(a,c); //yes

	cout << "What if I specify the type in the call to the function?...\n";
	typeTest<int, int>(a,c); //no problem

	cout << "What if I try to be tricky when I specify the type in the call to the function?...\n";
	typeTest<float, double>(0,0); //no problem

	cout << "What about a new type?: \n";
	Test t0{"t0",0}, t1{"t1", 1};
	typeTest(t0,t1); //interesting: a is type 4Test and b is 4Test
	
	cout << "What if we try to compare new type?: \n";
	//this of course fails to compile because there is no < operator declared for this type:
	//cout << "maxFunctionTemplate(t0,t1): " << maxFunctionTemplate(t0,t1) << endl;
	//further broken is trying to print out the result from an instance:
	//t3 = maxFunctionTemplate(t0,t1);
	//cout << "maxFunctionTemplate(t0,t1): " << t3 << endl;
	//how about a new type that does have these things defined?...
	BetterTest bt0{"bt0",0}, bt1{"bt1", 1};
	BetterTest bt3 = maxFunctionTemplate(bt0,bt1);
	cout << "maxFunctionTemplate(bt0,bt1): " << bt3 << endl;

}

void classTemplateExamples(){
	Item<int> item1 ("item1", 1);
	cout << "Instance of Item with templated datatype int: " << item1.get_name() << endl;
	Item<double> item2 ("item2", 2);
	cout << "Instance of Item with templated datatype double: " << item2.get_name() << endl;
	Item<string> item3 ("item3", "3"); //must use double quote; single quote = char
	cout << "Instance of Item with templated datatype string: " << item3.get_name() << endl;
	//nested templating
	vector<Item<int>> vec;
	
	//templated stuct:
	TemplatedStruct <int, string> ts0 {0, "hey"};
	cout << "templated struct t0: " << ts0.first << " " << ts0.second << endl;
	
	//Unfortunately, this doesn't seem to be possible; or if it is, I don't yet know how:
	BetterTest bt0{"bt0",0};
	//TemplatedStruct <char, BetterTest> ts1 ('h', bt0);
	//cout << "templated struct t1: " << ts1.first << " " << ts1.second << endl;
	
	//Note, this kind of TemplatedStruct is such a good idea that it's already defined as type pair
	pair<string, int> p0 {"p0", 0};
	cout << "pair<string, int>: " << p0.first << " " << p0.second << endl;
	//Can pair handle the BetterTest struct?
	//pair p1<string, BetterTest> {"p1", bt0};
	//no
	
	//But is a templated class an option?
	pair<string, Item<int>> p2 ("p2", item1);
	cout << "pair<string, Item>: " << p2.first << " " << p2.second.get_name() << endl;
	//yes
	
	//There is also a tuple which can handle any number of templateable types
	tuple <int, int, int> t0 {0,1,2};
	
	//Nested templating can be done on the parent / child class
	Item<Item<int>> item0 ("item0",item1);
	cout << "Instance of Item with templated datatype Item<int>: name: " << item0.get_name() << endl;
	cout << "\t\t\t\t\t  ^ value's name: " << item0.get_value().get_name() << endl;

	//Generic Array Template Class
	GATC<int, 5> gatci; //elements will be type int, size is 5
	cout << "Size of gatc of ints is " << gatci.get_size() << endl;
	cout << "Initial junk contents are: " << gatci << endl;
	GATC<float, 5> gatcf; 
	cout << "Initial junk contents of gatc of floats are " << gatcf << endl;
}

void containersExamples(){
	/*Member functions common to all containers:
	default constructor
	overloaded constructor
	copy constructor
	move constructor
	destructor
	copy assignment
	move assignment 
	size
	empty
	insert
	< <=
	> >=
	== !=
	swap
	erase
	clear
	begin end - iterators
	rbegin rend - reverse_iterator
	cbegin cend - const_iterator
	crbegin crend - const_reverse_iterator
	
	Containers must contain elements that have or overload < & ==
	
	Iterators work like pointers.
	Most container classes be be traversed by iterators except stack & queue
	*/
	
	//Iterator examples:
	vector<int>::iterator itV;
	list<string>::iterator itL;
	map<string, string>::iterator itM;
	set<char>::iterator itS;
	
	//vector is implemented in contiguous memory
	vector<int> vec {1,2,3};
	//point to first element:
	itV = vec.begin();
	//point to one after last element
	itV = vec.end();
	
	set<char> abc {'a','b','c'};
	//set may or may not be implemented in contiguous memory
	itS = abc.begin();
	
	//if container is empty, then , e.g., vec.begin() will point to vec.end()
	
	//easier way to initialize an iterator:
	auto itVb = vec.begin();
	//alternatively
	//auto itVb = std::begin(vec);
	
	//See L11.png for table of common operations with iterators
	
	//Common traversal:
	cout << "Traversing vector with iterator: ";
	while(itVb != itV) {//begin != end
		cout << *itVb << " ";
		itVb++;
	} //this is what range based for loop over a container does behind the scenes
	cout << endl;

	//While vector can randomly access elements, some containers cannot, 
	//thus sometimes iterators are necessary
	//Same as above but more readable:
	///for(auto it = vec.begin(); it != vec.end(); it++){ ... }
	
	//Reverse iterator: works in reverse;
	//last is first and first is last
	//++ moves backwards, -- moves forward
	vector<int>::reverse_iterator itVr = vec.rbegin();
	cout << "Traversing vector with reverse iterator: ";
	while(itVr != vec.rend()) {
		cout << *itVr << " ";
		itVr++;
	} 
	cout << endl;
	
	//Constant iterator (read only values from the container) can be declared like this:
	vector<int>::const_iterator itVc0 = vec.begin();
	// or this:
	auto itVc1 = vec.cbegin();
	
	//Map example
	map<string, string> stuff {{"a","1"},{"b","2"}};
	itM = stuff.begin();
	cout << "An element in a map: {" << itM->first << "," << itM->second << "}\n";
}