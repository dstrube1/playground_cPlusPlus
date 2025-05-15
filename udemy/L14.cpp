#include <iostream> 
#include <vector>
#include <cstdlib> //required for rand()
#include <ctime> //required for time()
#include <array>

//This is bad practice:
//using namespace std;
//https://www.geeksforgeeks.org/using-namespace-std-considered-bad-practice/#

//but typing "std::" everywhere is annoying, so ...
//Trying to start doing this more:
using std::cout;
using std::endl;
using std::swap;
using std::vector;
using std::array;

/*
# To compile:
g++ -std=c++14 -o L14.o L14.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail, and the tick marks in BIG fail

# To run:
./L14.o

Sorting and searching
Starting here:
https://en.wikipedia.org/wiki/Cycle_sort
and here:
https://www.toptal.com/developers/sorting-algorithms
*/

const int BIG = 1'000;
void print10RandomLists();
void printOneLargeRandomList();
vector<int> getBigRandomVector();
array<int, BIG> getBigRandomLArray();

//template <typename type_array>
//void cycle_sort(type_array *Array, int array_size);

//template <typename T> 
//void cycle_sort(T &arr, int array_size);

template <typename T> 
void displayContainer(const T &container){
	// assuming T is a list, forward_list, vector, deque, or set
	cout << "[ ";
	for (auto c : container) cout << c << " ";
	cout << "]\n";
}

void displayArray(const array<int, BIG> &arr);

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//print10RandomLists();
	//printOneLargeRandomList(); 
	
	//Get a big array or vector of random numbers, then sort it using various algorithms
	vector<int> vec = getBigRandomVector();
	cout << "Vector before sort: \n";
	displayContainer(vec);
	
	//TODO: 
	//cycle_sort(vec, BIG);
	//candidate template ignored: could not match 'type_array *' against 'vector<int>'
	//cout << "After sort: \n";
	//displayContainer(vec);
	
	array<int, BIG> arr = getBigRandomLArray();
	cout << "Array before sort: \n";
	displayArray(arr);
	//cycle_sort(arr, BIG);
	//again -_-:
	//candidate template ignored: could not match 'type_array *' against 'array<int, BIG>'
	//cout << "After sort: \n";
	//displayArray(arr);
	
	//Must get familiar enough with cycle sort (in Java and/or Python), 
	//then come back and try again here
	//THEN update the wikipedia page
	
	cout << "\nDone\n\n";
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////// END main
//////////////////////////////////////////////////////////////////////////////////////////

void print10RandomLists(){
	const int min = 1; //lower bound (inclusive)
	const int max = 100; //upper bound (inclusive)
	int random_number = -1;
	const int count = 10;
	//seed the random number generator
	srand(time(nullptr));
	cout << "time(nullptr): " << time(nullptr) << endl;
	cout << count << " random lists: ";
	for (int i = 0; i < count; i++){
		while (random_number != max && random_number != min){
			random_number = rand() % max + min;
			cout << random_number << " ";
		}
		cout << endl;
		random_number = -1;
	}
}

void printOneLargeRandomList(){
	const int min = 1; //lower bound (inclusive)
	const int max = 100; //upper bound (inclusive)
	int random_number = -1;
	const int count = 1000;
	srand(time(nullptr));
	for (int i = 0; i < count; i++){
		random_number = rand() % max + min;
		cout << random_number << " ";
	}
	cout << endl;
}

/*template <typename type_array>
void cycle_sort(type_array *Array, int array_size){
	//from https://en.wikipedia.org/wiki/Cycle_sort
	//TODO:
	//Does this work for any collection where the items can be accessed with subscript ([]), or only arrays?
	for (int cycle_start = 0; cycle_start < array_size - 1; cycle_start++)
	{
		type_array item = Array[cycle_start];

		int pos = cycle_start;
		for (int i = cycle_start + 1; i < array_size; i++)
			if (Array[i] < item)
				pos += 1;
		if (pos == cycle_start)
			continue;
		while (item == Array[pos])
			pos += 1;

		swap(Array[pos], item);

		while (pos != cycle_start)
		{
			pos = cycle_start;
			for (int i = cycle_start + 1; i < array_size; i++)
				if (Array[i] < item)
					pos += 1;
			while (item == Array[pos])
				pos += 1;

			swap(Array[pos], item);
		}
	}
}*/

/*template <typename T> 
void cycle_sort(T &arr, int array_size){
	//Trying to rewrite this in a way that doesn't break
	//It becomes apparent pretty quickly that the code on the wikipedia page 
	wasn't tested with a std::array, if at all
	
	for (int cycle_start = 0; cycle_start < array_size - 1; cycle_start++)
	{
		T item = arr[cycle_start];
	}
}*/

vector<int> getBigRandomVector(){
	vector<int> vec {};
	int random_number;
	for (int i = 0; i < BIG; i++){
		random_number = rand() % BIG;
		//Can't do this to add / insert:
		//vec[i] = random_number;
		//^=> zsh: segmentation fault  ./L14.o
		vec.push_back(random_number);
	}
	return vec;
}

array<int, BIG> getBigRandomLArray(){
	array<int, BIG> arr;
	int random_number;
	for (int i = 0; i < BIG; i++){
		random_number = rand() % BIG;
		arr[i] = random_number;
	}
	return arr;
}

void displayArray(const array<int, BIG> &arr){
	cout << "[ ";
	for (auto i : arr) cout << i << " ";
	cout << "]\n";
}