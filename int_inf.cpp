#include <iostream>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.cpp"
#include "extraFunc.cpp"
/* singed int library 
needs better multiplacation and division functions*/

class int_inf{
    public:
    dynamic_array <uint_fast64_t> value;
    size_t &size = value.size;
    int_inf(uint_fast64_t init,size_t start_size = 4, bool negative = 0 ){
        value = dynamic_array <uint_fast64_t>(init,start_size,(((int_fast64_t)init < 0) || negative)?UINT64_MAX:0);// cheack not working posibly breaking >> function
    }
    size_t realSize(){
        return value.realSize();
    }
    void operator=(const int_inf &a){
        this->value = a.value;
    }
    void operator=(const uint_fast64_t a){
        int_inf(a,4,0);
    }
    bool operator==(const int_inf &a){ // comspre to normal int
        bool returnVal;
        for(uint_fast64_t i = 0; i < value.size; i++){
            returnVal &= value[i] == a.value[i];
        }
        return returnVal;
    }
    bool operator<(const int_inf &a){
        bool returnVal = 0;
        if(value.realSize() < a.value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] == a.value[i]; i--){
            returnVal = (value[i] < a.value[i]);
            if(i == -1) return 0;
        }
        return returnVal;
    }
    bool operator>(const int_inf &a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] == a.value[i]; i--){
            returnVal = (a.value[i] < value[i]);
            if(i == -1) return 0;
        }
        return returnVal;
    }
    bool operator<=(const int_inf &a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] > a.value[i]; i--){
            returnVal = (a.value[i] <= value[i]);
            if(i == -1) return 1;
        }
        return returnVal;
    }
    bool operator>=(const int_inf &a){
        bool returnVal = 0;
        if(a.value.realSize() < value.realSize()) return 1;
        for(uint_fast64_t i = value.size-1;value[i] <
         a.value[i]; i--){
            returnVal = (a.value[i] <= value[i]);
            if(i == -1) return 1;
        }
        return returnVal;
    }
    void operator>>=(const size_t &a){
        for(uint_fast64_t i = 0; i < value.size-1; i++){
        uint_fast64_t part = value.pointer[i]>>a | value.pointer[i+1]<<64-a;// 
            value.pointer[i] = part;
        }
        value.pointer[value.size-1] >>= a;
    }
    void operator<<=(const size_t &a){
        for(uint_fast64_t i = value.size-1; i > 0 ; i--){
        uint_fast64_t part = value.pointer[i]<<a | value.pointer[i-1]>>64-a;
            value.pointer[i] = part;
        }
        value.pointer[0] <<= a;
    }
    void operator|=(const int_inf &a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] |= a.value[i];
        }
    }
    void operator&=(const int_inf &a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] &= a.value[i];
        }
    }
    void operator^=(const int_inf &a){
        uint_fast64_t test = (a.value.realSize() > value.realSize())? a.value.realSize():value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            value[i] ^= a.value[i];
        }
    }
    void operator^=(const uint_fast64_t &a){
            value[0] ^= a;
    }
    void operator&=(const uint_fast64_t &a){
            value[0] &= a;
    }
    void operator|=(const uint_fast64_t &a){
            value[0] |= a;
    }
    void operator~(){
        for(uint_fast64_t i = 0; i < value.size; i++){
            value[i] = ~value[i];
        }
    }
    int_inf operator^(const uint_fast64_t &rvalue) const {
        int_inf ret = *this;
        ret ^= rvalue;
        return ret;
    }
    int_inf operator|(const uint_fast64_t &rvalue) const {
        int_inf ret = *this;
        ret |= rvalue;
        return ret;
    }
    int_inf operator&(const uint_fast64_t &rvalue) const {
        int_inf ret = *this;
        ret &= rvalue;
        return ret;
    }
    int_inf operator^(const int_inf &rvalue) const {
        int_inf ret = *this;
        ret ^= rvalue;
        return ret;
    }
    int_inf operator|(const int_inf &rvalue) const {
        int_inf ret = *this;
        ret |= rvalue;
        return ret;
    }
    int_inf operator&(const int_inf &rvalue) const {
        int_inf ret = *this;
        ret &= rvalue;
        return ret;
    }
    void operator++(int null){
        for(uint_fast64_t i = 0;value[i]++ == (UINT64_MAX);i++);
    }
    void operator+=(const uint_fast64_t &rvalue){
        if(eFunc::addOvf(value[0],rvalue)){
                for(uint_fast64_t b = 1;value[b]++ == (UINT64_MAX);b++)if(b >= value.size-1)break;
        }
    }
    void addOffset(const uint_fast64_t &rvalue, const size_t &offset){
        if(eFunc::addOvf(value[offset],rvalue)){
                for(uint_fast64_t b = 1+offset;value[b]++ == (UINT64_MAX);b++);
        }
    }
    int_inf addOffset(const uint_fast64_t &rvalue, const size_t &offset) const {
        int_inf ret = *this;
        ret.addOffset(rvalue,offset);
        return ret;
    }
    void operator+=(const int_inf &rvalue){
        for(size_t i = 0;i < value.size || i < rvalue.value.size; i++){
            if(eFunc::addOvf(value[i],rvalue.value[i])){
                for(uint_fast64_t b = i+1;value[b]++ == (UINT64_MAX);b++)if(b >= value.size-1 &&  b >= rvalue.value.size-1)break;
            }
        }
    }
    int_inf operator+(const int_inf &rvalue) const {
        int_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    int_inf operator+(const uint_fast64_t &rvalue) const {
        int_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    void operator--(int null){
        for(uint_fast64_t i = 0;value[i]-- == 0;i++)if(i >= value.size)break;
    }
    

    void operator-=(const int_inf &rvalue){
        for(size_t i = 0;i < value.size; i++){
            if(value[i] < rvalue.value[i]){
                value[i] -= rvalue.value[i];
                for(uint_fast64_t b = i+1;value[b]-- == 0;b++)if(b >= value.size-1 &&  b >= rvalue.value.size-1)break;
            }else {
                value[i] -= rvalue.value[i];
            }
        }
    }
    void operator-=(const uint_fast64_t &rvalue){
        if(value[0] < rvalue){
            value[0] -= rvalue;
            for(uint_fast64_t b = 1;value[b]-- == 0;b++)if(b >= value.size-1)break;
         }else {
            value[0] -= rvalue;
        }
    }
    int_inf operator-(const int_inf &rvalue) const {
        int_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    int_inf operator-(const uint_fast64_t &rvalue) const {
        int_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    int_inf operator*(const int_inf &rvalue){
        int_inf out = int_inf(0,value.size*rvalue.value.size); // find size bcuase of overflow it will be larger // is it posible to have it without a new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue.value[b],value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        return out;
    }
    int_inf operator*(const uint_fast64_t &rvalue){
        int_inf out = int_inf(0,value.size); // find size bcuase of overflow it will be larger // is it posible to have it without a new variable 
        for(size_t i = 0;i < value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue,value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        return out;
    }
    void operator*=(const uint_fast64_t &rvalue){
        *this = *this*rvalue; // slow!!!!!
    }
    void operator*=(const int_inf &rvalue){
        *this = *this*rvalue; // slow !!!!
    }


    void operator/=(const int_inf &rvalue){
        for(uint64_t i = rvalue.value.size-1;;){
        uint_fast64_t remainder = 0;
        //this->value[i] = eFunc::div_rq(this.value[io],rvalue.value[i],remainder);
        }
    }
    void operator/=(const uint_fast64_t &rvalue){
        //for(uint64_t i = rvalue.value.size-1;;){
        //uint_fast64_t remainder = 0;
        //this->value[i] = eFunc::div_rq(this.value[io],rvalue.value[i],remainder);
        //}
    }
};