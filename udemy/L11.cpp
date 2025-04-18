#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric> // required for accumulate
#include <utility> // required for std::pair
#include <list>
#include <map> // for map & multimap
#include <set> // for set & multiset
#include <cctype> // for ::toupper
#include <array>
#include <deque>
#include <forward_list>
#include <iterator> // for std::advance
#include <unordered_set> // for unordered_set & unordered_multiset
#include <unordered_map> // for unordered_map & unordered_multimap
#include <fstream>
#include <stack>
#include <queue>

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
		// #define PI 3.14159
		float p = 3.14159;
	constants are better because they're typed (ie have a specified data type) and are known to the compiler
*/

// example of a macro that take arguments:
#define MAX(a,b) ((a > b) ? a : b)
// example of macro that take arguments going wrong:
#define SQUARE(a) a * a
#define BETTER_SQUARE(a) (a * a)

class SetTestClass{
	string name;
	friend ostream &operator<<(ostream &os, const SetTestClass &stc){
		os << stc.name;
		return os;
	};
	public: 
		SetTestClass(string n):name{n} {}
		bool operator<(const SetTestClass &rhs) const {
			return true;
			// return this->name < rhs.name;
			// If making a set of a custom object, when inserting or finding, 
			// the < operator determines which attribute is the key.
		};
		bool operator==(const SetTestClass &rhs) const {
			// return false;
			return this->name == rhs.name;
		};
};

void algorithmExamples();
void macroExamples();
void functionTemplateExamples();
void classTemplateExamples();
void containersExamples();
void arrayExamples();
void displayArray(const array<int, 5> &arr);
void vectorExamples();
void dequeTests();
bool is_palindome(const string& s);
void listAndFListTests();
void setTests();
void printInsertResultSTC(pair<set<SetTestClass>::iterator,bool> insertResult);
void mapTests();
void challenge3();
void stackTests();
void queueTests();
bool is_palindome_qs(const string& s);
void priorityQueueTests();

template <typename T> 
void displayContainer(const T &container){
	// assuming T is a list, forward_list, vector, deque, or set
	cout << "[ ";
	for (auto c : container) cout << c << " ";
	cout << "]\n";
}

template <typename T1, typename T2> 
void displayMap(const map<T1,T2> &mp);
template <typename T1, typename T2> 
void displayMap(const multimap<T1,T2> &mp);
template <typename T> 
void displayStack(stack<T> s);
template <typename T> 
void displayQueue(queue<T> q);
template <typename T> 
void displayQueue(priority_queue<T> pq);

// The following can also use 'class' instead of 'typename' - "essentially equivalent":
template <typename T> 
T maxFunctionTemplate(T a, T b){
	// this function is good for any type that supports the > operator, 
	// either natively or overloaded
	return (a > b) ? a : b;
}

// This can use more than 1 type
template <typename T1, typename T2> 
void typeTest(T1 a, T2 b){
	cout << "typeTest, where a is type " << typeid(a).name() << " and b is " << typeid(b).name() << endl;
}

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
	// Note, template classes are usually completely contained in header (.h) files, no .cpp
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

// similarly for a struct:
template <typename T1, typename T2> 
struct TemplatedStruct {
	T1 first;
	T2 second; // can be the same or different type
};

template <typename T, int N> 
class GATC{ // Generic Array Template Class
	// initialized like this:
	// GATC<N> gatc;
	// where N is the size, not the type; this will be a non-type templated class
	// This is just for an example; if really need something like this, use std::array
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
		// overloaded subscript operator
		T &operator[](int index){ // is 'index' a reserved keyword?
			return values[index];
			// Usage: nums[i] 
			// which is(?) equivalent to: nums.operator[](i)
		}
};

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// algorithmExamples();
	// macroExamples();
	// functionTemplateExamples();
	// classTemplateExamples();
	// containersExamples();
	// arrayExamples();
	// vectorExamples();
	// dequeTests();
	// listAndFListTests();
	// setTests();
	// mapTests();
	// challenge3();
	// stackTests();
	// queueTests();
	priorityQueueTests();
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

struct Square_Functor {
	void operator()(int x){ // overload () operator
		cout << x * x << " ";
	}
};

void square_function_pointer(int x){
	cout << x * x << " ";
}

