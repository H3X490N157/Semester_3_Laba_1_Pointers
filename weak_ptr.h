#pragma once

#include "shared_ptr.h"
#include "my_swap.h"
#include "my_move.h"
#include "My_TypeTraits.h"
template <typename T,class Deleter =  My_Universal_Deleter<T> >
class weak_ptr{
using U = remove_extent_t<T>;
private:
    U* ptr;
    typename shared_ptr<T, Deleter>::ControlBlock* counter;
        void swap(weak_ptr<T, Deleter>& w_ptr){
        my_swap(ptr,w_ptr.ptr);  
        my_swap(counter,w_ptr.counter);
    }
public:

    weak_ptr():ptr(nullptr),counter(nullptr){}
    weak_ptr(std::nullptr_t):weak_ptr(){}
    weak_ptr(const shared_ptr<T, Deleter>& sh_ptr):ptr(sh_ptr.ptr),counter(sh_ptr.counter){
        if(counter && ptr) counter->weak_count++;
    }
    weak_ptr(const weak_ptr<T, Deleter>& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        if(counter && ptr) counter->weak_count++;
    }
    weak_ptr(weak_ptr<T, Deleter>&& w_ptr):ptr(w_ptr.ptr),counter(w_ptr.counter){
        w_ptr.ptr = nullptr;
        w_ptr.counter = nullptr;
    }

    bool is_expired() const {
        if(!counter) return true;
        return counter->ref_count == 0;
    }
    //переименовать get_usage_count
    
    size_t get_usage_count() const {
        if(!counter) return 0 ;
        return counter->weak_count;
    }
    shared_ptr<T, Deleter> lock() const {
        return shared_ptr<T, Deleter>(*this);
    }

    weak_ptr& operator=(const weak_ptr<T,Deleter>& w_ptr){
        if(ptr==w_ptr.ptr) return *this;
        weak_ptr<T,Deleter> temp_ptr(w_ptr);
        swap(temp_ptr); 
        return *this;
    }
    weak_ptr& operator=(weak_ptr<T,Deleter>&& w_ptr){
        if(ptr==w_ptr.ptr) return *this;
        swap(w_ptr); 
        return *this;
    }
    weak_ptr& operator=(std::nullptr_t){
        if(!ptr) return *this;
        weak_ptr<T,Deleter> temp_ptr;
        swap(temp_ptr); 
        return *this;
    }

    ~weak_ptr(){
        if(!counter) return ;
        counter->weak_count--;
        if(!counter->weak_count && !counter->ref_count){
            delete counter;
        }
    }

};
