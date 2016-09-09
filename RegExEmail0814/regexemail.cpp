#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(void){
	cout << endl;
	
	string email = "rainer@grimm-jaud.de";
	
	string regExprStr(R"(([\w.%+-]+)@([\w.-]+)\.([a-zA-Z]{2,4}))");
	regex rgx(regExprStr);
	smatch match;
	
	if (regex_match(email, match, rgx)){
		cout << "Text: " << email << endl;
		cout << endl;
		cout << "Email Address: " << match[0] << endl;
		cout << "Local Part:" << match[1] << endl;
		cout << "Domain name:" << match[2] << "." << match[3] << endl;
		cout << "Extension name:" << match[3] << endl;
	}
	
	cout << endl;
}

