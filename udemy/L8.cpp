#include <iostream>
#include <string>
#include <vector>
#include <memory> //required for smart pointers

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L8.o L8.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L8.o

Smart pointers

problems with dumb pointers:
1- uninitialized / wild: could be pointing anywhere in data; if store data in one, could be catastrophic
2- memory leak: if memory allocated on the heap isn't deallocated
3- dangling: pointer is pointing to storage that it thinks is valid, but has already been deallocated
4- not exception safe: if exception is thrown before deleting pointer

RAII: resource acquisition is initialization
resource is acquired in the constructor, and relinquished in the destructor;
idiom followed by smart pointers

Types of Smart pointers:
1- unique_ptr
2- shared_ptr
3- weak_ptr
4- auto_ptr [deprecated]

operators:
*  : dereference
-> : member selection
pointer arithmetic not supported (++, --, etc)

When you declare a smart pointer object, that object is placed on the stack

*/

class SomeClass{
	private:
		string name;
	public:
		SomeClass(){cout << "SomeClass default ctor\n"; name = "default";}
		SomeClass(string n){name = n; cout << "SomeClass " << name << " ctor\n";}
		void method(string type){cout<<"method from SomeClass with " << type << " pointer\n";}
		void setName(string n){name = n;}
		string getName(){return name;}
		~SomeClass(){cout<<"SomeClass destructor for " << name << "\n";}
};

void unique_ptr_tests();
void shared_ptr_tests();
void shared_ptr_param_test(shared_ptr<int> sptr);
void weak_ptr_tests();
void custom_deleter_tests();
void custom_deleter(SomeClass *a_ptr);

