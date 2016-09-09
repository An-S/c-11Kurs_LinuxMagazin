#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(void){
	cout << endl;
	
	string gtext{"+0,85 -13,2 1,0 ,45 -13,7 1,03425 10134,25"};
				 
	cout << gtext << endl;
	
	
	try{
		regex rgxDbl(R"(([+-]?[0-9]*),?([0-9]+))");
		string etext {regex_replace(gtext, rgxDbl, "$1.$2")};
		cout << etext << endl << endl;
	}catch(regex_error &exp){
		cout << "Catched exception: " << exp.what() << endl;
	}
	
}

