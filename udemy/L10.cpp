#include <iostream> //provides definitions for formatted input and output from/to streams
#include <fstream> // "														" 	file streams

//#include <iomanip> //provides definitions for manipulators used to format stream I/O
//NOTE: fstream seems to include iomanip, so if fstream is included, then iomanip is redundant

//#include <string>
//#include <vector>

using namespace std;

/*
# To compile:
g++ -std=c++14 -o L10.o L10.cpp

# without -o, outputs to default a.out
# without -std=c++14 , {} initializers fail

# To run:
./L10.o

I/O & Streams

Commonly used stream classes:
ios: basic support for formatted and unformatted IO ops; base class for most other classes
ifstream: high-level input ops on file streams
ofstream: high-level output ops on file streams
fstream: high-level I/O ops on file streams; derived from ifstream and ofstream
stringstream: high-level I/O ops on memory based strings; derived from istringstream and ostringstream

Global stream objects: initialized before main executes
instance of istream:
cin: by default connected to standard input device (keyboard); input won't be automatic until user hits Enter
instances of ostream:
cout: won't output until the stream buffer is full, OR we provide a std::inline, OR stream is flushed
cerr: unbuffered, best used for errors
clog: unbuffered, best used for log messages

*/

void booleanStreamManipulation();

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////BEGIN main
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//Stream manipulation: 
	// - can be used on input and output streams
	// - time of the effect on the stream varies
	// - can be used as member function or manipulator:
	//member function / method:
	cout.width(10);
	//manipulator:
	cout << setw(10); //overloading the insertion operator
	//manipulator will fail to compile if iomanip (or something else that includes it) isn't included
	//stream manip method won't, but manipulator is usually  preferred practice
	
	//common stream manipulators:
	/*
	Boolean: boolalpha, noboolalpha
	Integer: dec, hex, oct, showbase, noshowbase, showpos (show postive '+' symbol), noshowpos, uppercase, nouppercase
	Floating point: fixed, scientific, setprecision, showpoint, noshowpoint, showpos, noshowpos
	Field width, justification, and fill: setw, left, right, internal, setfill
	Others: endl, flush (like endl, but doesn't add a newline), skipws, noskipws, ws (whitespace, usually for input streams)
	*/
	
	booleanStreamManipulation();
	
	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void booleanStreamManipulation(){
	const bool T = true;
	const bool F = false;
	cout << "Pre boolean stream manipulation (ie, default): " << endl;
	cout << "true: " << T << endl;
	cout << "false: " << F << endl;

	cout << "Post boolalpha: " << endl;
	cout << boolalpha;
	cout << "true: " << T << endl;
	cout << "false: " << F << endl;
	//Can toggle back and forth between boolalpha and noboolalpha, 
	//but it will stay that way for the remainder of the program
	
	//formatting boolean types (?):
	//method version:
	cout.setf(std::ios::boolalpha);
	//Interesting: this throws an error:
	//cout.setf(ios::noboolalpha);
	//error: no member named 'noboolalpha' in 'std::ios'; did you mean 'boolalpha'?
	//manipulator version:
	cout << reset
}