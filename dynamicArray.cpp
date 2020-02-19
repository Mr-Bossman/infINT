#include <iostream>
#include <stdio.h>
#include <string.h>
template <class Type>
class dynamic_array {
    public:
    Type *pointer = nullptr ;
    size_t size;
    dynamic_array(size_t size = 1, Type initVal = 0){
            this->size = size;
            pointer = new Type[size];
            memset(pointer, 0, size*sizeof(Type));
            pointer[0] = initVal;
    }
    size_t realSize() const {
        size_t i = size-1;
        while(pointer[i]==0)i--;
        return i;
    }
    Type &operator[]  (const size_t index) {
        if(index >= size){
             expand(index+1);
        }
        return pointer[index];
    }
    const Type operator[]  (const size_t index) const {
        if(index >= size){
            return 0;
        }
        return pointer[index];
    }
    Type* expand(const size_t size) {
        Type *new_ptr = new Type[size];
        memset(new_ptr+this->size, 0, (size-this->size)*sizeof(Type));
        while(this->size--){
            new_ptr[this->size] = pointer[this->size];
        }
        delete[] pointer;// need to set end to 0 with memset 
        this->size = size;
        return pointer = new_ptr;
    }
    void Delete(){
        delete[] pointer;
        size = 0;
        pointer = nullptr;
    }
};