void algorithmExamples(){
	// Simple example:
	vector<int> vec {1,5,3};
	cout << "vector before sorting:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	// Sort from beginning to end:
	sort(vec.begin(), vec.end());
	// Sort works on not just vectors
	// Also, can specify how to sort, like sort account objects by balance
	
	cout << "vector after sorting:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	// Reverse
	reverse(vec.begin(), vec.end());
	cout << "vector after reversing:\n";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	// Accumulate - requires #include <numeric>
	int sum = std::accumulate(vec.begin(), vec.end(), 0);
	cout << "sum of vector:\n" << sum << endl;		
	
	// More:
	// https://en.cppreference.com/w/cpp/algorithm
	
	// All STL algorithms expect at least one iterator
	
	// The possibility of iterator invalidation is something to be aware of. For example:
	// while iterating over a collection, call clear(). Then what? 
	// Undefined; iterator will be unknowingly invalid, so be careful.
	
	// Find
	auto loc = find(vec.begin(), vec.end(), 3);
	if (loc != vec.end()) {//found it!
		cout << "found " << *loc << endl; 
		// find returns iterator pointing to the first found instance...
		// but where? loc is not the index, it's a pointer to the value
	}
	// This works for any container of objects that have '==' defined.
	// If using find on a container of custom objects of class C, then C must override operator==
	
	// for_each - applies function to each element
	// function must be provided as:
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

	// Lambda - introduced in C++11, aka closure, block, and anonymous function
	cout << "Squaring with a lambda: ";
	for_each(vec.begin(), vec.end(), 
		[](int x) {cout << x * x << " ";}  // lambda
		);
	cout << endl;

	cout << "Original vector is unchanged: ";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	// Count
	int lookFor = 3;
	int num = count(begin(vec), end(vec), lookFor);
	cout << "Found '" << lookFor << "' " << num << " time(s)\n";
	lookFor = 4;
	num = count(begin(vec), end(vec), lookFor);
	cout << "Found '" << lookFor << "' " << num << " time(s)\n";
	
	// Count if (if some condition is met), using a lambda
	int num_evens = count_if(begin(vec), end(vec), [](int x){return x % 2 == 0;});
	int num_odds = count_if(begin(vec), end(vec), [](int x){return x % 2 != 0;});
	cout << "Found " << num_evens << " evens and " << num_odds << " odds\n";
	
	// Replace - affects container in place, replaces all found
	vec.push_back(1);
	replace(begin(vec), end(vec), 1, 2);
	cout << "Vector with 1 added, then replace 1 with 2: ";
	for(auto element : vec){
		cout << element << " ";
	}
	cout << endl;
	
	// all_of: returns true if the lambda function returns true for all elements
	bool allLessThan100 = all_of(begin(vec), end(vec), [](int x){return x < 100;});

	// transform - apply passed in function to all elements
	// 3rd param is where to start the transformation
	string s = "this is a test";
	cout << "Before transform: " << s << endl;
	transform(begin(s), end(s), begin(s), ::toupper);
	cout << "After transform: " << s << endl;
}

void macroExamples(){
	cout << "Macro examples:\n";
	// Parameterized macro 
	cout << "MAX(10,20): " << MAX(10,20) << endl;
	cout << "MAX(2.4,3.5): " << MAX(2.4,3.5) << endl;
	cout << "MAX('A','C'): " << MAX('A','C') << endl;
	
	// example of macro that take arguments going wrong:
	int result = SQUARE(5); // expect 25
	cout << "SQUARE(5): " << result << endl; // get 25, good
	result = 100 / SQUARE(5); // expect 100 / 25 = 4
	cout << "100 / SQUARE(5): " << result << endl; // get 100 / 5 * 5 = 100, bad
	// fix 1:
	result = 100 / (SQUARE(5)); // expect 100 / 25 = 4
	cout << "100 / (SQUARE(5)): " << result << endl; // get 100 / (5 * 5) = 4
	// fix 2:
	result = 100 / BETTER_SQUARE(5); // expect 100 / 25 = 4
	cout << "100 / BETTER_SQUARE(5): " << result << endl; // get 100 / (5 * 5) = 4
	// even better solution: don't use macros with arguments; use function templates instead
}

struct Test{
	// example of something more complex than a primitive (structs) 
	// that can be passed to a function template:
	string s;
	int i;
};

struct BetterTest{
	string s;
	int i;
	// overload > operator:
	bool operator>(const BetterTest &rhs) const{
		return this->i > rhs.i;
	}
};
// overload <<
// if defined in the class, then use the 'friend' modifier
ostream &operator<<(ostream &os, const BetterTest &bt){
	os << bt.s;
	return os;
}