//Section 17 Challenge 1
unique_ptr<vector<shared_ptr<SomeClass>>> make();
bool fill(vector<shared_ptr<SomeClass>> &vec, int num);
void display(const vector<shared_ptr<SomeClass>> &vec);

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
/**/

	//unique_ptr_tests();
	//shared_ptr_tests();
	//weak_ptr_tests();
	//custom_deleter_tests();
	
	//Section 17 Challenge 1:
	//unique_ptr<vector<shared_ptr<SomeClass>>> vec_ptr;
	auto vec_ptr = make();
	cout << "How many data points for the challenge?: ";
	int num;
	cin >> num;
	if (fill(*vec_ptr, num)){
		display(*vec_ptr);
	}
	//Smart pointers are usually deleted automatically when they go out of scope
	
	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void unique_ptr_tests(){
	cout << "Exploring unique_ptr:\n";
	unique_ptr<SomeClass> uptr;
	//Call methods like so:
	uptr->method("unique");
	//segmentation fault - why?!: 
	//uptr->setName("uptr");
	//Does this call a destructor outloud? No
	//uptr.reset();
	
	//TODO: how to test these?:
	//can be only one unique pointer pointing to the same object of type T on the heap
	//when pointer is destroyed, what it points to is destroyed
	
	//Can create more than one pointer for the same class
	unique_ptr<SomeClass> uptr0;
	//Can't do this:
	//uptr0 = uptr;
	//error: object of type 'unique_ptr<SomeClass>' cannot be assigned because its copy assignment operator is implicitly deleted
	//But can do this:
	uptr0 = move(uptr); //std::move()
	//uptr0 now owns what was pointed to by uptr, and uptr is now = nullptr
	
	//cannot be assigned or copied
	//unique_ptr<SomeClass> uptr1 = uptr;
	//unique_ptr<SomeClass> uptr1 (uptr);
	//error: call to implicitly-deleted copy constructor of 'unique_ptr<SomeClass>'

	//Can't do this because	"no viable conversion from 'SomeClass *' to 'unique_ptr<SomeClass>'"
	//unique_ptr<SomeClass> uptr2 = new SomeClass();
	//But can do this:
	unique_ptr<SomeClass> uptr2 {new SomeClass("uptr2")};
	//Does this call the destructor sooner? Yes
	//uptr2.reset();
	
	unique_ptr<int> uptr3 {new int{100} };
	cout << "uptr3: " << *uptr3 << endl;
	*uptr3 = 200;
	cout << "uptr3: " << *uptr3 << endl;
	cout << "uptr3's address: " << uptr3.get() << endl;
	cout << "resetting uptr3..." << endl;
	uptr3.reset();
	//segmentation fault: 
	//cout << "uptr3: " << *uptr3 << endl;
	if(!uptr3) //shortcut for uptr3 == nullptr 
	{
		cout << "after call to reset(), uptr3 is now nullptr" << endl;
	}
	
	vector <unique_ptr<int> > vec;
	//cannot set uptr3 in either of these ways:
	//uptr3 {new int{100} };
	//uptr3 = new int{100} ;
	unique_ptr<int> uptr4 {new int{100} };
	//if try this:
	//vec.push_back(uptr4);
	//then get these:
	//error: call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'
	//note: copy constructor is implicitly deleted because 'unique_ptr<int>' has a user-declared move constructor
	//long story short: copy not allowed for unique pointers
	//but it can be moved
	vec.push_back(move(uptr4));
	//uptr4 now gives up ownership of the pointer, the vector now owns the pointer, and uptr4 will be set to nullptr
	if (!uptr4) cout << "after being moved to a vector, uptr4 is now nullptr\n";
	//So then what is the point of moving a unique pointer into a vector if the pointer will then become null?
	//Let's try this a different way:
	vec.push_back(make_unique<int>(1));
	vec.push_back(make_unique<int>(2));
	vec.push_back(make_unique<int>(3));
	//can't do this:
	//for(auto i : vec) {
	//error: call to implicitly-deleted copy constructor of 'std::unique_ptr<int>'
	//but can do this:
	cout << "Looping thru a vector of unique pointers of ints:" << endl;
	for(const auto &i : vec) { //this const is optional, but it must be a reference
		cout << "*i: " << *i << endl;
	}
	
	cout << "making a new unique pointer using make_unique<>()...\n";
	unique_ptr<int> uptr5 = make_unique <int>(100);
	auto uptr6 = make_unique <SomeClass>("uptr6");
	uptr6->method("uptr6");
	//More efficient - no use of new or delete
	
	//End of method; make some room to differentiate this from next method(s)
	cout << endl;
	//Interesting, no destructor call for uptr or uptr0, uptr2
}

