#include <iostream>
#include <stdio.h>
#include <string.h>
template <class Type>
class dynamic_array {
    public:
    Type *pointer = nullptr;
    size_t offset = 0;
    size_t size;
    dynamic_array(Type initVal = 0 ,size_t size = 1){
        this->size = size;
        this->pointer = new Type[size];
        while(size--){
            this->pointer[size] = 0;
        }
        this->pointer[0] = initVal;
    }
    ~dynamic_array(){
        delete[] this->pointer;
        this->size = this->offset = 0;
        this->pointer = nullptr;
    }
    void del(){
        delete[] this->pointer;
        this->size = this->offset = 0;
        this->pointer = nullptr;
    }
    dynamic_array (const dynamic_array& rvalue) {
        delete[] pointer;
        this->size = rvalue.size;
        this->pointer = new Type[size];
        this->offset = 0;
        while(this->size--){
            this->pointer[this->size] = rvalue.pointer[this->size+rvalue.offset];
        }
        this->size = rvalue.size;
    }
    dynamic_array& operator= (dynamic_array&& rvalue){
        delete[] pointer;
        this->size = rvalue.size;
        this->pointer = new Type[size];
        this->offset = 0;
        while(this->size--){
            this->pointer[this->size] = rvalue.pointer[this->size+rvalue.offset];
        }
        this->size = rvalue.size;
        return *this;
    }
    void operator=(const dynamic_array &rvalue) {
        delete[] pointer;
        this->size = rvalue.size;
        this->pointer = new Type[size];
        this->offset = 0;
        while(this->size--){
            this->pointer[this->size] = rvalue.pointer[this->size+rvalue.offset];
        }
        this->size = rvalue.size;
    }
    size_t realSize() const {
        register size_t i = this->size-1;
        while(this->pointer[i]==0 && i > 0)i--;
        return i;
    }
    Type &operator[]  (const size_t &index) {
        if(index+this->offset >= *(&this->pointer + 1) - this->pointer){
             expand(index+1);
        }
        if(index+this->offset >= size)pointer[index+this->offset] = 0;
        return pointer[index+this->offset];
    }
    const Type operator[]  (const size_t &index) const {
        if(index+this->offset >= size ){
            return 0;
        }
        return pointer[index+this->offset];
    }
    Type* expand(const size_t size) {
        Type *new_ptr = new Type[size];
        register size_t loop = size;
        while(loop-- > this->size){
            new_ptr[loop] = 0;
        }
        while(this->size--){
            new_ptr[this->size] = pointer[this->size+this->offset];
        }
        delete[] pointer; 
        this->size = size;
        return this->pointer = new_ptr;
    }
    Type pop(){
        register Type ret = (*this)[0];
        this->offset++;
        return ret;
    }
    void pop(const size_t& shift){
        this->offset += shift;
    }
    Type* Rshift(size_t& shift){
        register Type *new_ptr = new Type[this->size+shift];
        register size_t size = this->size;
        this->size += shift;
        while(size--){
            new_ptr[size+shift] = pointer[size+this->offset];
        }
        while(shift--){
            new_ptr[shift] = 0;
        }
        delete[] pointer; 
        return this->pointer = new_ptr;
    }
    Type* Rshift(const size_t&& shiftA){
        register size_t shift = shiftA;
        Type *new_ptr = new Type[this->size+shift];
        register size_t size = this->size;
        this->size += shift;
        while(size--){
            new_ptr[size+shift] = pointer[size+this->offset];
        }
        while(shift--){
            new_ptr[shift] = 0;
        }
        delete[] pointer; 
        return this->pointer = new_ptr;
    }
};