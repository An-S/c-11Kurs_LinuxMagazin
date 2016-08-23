#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::endl;

using std::vector;
//using std::chrono;

class BigArrayCopy
{

public:
    BigArrayCopy(size_t len): len_(len), data_(new int[len]) {}

    BigArrayCopy(const BigArrayCopy& other): len_(other.len_),data_(new int[other.len_])
    {
        cout << "copy construction of " << other.len_ << " elements "<< endl;
        std::copy(other.data_, other.data_ + len_, data_);
    }

    BigArrayCopy& operator=(const BigArrayCopy& other)
    {
        cout << "copy assignment of " << other.len_ << " elements "<< endl;
        if (this != &other)
        {
            delete[] data_;

            len_ = other.len_;
            data_ = new int[len_];
            std::copy(other.data_, other.data_ + len_, data_);
        }
        return *this;
    }

    BigArrayCopy(BigArrayCopy&& other): len_(other.len_),data_(other.data_)
    {
        cout << "move construction of " << other.len_ << " elements "<< endl;
        other.len_ = 0;
        other.data_ = nullptr;
    }

    BigArrayCopy& operator=(BigArrayCopy&& other)
    {
        cout << "move assignment of " << other.len_ << " elements "<< endl;
        if (this != &other)
        {
            delete[] data_;

            len_ = other.len_;
            data_ = other.data_;//new int[len_];
            //std::copy(other.data_, other.data_ + len_, data_);
            other.len_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~BigArrayCopy()
    {
        if (data_ != nullptr) delete[] data_;
    }

private:
    size_t len_;
    int* data_;
};

int main()
{

    cout << endl;

    auto begin= std::chrono::system_clock::now();

    vector<BigArrayCopy> myVec;
    myVec.reserve(2); //prevent reallocation of vector together with contents

    BigArrayCopy bArray(11111111);
    BigArrayCopy bArray2(bArray);
    myVec.push_back(bArray);


    bArray= BigArrayCopy(22222222);

    myVec.push_back(BigArrayCopy(33333333));
    auto end= std::chrono::system_clock::now() - begin;


    cout << "time in seconds: " << std::chrono::duration<double>(end).count() << endl;

}