void functionTemplateExamples(){
	// Type checking is done at compile time, not run time like other languages
	// Type checking at compile time = better performance
	// No code is generated until the user uses a specialized version of the template
	cout << "Function template examples:\n";

	cout << "maxFunctionTemplate(10,20): " << maxFunctionTemplate(10,20) << endl;
	cout << "maxFunctionTemplate(2.4,3.5): " << maxFunctionTemplate(2.4,3.5) << endl;
	cout << "maxFunctionTemplate('A','C'): " << maxFunctionTemplate('A','C') << endl;
	// optionally can specify the type of the parameter(s) like so:
	cout << "maxFunctionTemplate<int>(10,20): " << maxFunctionTemplate<int>(10,20) << endl;
	
	int a{};
	float b{};
	typeTest(a,b);
	
	cout << "Can they be the same type?...\n";
	int c{};
	typeTest(a,c); // yes

	cout << "What if I specify the type in the call to the function?...\n";
	typeTest<int, int>(a,c); // no problem

	cout << "What if I try to be tricky when I specify the type in the call to the function?...\n";
	typeTest<float, double>(0,0); // no problem

	cout << "What about a new type?: \n";
	Test t0{"t0",0}, t1{"t1", 1};
	typeTest(t0,t1); // interesting: a is type 4Test and b is 4Test
	
	cout << "What if we try to compare new type?: \n";
	// this of course fails to compile because there is no < operator declared for this type:
	// cout << "maxFunctionTemplate(t0,t1): " << maxFunctionTemplate(t0,t1) << endl;
	// further broken is trying to print out the result from an instance:
	// t3 = maxFunctionTemplate(t0,t1);
	// cout << "maxFunctionTemplate(t0,t1): " << t3 << endl;
	// how about a new type that does have these things defined?...
	BetterTest bt0{"bt0",0}, bt1{"bt1", 1};
	BetterTest bt3 = maxFunctionTemplate(bt0,bt1);
	cout << "maxFunctionTemplate(bt0,bt1): " << bt3 << endl;

}

void classTemplateExamples(){
	Item<int> item1 ("item1", 1);
	cout << "Instance of Item with templated datatype int: " << item1.get_name() << endl;
	Item<double> item2 ("item2", 2);
	cout << "Instance of Item with templated datatype double: " << item2.get_name() << endl;
	Item<string> item3 ("item3", "3"); // must use double quote; single quote = char
	cout << "Instance of Item with templated datatype string: " << item3.get_name() << endl;
	// nested templating
	vector<Item<int>> vec;
	
	// templated stuct:
	TemplatedStruct <int, string> ts0 {0, "hey"};
	cout << "templated struct t0: " << ts0.first << " " << ts0.second << endl;
	
	// Unfortunately, this doesn't seem to be possible; or if it is, I don't yet know how:
	BetterTest bt0{"bt0",0};
	// TemplatedStruct <char, BetterTest> ts1 ('h', bt0);
	// cout << "templated struct t1: " << ts1.first << " " << ts1.second << endl;
	
	// Note, this kind of TemplatedStruct is such a good idea that it's already defined as type pair
	pair<string, int> p0 {"p0", 0};
	cout << "pair<string, int>: " << p0.first << " " << p0.second << endl;
	// Can pair handle the BetterTest struct?
	// pair p1<string, BetterTest> {"p1", bt0};
	// no
	
	// But is a templated class an option?
	pair<string, Item<int>> p2 ("p2", item1);
	cout << "pair<string, Item>: " << p2.first << " " << p2.second.get_name() << endl;
	// yes
	
	// There is also a tuple which can handle any number of templateable types
	tuple <int, int, int> t0 {0,1,2};
	
	// Nested templating can be done on the parent / child class
	Item<Item<int>> item0 ("item0",item1);
	cout << "Instance of Item with templated datatype Item<int>: name: " << item0.get_name() << endl;
	cout << "\t\t\t\t\t  ^ value's name: " << item0.get_value().get_name() << endl;

	// Generic Array Template Class
	GATC<int, 5> gatci; //elements will be type int, size is 5
	cout << "Size of gatc of ints is " << gatci.get_size() << endl;
	cout << "Initial junk contents are: " << gatci << endl;
	GATC<float, 5> gatcf; 
	cout << "Initial junk contents of gatc of floats are " << gatcf << endl;
}

