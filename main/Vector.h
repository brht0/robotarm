#ifndef __VECTOR_H__
#define __VECTOR_H__

// temporary fix because arduino sucks

template<typename T>
class Vector{
public:
    Vector(){}
    ~Vector(){}

    int size(){
      return used_index;
    }

    void push_back(T newData){
        if(used_index > length_-1){
            return;
        }

        data[used_index] = newData;
        used_index ++;
    }
    
    T& operator[](int index){
        if(index < 0 || index > used_index - 1)
            return data[0];
        return data[index];
    }

private:
    int used_index = 0;

    int length_ = 10;
    T data[10];
};

#endif // __VECTOR_H__