void shared_ptr_tests(){
	//Not unique- can be many shared_ptrs pointing to the same object
	//Can be assigned, copied, and moved
	
	//unique pointers can be used to allocate arrays of objects on the heap
	//but shared pointers don't support managing arrays by default(?)
	
	//when use count is 0, then the managed object on the heap is destroyed
	//simple and effective, but adds overhead, but usually not a big deal
	
	shared_ptr<int> sptr0 {new int {100}};
	cout << "shared pointer sptr0 after initialization: " << *sptr0 << endl;
	*sptr0 = 200;
	cout << "shared pointer sptr0 after assignment: " << *sptr0 << endl;

	shared_ptr<SomeClass> sptr;
	sptr->method("shared");
	//interesting that the deconstructor doesn't seem to get called

	//can't do this:
	//delete sptr;
	//error: cannot delete expression of type 'shared_ptr<SomeClass>'
	
	//use_count & reset:
	cout << "use_count of sptr0 before creating sptr1 (via copy constructor): " << sptr0.use_count() << endl;
	shared_ptr<int> sptr1 {sptr0};
	
	cout << "use_count of sptr0 after creating sptr1, before sptr0.reset(): " << sptr0.use_count() << endl;
	cout << "sptr1.use_count(), before sptr0.reset(): " << sptr1.use_count() << endl;
	
	sptr0.reset(); //sptr0 is "nulled out"
	cout << "sptr0.use_count() after reset: " << sptr0.use_count() << endl;
	cout << "sptr1.use_count() after sptr0's reset: " << sptr1.use_count() << endl;
	if (!sptr0) cout << "sptr0 is null\n";
	else cout << "sptr0 is not null\n";
	//it is null
	
	vector <shared_ptr<int>> vec;
	//unlike unique pointer, can do this - copy:
	vec.push_back(sptr1);
	cout << "sptr1.use_count() after adding it to a vector: " << sptr1.use_count() << endl;
	//2 because 1 is from sptr1 and the other is the copy in the vector
	
	//adding null pointer to vector is allowed, but trying to print it = segmentation fault
	//vec.push_back(sptr0);
	cout << "Looping thru a vector of shared pointers of ints:" << endl;
	for(const auto &i : vec){
		cout << "*i: " << *i << endl;
	}
	
	//make_unique was added in C++14
	//make_shared has been around since C++11
	//make_shared is more efficient than using new
	cout << "Reinitializing sptr0 with make_shared" << endl;
	sptr0 = make_shared<int>(100);
	cout << "Assigning sptr1 to sptr0" << endl;
	sptr1 = sptr0;
	cout << "sptr0.use_count(): " << sptr0.use_count() << endl;
	cout << "sptr1.use_count(): " << sptr1.use_count() << endl;
	cout << "vector still works, oddly enough:" << endl;
	vec.push_back(sptr0);
	//what if I try to re-add something that might already be in there?
	vec.push_back(sptr1);
	//apparently no problem
	for(const auto &i : vec){
		cout << "*i: " << *i << endl;
	}
	
	//What if we pass a shared pointer as a parameter by value?
	cout << "use_count of sptr0 before shared_ptr_param_test: " << sptr0.use_count() << endl;
	shared_ptr_param_test(sptr0);
	cout << "use_count of sptr0 after shared_ptr_param_test: " << sptr0.use_count() << endl;
	
	//When they go out of scope, the last shared pointer that references an object is the one responsible for cleanup; but that's something I don't have to worry about
}

void shared_ptr_param_test(shared_ptr<int> sptr){
	cout << "If passing a shared pointer as a parameter by value, it makes a copy of the pointer itself, not the thing it points to." << endl;
	cout << "use_count of sptr: " << sptr.use_count() << endl;
}

class B; //forward declaration, so that class A can use it before it's implemented

class A{
	shared_ptr<B> b_ptr;
	public:
		void set_B(shared_ptr<B> &bp){b_ptr = bp;}
		A(){cout << "A ctor" << endl;}
		~A(){cout << "A dtor" << endl;}
};

class B{
	//shared_ptr<A> a_ptr;
	weak_ptr<A> a_ptr;
	public:
		void set_A(shared_ptr<A> &ap){a_ptr = ap;}
		//void set_A(weak_ptr<A> ap){a_ptr = ap;}
		//Interestingly, we don't have to make this parameter a weak pointer to fix the problem
		B(){cout << "B ctor" << endl;}
		~B(){cout << "B dtor" << endl;}
};

void weak_ptr_tests(){
	//unlike shared pointer, weak pointer does not participate in owning relationship
	//a weak pointer is always created from a shared pointer; doesn't affect use_count
	//used to prevent strong reference cycles
	//If Class A has a shared_ptr that refers to Class B that has a shared_ptr that refers to A, then this prevents heap deallocation; 
	//OTOH, if A has a shared_ptr that refers to B which has a weak pointer that refers to A, then heap storage will be deallocated properly
	//A a;
	//B b;
	shared_ptr<A> a_ptr = make_shared<A>();
	shared_ptr<B> b_ptr = make_shared<B>();
	a_ptr->set_B(b_ptr);
	b_ptr->set_A(a_ptr);
	//If B uses a shared pointer, then the circular reference prevents cleanup
	//If B uses a weak pointer, then there is no circular reference, & cleanup is good

	//Note, there is no make_weak; just cast a shared as a weak;
	//weak_ptr<A> test = make_weak<A>();
	weak_ptr<A> test = a_ptr;
	//Does it work in the other direction?
	//shared_ptr<A> a_ptr0 = test;
	//No: error: no viable conversion from 'weak_ptr<A>' to 'shared_ptr<A>'
}

