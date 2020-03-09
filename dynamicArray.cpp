#include <iostream>
#include <stdio.h>
#include <string.h>
template <class Type>
class dynamic_array {
    public:
    Type *pointer = nullptr ;
    size_t size;
    Type fill = 0;
    dynamic_array(Type initVal = 0 ,size_t size = 1,const Type fill = 0){
        this->size = size;
        pointer = new Type[size];
        set(pointer, fill, size);
        pointer[0] = initVal;
        this->fill = fill;
    }
    ~dynamic_array(){
        delete[] pointer;
        size = 0;
        pointer = nullptr;
    }
    void del(){
        delete[] pointer;
        size = 0;
        pointer = nullptr;
    }
    dynamic_array (const dynamic_array& rvalue) {
        delete[] pointer;
        this->size = rvalue.size;
        pointer = new Type[rvalue.size];
        cpy(pointer, rvalue.pointer, rvalue.size );
    }
    dynamic_array& operator= (dynamic_array&& rvalue){
        delete[] pointer;
        this->size = rvalue.size;
        pointer = new Type[rvalue.size];
        cpy(pointer, rvalue.pointer, rvalue.size );
        return *this;
    }
    void operator=(const dynamic_array &rvalue) {
        delete[] pointer;
        this->size = rvalue.size;
        pointer = new Type[rvalue.size];
        cpy(pointer, rvalue.pointer, rvalue.size );
    }
    size_t realSize() const {
        size_t i = size-1;
        while(pointer[i]==0 && i > 0)i--;
        return i;
    }
    Type &operator[]  (const size_t &index) {
        if(index >= size){
             expand(index+1);
        }
        return pointer[index];
    }
    const Type operator[]  (const size_t &index) const {
        if(index >= size){
            return 0;
        }
        return pointer[index];
    }
    Type* expand(const size_t &size) {
        Type *new_ptr = new Type[size];
        set(new_ptr+this->size, fill, (size-this->size));
        while(this->size--){
            new_ptr[this->size] = pointer[this->size];
        }
        delete[] pointer; 
        this->size = size;
        return pointer = new_ptr;
    }
    
    Type * cpy (Type *dest, const Type *src, size_t len) {
        Type *d = dest;
        const Type *s = src;
        while (len--)
            *d++ = *s++;
        return dest;
    }
    Type * set (Type *dest, const Type val, size_t len) {
    Type *ptr = dest;
    while (len--)
        *ptr++ = val;
    return dest;
    }
};