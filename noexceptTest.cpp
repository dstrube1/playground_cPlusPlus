#include <iostream>
#include <vector>
//This is included in the sample code in noexcept.html (specified below), but doesn't seem actually necessary:
//#include <utility> 

//Bad habit:
//using namespace std;

/*
# To compile:
# most basic:
g++ -std=c++11 -o noexceptTest.o noexceptTest.cpp

# without -o, outputs to default a.out

# without -std=c++11 (or 14, or 17...), 2 warnings and 12 errors, such as:
	1- error: expected function body after function declarator
void no_throw() noexcept;

	2- warning: 'auto' type specifier is a C++11 extension [-Wc++11-extensions]
auto lmay_throw = []{};

	3- error: expected expression
auto lmay_throw = []{};

	4- error: use of undeclared identifier 'noexcept'

# To run:
./noexceptTest.o

From https://en.cppreference.com/w/cpp/language/noexcept.html

My contributions:
1- removing apparently unnecessary #include <utility> 
2- specifying how to build successfully 
3- specifying output in comments

*/

void may_throw();
void no_throw() noexcept;
auto lmay_throw = []{};
auto lno_throw = []() noexcept {};

class T
{
public:
    ~T(){} // dtor prevents move ctor
           // copy ctor is noexcept
};
 
class U
{
public:
    ~U(){} // dtor prevents move ctor
           // copy ctor is noexcept(false)
    std::vector<int> v;
};
 
class V
{
public:
    std::vector<int> v;
};

int main()
{
	T t;
    U u;
    V v;
 
    std::cout << std::boolalpha <<
        "may_throw() is noexcept(" << noexcept(may_throw()) << ")\n" 			// false
        "no_throw() is noexcept(" << noexcept(no_throw()) << ")\n"				// true
        "lmay_throw() is noexcept(" << noexcept(lmay_throw()) << ")\n"			// false
        "lno_throw() is noexcept(" << noexcept(lno_throw()) << ")\n"			// true
        "~T() is noexcept(" << noexcept(std::declval<T>().~T()) << ")\n"		// true
        // note: the following tests also require that ~T() is noexcept because
        // the expression within noexcept constructs and destroys a temporary
        "T(rvalue T) is noexcept(" << noexcept(T(std::declval<T>())) << ")\n"	// true
        "T(lvalue T) is noexcept(" << noexcept(T(t)) << ")\n"					// true
        "U(rvalue U) is noexcept(" << noexcept(U(std::declval<U>())) << ")\n"	// false
        "U(lvalue U) is noexcept(" << noexcept(U(u)) << ")\n"					// false
        "V(rvalue V) is noexcept(" << noexcept(V(std::declval<V>())) << ")\n"	// true
        "V(lvalue V) is noexcept(" << noexcept(V(v)) << ")\n";					// false
        
	std::cout << "\nDone\n";
	return 0;
}