void custom_deleter_tests(){
	//test of custom deleter using a function:
	cout << "Test of custom deleter using a function for a shared pointer..." << endl;
	shared_ptr<SomeClass> sc_shared_ptr0 {new SomeClass{"sc_shared_ptr0"}, custom_deleter };
	//cout << "Test of custom deleter using a function for a unique pointer..." << endl;
	//unique_ptr<SomeClass> sc_unique_ptr0 {new SomeClass{"sc_unique_ptr0"}, custom_deleter};
	
	//tests of custom deleter using a lambda:
	cout << "Test of custom deleter using a lambda for a shared pointer..." << endl;
	shared_ptr<SomeClass> sc_shared_ptr1 (new SomeClass{}, [] (SomeClass *sc_shared_ptr1){
		//Note: this and the destructor message show up after "Done"
		cout << "Using custom deleter via lambda for a shared pointer" << endl;
		delete sc_shared_ptr1;
	});
	
	/*
	cout << "Test of custom deleter using a lambda for a unique pointer..." << endl;
	unique_ptr<SomeClass> sc_unique_ptr1 (new SomeClass{}, [] (SomeClass *sc_unique_ptr1){
		//Note: this and the destructor message show up after "Done"
		cout << "Using custom deleter via lambda for a unique pointer" << endl;
		delete sc_unique_ptr1;
	});
	Supposedly possible with unique pointer, but haven't seen it work yet
	*/
}

void custom_deleter(SomeClass *a_ptr){
	//uncommon need to do more than just destroy object on the heap;
	//achievable via functions, lambdas, and others
	//not available if the smart pointer is made with make_shared or make_unique
	cout << "Deleting smart pointer to SomeClass object from function " << __func__ << endl;
	//__func__ = this function's name
	delete a_ptr;
	//Gets much more complicated when you've got raw pointers to c-structures that are used in c-frameworks which don't have destructors
}

//Section 17 Challenge 1
unique_ptr<vector<shared_ptr<SomeClass>>> make(){
	/*
	If we want to pre-populate the vector, uncomment this stuff
	shared_ptr<SomeClass> sp0 = make_shared<SomeClass>("0");
	shared_ptr<SomeClass> sp1 = make_shared<SomeClass>("1");
	shared_ptr<SomeClass> sp2 = make_shared<SomeClass>("2");

	vector<shared_ptr<SomeClass>> vec;
	vec.push_back(sp0);
	vec.push_back(sp1);
	vec.push_back(sp2);
	*/

	//unique_ptr<vector<shared_ptr<SomeClass>>> up = make_unique <vector<shared_ptr<SomeClass>>>();//vec);
	//return up;
	return make_unique <vector<shared_ptr<SomeClass>>>();//vec);
}
	
bool fill(vector<shared_ptr<SomeClass>> &vec, int num){
	if (num <= 0) {
		cout << "Input must be greater than 0, not " << num << endl;
		return false;
	}
	if (num > 100) {
		cout << "Input must be less than or equal to 100, not " << num << endl;
		return false;
	}
	for (int i = 0; i < num; i++){
		//Alternatively, populate with randoms, or with more user input
		//shared_ptr<SomeClass> sp = make_shared<SomeClass>(to_string(i));
		//vec.push_back(sp);
		vec.push_back(make_shared<SomeClass>(to_string(i)));
	}
	return true;
}

void display(const vector<shared_ptr<SomeClass>> &vec){
	cout << "Here are the contents:\n";
	for(const auto sp : vec){
		cout << sp->getName() << " ";
	}
	cout << endl;
}

