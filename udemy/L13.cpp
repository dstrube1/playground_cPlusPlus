#include <iostream> 
#include <thread>
#include <climits>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L13.o L13.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L13.o

Multithreading
Starting here:
https://www.geeksforgeeks.org/multithreading-in-cpp/#
*/

void func0();
void func1(string s);
void func2(string s1, string s2);

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "Before creating the threads...\n";
	
	// Create threads that runs the function func
    thread t0(func0);
    thread t1(func1, "1");
    thread t2(func2, "1", "2");
    
    //Adding a delay before join (and the following printout) shows that the thread starts executing before join, in fact as soon as the thread is created
    for (int i = 0; i < INT_MAX / 2; i++){}
    
    cout << "After creating the threads, before joining...\n";
    
    // Main thread waits for threads to finish
    t0.join();  
    t1.join();  
    t2.join();  
    
    cout << "Main thread finished.";
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

// Functions to be run by the thread
void func0() {
    cout << "Hello from func0!" << endl;
}

void func1(string s) {
    cout << "Hello from func1: " << s << endl;
}

void func2(string s1, string s2) {
    cout << "Hello from func2: " << s1 << ", " << s2 << endl;
}