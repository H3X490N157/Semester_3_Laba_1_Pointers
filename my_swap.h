#pragma once 

#include "my_move.h"

template <typename T>
void my_swap(T& a, T& b)
{
    T buf = my_move(a);
    a = my_move(b);
    b = my_move(buf);
}