#pragma once 
#include "static_cast_move.h"

template <typename T>
void my_swap(T& a, T& b)
{
    T buf = mover(a);
    a = mover(b);
    b = mover(buf);
}