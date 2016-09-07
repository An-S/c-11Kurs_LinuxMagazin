#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Base{
public:
	Base() = default;
	Base(int i){
		cout << "Base::Base(" << i << ")" << endl;
	}

	Base(string s){
		cout << "Base::Base(" << s << ")" << endl;
	}
};

class Derived: public Base{
public:
	using Base::Base;

	Derived(double d){
		cout << "Derived::Derived(" << d << ")" << endl;
	}
};

int main(){
	cout << endl;

	Derived(2011);
	Derived("C++11");
	Derived(0.33);
	cout << endl;
}

