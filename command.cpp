//source code file number -> 3
#include "command.h"
#include "token.h"
namespace {
	const char quit = 'q', print = ';', let = 'L', del = 'D';
}

//function number -> 1
//No error codes
//Check if variable is already defined 
int command::check(string name) {
	for (variable& i : variables) {
		if (i.name == name) {
			cerr << "Variable already defined" << endl;
			return 1;
		}
	}
	for (variable& i : pre_defined) {
		if (i.name == name) {
			cerr << "Variable already pre-defined" << endl;
			return 2;
		}
	}
	return 0;
}


//function number -> 2
//error_codes -> 321,322,323,324
//Define a new variable
variable command::define_variable() {
	char x;
	string name = "";
	int val;
	cin >> x;

	//Checking if variable name starts with symbol or number
	if (!isalpha(x)) {
		return variable(321);
	}
	//do while loop constructs variable name by taking one character at a time and stope when '=' is encountered
	do {
		name += x;
		cin >> x;
		//checking if variable name has non-alpha-numeric character
		if (!(isalnum(x) || x == '=') || (x == ' ' && cin.peek() != '=')) {
			return variable(322);
		}
	} while (x != '=');

	cin >> val;
	if (!cin) { 
		return variable(323);
	}
	int a=check(name);//checks if variabe is already defined
	if (a != 0) {
		return variable(324);
	}
	variables.push_back(variable(name, val));
	return variable(name,val);//success
}

//Function number -> 3
//error code -> 331
//get variable value if defined
double command::var_value(string name) {
	for (variable& i : variables) {
		if (i.name == name)
			return  i.value;
	}
	for (variable& i : pre_defined) {
		if (i.name == name)
			return i.value;
	}
	//no variable found invalid token returned
	throw 331;
}

//function number -> 4
//No error codes
//Pre-Defined variables
void command::pre() {
	pre_defined.push_back(variable("pi", 3.14159265/*358979323846264338327950*/));
	pre_defined.push_back(variable("e", 2.71828182/*845904523536028747135266*/));
}