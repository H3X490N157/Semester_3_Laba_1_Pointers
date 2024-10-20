//#include <iostream>
#include "shared_ptr.h"
#include "DynamicArray.h"
#include "DynamicArrayTest.h"
#include "SharedPtrTest.h"
#include "UniquePtrTest.h"
#include <iostream>
//clang++ main.cpp  -Wall -Wextra -o main.exe
int main(){
    /*
    int* ptr = new int[10];
    {
        for(int i =0 ; i<10 ; i++){
            ptr[i]=i;
        }
        auto ptr1 = shared_ptr<int[],My_Universal_Deleter<int[]>>(ptr);
        assert(ptr1.get_usage_count() == 1);
        for(int i =0 ; i<10 ; i++){
            std::cout<<ptr1[i]<<std::endl;
        }
    }
    auto ptr2 = make_shared<int>(10);
    std::cout<<ptr[0]<<std::endl;
    auto ptr2 = make_shared<int>(10);
    std::cout<<sizeof(shared_ptr<double>)<<std::endl;
    std::cout<<sizeof(unique_ptr<double>)<<std::endl;
    std::cout<<sizeof(weak_ptr<double>)<<std::endl;
    */
    

    test_move();
    test_swap();
    Test_DynamicArray_Constructors();
    Test_DynamicArray_Set();
    Test_DynamicArray_CompareOperator();
    test_shared_ptr_main();
    test_unique_ptr_main();
    std::cout<<"Success"<<std::endl;
}