void containersExamples(){
	/*
	Member functions common to all containers:
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
	
	// Iterator examples:
	vector<int>::iterator itV;
	list<string>::iterator itL;
	map<string, string>::iterator itM;
	set<char>::iterator itS;
	
	// vector is implemented in contiguous memory
	vector<int> vec {1,2,3};
	// point to first element:
	itV = vec.begin();
	// point to one after last element
	itV = vec.end();
	
	set<char> abc {'a','b','c'};
	// set may or may not be implemented in contiguous memory
	itS = abc.begin();
	
	// if container is empty, then , e.g., vec.begin() will point to vec.end()
	
	// easier way to initialize an iterator:
	auto itVb = vec.begin();
	// alternatively
	// auto itVb = std::begin(vec);
	
	// See L11.png for table of common operations with iterators
	
	// Common traversal:
	cout << "Traversing vector with iterator: ";
	while(itVb != itV) {//begin != end
		cout << *itVb << " ";
		itVb++;
	} // this is what range based for loop over a container does behind the scenes
	cout << endl;

	// While vector can randomly access elements, some containers cannot, 
	// thus sometimes iterators are necessary
	// Same as above but more readable:
	// for(auto it = vec.begin(); it != vec.end(); it++){ ... }
	
	// Reverse iterator: works in reverse;
	// last is first and first is last
	// ++ moves backwards, -- moves forward
	vector<int>::reverse_iterator itVr = vec.rbegin();
	cout << "Traversing vector with reverse iterator: ";
	while(itVr != vec.rend()) {
		cout << *itVr << " ";
		itVr++;
	} 
	cout << endl;
	
	// Constant iterator (read only values from the container) can be declared like this:
	vector<int>::const_iterator itVc0 = vec.begin();
	// or this:
	auto itVc1 = vec.cbegin();
	
	// Map example
	map<string, string> stuff {{"a","1"},{"b","2"}};
	itM = stuff.begin();
	cout << "An element in a map: {" << itM->first << "," << itM->second << "}\n";
}

void arrayExamples(){
	// use array instead of raw pointers when possible
	// comes with all iterators which do not invalidate
	// Added in C++11
	
	// In C++11, array must be initialized with double curly braces:
	// array<int, 5> arr {{1,2,3,4,5}};
	// In C++14, single curly braces are good enough (and double braces are still accepted)
	array<int, 5> arr {1,2,3,4,5};

	// common methods:
	arr.size(); 
	arr.at(0); // throws exception if out of bounds
	arr[1]; // no bounds checking
	arr.front();
	arr.back();
	arr.empty();
	
	array<int, 5> arr1 {2,3,4,5,6};
	arr.swap(arr1); // must be the same size
	// arr.fill(0); // replace everything with 0
	
	// raw array address
	int *data = arr.data();
	cout << "First element in arr from a data pointer, before changing: " << *data << endl;
	cout << "Array: ";
	displayArray(arr);
	*data = 0;
	cout << "After changing: " << endl;
	displayArray(arr);
	data++;
	(*data)++;
	cout << "After moving pointer, and then (*data)++ : " << endl;
	displayArray(arr);
	
	// Max & min
	// long name for iterator type returned:
	std::array<int,5>::iterator min_num = std::min_element(arr.begin(), arr.end());
	// let the compiler figure it out:
	auto max_num = max_element(arr.begin(), arr.end());
	cout << "min: " << *min_num << "; max: " << *max_num << endl;
	
	// Adjacent find
	auto adjacent = adjacent_find(arr.begin(), arr.end());
	if (adjacent != arr.end()){
		cout << "Adjacent elements found with value: " << *adjacent << endl;
	}else{
		cout << "No adjacent elements found." << endl;
	}
}

void displayArray(const array<int, 5> &arr){
	cout << "[ ";
	for (auto i : arr) cout << i << " ";
	cout << "]\n";
}

void vectorExamples(){
	// direct element access - constant time
	// add or delete from back: constant time
	// add or delete anywhere else: linear time
	// supports all iterators and they may become invalid (e.g., when vector is resized)
	
	vector<int> vec {1,2,3};
	// Overloaded constructor, ten 100s:
	vector<int> vec1 (10, 100);
	
	// like with array, can be reinitialized with assignment:
	vec1 = {2,4,6,8,10};
	cout << "vector size: " << vec.size() << endl;
	cout << "capacity: " << vec.capacity() << endl; // same as size by default; what if add an element, how big does the capacity get?...
	vec.push_back(0);
	cout << "capacity after push_back: " << vec.capacity() << endl; // doubled
	// shrink_to_fit:
	vec.shrink_to_fit();
	cout << "capacity after shrink_to_fit: " << vec.capacity() << endl; // shrunk to fit
	// reserve:
	vec.reserve(10);
	cout << "capacity after reserve(10): " << vec.capacity() << endl; // 10

	cout << "max_size: " << vec.max_size() << endl; 
	// ^ 4611686018427387903 = 4,611,686,018,427,387,903 =~ 4.6 quintillion
	
	// just like array, subscript access doesn't check for bounds, and .at() does
	
	// pop_back() removes last element
	
	// emplace_back() efficiently adds to the end with parameters that 
	// would be used for the constructor of the object to be added; e.g.:
	vector<pair<string, int>> vec2;
	vec2.emplace_back("p0", 0);
	
	// Same as array:
	// vec.empty()
	
	// vector swap - vectors can be different size, but must be the same type; this works:
	vec.swap(vec1);
	// this fails:
	// vec.swap(vec2);
	// 'vector<int, allocator<int>>' cannot bind to a value of unrelated type 'vector<pair<std::string, int>,
	
	// Find and insert:
	cout << "vec: ";
	displayContainer(vec); // 2 4 6 8 10
	cout << "vec1: ";
	displayContainer(vec1); // 1 2 3 0
	auto it1 = find(vec1.begin(), vec1.end(), 3);
	vec1.insert(it1, 10);
	cout << "After inserting 10 into vec1 where 3 was: ";
	displayContainer(vec1); // 1 2 10 3 0
	vec1.insert(it1, vec.begin(), vec.end()); // udemy course said this should be vec1::insert...
	cout << "After inserting vec into vec1 where 3 was: ";
	displayContainer(vec1); // 1 2 2 4 6 8 10 10 3 0
	
	// vec.clear() // this will remove all elements
	vec1.erase(vec1.begin(), vec1.begin()+2); // +n where n = number of elements to remove from beginning
	cout << "After erasing from begin to begin + 2: ";
	displayContainer(vec1); // 2 4 6 8 10 10 3 0
	vec1.erase(vec1.end()-1, vec1.end());
	cout << "After erasing from end-1 to end: ";
	displayContainer(vec1); // 2 4 6 8 10 10 3
	
	// copy and back_inserter:
	cout << "vec: ";
	displayContainer(vec); // 2 4 6 8 10
	copy(vec1.begin(), vec1.end(), back_inserter(vec));
	cout << "vec after copying vec1 into vec using back_inserter: ";
	displayContainer(vec); // 2 4 6 8 10 2 4 6 8 10 10 3
	
	// copy_if
	vec = {1,2,3,4,5};
	vec1 = {2,4,6,8,10};
	cout << "vec & vec1 before copy_if: \n";
	displayContainer(vec); 
	displayContainer(vec1); 
	copy_if(vec.begin(), vec.end(), back_inserter(vec1),
		[](int x){return x % 2 == 0;});
	cout << "vec & vec1 after copy_if (allowing only evens into vec1 from vec): \n";
	displayContainer(vec); 
	displayContainer(vec1); 
	
	// transform
	vector<int> vec3 = {1,2,3,4,5};
	vector<int> vec4 = {10,20,30,40,50};
	vector<int> vec5;
	transform(vec3.begin(),vec3.end(),vec4.begin(), back_inserter(vec5), 
		[](int x,int y){ return x * y;});
	cout << "vec3: ";
	displayContainer(vec3); // 1 2 3 4 5
	cout << "vec4: ";
	displayContainer(vec4); // 10 20 30 40 50
	cout << "vec5 after transform (vec3 x * vec4 y): ";
	displayContainer(vec5); // 
	
}

void dequeTests(){
	/*
	Dynamic size, handled automatically; 
	Elements are not stored in contiguous memory, like a linked list of vectors
	direct element access and insertion/deletion at front AND back: constant time
	other insert and removal: linear time
	all iterators available, may invalidate (like when it changes size)
	*/
	deque<int> deck0 {1,2,3,4,5};
	deque<int> deck1 (10,100); // 10 elements, all 100
	auto front = deck0.front();
	cout << "front: " << front << endl;
	auto back = deck0.back();
	cout << "back: " << back << endl;
	deck0.push_back(6);
	deck0.push_front(0);
	cout << "After pushing to front and back: " << endl;
	displayContainer(deck0);
	/*
	These don't return anything, just delete
	front = deck0.pop_front();
	cout << "front after pop_front: " << front << endl;
	back = deck0.pop_back();
	cout << "back after pop_back: " << back << endl;
	*/
	
	// Also an option, like in vector:
	deck0.emplace_front(-1);
	deck0.emplace_back(7);
	
	// copy with front_inserter and back_inserter
	vector<int> vec {1,2,3};
	deque <int> deck2;
	deque <int> deck3;
	
	copy(vec.begin(),vec.end(),front_inserter(deck2));
	cout << "After copying with front_inserter: " << endl;
	displayContainer(deck2);

	copy(vec.begin(),vec.end(),back_inserter(deck3));
	cout << "After copying with back_inserter: " << endl;
	displayContainer(deck3);
}

