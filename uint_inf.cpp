#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include "dynamicArray.cpp"
#include "extraFunc.cpp"
#include <bitset>
/* unsinged int library 
needs better multiplacation and division functions
add mod and div combo functions
find memory leeks !!!! big problem
find problems
streamline function implementatons
*/
class uint_inf{
    public:
    dynamic_array <uint_fast64_t> value;
    size_t &size = value.size; 
    uint_inf() : value(dynamic_array <uint_fast64_t>(0,1,0)) {} 
    //uint_inf(uint_fast64_t init = 0) : value(dynamic_array <uint_fast64_t>(init,1,0)){} 
    uint_inf(uint_fast64_t init = 0,size_t start_size= 4): value(dynamic_array <uint_fast64_t>(init,start_size,0)){}

    uint_inf (const uint_inf& rvalue) {//http://www.cplusplus.com/doc/tutorial/classes2/
        this->value = dynamic_array <uint_fast64_t>(0,1,0);
        this->value = rvalue.value;
    }

    ~uint_inf(){
        this->value.del();
    }
    uint_inf& operator=(const uint_inf &rvalue){
        this->value = rvalue.value;
        return *this;
    }
    void operator=(const uint_fast64_t &rvalue){
        this->value[0] = rvalue;
    }
    void del(){
        return this->value.del();
    }
    size_t realSize()const{
        return this->value.realSize();
    }
    bool operator==(const uint_inf &rvalue)const{
        for(uint_fast64_t i = 0; i < this->value.size; i++){ // probably broken
            if(this->value[i] != rvalue.value[i])return 0;
        }
        return 1;
    }
    bool operator==(const uint_fast64_t &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return this->value[0] == rvalue;
    }
    bool operator!=(const uint_inf &rvalue)const{
        if(this->value.realSize()!=rvalue.value.realSize()) return 1;
        uint_fast64_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] != rvalue.value[i]);
    }
    bool operator!=(const uint_fast64_t &rvalue) const{
        if(this->value.realSize()>1) return 1;
        return this->value[0] != rvalue;
    }
    bool operator<(const uint_inf &rvalue) const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        uint_fast64_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] < rvalue.value[i]);
    }
    bool operator<(const uint_fast64_t &rvalue)const {
        if(this->value.realSize()>1) return 0;
        return (this->value[0] < rvalue);
    }
    bool operator>(const uint_inf &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        uint_fast64_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] > rvalue.value[i]);
    }
    bool operator>(const uint_fast64_t &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] > rvalue);
    }
    bool operator<=(const uint_inf &rvalue)const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        uint_fast64_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] <= rvalue.value[i]);
    }
    bool operator<=(const uint_fast64_t &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return (this->value[0] <= rvalue);
    }
    bool operator>=(const uint_inf &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        uint_fast64_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] >= rvalue.value[i]);
    }
    bool operator>=(const uint_fast64_t &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] >= rvalue);
    }
    void operator>>=(const size_t &rvalue){
        for(uint_fast64_t i = 0; i < this->value.size-1; i++){
        uint_fast64_t part = this->value.pointer[i]>>rvalue | this->value.pointer[i+1]<<(uint64_t)64-rvalue;
            this->value.pointer[i] = part;
        }
        this->value.pointer[this->value.size-1] >>= rvalue;
    }
    void operator<<=(const size_t &rvalue){
        for(uint_fast64_t i = this->value.size-1; i > 0 ; i--){
        uint_fast64_t part = this->value.pointer[i]<<rvalue | this->value.pointer[i-1]>>(uint64_t)64-rvalue;
            this->value.pointer[i] = part;
        }
        this->value.pointer[0] <<= rvalue;
    }
    uint_inf operator<<(const size_t &rvalue) const {
        uint_inf ret = *this;
        ret <<= rvalue;
        return ret;
    }
    uint_inf operator>>(const size_t &rvalue) const {
        uint_inf ret = *this;
        ret >>= rvalue;
        return ret;
    }
    void operator|=(const uint_inf &rvalue){
        uint_fast64_t test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            this->value[i] |= rvalue.value[i];
        }
    }
    void operator&=(const uint_inf &rvalue){
        uint_fast64_t test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            this->value[i] &= rvalue.value[i];
        }
    }
    void operator^=(const uint_inf &rvalue){
        uint_fast64_t test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(uint_fast64_t i = 0; i < test; i++){
            this->value[i] ^= rvalue.value[i];
        }
    }
    void operator^=(const uint_fast64_t &rvalue){
            this->value[0] ^= rvalue;
    }
    void operator&=(const uint_fast64_t &rvalue){
            this->value[0] &= rvalue;
    }
    void operator|=(const uint_fast64_t &rvalue){
            this->value[0] |= rvalue;
    }
    uint_inf operator~(){
        for(uint_fast64_t i = 0; i < this->value.size; i++){
            this->value[i] = ~this->value[i];
        }
        return *this;
    }
    uint_inf operator^(const uint_fast64_t &rvalue) const {
        uint_inf ret = *this;
        ret ^= rvalue;
        return ret;
    }
    uint_inf operator|(const uint_fast64_t &rvalue) const {
        uint_inf ret = *this;
        ret |= rvalue;
        return ret;
    }
    uint_inf operator&(const uint_fast64_t &rvalue) const {
        uint_inf ret = *this;
        ret &= rvalue;
        return ret;
    }
    uint_inf operator^(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret ^= rvalue;
        return ret;
    }
    uint_inf operator|(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret |= rvalue;
        return ret;
    }
    uint_inf operator&(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret &= rvalue;
        return ret;
    }
    uint_inf operator++(int null){
        for(uint_fast64_t i = 0;this->value[i]++ == (UINT64_MAX);i++);
        return *this;
    }
    void operator+=(const uint_fast64_t &rvalue){
        if(eFunc::addOvf(this->value[0],rvalue)){
                for(uint_fast64_t b = 1;this->value[b]++ == (UINT64_MAX);b++);
        }
    }
    void addOffset(const uint_fast64_t &rvalue, const size_t &offset){
        if(eFunc::addOvf(this->value[offset],rvalue)){
                for(uint_fast64_t b = 1+offset;this->value[b]++ == (UINT64_MAX);b++);
        }
    }
    uint_inf addOffset(const uint_fast64_t &rvalue, const size_t &offset) const {
        uint_inf ret = *this;
        ret.addOffset(rvalue,offset);
        return ret;
    }
    void operator+=(const uint_inf &rvalue){
        for(size_t i = 0;i < this->value.size || i < rvalue.value.size; i++){
            if(eFunc::addOvf(this->value[i],rvalue.value[i])){
                for(uint_fast64_t b = i+1;this->value[b]++ == (UINT64_MAX);b++);
            }
        }
    }
    uint_inf operator+(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf operator+(const uint_fast64_t &rvalue) const {
        uint_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf operator--(int null){
        for(uint_fast64_t i = 0;this->value[i]-- == 0;i++)if(i >= this->value.size-1)break;
        return *this;
    }
    void operator-=(const uint_inf &rvalue){
        for(size_t i = 0;i < this->value.size; i++){
            if(this->value[i] < rvalue.value[i]){
                this->value[i] -= rvalue.value[i];
                for(uint_fast64_t b = i+1;this->value[b]-- == 0;b++)if(b >= this->value.size-1 &&  b >= rvalue.value.size-1)break;
            }else {
                this->value[i] -= rvalue.value[i];
            }
        }
    }
    void operator-=(const uint_fast64_t &rvalue){
        if(this->value[0] < rvalue){
            this->value[0] -= rvalue;
            for(uint_fast64_t b = 1;this->value[b]-- == 0;b++)if(b >= this->value.size-1)break;
         }else {
            this->value[0] -= rvalue;
        }
    }
    uint_inf operator-(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf operator-(const uint_fast64_t &rvalue) const {
        uint_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf operator*(const uint_inf &rvalue) const {
        uint_inf out = uint_inf(0,(this->value.realSize()+1)*(rvalue.value.realSize()+1)); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        return out;
    }
    uint_inf operator*(const uint_fast64_t &rvalue) const{
        uint_inf out = uint_inf(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        return out;
    }
    void operator*=(const uint_fast64_t &rvalue){
        uint_inf out = uint_inf(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        *this = out; // slow
        out.del(); 
    }
    void operator*=(const uint_inf &rvalue){
        uint_inf out = uint_inf(0,(this->value.realSize()+1)*20); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                uint_fast64_t highWord;
                out.addOffset(eFunc::mul128(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        *this = out; // slow
        out.del();   
    }
    void operator/=(const uint_inf &rvalue){
        uint_inf remainder = 0;
        for(uint_fast64_t i = this->value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }   
        remainder.del();
    }
    void operator/=(const uint_fast64_t &rvalue){
        uint_inf remainder = 0;
        for(uint_fast64_t i = this->value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }   
        remainder.del();
    }
    uint_inf operator/(const uint_fast64_t &rvalue) const {
        uint_inf out = *this;
        out /= rvalue;
        return out;
    }
    uint_inf operator/(const uint_inf &rvalue) const {
        uint_inf out = *this;
        out /= rvalue;
        return out;
    }
    void operator%=(const uint_fast64_t &rvalue) {
        uint_inf remainder = 0;
        for(uint_fast64_t i = value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }  
        *this = remainder; 
        remainder.del();
    }
    void operator%=(const uint_inf &rvalue) {
        uint_inf remainder = 0;
        for(uint_fast64_t i = value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }  
        *this = remainder;
        remainder.del();
    }
    uint_inf divideRemainder(const uint_fast64_t &rvalue){
        uint_inf remainder = 0;
        for(uint_fast64_t i = this->value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf divideRemainder(const uint_inf &rvalue){
        uint_inf remainder = 0;
        for(uint_fast64_t i = this->value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((uint64_t)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf operator%(const uint_inf &rvalue) const {
        uint_inf out = *this;
        uint_inf remainder = 0;
        for(uint_fast64_t i = out.value.size; i-- > 0;){
            for(uint_fast64_t b = 64; b-- > 0;){
                remainder <<= 1;
                if(uint_fast64_t temp = (out.value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    out.value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    out.value[i] |= ((uint64_t)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf operator%(const uint_fast64_t &rvalue) const {
        uint_inf out = *this;
        out %= rvalue;
        return out;
    }
    std::string toString2() const {
        std::stringstream out;
        for(uint_fast64_t i = this->value.size; i-- > 0;){
            out << std::bitset<64>(this->value[i]);
        }
        return out.str();
    }
    std::string toString10() const {
        std::string out;
        uint_inf div = *this;
        while(div != 0) out.insert(0,std::to_string((div.divideRemainder(10)).value[0]));
        return out;
    }
};