#pragma once

#include <stdexcept>
#include "my_swap.h"
#include "unique_pointer.h"


template <typename T>
class DynamicArray{
private:
    int size;
    unique_ptr<T[]> elements;
    void swap(DynamicArray<T>& toSwap){
        my_swap(size, toSwap.size);
        my_swap(elements, toSwap.elements);
    }
public:
    DynamicArray(): size(0), elements(nullptr){} ;
    DynamicArray(int size): size(size){
        if(size < 0) 
            throw std::invalid_argument("некорректная размерность");
        if(size > 0) 
            elements=unique_ptr<T[]>(new T[size]);
    }

    DynamicArray(const unique_ptr<T[]>& items, int count):DynamicArray<T>(count){
        if(items == nullptr) 
            throw std::invalid_argument("некорректная размерность");
        for(int i = 0; i < count; i++){
            elements[i] = items[i];
        }
    }
    DynamicArray(const T* ptr , int count):DynamicArray<T>(count){
        if(ptr == nullptr) 
            throw std::invalid_argument("некорректная размерность");
        for(int i = 0;i < count; i++){
            elements[i] = ptr[i];
        }
    }
    DynamicArray(const T& fillElem, int count):DynamicArray<T>(count){
        for(int i = 0;i < size; i++){
            elements[i] = fillElem;
        }
    }
    DynamicArray(const DynamicArray<T>& array):DynamicArray<T>(array.elements,array.size){
        for(int i = 0;i < size; i++){
            elements[i] = array.elements[i];
        }
    }

    virtual ~DynamicArray() = default;

    int GetLength() const { 
        return this->size; 
    }

    T Get(int index) const {
        if(size <=index || index<0)
            throw std::out_of_range("неправильный инлекс");
        return elements[index];
    }

    void Set(const T& value,int index) {
        if(size<=index||index<0) 
            throw std::out_of_range("Некорректный индекс");
        elements[index]=value;
    }
    void Resize(int newSize,int offset){ 
        if(newSize<0 || offset<0 || offset+size>newSize)
            throw std::invalid_argument("");
        if(!newSize){
            elements.reset();
            return;
        }
        auto buf = unique_ptr<T[]>( new T[newSize] );
        if(elements != nullptr){
            for(int i = 0; i < std::min(size,newSize); i++){
                buf[i+offset] = elements[i];
            }
        }
        elements = buf;
        size = newSize;
    }

    void Resize(int newSize){ 
        if(newSize<0||size>newSize)
            throw std::invalid_argument("Неправильная работа resize");
        if(newSize == 0){
                elements.reset();
            return;
        }
        auto buf = unique_ptr<T[]>( new T[newSize] );
        if(elements != nullptr){
            for(int i = 0;i<std::min(size,newSize);i++){
                buf[i] = elements[i];
            }
            elements.reset();
        }
        elements = buf;
        size = newSize;
    }

    T& operator[](int index){
        if(size <= index)
            throw std::out_of_range("Не");
        if(size <= 0) 
            throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    const T& operator[](int index) const{
        if(size <= index)
            throw std::out_of_range("Некорректный индекс");
        if(size <= 0) 
            throw std::out_of_range("Getter call in empty collection");
        return elements[index];
    }
    bool operator==(const DynamicArray<T>& array){
        if(array.size != size) 
            return false;
        for(int i = 0; i < array.size; i++){
            if(array[i]!=(*this)[i])
                return false;
        }
        return true;
    }
    DynamicArray<T>& operator=( DynamicArray<T> array){ 
       swap(array);
       return *this;
    }
};