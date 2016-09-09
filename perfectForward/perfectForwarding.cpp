#include <iostream>

using std::forward;

using std::cout;
using std::endl;

template <typename T, typename T1>
T createClassic(const T1& t1){
  cout << "const T1& t1" << endl;
  return T(t1);
}

template <typename T, typename T1>
T createClassic(T1& t1){
  cout << "T1& t1" << endl;
  return T(t1);
}


template <typename T, typename T1>
T createNew(T1&& t1){
  cout << "T1&& t1" << endl;
  return T(forward<T1>(t1));
}

int main(){

  cout << endl;

  cout << "C++98" << endl;
  int six= 6;
  cout << "  Rvalue => : " ;
  int mySix2= createClassic<int>(6);
  cout << "  Lvalue => : ";
  int mySix= createClassic<int>(six);

  cout << endl;

  cout << "C++11" << endl;
  int five= 5;
  cout << "  Rvalue => : ";
  int myFive2= createNew<int>(5);
  cout << "  Lvalue => : ";
  int myFive= createNew<int>(five);

  cout << endl;

}
