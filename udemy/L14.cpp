#include <iostream> 
#include <vector>
#include <cstdlib> //required for rand()
#include <ctime> //required for time()

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L14.o L14.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail, and the tick marks in 100'000'000 fail

# To run:
./L14.o

Sorting and searching

*/


//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	cout << "\nRandom and time stuff:\n";
	cout << "RAND_MAX here is: " << RAND_MAX << endl; // 2,147,483,647 =~ 2 billion; guaranteed to be at least 32,767
	const int min = 1; //lower bound (inclusive)
	const int max = 100; //upper bound (inclusive)
	int random_number = -1;
	const int count = 10;
	//seed the random number generator
	srand(time(nullptr));
	cout << "time(nullptr): " << time(nullptr) << endl;
	cout << count << " random numbers: ";
	while (random_number != max && random_number != min){
		random_number = rand() % max + min;
		cout << random_number << " ";
	}
	cout << endl;

	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