bool is_palindome(const string& s){
	// using deque
	deque<char> d;
	
	for(char c : s){
		if(std::isalpha(c)) d.push_back(std::toupper(c));
	}
	char c1{};
	char c2{};
	while(d.size() > 1){
		c1 = d.front();
		c2 = d.back();
		d.pop_front();
		d.pop_back();
		if (c1 != c2) return false;
	}
	return true;
}

void listAndFListTests(){
	// sequence containers, non-contiguous in memory
	// no direct access to elements - no list[n] or list.at(n)
	// efficient inserting and deleting once an element is found
	
	// List: doubly linked list - can go forward or backward
	// Dynamic size
	// all iterators available and invalidate when element is deleted
	list <int> L {1,2,3,4,5}; // also has the overloaded ctor(size,init_value)
	auto front = L.front();
	auto back = L.back(); 
	cout << "initial list: \n";
	displayContainer(L);
	cout << "front: " << front << "; back: " << back << endl;
	// also has push_back, pop_back, push_front, pop_front, emplace_front, and emplace_back
	
	// insert with iterator result from find
	auto it = find(L.begin(), L.end(), 3);
	L.insert(it, 10); // insert 10 before 3
	cout << "insert 10 before 3 using iterator: \n";
	displayContainer(L);
	
	advance(it, -3); // move iterator back 3 spaces, tp point at the 1

	L.erase(it); // delete what iterator is pointing to, new list: 2,10,3,4,5
	// this invalidates the iterator; 
	// otherwise, can traverse the list with it++ & it--
	// it* to dereference
	cout << "erase at iterator: \n";
	displayContainer(L);

	L.resize(2); // delete everything down to size = 2; L={2,10}
	cout << "resize(2): \n";
	displayContainer(L);

	L.resize(5); // size up to 5; L={2,10,0,0,0}
	cout << "resize(5): \n";
	displayContainer(L);

	// forward_list: singly-linked list, uni-directional, less overhead than list
	// reverse iterators, .size() and .back() (and other backward stuff) not available
	// otherwise same as list
	forward_list<int> fL {1,2,3,4,5};
	auto fL_front = fL.front();
	cout << "initial forward_list: \n";
	displayContainer(fL);
	cout << "front: " << fL_front << "; NO back" << endl;

	// push_front, pop_front, emplace_front
	
	// Since there is no .size() method built in, 
	// if size is ever wanted, then must either first traverse the forward_list and make a count,
	// or make a count when initializing and update the count on each insert.
	// Speaking of insert...
	auto it_fL = find(fL.begin(), fL.end(),3);

	fL.insert_after(it_fL, 10);
	cout << "forward_list after insert_after((iterator at 3), 10): \n";
	displayContainer(fL);

	fL.emplace_after(it_fL, 100);
	cout << "forward_list after emplace_after((iterator at 3), 100): \n";
	displayContainer(fL);

	fL.erase_after(it_fL);
	cout << "forward_list after erase_after(iterator at 3): \n";
	displayContainer(fL);
	
	// iterator does not invalidate after erases
	
	// same results from resize as those for list
}

