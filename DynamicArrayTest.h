#pragma once
#include "DynamicArray.h"
#include <cassert>

void Test_DynamicArray_Constructors(){
    int a[]={1,2,3,4,5,6};
    int fillElem = 8;
    DynamicArray<int> test1(6);
    assert(test1.GetLength()==6);

    DynamicArray<int> test2(a,6);
    assert(test2.GetLength()==6);
    for(int i=0;i<test2.GetLength();i++){
        assert(test2.Get(i)==a[i]);
    }
    DynamicArray<int> test3(fillElem,7);
    assert(test3.GetLength()==7);
    for(int i=0;i<test3.GetLength();i++){
        assert(test3.Get(i)==fillElem);
    }
    DynamicArray<int> test4(test2);
    assert(test4.GetLength()==test2.GetLength());
    for(int i=0;i<test4.GetLength();i++){
        assert(test2.Get(i)==test4.Get(i));
    }
}
void Test_DynamicArray_Set(){
    int a[]={1,2,3,4,5,6};
    DynamicArray<int> test5(a,6);
    assert(test5.GetLength()==6);
    assert(test5.Get(3)==a[3]);
    test5.Set(9,3);
    assert(test5.Get(3)==9);
    test5[3]=10;
    assert(test5[3]==10);
}

void Test_DynamicArray_CompareOperator(){
    int a[]={1,2,3,4,5,6};
    DynamicArray<int> test10(a,6);
    DynamicArray<int> test11(a,6);
    assert(test10==test11 );
    test11[4]=1323;
    assert(! (test10==test11) );
}