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
void integerStreamManipulation();
void floatingPointStreamManipulation();
void fieldWidthAlignAndFill();

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
	
	//booleanStreamManipulation();
	
	//integerStreamManipulation();
	
	floatingPointStreamManipulation();
	
	cout << "Done" << endl << endl;
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////END main
//////////////////////////////////////////////////////////////////////////////////////////

void booleanStreamManipulation(){
	//Boolean stream manipulators: boolalpha, noboolalpha
	//Default: noboolalpha
	
	const bool T = true;
	const bool F = false;
	cout << "Pre boolean stream manipulation (ie, default): " << endl;
	//default behavior:
	//cout << noboolalpha;
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
	cout << "Setting boolalpha, method version:\n";
	cout.setf(std::ios::boolalpha);
	cout << "true: " << T << endl;
	cout << "false: " << F << endl;
	
	//Interesting: this throws an error:
	//cout.setf(ios::noboolalpha);
	//error: no member named 'noboolalpha' in 'std::ios'; did you mean 'boolalpha'?

	//Does running this again toggle it back to noboolalpha? No
	/*cout.setf(std::ios::boolalpha);
	cout << "true: " << T << endl;
	cout << "false: " << F << endl;*/
	
	
	//Reset back to default, manipulator version:
	cout << "Reset back to default, manipulator version:\n";
	cout << resetiosflags(ios::boolalpha);
	cout << "true: " << T << endl;
	cout << "false: " << F << endl;
}

void integerStreamManipulation(){
	//Integer stream manipulators: dec, hex, oct, showbase, noshowbase, showpos (show postive '+' symbol), noshowpos, uppercase, nouppercase
	//Defaults: dec, noshowbase, noshowpos, nouppercase
	
	int num {255};
	
	cout << "num in base 10: " << num << endl;
	
	cout << hex;
	cout << "num in base 16: " << num << endl;
	
	cout << oct;
	cout << "num in base 8: " << num << endl;
	
	cout << showbase;
	cout << "showbase: " << num << endl;
	
	cout << dec << showpos;
	cout << "dec showpos: " << num << endl; //only affects dec
	
	cout << hex << uppercase;
	cout << "hex uppercase: " << num << endl; //only affects hex
	
	//using setf:
	//cout.setf(ios::showbase);
	//cout.setf(ios::uppercase);
	//cout.setf(ios::showpos);
	//etc
	
	//reset to defaults:
	//cout << resetiosflags(ios::basefield);
	//cout << resetiosflags(ios::showbase);
	//cout << resetiosflags(ios::showpos);
	//cout << resetiosflags(ios::uppercase);
}

void floatingPointStreamManipulation(){
	//Floating point stream manipulators: fixed, scientific, setprecision, showpoint, noshowpoint, showpos, noshowpos
	//Defaults: 
		//setprecision: number of digits displayed (6)  
		//fixed: not fixed to a specific number of digits after the decimal point
		//noshowpoint: trailing zeroes are not displayed
		//nouppercase: when displaying scientific notation
		//noshowpos: no + for positive numbers (is this changeable?)
	
	//To reset precision later on, must first do this:
	const streamsize ORIGINAL_PRECISION = cout.precision(); 
	//if not parameter, this^ gets precision
	//if yes parameter, this^ sets precision
	cout << "floating point current streamsize: " << ORIGINAL_PRECISION << endl;

	double num;
	num = 12.34;
	cout << "12.34 with defaults: " << num << endl;
	cout << showpoint; //show trailing zeroes up to precision
	cout << "12.34 with showpoint: " << num << endl;

	// {1'234.5678};
	num = 1'234.5678;
	cout << "1,234.5678 with default precision (6 digits): " << num << endl;
	
	num = 123'456'789.987654321;
	cout << "123,456,789.987654321 : " << num << endl;
	
	cout << setprecision(9);
	//alternatively:
	//cout.precision(9); 
	//note the rounding: 123456790
	cout << "123,456,789.987654321 with setprecision(9) : " << num << endl;

	cout << setprecision(6); //set this back to default
	cout << fixed;
	//displays precision 6 from the decimal
	cout << "123,456,789.987654321 with fixed : " << num << endl;

	cout << setprecision(20);
	//interestingly inaccurate
	cout << "123,456,789.987654321 with setprecision(20) : " << num << endl;

	//what if there are fewer than n digits after the decimal, ie, fewer than n significant digits?
	num = 123.0;
	cout << setprecision(6); //set this back to default
	cout << "123.0 with fixed : " << num << endl;
	
	//scientific notation
	num = 123'456'789.987654321;
	cout << setprecision(3); 
	cout << scientific;
	cout << "123,456,789.987654321 with scientific notation : " << num << endl;
	
	cout << uppercase;
	cout << "123,456,789.987654321 with uppercase scientific notation : " << num << endl;

	cout << fixed; //reset scientific	
	cout << showpos;
	cout << "123,456,789.987654321 with positive : " << num << endl;
	
	num = 12.34;
	/*
	how to reset to defaults? 4 steps
	*/
	//1
	cout.unsetf(ios::scientific | ios::fixed);
	//alternatively, that is equivalent to this:
	//cout << resetiosflags(ios::floatfield);
	
	//2
	//cout.unsetf(ios::showpos);
	//or
	cout << resetiosflags(ios::showpos);
	
	//3
	//cout.unsetf(ios::showpoint);
	//or
	cout << resetiosflags(ios::showpoint);
	
	//4
	//Couple ways to do this:
	//cout.precision(ORIGINAL_PRECISION); 
	//But I like this better - this is cleaner (albeit undocumented(?))
	cout << setprecision(-1);
	//https://stackoverflow.com/questions/12560291/set-back-default-floating-point-print-precision-in-c
	
	//5
	//one can't tell if uppercase is still active while scientific is turned off, 
	//but if scientific gets turned back on and uppercase hasn't been reset yet, 
	//then uppercase will still be active
	//cout.unsetf(ios::uppercase);
	//or
	cout << resetiosflags(ios::uppercase);
	
	cout << "12.34 with defaults: " << num << endl;
	cout << showpoint;
	cout << "12.34 with showpoint: " << num << endl;
}

void fieldWidthAlignAndFill(){
	//
}