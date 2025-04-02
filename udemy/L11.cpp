#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric> //required for accumulate
#include <utility> //required for std::pair

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


//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//algorithmExamples();
	//macroExamples();
	//functionTemplateExamples();
	
	classTemplateExamples();
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void algorithmExamples(){
	//Simple example:
	vector<int> v {1,5,3};
	cout << "vector before sorting:\n";
	for(auto element : v){
		cout << element << " ";
	}
	cout << endl;
	
	//Sort from beginning to end:
	sort(v.begin(), v.end());
	//Sort works on not just vectors
	//Also, can specify how to sort, like sort account objects by balance
	
	cout << "vector after sorting:\n";
	for(auto element : v){
		cout << element << " ";
	}
	cout << endl;
	
	//Reverse
	reverse(v.begin(), v.end());
	cout << "vector after reversing:\n";
	for(auto element : v){
		cout << element << " ";
	}
	cout << endl;
	
	//Accumulate - requires #include <numeric>
	int sum = std::accumulate(v.begin(), v.end(), 0);
	cout << "sum of vector:\n" << sum << endl;		
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
	cout << "pair: " << p0.first << " " << p0.second << endl;
	//Can pair handle the BetterTest struct?
	//pair p1<string, BetterTest> {"p1", bt0};
	//no
	
	//There is also a tuple which can handle any number of templateable types
	tuple <int, int, int> t0 {0,1,2};
}