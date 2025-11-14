#include <iostream>

/**
 *
 *
 */

// Simple buffer managing a dynamic array of integers

class DataBuffer{
	int* data;
	size_t size;
	public:
		DataBuffer(size_t n) : size(n){
			data = new int[n];
		}
		
		~DataBuffer(){ 
			delete[] data; 
		}
		
		//Copy constructor duplicates the pointer handle
		DataBuffer(const DataBuffer& other){
			data = other.data;
			size = other.size;
		}
		
		int get(size_t indx) const{
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
    buffer1.set(10, 100);
    DataBuffer buffer2 = buffer1;
    std::cout << buffer2.get(10) << std::endl;
}