void setTests(){
	// associate container, fast retrieval using a key
	// usually implemented as a balanced binary tree or hashset
	// types of sets:
	//	set
	//	unordered_set
	//	multiset
	//	unordered_multiset
	// ordered by key, no duplicates allowed
	// all iterators allowed which are invalidated on delete
	set<int> sit {1,2,4,5};
	cout << "initial set: \n";
	displayContainer(sit);
	// no concept of front and back
	
	// automatically sorts on insert
	pair<set<int>::iterator,bool> insertResult = sit.insert(3); 
	cout << "set after insert 3: \n";
	displayContainer(sit);
	// try to insert a duplicate:
	insertResult = sit.insert(3); // quietly fails
	cout << "set after trying to insert a duplicate: \n";
	displayContainer(sit);
	if(insertResult.second){
		// first is an iterator to the inserted element, or the duplicate's original 
		cout << "duplicate insert succeeded\n";
	}else{
		cout << "duplicate insert failed\n";
	}
	
	// What if the overloaded == always returns false?
	cout << "\nTesting what happens when trying to insert duplicate of class that overloads "
		<< "== & <, but == always returns false...\n";
	set<SetTestClass> setTestClassSet {};
	SetTestClass stc1("name");
	cout << "name of stc1: " << stc1 << endl;
	SetTestClass stc2("name");
	cout << "name of stc2: " << stc2 << endl;
	auto insertResultSTC = setTestClassSet.insert(stc1);
	printInsertResultSTC(insertResultSTC);
	cout << "Trying to insert stc1 again...\n";
	insertResultSTC = setTestClassSet.insert(stc1);
	printInsertResultSTC(insertResultSTC);
	cout << "Trying to insert stc2...\n";
	insertResultSTC = setTestClassSet.insert(stc2);
	printInsertResultSTC(insertResultSTC);
	cout << endl;
	// TIL that it doesn't matter if == always returns false; it matters if < always returns true
		
	// erase can take either the item being erased (key) or an iterator to it
	// erasing via iterator is more efficient
	
	int num = sit.count(3); // returns 0 or 1
	cout << "count of element 3: " << num << endl;
	
	sit.clear();
	bool isEmpty = sit.empty();
	cout << boolalpha;
	cout << "result of empty() after clear(): " << isEmpty << endl;

	multiset<int> mset {1,2,3,4,5};
	cout << "initial multiset: \n";
	displayContainer(mset);
	mset.insert(3); 
	cout << "set after insert 3: \n";
	displayContainer(mset);

	unordered_set<int> uoset {1,2,4,3,5};
	// unordered, no duplicates allowed
	// elements can't be modified, must be erased and new element inserted
	// (presumably for ordered sets, they can be modified in place)
	// no reverse iterators
	
	unordered_multiset<int> uomset {1,2,3,2,4,5};
	// no reverse iterators allowed
	
	// When searching in a set, for efficiency, should use the set.find(), not std::find()
}

