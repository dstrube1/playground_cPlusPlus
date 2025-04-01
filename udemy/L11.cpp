#include <iostream> 
#include <vector>
#include <algorithm>
#include <numeric> //required for accumulate


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
	constants are better because they're typed (ie have a specified type) and are known to the compiler
*/
//	example of a macro that take arguments:
#define MAX(a,b) ((a > b) ? a : b)
//example of macro that take arguments going wrong:
#define SQUARE(a) a * a
#define BETTER_SQUARE(a) (a * a)

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
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
	//even better solution: don't use macros with arguments; use function templeates instead

	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////
