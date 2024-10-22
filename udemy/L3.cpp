#include <iostream>
#include <vector>

//Started taking notes while going thru this course:
//https://gbg.udemy.com/course/beginning-c-plus-plus-programming/
//Notes started getting cumbersome, so splitting them up into multiple files

using namespace std;

/*
# To compile:
g++ -o -std=c++14 L3.o L3.cpp
# without -o, outputs to default a.out
# without -std=c++14 , can't use tick marks

# To run:
./L3.o

*/

int main()
{
	//for loops
	/**/
	//this is valid and endless:
	//for(;;){cout<<".";}
	
	//what about just initialization (1st) and change (3rd), no 2nd step (test)?
	//Yes:
	for (int i = 1;;i++){
		//Remember: must compile with c++14 to get tick marks in numbers
	
		//this doesn't seem to overflow and is endless unless there's a break within
		if (i % 10'000'000 == 0) {
			// this batches up a while and then prints out a bunch at once
			cout<<".";
		}
		
		if (i % 100'000'000 == 0) {		
			break; 
		}
	}
	cout<<"Broke out\n";
	
	//range-based for loop
	int arr[] = {1,2,3};
	for (auto i : arr){
		cout << i << " ";
	}
	cout << endl;
	
	vector <int> vints {1,2,3,4};
	for (auto i : vints){
		cout << i << " ";
	}
	cout << endl;
	
	//also works on collections of characters, aka strings
	string str = "test";
	for(auto c : str){
		cout << c << " ";
	}
	cout << endl;
	/**/	

	//Letter Pyramid 
	/**/string input {};
	cout << "Enter some string: ";
	getline(cin, input);
	for(int i=0; i < input.length(); i++){
		for(int j = 1; j < input.length() - i; j++)
			cout << " ";
		for(int k = 0; k <= i; k++)
			cout << input.at(k);
		if(i > 0){
			for (int h = i - 1; h >= 0; h--)
				cout << input.at(h);
		}
		cout << endl;
	}/**/

	//C-style string
	/**/
	//char ok[]; //is it okay to declare a c style string with no size specified and no initialization? no
	char ok[] = "okay"; //what about no size specified and initialization? yes
	cout << "size of ok[] ''okay'': " << sizeof(ok) << endl;
	size_t size = sizeof(ok); //the proper datatype of sizes
	//https://en.cppreference.com/w/cpp/types/size_t
	char ok0[size]; //is this okay? yes
	char test [8];
	cout << "test before assignment:'" << test << "'" << endl;
	//test="blah";//error: incompatible types in assignment of ‘const char [5]’ to ‘char [8]’
	//test = "blah123";//same size, still error: invalid array assignment
	strcpy(test, "blah");//OK; defined here: #include <cstring>
//	strcpy(test, "blahblahblah");//copying to out of bounds (with compiler warning) - works but potentially dangerous

	strcat(test, "12345"); //concatenate
	cout << "test:'" << test << "'" << endl;
	int length = strlen(test); //concatenating can safely affect length
	cout << "length: " << length << endl;
	int compare = strcmp(test, "test"); // compare
	cout << "compared to 'test': " << compare << endl;
	char line[4];
	cout << "enter some text for line[4] (using getline(line,5)): ";
	cin.getline(line,5); //getline's 2nd parameter specifies the length it will get up to; 
	//if the value of the 2nd parameter is greater than the size of the cstyle string, it will stop at the size of the cstyle string
	//just using 'cin >> line' stops reading at whitespace; getline does not stop at whitespace
	cout << "you entered: " << line << endl;
	/**/

	//C++ String
	/**/
 	string s = "test";
 	int start_index = 0;
 	int length0 = 2;
 	string s1 = "e";
	s = s.substr(start_index, length0);
	int i = s.find(s1);
	int j = s.find(s1, start_index);
	//int k = s.rfind(...
	cout << "in string s ('test'), index of '': " << s.find("") << endl; //0
	cout << "string::npos: " << string::npos << endl; // 18446744073709551615, or 18,446,744,073,709,551,615, ~18 quintillion
	//s.erase(start_index, length);
	//s.clear(); //empties the string
	string s0 = {s, 1, 2};
	s = s + "def"; //ok
	//s = "123" + "456" + s; //compiler error
	s = s + "123" + "456"; //no compiler error

	cout << "s: " << s << endl;
	cout << "s0: " << s0 << endl;
 	/**/
 	
	cout << "Done\n";
	return 0;
}

