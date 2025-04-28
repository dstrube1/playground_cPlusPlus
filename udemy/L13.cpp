#include <iostream> 
#include <thread>
#include <climits> //for INT_MAX
#include <vector>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L13.o L13.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail, and the tick marks in 100'000'000 fail

# To run:
./L13.o

Multithreading
Starting here:
https://www.geeksforgeeks.org/multithreading-in-cpp/#
See also: Thread Management section in ^

*/

void func0(); //function pointer
void func1(string s1, string s2);
void func2(int j);

struct Square_Functor { //from L11
	void operator()(int x){ // overload () operator
		cout << "Square_Functor (struct): " << (x * x) << " " << endl;
	}
};

class Double_Functor { 
// not to be confused with double Functor (where datatype of input is double)
	private:
		int x;
	public:
		Double_Functor(int x) {this->x = x;} 
		void operator()() const { 
			cout << "Double_Functor (class): " << (x + x) << " " << endl;
		}
};

class CWF{ //class with functions, Non-Static and Static 
	public:
		//Non-Static Member Function
		void f1(int num){ cout << "f1: " << num << " \n"; }
		//Static Member Function
		static void f2(int num){ cout << "f2: " << num << " \n"; }
};

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Before creating the threads...\n";
	
	string s = "a lambda";
	
	// Create threads that run... 
	//0 - a function pointer 
    thread t0(func0);
    //1 - a lambda
    thread t1([](string t){cout << "Hello from " << t << " " << endl; }, s);
    //2 - a function with parameters
    thread t2(func1, "2", "3");
    //3 - a function object (aka functor) from a struct
    Square_Functor square_functor;
    thread t3(square_functor, 3);
	//4 - a function object (aka functor) from a class
	Double_Functor double_functor(3);
	thread t4(double_functor);
	//Non-Static and Static Member Function
	CWF cwf;
	//non-static
	thread t5(&CWF::f1, &cwf, 4); //note the & in front of CWF
	//static
	thread t6(&CWF::f2, 5); //note the & in front of CWF
	
    //syntax is like this:
    //thread thread_name(callable);
	//where callable is: 
	//	function pointer, function object, lambda, or member function (static or non)
    
    //Adding a delay before join (and the following printout) shows that the thread starts executing before join, in fact as soon as the thread is created
    for (int i = 0; i < INT_MAX / 2; i++){}
    
    cout << "After creating the threads, before joining...\n";
    
    // Main thread waits for threads to finish
    t0.join();  
    t1.join();  
    t2.join();  
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    /*
    Sometimes the output is like this:
Before creating the threads...
Hello from func1: Hello from func2: Hello from func0!
1
2, 3
After creating the threads, before joining...
    */
    
    cout << "Trying with a vector of threads...\n";
    vector<thread> vec {};
    for (int i = 2; i <= 10; i++){
    	//don't do this:
	    //thread t(func2, i);
	    //vec.push_back(t);
	    
	    vec.emplace_back(func2, i);
	}
	for(auto& t : vec) t.join();
	//if using push_back instead of emplace_back, then the above line gives this:
	//^:  error: calling a private constructor of class 'std::thread'
	//before using emplace_back instead of push_back, this didn't work either:
	//for (int i = 0; i < vec.size(); i++){
	//	vec[i].join();
	//}
    
    cout << "\nMain thread finished.\n";
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

// Functions to be run by the thread
void func0() {
    cout << "Hello from func0 (function pointer)!" << endl;
}

void func1(string s1, string s2) {
    cout << "Hello from func1(s1, s2): " << s1 << ", " << s2 << endl;
}

void func2(int j){
	//this function will be called from a vector of threads;
	//the function will cycle thru a for loop with a large range;
	//the parameter j will determine how large the range is;
	//at intervals in the loop, the function will print out the value of j
	for (int i = 0; i < INT_MAX / j; i++){
		if (i % 100'000'000 == 0) cout << j << " ";
	}
}
