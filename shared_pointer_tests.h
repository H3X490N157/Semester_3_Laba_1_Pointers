#pragma once
#include <cassert>
#include <string>
#include "shared_pointer.h"
#include "weak_pointer.h"
#include "my_swap.h"
#include "static_cast_move.h"

void test_swap(){
    int x = 12;
    int y = 34;
    my_swap(x, y);
    assert(x == 34);
    assert(y == 12);
    std::string first = "hello";
    std::string second = "world";
    my_swap(first, second);
    assert(first == "world");
    assert(second == "hello");
}

void test_move(){
    int x = 15;
    int y = 25;
    x = mover(y);
    assert(x == 25);
    assert(y == 25);
    std::string first = "foo";
    std::string second = "bar";
    first = mover(second);
    assert(first == "bar");
    assert(second == "");
}

void test_shared_pointer_constructor(){
    auto ptrA = shared_ptr<int>(new int(50));
    assert(*ptrA == 50);
    assert(ptrA.get_usage_count() == 1);
}

void test_shared_pointer_copy_constructor(){
    auto ptrB = shared_ptr<int>(new int(50));
    auto ptrC = ptrB;
    assert(*ptrC == 50);
    assert(ptrC == ptrB);
    assert(ptrC.get_usage_count() == 2);
}

void test_shared_pointer_move_constructor(){
    auto ptrD = shared_ptr<int>(new int(75));
    auto ptrE = shared_ptr<int>(mover(ptrD));
    assert(*ptrE == 75);
    assert(ptrE.get_usage_count() == 1);
    assert(ptrD.is_free());
}

void test_shared_pointer_destructor(){
    int* raw_ptr = new int(100);
    {   
        auto ptrF = shared_ptr<int>(raw_ptr);
        assert(*ptrF == 100);
        assert(ptrF.get_usage_count() == 1);
        {
            auto ptrG = ptrF;
            assert(*ptrG == 100);
            assert(ptrG.get_usage_count() == 2);
        }
        assert(ptrF.get_usage_count() == 1);
    }
    assert(raw_ptr == nullptr);
}

void test_shared_pointer_assignment(){
    auto ptrH = shared_ptr<int>(new int(60));
    assert(*ptrH == 60);
    assert(ptrH.get_usage_count() == 1);
    auto ptrI = shared_ptr<int>(new int(90));
    assert(*ptrI == 90);
    assert(ptrI.get_usage_count() == 1);
    ptrI = ptrH;
    assert(*ptrH == *ptrI && *ptrH == 60);
    assert(ptrI.get_usage_count() == ptrH.get_usage_count() && ptrI.get_usage_count() == 2);

    auto ptrJ = shared_ptr<int>(new int(30));
    auto ptrK = shared_ptr<int>(new int(40));
    assert(*ptrJ == 30);
    assert(ptrJ.get_usage_count() == 1);
    ptrJ = shared_ptr<int>(mover(ptrK));
    assert(*ptrJ == 40);
    assert(ptrJ.get_usage_count() == 1);
    assert(ptrK.is_free());
}

void test_shared_ptr_funcs(){
    {
        auto ptrL = make_shared<int>(70);
        assert(*ptrL == 70);
        assert(ptrL.get_usage_count() == 1);
        auto ptrM = make_shared<std::string>(5, 'x');
        assert(*ptrM == "xxxxx");
    }
    {
        int* raw_ptr1 = new int(55);
        auto ptrN = shared_ptr<int>(raw_ptr1);
        assert(*ptrN == 55);
        assert(ptrN.get_usage_count() == 1);
        ptrN.reset();
        assert(ptrN.is_free());
    }
    {
        int* raw_ptr2 = new int(80);
        auto ptrO = shared_ptr<int>(raw_ptr2);
        assert(*ptrO == 80);
    }
    
    {
        auto ptrP = make_shared<std::string>(6, 'z');
        assert(ptrP->length() == 6);
    }
    {
        int* raw_array = new int[5];
        for (int i = 0; i < 5; i++) {
            raw_array[i] = i * 2;
        }
        auto ptrQ = shared_ptr<int[]>(raw_array);
        for (int i = 0; i < 5; i++) {
            assert(ptrQ[i] == i * 2);
        }
    }
}

void test_weak(){
    auto weakPtr = weak_ptr<int>();
    assert(weakPtr.is_expired());
    {
        auto sharedPtr1 = shared_ptr<int>(new int(99));
        assert(*sharedPtr1 == 99);
        assert(sharedPtr1.get_usage_count() == 1);
        assert(sharedPtr1.get_weak_count() == 0);
        auto weakPtr1 = weak_ptr<int>(sharedPtr1);
        assert(sharedPtr1.get_weak_count() == 1);
        assert(weakPtr1.get_usage_count() == 1);
        assert(!weakPtr1.is_expired());
        weakPtr = weak_ptr<int>(sharedPtr1);
        assert(sharedPtr1.get_weak_count() == 2);
        assert(weakPtr.get_usage_count() == 2);
    }
    assert(weakPtr.is_expired());
}

void test_shared_ptr_compare(){
    auto ptrX = shared_ptr<int>();
    assert(ptrX == nullptr);
    assert(nullptr == ptrX);
}
