#include <iostream>
#include <complex>

//compiling and running
/*
# To compile:
# most basic:
g++ -o complexTest.o complexTest.cpp
# without -o, outputs to default a.out

# To run:
./complexTest.o

From https://en.cppreference.com/w/cpp/numeric/complex/proj.html

*/

int main()
{
    std::complex<double> c1(1, 2);
    std::cout << "proj" << c1 << " = " << std::proj(c1) << '\n';	// (1,2)
	
    std::complex<double> c2(INFINITY, -1);
    std::cout << "proj" << c2 << " = " << std::proj(c2) << '\n';	// (inf, -0)
	
    std::complex<double> c3(0, -INFINITY);
    std::cout << "proj" << c3 << " = " << std::proj(c3) << '\n';	// (inf, -0)
    
	std::cout << "\nDone\n";
	return 0;
}

