#ifndef __SHALLOW_H__
#define __SHALLOW_H__

#include <string>

using namespace std;

class shallow{
	private:
		int priv0;
		string priv1 {"shallow initial value"};
	public:
		shallow (int p0, string p1);
		shallow ();
		//If implemented in class, the constructors would look like this:
		/*
		//Constructor initialization lists are more efficient than old fashioned constructor initialization
		shallow (int p0, string p1) : priv0 {p0}, priv1 {p1} {cout << "Construcctor with 2 parameters : "<< p0 << "," << p1 << "\n";} 
		//Delegating constructor
		shallow () : shallow{0, ""} { cout << "Default construcctor, no parameters, delegating to constructor with params\n";} 
		//Alternatively: Constructor with default values, making other constructors superfluous:
		//shallow (int p0 = 0, string p1 = "a");
		*/
		//But better to implement them outside the class (instead we'll just declare them), along with other methods, like this one:
		int getPriv0();
		void setPriv1(string p1);

		//Copy constructor
		shallow (const shallow &source);

		//Destructor
		~shallow();
};

#endif //__SHALLOW_H__

