#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(void){
	cout << endl;
	
	string log = "66.249.64.13 - - [18/Sep/2012:11:07:48 +1000] GET /robots.txt HTTP/"
				 "1.0 200 468 - Googlebot/2.1\n"
				 "66.249.64.13 - - [18/Sep/2012:11:07:48 +1000] GET / HTTP/1.0 "
				 "200 64 - Googlebot/2.1";
				 
	cout << log << endl;
	
	regex rgxIPs(R"([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})");
	string alog {regex_replace(log, rgxIPs, "XXX.XXX.XXX.XXX")};
	
	cout << alog << endl << endl;
	
	cout << endl;
}

