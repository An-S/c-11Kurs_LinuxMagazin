#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::chrono::system_clock;
using std::chrono::duration;

using std::vector;

class BigArray{

public:
  BigArray(size_t len): len_(len), data_(new int[len]){}

  BigArray(const BigArray& other): len_(other.len_),data_(new int[other.len_]){
    cout << "copy construction of " << other.len_ << " elements "<< endl;
    std::copy(other.data_, other.data_ + len_, data_);
   }

  BigArray& operator=(const BigArray& other){
     cout << "copy assignment of " << other.len_ << " elements "<< endl;
     if (this != &other){
        delete[] data_;

        len_ = other.len_;
        data_ = new int[len_];
        std::copy(other.data_, other.data_ + len_, data_);
     }
     return *this;
  }

   BigArray(BigArray&& other): len_(other.len_),data_(other.data_){
     cout << "move construction of " << other.len_ << " elements "<< endl;
     other.len_= 0;
     other.data_ = nullptr;
   }

   BigArray& operator=(BigArray&& other){
     cout << "move assignment of " << other.len_ << " elements "<< endl;
     if (this != &other){
       delete[] data_;

       len_= other.len_;
       data_= other.data_;

       other.data_ = nullptr;
       other.len_= 0;
     }
     return *this;
   }

  ~BigArray(){
     if (data_ != nullptr) delete[] data_;
  }

private:
  size_t len_;
  int* data_;
};

int main(){

  cout << endl;

  vector<BigArray> myVec;
  myVec.reserve(2);

  BigArray bArray(11111111);
  BigArray bArray2(bArray);
  myVec.push_back(bArray);

  auto begin= system_clock::now();

  bArray= BigArray(22222222);
  myVec.push_back(BigArray(33333333));

  auto end= system_clock::now() - begin;
  auto timeInSeconds= duration<double>(end).count();

  cout << endl;
  cout << "time in seconds: " << timeInSeconds << endl;
  cout << endl;

}


