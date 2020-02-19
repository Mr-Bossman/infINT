#include <iostream>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.cpp"
#include "extraFunc.cpp"

#include <bitset> // uneedd exept for tests


class infINT{
    public:
    dynamic_array <uint_fast64_t> value;
    size_t &size = value.size; 
    infINT(uint_fast64_t init = 0,size_t start_size= 4){
        value = dynamic_array <uint_fast64_t>(start_size,init);
    }
    size_t realSize(){
        return value.realSize();
    }
    bool operator==(const infINT a){ // comspre to normal int
        bool returnVal;
        for(uint_fast64_t i = 0; i < value.size; i++){
            returnVal &= value[i] == a.value[i];
        }
        return returnVal;
    }
    bool operator<(const infINT a){
        bool returnVal = 0;
        if(value.realSize() < a.value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] == a.value[i]; i--){
            returnVal = (value[i] < a.value[i]);
            if(i == -1) return 0;
        }
        return returnVal;
    }
    bool operator>(const infINT a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] == a.value[i]; i--){
            returnVal = (a.value[i] < value[i]);
            if(i == -1) return 0;
        }
        return returnVal;
    }
    bool operator<=(const infINT a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] > a.value[i]; i--){
            returnVal = (a.value[i] <= value[i]);
            if(i == -1) return 1;
        }
        return returnVal;
    }
    bool operator>=(const infINT a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] <
         a.value[i]; i--){
            returnVal = (a.value[i] <= value[i]);
            if(i == -1) return 1;
        }
        return returnVal;
    }
    void operator>>=(const size_t a){
        for(uint_fast64_t i = 0; i < value.size-1; i++){
        uint_fast64_t part = value.pointer[i]>>a | value.pointer[i+1]<<64-a;// 
            value.pointer[i] = part;
        }
        value.pointer[value.size-1] >>= a;
    }
    void operator<<=(const size_t a){
        for(uint_fast64_t i = value.size-1; i > 0 ; i--){
        uint_fast64_t part = value.pointer[i]<<a | value.pointer[i-1]>>64-a;
            value.pointer[i] = part;
        }
        value.pointer[0] <<= a;
    }
    void operator|=(const infINT a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] |= a.value[i];
        }
    }
    void operator&=(const infINT a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] &= a.value[i];
        }
    }
    void operator^=(const infINT a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] ^= a.value[i];
        }
    }
    void operator^=(const uint_fast64_t a){
            value[0] ^= a;
    }
    void operator&=(const uint_fast64_t a){
            value[0] &= a;
    }
    void operator|=(const uint_fast64_t a){
            value[0] |= a;
    }
    void operator~(){
        for(uint_fast64_t i = 0; i < value.size; i++){
            value[i] = ~value[i];
        }
    }
    infINT operator^(const uint_fast64_t rvalue) const {
        infINT ret = *this;
        ret ^= rvalue;
        return ret;
    }
    infINT operator|(const uint_fast64_t rvalue) const {
        infINT ret = *this;
        ret |= rvalue;
        return ret;
    }
    infINT operator&(const uint_fast64_t rvalue) const {
        infINT ret = *this;
        ret &= rvalue;
        return ret;
    }
    infINT operator^(const infINT rvalue) const {
        infINT ret = *this;
        ret ^= rvalue;
        return ret;
    }
    infINT operator|(const infINT rvalue) const {
        infINT ret = *this;
        ret |= rvalue;
        return ret;
    }
    infINT operator&(const infINT rvalue) const {
        infINT ret = *this;
        ret &= rvalue;
        return ret;
    }
    void operator++(int null){
        for(uint_fast64_t i = 0;value[i]++ == (UINT64_MAX);i++);
    }
    void operator+=(const uint_fast64_t rvalue){
        if(eFunc::addOvf(value[0],rvalue)){
                for(uint_fast64_t b = 1;value[b]++ == (UINT64_MAX);b++);
        }
    }
    void operator+=(const infINT rvalue){
        for(size_t i = 0;i < value.size || i < rvalue.value.size; i++){

            
            if(eFunc::addOvf(value[i],rvalue.value[i])){
                for(uint_fast64_t b = i+1;value[b]++ == (UINT64_MAX);b++);
            }
        }
    }
    infINT operator+(const infINT rvalue) const {
        infINT ret = *this;
        ret += rvalue;
        return ret;
    }
    infINT operator+(const uint_fast64_t rvalue) const {
        infINT ret = *this;
        ret += rvalue;
        return ret;
    }
    void operator--(int null){
        for(uint_fast64_t i = 0;value[i]-- == 0;i++)if(i >= value.size)exit(-1);
    }
    

    void operator-=(const infINT rvalue){
        for(size_t i = 0;i < value.size; i++){
            if(value[i] < rvalue.value[i]){
                value[i] -= rvalue.value[i];
                for(uint_fast64_t b = i+1;value[b]-- == 0;b++)if(b >= value.size-1)exit(-1); // negative number
            }else {
                value[i] -= rvalue.value[i];
            }
        }
    }
    void operator-=(const uint_fast64_t rvalue){
        if(value[0] < rvalue){
            value[0] -= rvalue;
            for(uint_fast64_t b = 1;value[b]-- == 0;b++)if(b >= value.size-1)exit(-1); // negative number
         }else {
            value[0] -= rvalue;
        }
    }
    infINT operator-(const infINT rvalue) const {
        infINT ret = *this;
        ret -= rvalue;
        return ret;
    }
    infINT operator-(const uint_fast64_t rvalue) const {
        infINT ret = *this;
        ret -= rvalue;
        return ret;
    }
    infINT operator*(const infINT rvalue){
        infINT out = infINT(0,value.size); // find size bcuase of overflow it will be larger // is it posible to have it without a new variable 
        for(size_t i = 0;i < value.size; i++){
            for(size_t b = 0;b < rvalue.value.size; b++){
                out.value[(i+b)+1] += eFunc::mulH(rvalue.value[b],value[i]);
                out.value[(i+b)] += eFunc::mulL(rvalue.value[b],value[i]);
            }
        }
        return out;
    }
    infINT operator*(const uint_fast64_t rvalue){
        infINT out = infINT(0,value.size); // find size bcuase of overflow it will be larger // is it posible to have it without a new variable 
        for(size_t i = 0;i < value.size; i++){
            out.value[i+1] += eFunc::mulH(rvalue,value[i]);
            out.value[i] += eFunc::mulL(rvalue,value[i]);
        }
        return out;
    }
};