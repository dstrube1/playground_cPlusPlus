#include <iostream> 
#include <cassert>
#include <mutex>

/*
# To compile:
g++ -std=c++20 -o RingBuffer.o RingBuffer.cpp

# without -o, outputs to default a.out
# without -std=c++20, std::scoped_lock calls fail

# To run:
./RingBuffer.o

*/

template<typename T>
struct RingBuffer
{
    RingBuffer(size_t capacity)
    {
        _capacity = capacity;
        _data = new T[_capacity];
        _writer = 0;
        _reader = 0;
        _size = 0;
    }
    
    ~RingBuffer(){
        delete[] _data;
    }
    
    size_t size()
    {
        //_m.lock();

        return _size;

        //_m.unlock();
    }

    void enqueue(const T& e)
    {
        //_m.lock(); 
        //std::lock_guard<std::mutex> lock(_m);
        std::scoped_lock lock(_m);

        if (size() >= _capacity) { 
        	// If using plain mutex.lock(), it doesn't get unlocked when error is thrown
        	throw std::runtime_error("Buffer is full"); 
        }

        _data[_writer % _capacity] = e;
        _writer = _writer + 1;
        _size = _size + 1;
        //_m.unlock();
    }

    T dequeue()
    {
        //_m.lock(); 
        std::scoped_lock lock(_m);
        //std::unique_lock<std::mutex> lock(_m);
        //std::lock_guard<std::mutex> lock(_m);
        //TODO: replace with context aware mutex

        if (size() == 0) { throw std::runtime_error("Buffer is empty"); }

        auto popped = _reader % _capacity;
        _reader = _reader + 1;  
        _size = _size - 1;
        //_m.unlock();
        return _data[popped];

        
    }

private:
    std::mutex _m;
    T* _data;
    uint16_t _capacity, _reader, _writer, _size;
};

int main(int argc, const char* argv[]) 
{
    RingBuffer<int> rb(1);
    /* Test cases */
    rb.enqueue(3);
    assert(rb.size() == 1);
    
    bool error = false;
    try{
        rb.enqueue(4);
    }catch(std::runtime_error e){
        error = true;
    }/*catch(...){
        error = true;
    }*/
    assert(error);
    
    error = false;
    auto popped = rb.dequeue();
    assert(popped == 3);
    assert(rb.size() == 0);
    try{
        popped = rb.dequeue();
    }catch(std::runtime_error e){
        error = true;
    }
    assert(error);
    
    std::cout << "Success!" << std::endl;
    
    return 0;
}
