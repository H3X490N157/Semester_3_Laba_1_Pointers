#pragma once
#include <cassert>
#include "DynamicArray.h"

void test_DynamicArray_constructors(){
    int numbers[] = {10, 20, 30, 40, 50, 60};
    int defaultElem = 42;
    DynamicArray<int> array1(5);
    assert(array1.GetLength() == 5);

    DynamicArray<int> array2(numbers, 6);
    assert(array2.GetLength() == 6);
    for (int i = 0; i < array2.GetLength(); i++) {
        assert(array2.Get(i) == numbers[i]);
    }

    DynamicArray<int> array3(defaultElem, 4);
    assert(array3.GetLength() == 4);
    for (int i = 0; i < array3.GetLength(); i++) {
        assert(array3.Get(i) == defaultElem);
    }

    DynamicArray<int> array4(array2);
    assert(array4.GetLength() == array2.GetLength());
    for (int i = 0; i < array4.GetLength(); i++) {
        assert(array4.Get(i) == array2.Get(i));
    }
}

void test_DynamicArray_set(){
    int elements[] = {11, 22, 33, 44, 55, 66};
    DynamicArray<int> array5(elements, 6);
    assert(array5.GetLength() == 6);
    assert(array5.Get(2) == elements[2]);
    array5.Set(99, 2);
    assert(array5.Get(2) == 99);
    array5[2] = 100;
    assert(array5[2] == 100);
}

void test_DynamicArray_comparator(){
    int data[] = {7, 14, 21, 28, 35, 42};
    DynamicArray<int> array10(data, 6);
    DynamicArray<int> array11(data, 6);
    assert(array10 == array11);
    array11[3] = 1000;
    assert(!(array10 == array11));
}
