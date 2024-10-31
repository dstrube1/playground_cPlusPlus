#include <iostream>
#include <vector>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -o L1.o -std=c++14 L1.cpp
# without -o, outputs to default a.out
# without the -std=c++14, get errors from declarations of arrays, vectors, and pointers

# To run:
./L1.o

*/

int main()
{

  //Arrays 
  /* */
  //most of these work on https://cpp.sh/  (except of course arr5), but not when compiling locally on my Mac with just "g++ -o this.o this.cpp", where only arr4 compiles.
  //However, compiling with specifying the c++ version number (like "g++ -std=c++14 -o this.o this.cpp" or "g++ -std=c++17 -o this.o this.cpp") works
  const int size = 2;

  int arr1 [5] {0,1,2,3,4};	//declare and initialize array with literal size; not available in all versions of c++, but is valid in c++14
  int arr2 [size] {0,1}; //declare and initialize array with const size
  int arr3 [] {1,2,3}; //initialize array so that size is inferred
  int arr4 [size]; //legal to declare without initializing as long as there is size
  //int arr5 []; //illegal to declare without size AND without initializing
  //if initialize an array with empty braces, then it will be filled with 0s:
  int arrEmpty[size] {};

  for (int i = 0; i < size; i++){
  	arr4[i] = i;
  }
  for (int i = 0; i < size; i++){
  	cout << "arr4[" << i << "] = " << arr4[i] << "; ";
  }
  cout << endl;
  cout << "Testing out of bounds... \n";
  //int test = arr4 [size]; //This gives a warning when compiling, but no error when running
  for (int i = size; i < size * 10; i++){
  	cout << "arr4[" << i << "] = " << arr4[i] << "; ";
  	if (i % 12 == 0) cout << endl;
  }
  cout << endl;
  short size0; 
  size0 = sizeof(arr4);
  cout << "Size of arr4: " << size0 << endl; // 8, 4 * const int size (2)
  int arr5 [100];
  size0 = sizeof(arr5);
  cout << "Size of arr5: " << size0 << endl; // 400, 4 * 100
  //What if I try to cin outside of bounds
  //cout << "Enter a number please: ";
  //cin >> arr4[2]; //no crash, just a warning from the compiler
  int arr2Da [size][size]{{}}; //2x2, filled with 0s
  for (int i = 0; i < size; i++){
  	for(int j = 0; j < size; j++){
  		arr2Da[i][j] = i + j;
  		cout << "arr2Da[" << i << "][" << j <<"] = "<< arr2Da[i][j] << "\n";
  	}
  }
  int test[0];
  /**/

  //vectors
  /**/
  vector <char> vchars {'a', 'e', 'i', 'o', 'u'}; //initializing with values
  vector <int> vints (10); //initializing with size
  vector <int> vints0 (10, 1); //initializing with size & all default values
  //initializing with () & {} is not allowed
  
  int size1;
  size1 = sizeof(vchars);
  cout << "Sizeof empty vector of chars: " << size1 << endl;
  size1 = sizeof(vints);
  cout << "Sizeof empty vector of ints: " << size1 << endl;
  //^both are 24 (bytes?) by default
  
  cout << "Actual size of empty vector of ints: " << vints.size() << endl;
  //from https://cplusplus.com/reference/vector/vector/
  cout << "Max size of empty vector of ints: " << vints.max_size() << endl;
  cout << "Capacity of empty vector of ints: " << vints.capacity() << endl;
  
  for(int i = 0; i < 100; i++){
  	vints[i] = i;
  	//This will halt at the limit of the vector actual size: 10
    //cout << "vints.at("<<i<<"): "<<vints.at(i)<<"\n";
    //This will go as far as you like:
    //cout << "vints["<<i<<"]:"<<vints[i]<<"\n";
    
    //If you put this before calls to at (or even after), then the above limit 
    //won't apply because this actually grows the vector
  	//vints.push_back(i * 2);
  }
  //Testing bounds
  //cout << "Enter a letter: ";
  //cin >> vchars.at(6); //Before the program stops to wait for user input here:
  //"libc++abi: terminating with uncaught exception of type std::out_of_range: vector"

  //using .at() function:
  //This similarly crashes:
  //vints.at(size) = size;
  //size = sizeof(vints);
  //cout << "Size of filled vector of ints: " << size << endl;//no change, still 24
  
  //2D vector
  vector<vector<int>> vints2d
  	{
  		{1,2,3,4},
  		{1,2,3},
  		{1,2,3,5}
  	};
  size1 = sizeof(vints2d);
  cout << "Sizeof 2d vector of ints: " << size1 << endl;
  cout << "2d vector of ints.size: " << vints2d.size() << endl;
  cout << "2d vector of ints[0].size: " << vints2d[0].size() << endl;
  cout << "2d vector of ints[1].size: " << vints2d[1].size() << endl;
  cout << "2d vector of ints.max_size: " << vints2d.max_size() << endl;
  /**/

  //extern, warning, and error
  /**/
  //extern ex isn't defined here, or anywhere, so the build throws a linker error, but only if we try to use ex
  //cout << "ex is " << ex << endl;

  //this throws a warning, but not an error
  int y = 1 / 0;
  //what if I try to print it out?
  //cout << "y is " << y << endl;
  //Floating point exception (core dumped)
  /**/
  
  //int max via brute force
  /*   */
	//This takes a little while
	int i = 1;
	 int i_p = 0;
	 long count = 0;
	
	while (i_p < i){
		i++;
		i_p++;
		count++;
		if (count % 10000000 == 0)
			printf(".");
			//cout<<".";
	}
	printf("\n");
	printf("Max of int found : %li\n", count);
/*  */
	cout << "Done" << endl;
	
	return 0;
}

