#include <iostream>
#include <string>
#include <cmath> //required for sqrt() & abs()
#include <cstdlib> //required for rand()
#include <ctime> //required for time()


//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -o L04.o L04.cpp
# without -o, outputs to default a.out

# To run:
./L04.o

*/

void static_test();
inline int add(int a, int b) { return a + b; }
unsigned long long factorial(unsigned long long n);
double a_penny_doubled_everyday(int days, double total_amount );

int main()
{
	//will this crash?
	//char crash[string::npos];
	//nope, won't even build: 
	//in Rocky Linux:
	//error: size of array ‘crash’ is negative
	//todo: char crash[math.abs(string::npos)];
	//on Mac:
	//error: array is too large (18446744073709551615 elements)

	//Maths
	/**/
	cout << "Various maths:\n";
	cout << "sqrt(400.0): " << sqrt(400.0) << endl;
	
	long double nposLD = string::npos; 
	cout << "absolute value of string::npos as long double: " << abs(nposLD) << endl; //1.84467e+19

	long long int nposLLI = string::npos; 
	cout << "absolute value of string::npos as long long int: " << abs(nposLLI) << endl; // = 1

	long long unsigned nposLLU = string::npos; 
	cout << "string::npos as long long unsigned: " << nposLLU << endl; //18446744073709551615
	cout << "abs(string::nposLLU): error: call of overloaded ‘abs(long long unsigned int&)’ is ambiguous" << endl; 
	
	//just declaring this doesn't seem to do any harm
	short arr[nposLLU];

	int a = -1;
	int b = -1;
	cout << "-1 + -1 = " << a + b << endl;
	/**/

	//more getline stuff:
	//getline(cin, s); //read line from cin stream into s until \n
	//getline(cin, s, 'x'); //read line until \n or 'x'

	//Random and time
	/**/
	cout << "\nRandom and time stuff:\n";
	cout << "RAND_MAX here is: " << RAND_MAX << endl; // 2,147,483,647 =~ 2 billion; guaranteed to be at least 32,767
	const int min = 1; //lower bound (inclusive)
	const int max = 100; //upper bound (inclusive)
	int random_number;
	const int count = 10;
	//seed the random number generator
	srand(time(nullptr));
	cout << "time(nullptr): " << time(nullptr) << endl;
	cout << count << " random numbers: ";
	for (int i=0; i < count; i++){
		random_number = rand() % max + min;
		cout << random_number << " ";
	}
	cout << endl;
	/**/
	
	/**/

	cout << "\nStatic function:\n";
	static_test();
	//cout << "is i0 accessible here?" << i0; no
	//Note that the value of static int i0 persists after the function is called
	static_test();
	/**/

	/**/
	cout << "\nRecursive function #1:\n";
 	cout << "52! = " << factorial(52) << " (but not really...)"<< endl; // 9994050523088551936 = 9,994,050,523,088,551,936 = almost 10 quintillion; but maybe not:
	//cout << "53! = " << factorial(53) << endl; // 13175843659825807360
	//cout << "54! = " << factorial(54) << endl; // 10519282829630636032
	//cout << "55! = " << factorial(55) << endl; // 6711489344688881664
	cout << "This function stops being reliable around 20...\n";
	for (unsigned long long i = 0; i < 22; i++){ //results start getting unreliable around 20
		cout << i << "! = " << factorial(i) << endl; 
	} //https://zeptomath.com/calculators/factorial.php?number=52&hl=en

	int days = 25; 
	double total_amount = 0.01;
	cout << "\nRecursive function #2:\n";
	cout << "a_penny_doubled_everyday for " << days << " days:\n";
	total_amount = a_penny_doubled_everyday(days, total_amount);
	cout << "total_amount = $" << total_amount << endl;
	//Interesting that this starts rounding on day 5:
	//5242.88 * 2 = 10485.76, but output says 10485.8

/**/

	
  cout << "Done\n";
  return 0;
}

void static_test(){
	static int i0 = 0;
	cout << "i0 before increment: " << i0 << endl;
	i0++;
	cout << "i0 after increment: " << i0 << endl;
}

//recursive function #1
unsigned long long factorial(unsigned long long n){
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

//recursive function #2
double a_penny_doubled_everyday(int days, double total_amount) {    
	cout << "day " << days << ", total amount = " << total_amount << endl;
    if (days <= 1) return total_amount;
    total_amount = total_amount * 2;
    total_amount += a_penny_doubled_everyday(--days, total_amount);
    return total_amount;
 }

