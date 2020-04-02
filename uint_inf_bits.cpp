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
find problems / test
optimize functions
*/
template <class Type>
class uint_inf{
    public:
    dynamic_array <Type> value;
    const size_t Tsize = 8*sizeof(Type);
    size_t &size = value.size; 
    uint_inf() : value(dynamic_array <Type>(0,4)) {} 
    uint_inf(Type init = 0,size_t start_size= 4): value(dynamic_array <Type>(init,start_size)){}

    uint_inf (const uint_inf<Type>& rvalue) {
        this->value = dynamic_array <Type>(0,4);
        this->value = rvalue.value;
    }
    ~uint_inf(){
        this->value.del();
    }
    uint_inf<Type>& operator=(const uint_inf<Type> &rvalue){
        this->value = rvalue.value;
        return *this;
    }
    uint_inf<Type> operator=(const Type &rvalue){
        this->value[0] = rvalue;
    }
    void del(){
        this->value.del();
    }
    size_t realSize()const{
        return this->value.realSize();
    }
    bool operator==(const uint_inf<Type> &rvalue)const{
        if(this->value.realSize()!=rvalue.value.realSize()) return 0;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] == rvalue.value[i]);
    }
    bool operator==(const Type &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return this->value[0] == rvalue;
    }
    bool operator!=(const uint_inf<Type> &rvalue)const{
        if(this->value.realSize()!=rvalue.value.realSize()) return 1;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] != rvalue.value[i]);
    }
    bool operator!=(const Type &rvalue) const{
        if(this->value.realSize()>1) return 1;
        return this->value[0] != rvalue;
    }
    bool operator<(const uint_inf<Type> &rvalue) const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] < rvalue.value[i]);
    }
    bool operator<(const Type &rvalue)const {
        if(this->value.realSize()>1) return 0;
        return (this->value[0] < rvalue);
    }
    bool operator>(const uint_inf<Type> &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] > rvalue.value[i]);
    }
    bool operator>(const Type &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] > rvalue);
    }
    bool operator<=(const uint_inf<Type> &rvalue)const{
        if(this->value.realSize()<rvalue.value.realSize()) return 1;
        else if(this->value.realSize()>rvalue.value.realSize()) return 0;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] <= rvalue.value[i]);
    }
    bool operator<=(const Type &rvalue)const{
        if(this->value.realSize()>1) return 0;
        return (this->value[0] <= rvalue);
    }
    bool operator>=(const uint_inf<Type> &rvalue)const{
        if(this->value.realSize()>rvalue.value.realSize()) return 1;
        else if(this->value.realSize()<rvalue.value.realSize()) return 0;
        register size_t i = this->value.size-1;
        while(this->value[i] == rvalue.value[i] && i > 0)i--;
        return (this->value[i] >= rvalue.value[i]);
    }
    bool operator>=(const Type &rvalue)const{
        if(this->value.realSize()>1) return 1;
        return (this->value[0] >= rvalue);
    }
    uint_inf<Type> operator>>=(const size_t &rvalue){
        register size_t temp = rvalue/Tsize;
        if(temp)this->value.pop(temp);
        register size_t mod = rvalue%Tsize;
        for(Type i = 0; i < this->value.size-1; i++){
            this->value[i] >>= mod; 
            this->value[i] |= this->value[i+1]<<(Type)Tsize-mod;
        }
        this->value[this->value.size-1] >>= mod;
        return *this;
    }
    uint_inf<Type> operator<<=(const size_t &rvalue){
        register size_t temp = rvalue/Tsize;
        if(temp)this->value.Rshift(temp);
        register size_t mod = rvalue%Tsize;
        for(Type i = this->value.realSize()+1; i > 0 ; i--){
            this->value[i] <<= mod;
            this->value[i] |= this->value[i-1]>>(Type)Tsize-mod;
        }
        this->value[0] <<= mod;
        return *this;
    }
    uint_inf<Type> operator<<(const size_t &rvalue) const {
        uint_inf<Type> ret = *this;
        ret <<= rvalue;
        return ret;
    }
    uint_inf<Type> operator>>(const size_t &rvalue) const {
        uint_inf<Type> ret = *this;
        ret >>= rvalue;
        return ret;
    }
    uint_inf<Type> div2() {
        for(Type i = 0; i < this->value.size-1; i++){
            this->value[i] >>= 1; 
            this->value[i] |= this->value[i+1]<<(Type)(Tsize-1);
        }
        this->value[this->value.size-1] >>= 1;
        return *this;
    }
    uint_inf<Type> mul2() {
        for(Type i = this->value.realSize()+1; i > 0 ; i--){
            this->value[i] <<= 1;
            this->value[i] |= this->value[i-1]>>(Type)(Tsize-1);
        }
        this->value[0] <<= 1;
        return *this;
    }
    uint_inf<Type> operator|=(const uint_inf<Type> &rvalue){
        register size_t test;
        if(rvalue.value.realSize() > this->value.realSize()){
             test = rvalue.value.realSize();
             this->value[rvalue.size-1] = 0;
        }else{
            test = this->value.realSize();
        }
        for(Type i = 0; i < test; i++){
            this->value[i] |= rvalue.value[i];
        }
        return *this;
    }
    uint_inf<Type> operator&=(const uint_inf<Type> &rvalue){
        register size_t test;
        if(rvalue.value.realSize() > this->value.realSize()){
             test = rvalue.value.realSize();
             this->value[rvalue.size-1] = 0;
        }else{
            test = this->value.realSize();
        }
        for(Type i = 0; i < test; i++){
            this->value[i] &= rvalue.value[i];
        }
        return *this;
    }
    uint_inf<Type> operator^=(const uint_inf<Type> &rvalue){
        register size_t test;
        if(rvalue.value.realSize() > this->value.realSize()){
             test = rvalue.value.realSize();
             this->value[rvalue.size-1] = 0;
        }else{
            test = this->value.realSize();
        }
        for(Type i = 0; i < test; i++){
            this->value[i] ^= rvalue.value[i];
        }
        return *this;
    }
    uint_inf<Type> operator^=(const Type &rvalue){
            this->value[0] ^= rvalue;
    }
    uint_inf<Type> operator&=(const Type &rvalue){
            this->value[0] &= rvalue;
            return *this;
    }
    uint_inf<Type> operator|=(const Type &rvalue){
            this->value[0] |= rvalue;
            return *this;
    }
    uint_inf<Type> operator~(){
        for(Type i = 0; i < this->value.size; i++){
            this->value[i] = ~this->value[i];
        }
        return *this;
    }
    uint_inf<Type> operator^(const Type &rvalue) const {
        uint_inf<Type> ret = *this;
        ret ^= rvalue;
        return ret;
    }
    uint_inf<Type> operator|(const Type &rvalue) const {
        uint_inf<Type> ret = *this;
        ret |= rvalue;
        return ret;
    }
    uint_inf<Type> operator&(const Type &rvalue) const {
        uint_inf<Type> ret = *this;
        ret &= rvalue;
        return ret;
    }
    uint_inf<Type> operator^(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> ret = *this;
        ret ^= rvalue;
        return ret;
    }
    uint_inf<Type> operator|(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> ret = *this;
        ret |= rvalue;
        return ret;
    }
    uint_inf<Type> operator&(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> ret = *this;
        ret &= rvalue;
        return ret;
    }
    uint_inf<Type> operator++(int null){
        for(size_t i = 0;this->value[i]++ == UINT64_MAX;i++);
        return *this;
    }
    uint_inf<Type> operator+=(const Type &rvalue){
        if(eFunc::addOvf(this->value[0],rvalue)){
                for(size_t b = 1;this->value[b]++ == UINT64_MAX;b++);
        }
        return *this;
    }
    uint_inf<Type> addOffset(const Type &rvalue, const size_t &offset){
        if(eFunc::addOvf(this->value[offset],rvalue)){
                for(size_t b = 1+offset;this->value[b]++ == UINT64_MAX;b++);
        }
        return *this;
    }
    uint_inf<Type> addOffset(const Type &rvalue, const size_t &offset) const {
        uint_inf<Type> ret = *this;
        ret.addOffset(rvalue,offset);
        return ret;
    }
    uint_inf<Type> operator+=(const uint_inf<Type> &rvalue){
        for(size_t i = 0;i < this->value.size || i < rvalue.value.size; i++){
            if(eFunc::addOvf(this->value[i],rvalue.value[i])){
                for(size_t b = i+1;this->value[b]++ == UINT64_MAX;b++);
            }
        }
        return *this;
    }
    uint_inf<Type> operator+(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf<Type> operator+(const Type &rvalue) const {
        uint_inf<Type> ret = *this;
        ret += rvalue;
        return ret;
    }
    uint_inf<Type> operator--(int null){
        for(Type i = 0;this->value[i]-- == 0;i++)if(i >= this->value.size-1)break;
        return *this;
    }
    uint_inf<Type> operator-=(const uint_inf<Type> &rvalue){
        for(size_t i = 0;i < this->value.size; i++){
            if(this->value[i] < rvalue.value[i]){
                this->value[i] -= rvalue.value[i];
                for(size_t b = i+1;this->value[b]-- == 0;b++)if(b >= this->value.size-1 &&  b >= rvalue.value.size-1)break;
            }else {
                this->value[i] -= rvalue.value[i];
            }
        }
        return *this;
    }
    uint_inf<Type> subOffset(const Type &rvalue, const size_t &offset){
        if(eFunc::subUnf(this->value[offset],rvalue)){
                for(size_t b = 1+offset;this->value[b]-- == 0;b++)if(b >= this->value.size-1)break;
        }
        return *this;
    }
    uint_inf<Type> subOffset(const Type &rvalue, const size_t &offset) const {
        uint_inf<Type> ret = *this;
        ret.subOffset(rvalue,offset);
        return ret;
    }
    uint_inf<Type> operator-=(const Type &rvalue){
        if(this->value[0] < rvalue){
            this->value[0] -= rvalue;
            for(size_t b = 1;this->value[b]-- == 0;b++)if(b >= this->value.size-1)break;
         }else {
            this->value[0] -= rvalue;
        }
        return *this;
    }
    uint_inf<Type> operator-(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf<Type> operator-(const Type &rvalue) const {
        uint_inf<Type> ret = *this;
        ret -= rvalue;
        return ret;
    }
    uint_inf<Type> operator*(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> out = uint_inf<Type>(0,this->value.realSize()+rvalue.value.realSize()); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        return out;
    }
    uint_inf<Type> operator*(const Type &rvalue) const{
        uint_inf<Type> out = uint_inf<Type>(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        return out;
    }
    uint_inf<Type> operator*=(const Type &rvalue){
        uint_inf<Type> out = uint_inf<Type>(0,this->value.realSize()+1); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue,this->value[i],highWord),i);
                out.addOffset(highWord,i+1);
        }
        *this = out; // slow
        out.del(); 
        return *this;
    }
    uint_inf<Type> operator*=(const uint_inf<Type> &rvalue){
        uint_inf<Type> out = uint_inf<Type>(0,this->value.realSize()+rvalue.value.realSize()); // find size bcuase of overflow it will be larger // is it posible to have it without rvalue new variable 
        for(size_t b = 0;b < rvalue.value.size; b++){
            for(size_t i = 0;i < this->value.size; i++){
                Type highWord;
                out.addOffset(eFunc::mul_bits<Type>(rvalue.value[b],this->value[i],highWord),(b+i));
                out.addOffset(highWord,(b+i)+1);
            }
        }
        *this = out; // slow
        out.del(); 
        return *this;  
    }
    uint_inf<Type> operator/=(const uint_inf<Type> &rvalue){
        uint_inf<Type> remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
        return *this;
    }
    uint_inf<Type> operator/=(const Type &rvalue){
        uint_inf<Type> remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
        return *this;
    }
    uint_inf<Type> operator/(const Type &rvalue) const {
        uint_inf<Type> out = *this;
        out /= rvalue;
        return out;
    }
    uint_inf<Type> operator/(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> out = *this;
        out /= rvalue;
        return out;
    }
    uint_inf<Type> operator%=(const Type &rvalue) {
        uint_inf<Type> remainder = 0;
        for(Type i = value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
        return *this;
    }
    uint_inf<Type> operator%=(const uint_inf<Type> &rvalue) {
        uint_inf<Type> remainder = 0;
        for(Type i = value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
        return *this;
    }
    uint_inf<Type> divideRemainder(const Type &rvalue){
        uint_inf<Type> remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
    uint_inf<Type> divideRemainder(const uint_inf<Type> &rvalue){
        uint_inf<Type> remainder = 0;
        for(Type i = this->value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
    uint_inf<Type> operator%(const uint_inf<Type> &rvalue) const {
        uint_inf<Type> out = *this;
        uint_inf<Type> remainder = 0;
        for(Type i = out.value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
    uint_inf<Type> operator%(const Type &rvalue) const {
        uint_inf<Type> out = *this;
        uint_inf<Type> remainder = 0;
        for(Type i = out.value.size; i-- > 0;){
            for(Type b = Tsize; b-- > 0;){
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
            out << std::bitset<8*sizeof(Type)>(this->value[i]) << ',';
        }
        return out.str();
    }
    std::string toString10() const {
        std::string out;
        uint_inf<Type> div = *this;
        while(div != 0) out.insert(0,std::to_string(div.divideRemainder(10).value[0]));
        return out;
    }
};