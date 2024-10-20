#pragma once 

#include "unique_ptr.h"
#include "my_swap.h"
#include "my_move.h"



void test_unptr_constructor(){
    //Constructor
    auto ptr1 = unique_ptr<int>(new int(10));
    assert(*ptr1 == 10);
}
void test_unptr_move_constructor(){
    //Move constructor
    auto ptr3 = unique_ptr<int>(new int(10));
    auto ptr4 = unique_ptr<int>(my_move(ptr3));
    assert(*ptr4 == 10);
    assert(ptr3.is_free());
}

void test_unique_ptr_funcs(){
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
        auto ptr3 = unique_ptr<int>(test_ptr1);
        assert(*ptr3 == 20);
        ptr3.reset();
        assert(ptr3.is_free());
    }
    //* operator
    {
        int* test_ptr2 = new int(20);
        auto ptr4 = unique_ptr<int>(test_ptr2);
        assert(*ptr4 == 20);
    }
    
    //-> operator
    {
        auto ptr2 = make_shared<std::string>(8,'a');
        assert(ptr2->length() == 8);
    }
    // [] operator
    {
        auto ptr1 = unique_ptr<int[]>(new int[10]);
        for(int i =0 ; i<10 ; i++){
            ptr1[i]=i;
        }
        for(int i =0 ; i<10 ; i++){
            assert(ptr1[i]==i);
        }
    }

}
void test_unique_ptr_compare(){
    void* p = new char[sizeof(int)*10];
    int* array = static_cast<int*>(p);
    for(int i =0 ; i<10 ; i++){
        array[i]=i;
    }
    auto ptr1 = unique_ptr<int>( array + 2 );
    auto ptr2 = unique_ptr<int>( array + 2 );
    auto ptr3 = unique_ptr<int>( array + 7 );
    auto ptr4 = unique_ptr<int>();
    assert(ptr4==nullptr);
    assert(nullptr==ptr4);
    assert( ptr1 == ptr2 );
    assert( !( ptr1!=ptr2) );
    ptr1.release();
    ptr3.release();
    ptr2.release();
}


void test_unique_ptr_main(){
    test_unptr_constructor();
    test_unptr_move_constructor();
    test_unique_ptr_funcs();
    test_unique_ptr_compare();
}