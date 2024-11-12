#ifndef __SHALLOW_H__
#define __SHALLOW_H__

#include <string>

using namespace std;

class shallow{
	private:
		int *priv0; 								//<-pointer
		string priv1 {"shallow initial value"};
	public:
		//Standard constructor declarations
		shallow (int p0, string p1);
		shallow ();

		//If implemented in class (and priv0 was just an int, not an int pointer), then the constructors would look like this:
		/*

		//Constructor initialization lists are more efficient than old fashioned constructor initialization
		shallow (int p0, string p1) : priv0 {p0}, priv1 {p1} {cout << "Construcctor with 2 parameters : "<< p0 << "," << p1 << "\n";} 

		//Delegating constructor
		shallow () : shallow{0, ""} { cout << "Default construcctor, no parameters, delegating to constructor with params\n";} 

		//Alternatively: Constructor with default values, making other constructors superfluous:
		//shallow (int p0 = 0, string p1 = "a");

		*/
		
		//Better to implement the constructors outside the class (instead we'll just declare them), 
		//along with other methods, like this one:
		int getPriv0();
		void setPriv1(string p1);

		//Copy constructor
		shallow (const shallow &source);

		//Destructor
		~shallow();
};

#endif //__SHALLOW_H__

