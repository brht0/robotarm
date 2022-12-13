#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Arduino.h"

template<typename T>
class Vector{
public:
    Vector(): data_(nullptr), length_(0), allocatedLength_(0) { Allocate(2); }
    Vector(Vector&& rhs): data_(rhs.data_), length_(rhs.length_), allocatedLength_(rhs.allocatedLength_) {
        rhs.data_ = nullptr;
    }
    Vector(Vector& rhs): data_(nullptr), length_(0), allocatedLength_(0) {
      Allocate(rhs.allocatedLength_);
      length_ = rhs.length_;
      for(unsigned i=0; i<length_; i++){
        data_[i] = rhs.data_[i];
      }
      rhs.data_ = nullptr;
    }
    ~Vector(){
        if(data_)
            delete[] data_;
        data_ = nullptr;
    }

    unsigned size(){
      return length_;
    }

    void clear(){
        length_ = 0;
    }

    void push_back(T newData){
        if(length_ >= allocatedLength_){
            Allocate(length_ + length_ / 2);
        }

        data_[length_] = newData;
        length_ ++;
    }

    void push_back(T&& newData){
        if(length_ >= allocatedLength_){
            Allocate(length_ + length_ / 2);
        }

        data_[length_] = newData;
        length_ ++;
    }
    
    T& operator[](int index){
        if(index < 0 || index > length_ - 1){
            Serial.println("Vector: Accessing index outside allowed range: " + String(index));
            return data_[0];
        }
        return data_[index];
    }

    using iterator=T*;
    using const_iterator=const T*;
    iterator begin() { return data_; }
    iterator end() { return data_+length_; }
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_+length_; }

private:
    void Allocate(unsigned newLength){
        T* newData = new T[newLength];
        for(unsigned i=0; i<length_; i++){
            newData[i] = data_[i];
        }
        allocatedLength_ = newLength;
        if(data_){
            delete[] data_;
        }
        data_ = newData;
    }

    unsigned length_;
    unsigned allocatedLength_;
    T* data_ = nullptr;
};

#endif // __VECTOR_H__
