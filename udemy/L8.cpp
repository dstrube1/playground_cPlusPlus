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

*/

class SomeClass{
	private:
		string name;
	public:
		SomeClass(string n){name = n;}
		void method(string type){cout<<"method from SomeClass with " << type << " pointer\n";}
		void setName(string n){name = n;}
		~SomeClass(){cout<<"SomeClass destructor for " << name << "\n";}
};

void unique_ptr_tests();
void shared_ptr_tests();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
/**/

	//unique_ptr_tests();
	shared_ptr_tests();

	weak_ptr<SomeClass> wptr;// = new SomeClass("weak");
	//wptr.method("weak");
	//cout << (*ptr) << endl;
	
	//All of these smart pointers will be deleted automatically when they go out of scope
	
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
	cout << "use_count of sptr0 before creating sptr1: " << sptr0.use_count() << endl;
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
	cout << "Reinitializing sptr0 with make_shared" << endl;
	sptr0 = make_shared<int>(100);
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
}

