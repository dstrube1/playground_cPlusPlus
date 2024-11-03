#include <iostream>
#include <string>
#include <vector>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -std=c++11 -o L5.o L5.cpp
# without -o, outputs to default a.out
# without -std=c++11, get warnings about use of auto; also error from the nullptr part of this:
# int *new_arr {nullptr};

# To run:
./L5.o

*/

void pass_by_ref(int &num);
void pass_vec_by_ref(const vector<int> &v);
int *largest(int *ptr1, int *ptr2);
int *make_array(size_t size, int initial_value = 0); //default parameter
void double_target(int *ptr);

int main()
{
	//Pointers and references
	/**/
	int h = 10;
	int *h_ptr = &h; //&: address; *: declare pointer
	//interesting, when compiling on Mac, this gives a compiler error, unless std=c++11:
	int *h_ptr0 {&h};
	cout << "value of h: " << h << endl;
	cout << "address of h: " << &h << endl;
	cout << "value of h (from h_ptr): " << *h_ptr << endl; //*: dereference pointer
	cout << "address of h (from h_ptr): " << h_ptr << endl;
	(*h_ptr)++;
	cout << "h after (*h_ptr)++ (must use parentheses) : " << h << endl;
	
	int i = 0;
	cout << "i before passByRef: " << i << endl;
	pass_by_ref(i);
	cout << "i after passByRef: " << i << endl;

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
	
	cout << "Before doubling with double_target(int *ptr): " << i1 << endl;
	double_target(&i1); // pass in the address of the target, i.e. pass by reference
	cout << "After doubling with double_target(int *ptr): " << i1 << endl;

	int *largest_ptr = {nullptr};
	largest_ptr = largest(&i1, &i2);
	cout << "Returning a pointer from a function (int *largest(int *ptr1, int *ptr2)): " << *largest_ptr << endl;

	int *my_arr;
	my_arr = make_array(10);
	//use it, then
	delete [] my_arr;

	int *test_ptr {nullptr};
	delete test_ptr; //what happens? nothing
	//what about this instead?:
	//cout << "dereferenced null pointer: " << *test_ptr << endl; // = Segmentation fault (core dumped)

	//References - like a pointer, but different: must be initialized at creation, and cannot be null, like a constant pointer that is automatically dereferenced
	vector<string> test {"1","2","3"};
	for (auto str : test) str = "4";
	cout << "After modifying copies of elements of a vector:\n";
	for (auto str : test) cout << str << " ";
	cout << "\nno change" <<endl;
	for (auto &str : test) str = "4";
	cout << "After modifying pointers to elements of a vector:\n";
	for (auto str : test) cout << str << " ";
	cout << "\nall changed" << endl; 
	
	//for (auto const &str : test) str = "4"; //<- compiler error; this is good if only displaying the contents without incurring the cost of copying each element into a temp variable
	//references must be assigned to l-values, cannot be assigned to r-values
	//int &ref = 100; //compiler error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
	//same if function f is expecting a reference- cannot pass in an r-value
 
 /**/

	
  cout << "Done\n";
  return 0;
}


void pass_by_ref(int &num){
	num++;
}

void pass_vec_by_ref(const vector<int> &v){
	//pass collections by reference because they're not all small
	for(auto i : v){}
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

/*
Never return a pointer to a local variable - it will compile and run, 
but fail as local varaibles are removed from the stack; 
the variable will be pointing to a new function's activation record
*/
int *never_do_this(){
	int size {};
	//...
	return &size; //this throws a warning, but not an error
}

int *or_this(){
	int size{};
	int *ptr {&size};
	//...
	return ptr; //this throws neither a warning nor an error
}
/**/