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
needs better shift cant shift more than 64
find problems
streamline function implementatons
*/
template <class Type>
class uint_inf{
    public:
    dynamic_array <Type> value;
    size_t &size = value.size; 
    uint_inf() : value(dynamic_array <Type>(0,1,0)) {} 
    //uint_inf(Type init = 0) : value(dynamic_array <Type>(init,1,0)){} 
    uint_inf(Type init = 0,size_t start_size= 4): value(dynamic_array <Type>(init,start_size,0)){}

    uint_inf (const uint_inf& rvalue) {//http://www.cplusplus.com/doc/tutorial/classes2/
        this->value = dynamic_array <Type>(0,1,0);
        this->value = rvalue.value;
    }
    ~uint_inf(){
        this->value.del();
    }
    uint_inf& operator=(const uint_inf &rvalue){
        this->value = rvalue.value;
        return *this;
    }
    void operator=(const Type &rvalue){
        this->value[0] = rvalue;
    }
    void del(){
        this->value.del();
    }
    size_t realSize()const{
        return this->value.realSize();
    }
    bool operator==(const uint_inf &rvalue)const{
        if(this->value.realSize()!=rvalue.value.realSize()) return 0;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] == rvalue.value[i]);
    }
    bool operator==(const Type &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return this->value[0] == rvalue;
    }
    bool operator!=(const uint_inf &rvalue)const{
        if(this->value.realSize()!=rvalue.value.realSize()) return 1;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] != rvalue.value[i]);
    }
    bool operator!=(const Type &rvalue) const{
        if(this->value.realSize()>1) return 1;
        return this->value[0] != rvalue;
    }
    bool operator<(const uint_inf &rvalue) const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] < rvalue.value[i]);
    }
    bool operator<(const Type &rvalue)const {
        if(this->value.realSize()>1) return 0;
        return (this->value[0] < rvalue);
    }
    bool operator>(const uint_inf &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] > rvalue.value[i]);
    }
    bool operator>(const Type &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] > rvalue);
    }
    bool operator<=(const uint_inf &rvalue)const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] <= rvalue.value[i]);
    }
    bool operator<=(const Type &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return (this->value[0] <= rvalue);
    }
    bool operator>=(const uint_inf &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        Type i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] >= rvalue.value[i]);
    }
    bool operator>=(const Type &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] >= rvalue);
    }
    void operator>>=(const size_t &rvalue){
        for(Type i = 0; i < this->value.size-1; i++){
            this->value[i] >>= rvalue; 
            this->value[i] |= this->value[i+1]<<(Type)sizeof(Type)-rvalue;
        }
        this->value[this->value.size-1] >>= rvalue;
    }
    void operator<<=(const size_t &rvalue){
        for(Type i = this->value.realSize()+1; i > 0 ; i--){
            this->value[i] <<= rvalue;
            this->value[i] |= this->value[i-1]>>(Type)sizeof(Type)-rvalue;
        }
        this->value[0] <<= rvalue;
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
    void div2() {
        for(Type i = 0; i < this->value.size-1; i++){
            this->value[i] >>= 1; 
            this->value[i] |= this->value[i+1]<<(Type)(sizeof(Type)-1);
        }
        this->value[this->value.size-1] >>= 1;
    }
    void mul2() {
        for(Type i = this->value.realSize()+1; i > 0 ; i--){
            this->value[i] <<= 1;
            this->value[i] |= this->value[i-1]>>(Type)(sizeof(Type)-1);
        }
        this->value[0] <<= 1;
    }
    void operator|=(const uint_inf &rvalue){
        Type test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(Type i = 0; i < test; i++){
            this->value[i] |= rvalue.value[i];
        }
    }
    void operator&=(const uint_inf &rvalue){
        Type test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(Type i = 0; i < test; i++){
            this->value[i] &= rvalue.value[i];
        }
    }
    void operator^=(const uint_inf &rvalue){
        Type test = (rvalue.value.realSize() > this->value.realSize())? rvalue.value.realSize():this->value.realSize();
        for(Type i = 0; i < test; i++){
            this->value[i] ^= rvalue.value[i];
        }
    }
    void operator^=(const Type &rvalue){
            this->value[0] ^= rvalue;
    }
    void operator&=(const Type &rvalue){
            this->value[0] &= rvalue;
    }
    void operator|=(const Type &rvalue){
            this->value[0] |= rvalue;
    }
    uint_inf operator~(){
        for(Type i = 0; i < this->value.size; i++){
            this->value[i] = ~this->value[i];
        }
        return *this;
    }
    uint_inf operator^(const Type &rvalue) const {
        uint_inf ret = *this;
        ret ^= rvalue;
        return ret;
    }
    uint_inf operator|(const Type &rvalue) const {
        uint_inf ret = *this;
        ret |= rvalue;
        return ret;
    }
    uint_inf operator&(const Type &rvalue) const {
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
        for(Type i = 0;this->value[i]++ == sizeof(Type);i++);
        return *this;
    }
    void operator+=(const Type &rvalue){
        if(eFunc::addOvf(this->value[0],rvalue)){
                for(Type b = 1;this->value[b]++ == sizeof(Type);b++);
        }
    }
    void addOffset(const Type &rvalue, const size_t &offset){
        if(eFunc::addOvf(this->value[offset],rvalue)){
                for(Type b = 1+offset;this->value[b]++ == sizeof(Type);b++);
        }
    }
    uint_inf addOffset(const Type &rvalue, const size_t &offset) const {
        uint_inf ret = *this;
        ret.addOffset(rvalue,offset);
        return ret;
    }
    void operator+=(const uint_inf &rvalue){
        for(size_t i = 0;i < this->value.size || i < rvalue.value.size; i++){
            if(eFunc::addOvf(this->value[i],rvalue.value[i])){
                for(Type b = i+1;this->value[b]++ == sizeof(Type);b++);
            }
        }
    }
    uint_inf operator+(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf operator+(const Type &rvalue) const {
        uint_inf ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf operator--(int null){
        for(Type i = 0;this->value[i]-- == 0;i++)if(i >= this->value.size-1)break;
        return *this;
    }
    void operator-=(const uint_inf &rvalue){
        for(size_t i = 0;i < this->value.size; i++){
            if(this->value[i] < rvalue.value[i]){
                this->value[i] -= rvalue.value[i];
                for(Type b = i+1;this->value[b]-- == 0;b++)if(b >= this->value.size-1 &&  b >= rvalue.value.size-1)break;
            }else {
                this->value[i] -= rvalue.value[i];
            }
        }
    }
    void operator-=(const Type &rvalue){
        if(this->value[0] < rvalue){
            this->value[0] -= rvalue;
            for(Type b = 1;this->value[b]-- == 0;b++)if(b >= this->value.size-1)break;
         }else {
            this->value[0] -= rvalue;
        }
    }
    uint_inf operator-(const uint_inf &rvalue) const {
        uint_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf operator-(const Type &rvalue) const {
        uint_inf ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf operator*(const uint_inf &rvalue) const {
        uint_inf out = uint_inf(0,(this->value.realSize()+1)*(rvalue.value.realSize()+1)); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        return out;
    }
    uint_inf operator*(const Type &rvalue) const{
        uint_inf out = uint_inf(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        return out;
    }
    void operator*=(const Type &rvalue){
        uint_inf out = uint_inf(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        *this = out; // slow
        out.del(); 
    }
    void operator*=(const uint_inf &rvalue){
        uint_inf out = uint_inf(0,(this->value.realSize()+1)*20); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        *this = out; // slow
        out.del();   
    }
    void operator/=(const uint_inf &rvalue){
        uint_inf remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }   
        remainder.del();
    }
    void operator/=(const Type &rvalue){
        uint_inf remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }   
        remainder.del();
    }
    uint_inf operator/(const Type &rvalue) const {
        uint_inf out = *this;
        out /= rvalue;
        return out;
    }
    uint_inf operator/(const uint_inf &rvalue) const {
        uint_inf out = *this;
        out /= rvalue;
        return out;
    }
    void operator%=(const Type &rvalue) {
        uint_inf remainder = 0;
        for(Type i = value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }  
        *this = remainder; 
        remainder.del();
    }
    void operator%=(const uint_inf &rvalue) {
        uint_inf remainder = 0;
        for(Type i = value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }  
        *this = remainder;
        remainder.del();
    }
    uint_inf divideRemainder(const Type &rvalue){
        uint_inf remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf divideRemainder(const uint_inf &rvalue){
        uint_inf remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (this->value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    this->value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    this->value[i] |= ((Type)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf operator%(const uint_inf &rvalue) const {
        uint_inf out = *this;
        uint_inf remainder = 0;
        for(Type i = out.value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (out.value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    out.value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    out.value[i] |= ((Type)1<<b);
                }
            }
        }  
        return remainder;
    }
    uint_inf operator%(const Type &rvalue) const {
        uint_inf out = *this;
        uint_inf remainder = 0;
        for(Type i = out.value.size; i-- > 0;){
            for(Type b = sizeof(Type); b-- > 0;){
                remainder.mul2();
                if(Type temp = (out.value[i]>>b)&1){
                    remainder.value[0] |= temp;
                    out.value[i] ^= (temp<<b);
                }
                if (remainder >= rvalue){
                    remainder -= rvalue;
                    out.value[i] |= ((Type)1<<b);
                }
            }
        }  
        return remainder;
    }
    std::string toString2() const {
        std::stringstream out;
        for(Type i = this->value.size; i-- > 0;){
            out << std::bitset<sizeof(Type)>(this->value[i]);
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