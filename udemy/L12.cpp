#include <iostream> 
#include <vector>
//#include <algorithm>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L12.o L12.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L12.o

Lambdas
Introduced in C++ 11, expanded in C++14 & C++17

Types: stateless and stateful
*/

//Function object
class Multiplier{
	private:
		int num{};
	public:
		Multiplier(int n) : num {n} {}
		int operator() (int n) const {
			//Whenever this operator is used, the function associated with it is called, 
			//for any object of the multiplier type
			return num * n;
		}
};

//Template class for a generic displayer / generic function objects:
template <typename T> 
struct Displayer{
	void operator() (const T &data){
		cout << data << " ";
	}
};

void functionObjectTest();
void templateClassTest();
void lambdaTest();

template <typename T> 
void displayContainer(const T &container);

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//functionObjectTest();
	templateClassTest();
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

void functionObjectTest(){
	vector<int> vec {1,2,3,4};
	
	Multiplier mult(10);
	cout << "vector before multiplier function object:\n";
	displayContainer(vec);
	
	//this transforms all items in the vector:
	//transform(vec.begin(), vec.end(), vec.begin(), mult);
	//Same as this unnamed Multiplier:
	//transform(vec.begin(), vec.end(), vec.begin(), Multiplier(10));
	
	//this transforms all but the last
	transform(vec.begin(), vec.end()-1, vec.begin(), mult);
	
	//this transforms none
	//transform(vec.begin(), vec.end(), vec.end(), mult);
	
	cout << "vector after multiplier function object:\n";
	displayContainer(vec);
	
}

void templateClassTest(){
	Displayer<int> d1;
	//calling a Displayer object with the () operator calls the operator() overload
	d1(10);
	cout << endl;
	
	Displayer<string> d2;
	d2("Hi!");
	cout << endl;
	
	vector<int> vec1 {1,2,3,4,5};
	vector<string> vec2 {"vec2.0", "vec2.1"};
	cout << "vector1 before for_each...Displayer<int>():\n";
	displayContainer(vec1);
	
	//This calls Displayer on vec1 via anonymous Displayer object
	for_each(vec1.begin(), vec1.end(), Displayer<int>());
	cout << endl;
	//This calls Displayer on vec1 via named Displayer object
	for_each(vec1.begin(), vec1.end(), d1);
	cout << endl;
	
	cout << "vector2 before for_each...d2:\n";
	displayContainer(vec2);
	
	for_each(vec2.begin(), vec2.end(), Displayer<string>());
	cout << endl;
	for_each(vec2.begin(), vec2.end(), d2);
	cout << endl;
	
}

template <typename T> 
void displayContainer(const T &container){
	// assuming T is a list, forward_list, vector, deque, or set
	cout << "[ ";
	for (auto c : container) cout << c << " ";
	cout << "]\n";
}

void lambdaTest(){
	//
}