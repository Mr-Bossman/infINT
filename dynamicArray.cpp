#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
template <class Type>
class dynamic_array {
    public:
    Type *pointer = nullptr ;
    size_t size;
    size_t offset = 0;
    dynamic_array(Type initVal = 0 ,size_t size = 1){
        this->size = size;
        this->pointer = new Type[size];
        while(this->size--){
            this->pointer[this->size] = 0;
        }
        this->pointer[0] = initVal;
        this->size = size;
    }
    ~dynamic_array(){
        delete[] this->pointer;
        this->offset = this->size = 0;
        this->pointer = nullptr;
    }
    void del(){
        delete[] this->pointer;
        this->offset = this->size = 0;
        this->pointer = nullptr;
    }
    dynamic_array (const dynamic_array& rvalue) {
        delete[] this->pointer;
        this->size = rvalue.Size();
        this->pointer = new Type[this->size];
        while(this->size--){
            this->pointer[this->size] = rvalue.pointer[this->size+rvalue.offset];
        }
        this->size = rvalue.Size();
    }
    dynamic_array& operator= (const dynamic_array& rvalue){
        delete[] this->pointer;
        this->size = rvalue.Size();
        this->pointer = new Type[this->size];
        while(this->size--){
            this->pointer[this->size] = rvalue.pointer[this->size+rvalue.offset];
        }
        this->size = rvalue.Size();
        return *this;
    }
    size_t realSize() const {
        size_t i = this->size-1;
        while(this->pointer[i]==0 && i > 0)i--;
        return i;
    }
    size_t Size() const {
        return this->size-this->offset;
    }
    void swap(dynamic_array& rvalue){
        Type* tpointer = this->pointer;
        size_t tsize = this->size;
        size_t toffset = this->offset;
        this->pointer = rvalue.pointer;
        this->size = rvalue.size;
        this->offset = rvalue.offset;
        rvalue.offset = toffset;
        rvalue.size = tsize;
        rvalue.pointer = tpointer;
    }
    Type &operator[]  (const size_t &index) {
        if(index+this->offset >= this->size){
             expand(index+1);
        }
        if(index > this->size-this->offset)pointer[index+this->offset] = 0;
        return pointer[index+this->offset];
    }
    const Type operator[]  (const size_t &index) const {
        if(index+this->offset >= this->size ){
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
    Type* Lshift(size_t& shift){
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
    Type* Lshift(const size_t&& shiftA){
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
