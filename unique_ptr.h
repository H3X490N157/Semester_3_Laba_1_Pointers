#pragma once

#include "my_swap.h"
#include <cstddef>
#include "My_TypeTraits.h"


template <typename T,class Deleter =  My_Universal_Deleter<T>>
class unique_ptr{
using U = remove_extent_t<T>;
private:
    U* ptr;
    void swap(unique_ptr<T,Deleter>& un_ptr){
        my_swap(ptr,un_ptr.ptr); 
    }
public:
    //inline
    unique_ptr():ptr(nullptr){};
    explicit unique_ptr(std::nullptr_t):unique_ptr(){};
    explicit unique_ptr(U* in_ptr):ptr(my_move(in_ptr)){};
    
    unique_ptr(const unique_ptr<T,Deleter>& un_ptr) = delete;

    unique_ptr(unique_ptr<T,Deleter>&& un_ptr ):ptr(un_ptr.ptr){
        un_ptr.ptr = nullptr;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(U* new_ptr){ //убрать
        if(ptr==new_ptr) return ;
        auto buf = unique_ptr<T,Deleter>(new_ptr);
        swap(buf);
    }
    void reset(){
        auto buf =  unique_ptr<T,Deleter>();
        swap(buf);
    }
    U* release(){
        U* buf = ptr;
        ptr = nullptr;
        return buf;
    }
    U& operator*() {
        return *get();
    }
    U* operator->() {
        return get();
    }
    U* get() {
        return ptr;
    }
    const U& operator*() const {
        return *get();
    }
    const U* operator->() const {
        return get();
    }
    const U* get() const {
        return ptr;
    }

    template<typename K = T, typename = enable_if_t<is_array_t<K>> >
    U& operator[](int index) {
        return ptr[index];
    }
    template<typename K = T, typename = enable_if_t<is_array_t<K>> >
    const U& operator[](int index) const {
        return ptr[index];
    }
    unique_ptr& operator=(const unique_ptr<T,Deleter>& un_ptr)=delete;
    unique_ptr& operator=(std::nullptr_t){
        unique_ptr<T,Deleter> temp_ptr;
        swap(temp_ptr); 
        return *this;
    }
    unique_ptr& operator=(unique_ptr<T,Deleter>&& un_ptr){
        unique_ptr<T,Deleter> temp_ptr(my_move(un_ptr));
        swap(temp_ptr); 
        return *this;
    }
    ~unique_ptr(){
        Deleter my_delete = Deleter();
        my_delete(ptr);
    }
};



template<typename T,class Deleter =  My_Universal_Deleter<T>,typename... Args>
unique_ptr<T,Deleter> make_unique(Args&& ... args){
    return unique_ptr<T,Deleter>(new T(args...));
}

template<typename T,class Deleter =  My_Universal_Deleter<T>,typename... Args>
unique_ptr<T[],Deleter>make_unique(size_t size , Args&& ... args){
    T* ptr  = new T[size];
    for(int i =0 ; i<size;i++){
        ptr[i]=T(args...);
    }
    return unique_ptr<T,Deleter>(ptr);
}

template<typename T,class Deleter =  My_Universal_Deleter<T>>
unique_ptr<T[],Deleter> make_unique(size_t size){
    T* ptr = new T[size];
    return unique_ptr<T,Deleter>(ptr);
}



template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==(const unique_ptr<T,Deleter> &un_ptr_a, const unique_ptr<T,Deleter> &un_ptr_b) 
{
    return un_ptr_a.get() == un_ptr_b.get();
}

template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=(const unique_ptr<T,Deleter> &un_ptr_a, const unique_ptr<T,Deleter> &un_ptr_b) 
{
    return !(un_ptr_a == un_ptr_b);
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==(const unique_ptr<T,Deleter> &un_ptr , std::nullptr_t )
{
    return un_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==( std::nullptr_t , const unique_ptr<T,Deleter> &un_ptr  )
{
    return un_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=(const unique_ptr<T,Deleter> &un_ptr , std::nullptr_t )
{
    return !(un_ptr == nullptr);
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=( std::nullptr_t ,  const unique_ptr<T,Deleter> &un_ptr)
{
    return !(un_ptr == nullptr);
}

