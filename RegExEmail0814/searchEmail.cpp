#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(void){
	cout << endl;
	
	string email = "a text with an email address: rainer@grimm-jaud.de. trailing character sequence";
	
	string regExprStr(R"(([\w.%+-]+)@([\w.-]+)\.([a-zA-Z]{2,4}))");
	regex rgx(regExprStr);
	smatch match;
	
	if (regex_search(email, match, rgx)){
		cout << "Text: " << email << endl;
		cout << endl;
		cout << "Before email: \"" << match.prefix() << "\"" << endl;
		cout << "After email: \"" << match.suffix() << "\"" << endl;
		cout << "Address length: " << match.length() << endl;
		cout << "Email Address: \"" << match[0] << "\"" << endl;
		cout << "Local Part: \"" << match[1] << "\"" << endl;
		cout << "Domain name: \"" << match[2] << "." << match[3] << "\"" << endl;
		cout << "Extension name: \"" << match[3] << "\"" << endl;
	}
	
	cout << endl;
}

