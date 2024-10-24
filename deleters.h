#pragma once

template<typename T>
struct My_Universal_Deleter{
    void operator()(T* ptr){
        delete ptr;
    }
};
template<typename T>
struct My_Universal_Deleter<T[]>{
    void operator()(T* ptr){
        delete[] ptr;
    }
};



