#include <iostream>
#include <typeinfo>
#include <memory>
#include <utility>

using namespace std;

template<class elemT>
class resourceGuardT{
public:
    resourceGuardT(size_t N){
        myArray = new elemT[N];
        cerr << "Allocated " << N << " elements of type " << typeid(elemT).name() << endl;
        elemCnt = N;
    }
    ~resourceGuardT(){
        delete[] myArray;
        cerr << "Deleted " << elemCnt << " elements of type " << typeid(elemT).name() << endl;
    }

    shared_ptr<elemT> getPtr(void){
        return shared_ptr<elemT>(myArray);
    }

private:
   elemT *myArray;
   size_t elemCnt;
};

resourceGuardT<int> aquireResource(void){
    resourceGuardT<int> intlist(10000);
    return intlist;
}

unique_ptr<resourceGuardT<int>> aquireResource2(void){
    resourceGuardT<int>* intlist = new resourceGuardT<int>(5400);
    return unique_ptr<resourceGuardT<int>>(intlist);
}


resourceGuardT<int>&& aquireResource3(void){
    return move(resourceGuardT<int>(5500));
}

shared_ptr<resourceGuardT<int>> aquireResource4(void){
    resourceGuardT<int> intlist(5600);
    return shared_ptr<resourceGuardT<int>>(&intlist);
}

int main()
{
    cout << "Hello world!" << endl;
    aquireResource();
    aquireResource2();
    aquireResource3();
    aquireResource4();
    return 0;
}
