#pragma once 

template<typename T>
T&& my_move(T& in){
    return static_cast<T&&>(in); 
}
template<typename T>
T&& my_move(T&& in){
    return static_cast<T&&>(in);
}
