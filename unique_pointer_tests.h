#pragma once 

#include "unique_pointer.h"
#include "my_swap.h"
#include "static_cast_move.h"

void test_unique_pointer_constructor(){
    auto uniquePtrA = unique_ptr<int>(new int(25));
    assert(*uniquePtrA == 25);
}

void test_unique_pointer_move_constructor(){
    auto uniquePtrB = unique_ptr<int>(new int(50));
    auto uniquePtrC = unique_ptr<int>(mover(uniquePtrB));
    assert(*uniquePtrC == 50);
    assert(uniquePtrB.is_free());
}

void test_unique_ptr_funcs(){
    {
        auto sharedPtr1 = make_shared<int>(75);
        assert(*sharedPtr1 == 75);
        assert(sharedPtr1.get_usage_count() == 1);
        auto sharedPtr2 = make_shared<std::string>(6, 'x');
        assert(*sharedPtr2 == "xxxxxx");
    }
    {
        int* rawPtr1 = new int(100);
        auto uniquePtrD = unique_ptr<int>(rawPtr1);
        assert(*uniquePtrD == 100);
        uniquePtrD.reset();
        assert(uniquePtrD.is_free());
    }
    {
        int* rawPtr2 = new int(200);
        auto uniquePtrE = unique_ptr<int>(rawPtr2);
        assert(*uniquePtrE == 200);
    }
    {
        auto sharedPtr3 = make_shared<std::string>(10, 'y');
        assert(sharedPtr3->length() == 10);
    }
    {
        auto uniquePtrF = unique_ptr<int[]>(new int[5]);
        for(int i = 0; i < 5; i++){
            uniquePtrF[i] = i * 2;
        }
        for(int i = 0; i < 5; i++){
            assert(uniquePtrF[i] == i * 2);
        }
    }
}

void test_unique_ptr_compare(){
    void* rawMem = new char[sizeof(int) * 5];
    int* intArray = static_cast<int*>(rawMem);
    for (int i = 0; i < 5; i++) {
        intArray[i] = i + 10;
    }
    auto uniquePtrG = unique_ptr<int>(intArray + 1);
    auto uniquePtrH = unique_ptr<int>(intArray + 1);
    auto uniquePtrI = unique_ptr<int>(intArray + 4);
    auto uniquePtrJ = unique_ptr<int>();
    assert(uniquePtrJ == nullptr);
    assert(nullptr == uniquePtrJ);
    assert(uniquePtrG == uniquePtrH);
    assert(!(uniquePtrG != uniquePtrH));
    uniquePtrG.release();
    uniquePtrI.release();
    uniquePtrH.release();
}