void printInsertResultSTC(pair<set<SetTestClass>::iterator,bool> insertResult){
	if (insertResult.second){
		cout << "insert of SetTestClass succeeded\n";
	}else{
		cout << "insert of SetTestClass failed\n";
	}
}

void mapTests(){
	// Very similar to Set
	map<int,int> mp {
		{0,1},
		{1,2}
	};
	// Elements are stored as std::pair<k,v>, ordered by key (unless unordered)
	// Direct access via key
	// No duplicate (unless multi)
	// All iterators available, and invalidate on delete	
	
	// To insert:
	pair<int,int> p1 {2,3};
	mp.insert(p1);
	// or
	mp.insert(make_pair(3,4));
	// or
	mp[4] = 5;
	
	// To update:
	mp[4] = 6;
	// or
	mp.at(4) = 5;
	// .at() throws exception if key is not in the map:
	// mp.at(5) = 6;
	// terminating with uncaught exception of type std::out_of_range: map::at:  key not found
	
	// does displayContainer work for map?
	// displayContainer(mp);
	// no, won't even compile:
// error: invalid operands to binary expression ('std::ostream' (aka 'basic_ostream<char>') and 'std::pair<const int, int>')
	displayMap(mp);
	
	// To delete by key:
	mp.erase(4);
	// to delete by iterator after finding:
	auto it = mp.find(3); // for efficiency, should use the map.find(), not std::find()
	if (it != mp.end()) mp.erase(it);
	
	// To see if an element exists:
	int num = mp.count(2); // returns either 0 or 1
	
	// remove all elements:
	mp.clear();
	
	// true or false:
	bool isMapEmpty = mp.empty();
	cout << boolalpha << "Is map empty after clear?: " << isMapEmpty << endl;
	
	unordered_map<int,string> um{{1,"2"}, {0,"1"}};
	// cout << "Does displayMap work with an unordered map?\n";
	// displayMap(um);
	// no, won't even compile
	// elements are unordered, no duplicates allowed; no reverse iterators
	
	// What about a multimap?
	multimap<string,int> mm {};
	// displayMap(mm);
	// nope
	
	// multimap allows for duplicate keys, which seems a little weird to me.
	// How does find work?
	// "It returns an iterator to the first occurrence of the key if found, or to the end of the multimap if the key is not present."
	// "can use the equal_range member function to get iterators for the start and end of the elements with key":
// https://stackoverflow.com/questions/72841621/finding-all-the-values-with-given-key-for-multimap
	mm.insert(make_pair("0",1));
	cout << "Multimap after mm.insert(make_pair(\"0\",1)): \n";
	displayMap(mm);
	// interesting, no [] or .at()
	// mm.at("0") = 2;
	// cout << "Multimap after mm.at(\"0\") = 2: \n";
	// displayMap(mm);
	mm.insert(make_pair("0",3));
	cout << "Multimap after mm.insert(make_pair(\"0\",3)): \n";
	displayMap(mm);
	// all iterators are allowed
	
	unordered_multimap<string,string> umm {};
	// elements are unordered, duplicates allowed; no reverse iterators
	
}

template <typename T1, typename T2> 
void displayMap(const map<T1,T2> &mp){
	cout << "[ ";
	// each p is a pair<T1,T2>
	for (auto p : mp) cout << "{ " << p.first << " -> " << p.second << " }, ";
	cout << "]\n";
}

