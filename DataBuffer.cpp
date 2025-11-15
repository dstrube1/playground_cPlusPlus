#include <iostream>

/**
# To compile:
g++ -o DataBuffer.o DataBuffer.cpp
g++ -std=c++14 -o DataBuffer.o DataBuffer.cpp

# without -o, outputs to default a.out
# without -std=c++14, this part of deep copy constructor fails: data (new int[n]{})

# To run:
./DataBuffer.o

*/

// Simple buffer managing a dynamic array of integers

class DataBuffer{
	int* data;
	size_t size;
	public:
		// Meh
		/* Meh - Copy constructor
		DataBuffer(size_t n) : size(n){
			data = new int[n];
		}
		*/
		// Better - deep copy constructor: 
		DataBuffer(size_t n) : size(n), data (new int[n]{}) {}
		
		// Destroy - no need to improve anything here
		~DataBuffer(){ 
			delete[] data; 
		}
		
		// Meh
		// Copy constructor duplicates the pointer handle
		/*
		DataBuffer(const DataBuffer& other){
			data = other.data;
			size = other.size;
		}
		*/
		// Better:
		// Deep copy constructor:
		DataBuffer(const DataBuffer& other)
			: size(other.size), data (new int[other.size])
		{
			std::copy(other.data, other.data + other.size, data);
		}
		
		// (Overloading) Copy assignment operator (deep copy)
		// aka, rule of 3
		DataBuffer& operator=(const DataBuffer& other) {
			if( this != &other) { 
				// interesting - why not assign to self? 
				//oh, because it'd be redundant / a waste of time - self is already self
				delete[] data;
				size = other.size;
				data = new int[size];
				std::copy(other.data, other.data + size, data);
			}
			return *this;
		}
		/*
		// Alternative #1: Make it non-copyable; delete the copy constructor and assignment override
		DataBuffer(const DataBuffer&) = delete;
		DataBuffer& operator=(const DataBuffer&) = delete;
		// Prevents accidental shallow copies.
		// Often used in RAII classes.
		
		// Alternative #2: Use std::vector<int> instead of raw new[]
		#include <vector>
		//declare data member:
		std::vector<int> data;
		// in get / set:
		if (idx < data.size())...
		// No manual memory management.
		// Automatic deep copy.
		// No need for Rule of 3.
		// Much safer & idiomatic C++.
		
		// Other options:
		// 1- rule of 5: move constructor / assignment
		// 2- smart pointer (std::unique_ptr<int[]>)
		// 3- bounds-checked access that throws exceptions
		*/ 
		
		int get(size_t idx) const{
			if(idx < size){ // issue #1: < was <=
				return data[idx];
			}
			return -1;
		}
		
		void set(size_t idx, int value){
			if(idx < size){ // issue #2: no check for size
				data[idx] = value;
			}
		}
};

int main()
{
    DataBuffer buffer1(10);
    buffer1.set(9, 100); //Issue #3: first param was 10, out of bounds
    DataBuffer buffer2 = buffer1;
    std::cout << "Test of DataBuffer's overloaded copy assignment operator (deep copy):";
    std::cout << std::endl; 
    std::cout << buffer2.get(9) << std::endl; // was also 10 here
}

