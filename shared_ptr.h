#pragma once

#include "my_swap.h"
#include "my_move.h"
#include <cstddef>
#include "Deleters.h"
#include "My_TypeTraits.h"
#include <type_traits>
#include <iostream>
template<typename T,class Deleter>
class weak_ptr;


//реализовать Deleter или специализаицию для T[]
template<typename T,class Deleter =  My_Universal_Deleter<T> >
class shared_ptr{
private:
using U = remove_extent_t<T>;
    struct ControlBlock{
        size_t ref_count;
        size_t weak_count;
        ControlBlock(size_t ref = 0 , size_t weak = 0):ref_count(ref),weak_count(weak){}
    };
    U* ptr; 
    ControlBlock* counter;
    friend class weak_ptr<T,Deleter>;

    void swap(shared_ptr<T,Deleter>& sh_ptr){
        my_swap(ptr,sh_ptr.ptr);  
        my_swap(counter,sh_ptr.counter);
    }
public:
    shared_ptr():ptr(nullptr),counter(nullptr){};
    explicit shared_ptr( const weak_ptr<T,Deleter>& w_ptr ):ptr(w_ptr.ptr),counter(w_ptr.counter){
        if(counter) counter->ref_count++;
    }
    explicit shared_ptr(U* in_ptr) : ptr(my_move(in_ptr)) {
        if( ptr ){
            counter = new ControlBlock(1,0);
        }else{
            counter = nullptr;
        }
    };
    
    shared_ptr(const shared_ptr<T,Deleter>& sh_ptr ){
        ptr = sh_ptr.ptr;
        counter = sh_ptr.counter;
        if(counter) ++(counter->ref_count);
    }
    shared_ptr(shared_ptr<T,Deleter>&& sh_ptr ):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        sh_ptr.ptr = nullptr;
        sh_ptr.counter = nullptr;
    }
    size_t get_usage_count() const {
        if(!counter) return 0;
        return counter->ref_count;
    }
    size_t get_weak_count() const {
        if(!counter) return 0;
        return counter->weak_count;
    }
    bool is_unique() const {
        return get_usage_count() == 1;
    }
    bool is_free() const {
        return ptr == nullptr;
    }
    void reset(U* new_ptr){
        if(ptr==new_ptr) return ;
        auto buf = shared_ptr<T,Deleter>(new_ptr);
        swap(buf);
    }
    void reset(){
        auto buf = shared_ptr<T,Deleter>();
        swap(buf);
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

    shared_ptr& operator=(std::nullptr_t){
        if(!ptr) 
            return *this;
        shared_ptr<T,Deleter> temp_ptr;
        swap(temp_ptr); 
        return *this;
    }
    shared_ptr& operator=(const shared_ptr<T,Deleter>& sh_ptr){
        if(ptr==sh_ptr.ptr) 
            return *this;
        shared_ptr<T,Deleter> temp_ptr (sh_ptr);
        swap(temp_ptr); 
        return *this;
    }
    shared_ptr& operator=(shared_ptr<T,Deleter>&& sh_ptr){
        if(ptr==sh_ptr.ptr) 
            return *this;
        shared_ptr<T,Deleter> temp_ptr (sh_ptr);    
        swap(temp_ptr); 
        return *this;
    }
    ~shared_ptr(){
        if(!counter) 
            return;
        --(counter->ref_count);
        if( !counter->ref_count ){
            Deleter my_delete = Deleter();
            my_delete(ptr);
            if( !counter->weak_count ) delete counter ;
        }
    }
};

template<typename T,class Deleter =  My_Universal_Deleter<T>,typename... Args>
shared_ptr<T,Deleter> make_shared(Args&& ... args){
    return shared_ptr<T,Deleter>(new T(args...));
}
template<typename T,class Deleter =  My_Universal_Deleter<T>,typename... Args>
shared_ptr<T[],Deleter> make_shared(size_t size , Args&& ... args){
    T* ptr  = new T[size];
    for(int i =0 ; i<size;i++){
        ptr[i]=T(args...);
    }
    return shared_ptr<T[],Deleter>(ptr);
}

template<typename T,class Deleter =  My_Universal_Deleter<T>>
shared_ptr<T[],Deleter> make_shared(size_t size){
    T* ptr  = new T[size];
    return shared_ptr<T[],Deleter>(ptr);
}

template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==(const shared_ptr<T,Deleter> &sh_ptr_a, const shared_ptr<T,Deleter> &sh_ptr_b) 
{
    return sh_ptr_a.get() == sh_ptr_b.get();
}

template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=(const shared_ptr<T,Deleter> &sh_ptr_a, const shared_ptr<T,Deleter> &sh_ptr_b) 
{
    return !(sh_ptr_a == sh_ptr_b);
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==(const shared_ptr<T,Deleter> &sh_ptr , std::nullptr_t )
{
    return sh_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator==( std::nullptr_t,const shared_ptr<T,Deleter> &sh_ptr )
{
    return sh_ptr.get()==nullptr;
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=(const shared_ptr<T,Deleter> &sh_ptr , std::nullptr_t )
{
    return !(sh_ptr == nullptr);
}
template<typename T,class Deleter =  My_Universal_Deleter<T>>
bool operator!=( std::nullptr_t , const shared_ptr<T,Deleter> &sh_ptr)
{
    return !(sh_ptr == nullptr);
}