/*
This doesn't work.
Must make separate print methods for unordered_map, multimap, & unordered_multimap

template <typename T1, typename T2, typename T3> 
void displayTMap(const T3<T1,T2> &mp){
	cout << "[ ";
	for (auto p : mp) cout << "{ " << p.first << " -> " << p.second << " }, ";
	cout << "]\n";
}
*/

template <typename T1, typename T2> 
void displayMap(const multimap<T1,T2> &mp){
	cout << "[ ";
	// each p is a pair<T1,T2>
	for (auto p : mp) cout << "{ " << p.first << " -> " << p.second << " }, ";
	cout << "]\n";
}

void challenge3(){
	// part 1
	// read in all words from a file, then for each unique word, display the count of that word
	// Going back to L10 for file io reminders, and using this file as input
	string text_path {"L11.cpp"};
	ifstream in_file {text_path};
	if (! in_file.is_open()){
		cerr << "Problem opening file";
		return;
	}
	map<string, int> words {};
	while (!in_file.eof()){
		string text;
		in_file >> text;
		// To be tedious:
		// int num = words.count(text);
		/* if (num == 0){
			words[text] = 1;
		}
		else{
			words[text]++;
		} */
		// Better:
		words[text]++;
	}
	in_file.close();
	for(auto word : words){
		cout << word.first << " -> " << word.second << endl;
	}
	
	// No need to waste time on part 2
}

void stackTests(){
	// Last-in First-out (LIFO)
	// Can be implemented over any container that has a back: vector, list, or deque
	// All operations occur on one end, the top
	// No iterators supported
	// methods:
		// push: insert at the top
		// pop: remove from the top
		// top: gets top without removing it; can also be used to set the top: s.top() = x;
		// empty: T/F
		// size
	// Stack is a container adapter. One can specify what is the underlying container,
	// but deque is the default
	stack<int> s1; // dequeue
	stack<int, vector<int>> s2;
	stack<int, list<int>> s3;
	stack<int, deque<int>> s4;
	
	s1.push(10);
	s1.push(20);
	cout << "initial stack:\n";
	displayStack(s1);
}

template <typename T> 
void displayStack(stack<T> s){ 
	// stack is passed in by value so that the display doesn't affect the original
	cout << "[ ";
	while(!s.empty()){
		T temp = s.top();
		s.pop();
		cout << temp << " ";
	}
	cout << "]\n";
}

void queueTests(){
	// First-in First-out (FIFO)
	// Can be implemented over any container that has a front & back: list or deque
	// All operations are push to back and pop from front
	// No iterators supported
	// methods:
		// push: insert at the back
		// pop: remove from the front
		// front: get first element  
		// back: get last element
		// empty: T/F
		// size
	queue<int> q; // default underlying container is deque
	// can specify the container like this:
	queue<string, list<string>> q1;
	queue<string, deque<string>> q2;
	
	for (int i=1; i<=5;i++)
		q.push(i);
	cout << "original queue:\n";
	displayQueue(q);
}

template <typename T> 
void displayQueue(queue<T> q){ 
	// queue is passed in by value so that the display doesn't affect the original
	cout << "[ ";
	while(!q.empty()){
		T temp = q.front();
		q.pop();
		cout << temp << " ";
	}
	cout << "]\n";
}

bool is_palindome_qs(const string& s){
	// using queue & stack
	queue<char> que;
	stack<char> stk;
	for(char c : s){
		if(std::isalpha(c)) {
			que.push(std::toupper(c));
			stk.push(std::toupper(c));
		}
	}
	char c1{};
	char c2{};
	while(que.size() > 1){
		c1 = que.front();
		c2 = stk.top();
		que.pop();
		stk.pop();
		if (c1 != c2) return false;
	}
	return true;

}

void priorityQueueTests(){
	// allows inserts and removes from the front of the container in order determined by priority
	// elements stored as vector by default
	// largest value will always be at the front
	// iterators not allowed
	// methods:
		// push
		// pop
		// top
		// empty
		// size
	priority_queue<int> pq;
	for (int i=1; i<=5;i++)
		pq.push(i);
	cout << "original priority queue:\n";
	displayQueue(pq);
}

template <typename T> 
void displayQueue(priority_queue<T> pq){ 
	// priority_queue is passed in by value so that the display doesn't affect the original
	cout << "[ ";
	while(!pq.empty()){
		T temp = pq.top();
		pq.pop();
		cout << temp << " ";
	}
	cout << "]\n";
}

