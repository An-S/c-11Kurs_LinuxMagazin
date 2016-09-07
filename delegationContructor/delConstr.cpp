#include <cmath>
#include <iostream>

using namespace std;
#define degout(var, deg) cout << #var #deg << " = " << var##deg.get() << endl

class Degree{
public:
    Degree(int deg){
        degree = deg%360;
        if (degree < 0) degree += 360;
    }

    Degree(): Degree(0){}
    Degree(double deg): Degree(static_cast<int>(ceil(deg))) {}
    int get() const {return degree;}
private:
    int degree;
};

int main(){
    cout << endl;

    Degree degree10(10);
    Degree degree45(45);
    Degree degreeMin315(-315);
    Degree degree405(405);
    Degree degree;
    Degree degree44(44.45);

    degout (degree, 10);
	degout (degree, 45);
	degout (degree, Min315);
	degout (degree, 405);
	degout (degree, );
	degout (degree, 44);
}
