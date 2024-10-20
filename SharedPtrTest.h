#pragma once

#include "shared_ptr.h"
#include "weak_ptr.h"
#include "my_swap.h"
#include "my_move.h"
#include <cassert>
#include <string>

//#include <iostream>

void test_swap(){
    int a = 5;
    int b = 6;
    my_swap(a,b);
    assert(a == 6);
    assert(b == 5);
    std::string str1 = "abc";
    std::string str2 = "def";
    my_swap(str1,str2);
    assert(str1 == "def");
    assert(str2 == "abc");
}
void test_move(){
    int a = 5;
    int b = 6;
    a = my_move(b);
    assert(a == 6);
    assert(b == 6);
    std::string str1 = "abc";
    std::string str2 = "def";
    str1 = my_move(str2);
    assert(str1 == "def");
    assert(str2 == "");
}
void test_shptr_constructor(){
    //Constructor
    auto ptr1 = shared_ptr<int>(new int(10));
    assert(*ptr1 == 10);
    assert(ptr1.get_usage_count() == 1);
}
void test_shptr_copy_constructor(){
    //Copy constructor
    auto ptr2 = shared_ptr<int>(new int(10));
    auto ptr3 = ptr2;
    assert(*ptr3 == 10);
    assert(ptr3 == ptr2);
    assert(ptr3.get_usage_count() == 2);
}
void test_shptr_move_constructor(){
    //Move constructor
    auto ptr3 = shared_ptr<int>(new int(10));
    auto ptr4 = shared_ptr<int>(my_move(ptr3));
    assert(*ptr4 == 10);
    assert(ptr4.get_usage_count() == 1);
    assert(ptr3.is_free());
}

void test_shptr_destructor(){
    //Destructor test
    int* test_ptr = new int(10);
    {   
        auto ptr5 = shared_ptr<int>(test_ptr);
        assert(*ptr5 == 10);
        assert(ptr5.get_usage_count() == 1);
        {
            auto ptr6 = ptr5;
            assert(*ptr6 == 10);
            assert(ptr6.get_usage_count() == 2 );
        }
        assert(ptr5.get_usage_count() == 1 );
    }
    assert(test_ptr==nullptr);
}

void test_shptr_assignment(){
    //Assignmenet operator 
    auto ptr1 = shared_ptr<int>(new int(10));
    assert(*ptr1 == 10);
    assert(ptr1.get_usage_count() == 1);
    auto ptr2 = shared_ptr<int>(new int(20));
    assert(*ptr2 == 20);
    assert(ptr2.get_usage_count() == 1);
    ptr2 = ptr1;
    assert(*ptr1 == *ptr2 && *ptr1 == 10);
    assert(ptr2.get_usage_count() == ptr1.get_usage_count() && ptr2.get_usage_count() == 2);

    //Move Assignmenet operator 
    auto ptr4= shared_ptr<int>(new int(10));
    auto ptr5= shared_ptr<int>(new int(20));
    assert(*ptr4 == 10);
    assert(ptr4.get_usage_count() == 1);
    ptr4 = shared_ptr<int>(my_move(ptr5));
    assert(*ptr4 == 20);
    assert(ptr4.get_usage_count() == 1);
    assert(ptr5.is_free());
}

void test_shared_ptr_funcs(){
    //Make_shared
    {
        auto ptr1 = make_shared<int>(20);
        assert(*ptr1 == 20);
        assert(ptr1.get_usage_count() == 1);
        auto ptr2 = make_shared<std::string>(8,'a');
        assert(*ptr2 == "aaaaaaaa");
    }
    //Reset
    {
        int* test_ptr1 = new int(20);
        auto ptr3 = shared_ptr<int>(test_ptr1);
        assert(*ptr3 == 20);
        assert(ptr3.get_usage_count() == 1);
        ptr3.reset();
        assert(ptr3.is_free());
    }
    //* operator
    {
        int* test_ptr2 = new int(20);
        auto ptr4 = shared_ptr<int>(test_ptr2);
        assert(*ptr4 == 20);
    }
    
    //-> operator
    {
        auto ptr2 = make_shared<std::string>(8,'a');
        assert(ptr2->length() == 8);
    }
    // [] operator
    {
        int* test_ptr = new int[10];
        for(int i =0 ; i<10 ; i++){
            test_ptr[i]=i;
        }
        auto ptr1 = shared_ptr<int[]>(test_ptr);
        for(int i =0 ; i<10 ; i++){
            assert(ptr1[i]==i);
        }
    }

}

void test_weak(){
    auto wptr =  weak_ptr<int>();
    assert(wptr.is_expired());
    {
        auto ptr1 = shared_ptr<int>(new int(10));
        assert(*ptr1 == 10);
        assert(ptr1.get_usage_count() == 1); 
        assert(ptr1.get_weak_count() == 0); 
        auto wptr1 = weak_ptr<int>(ptr1);
        assert(ptr1.get_weak_count() == 1); 
        assert(wptr1.get_usage_count() == 1); 
        assert(! wptr1.is_expired() );
        wptr = weak_ptr<int>(ptr1);
        assert(ptr1.get_weak_count() == 2); 
        assert(wptr.get_usage_count() == 2); 

    }
    assert(wptr.is_expired());
}
void test_shared_ptr_compare(){
    auto ptr4 = shared_ptr<int>();
    assert(ptr4==nullptr);
    assert(nullptr==ptr4);
  
}


void test_shared_ptr_main(){
    test_shptr_constructor();
    test_shptr_copy_constructor();
    test_shptr_move_constructor();
    test_shptr_assignment();
    test_shared_ptr_funcs();
    test_shared_ptr_compare();
    test_weak();
}