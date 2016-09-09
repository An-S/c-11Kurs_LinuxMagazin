#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;

class BigArrayCopy{

public:
  BigArrayCopy(size_t len): len_(len), data_(new int[len]){}

  BigArrayCopy(const BigArrayCopy& other): len_(other.len_),data_(new int[other.len_]){
    cout << "copy construction of " << other.len_ << " elements "<< endl;
    std::copy(other.data_, other.data_ + len_, data_);
   }

  BigArrayCopy& operator=(const BigArrayCopy& other){
     cout << "copy assignment of " << other.len_ << " elements "<< endl;
     if (this != &other){
        delete[] data_;

        len_ = other.len_;
        data_ = new int[len_];
        std::copy(other.data_, other.data_ + len_, data_);
     }
     return *this;
  }

  ~BigArrayCopy(){
     if (data_ != nullptr) delete[] data_;
  }

private:
  size_t len_;
  int* data_;
};

int main(){

  cout << endl;

  vector<BigArrayCopy> myVec;

  BigArrayCopy bArray(11111111);
  BigArrayCopy bArray2(bArray);
  myVec.push_back(bArray);

  bArray= BigArrayCopy(22222222);
  myVec.push_back(BigArrayCopy(33333333));

  cout << endl;

}


