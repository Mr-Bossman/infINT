#include "uint_inf_bits.cpp"
template <class Type>
class floating_inf {
    /*
    add size 
    add all adds from uint_inf
    add double too 
    add functions with doubles
    test!!!
    */
    uint_fast64_t exponent = 0;
    uint_inf<Type> value = uint_inf<Type>(1,1,1);
    uint_inf<Type> exponenialShift(uint_fast64_t &new_exponent) const { // cant shift more than 64  // also mabey needs to be faster
        return (new_exponent < this->exponent)?this->value << (new_exponent - this->exponent):this->value;//same becuse we dont want it smaller
    }
    uint_inf<Type> exponenialShift(uint_fast64_t &new_exponent){// cant shift more than 64
        return (new_exponent < this->exponent)?this->value <<= (new_exponent - this->exponent):this->value;//same becuse we dont want it smaller
    }
    bool operator==(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) == rvalue.exponenialShift(this->exponent);
    }
    bool operator!=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) != rvalue.exponenialShift(this->exponent);
    }
    bool operator<=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) <= rvalue.exponenialShift(this->exponent);
    }
    bool operator>=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) >= rvalue.exponenialShift(this->exponent);
    }
    bool operator<(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) < rvalue.exponenialShift(this->exponent);
    }
    bool operator>(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) > rvalue.exponenialShift(this->exponent);
    }
    void operator+=(const floating_inf &rvalue) {
        this->exponenialShift(rvalue.exponent) += rvalue.exponenialShift(this->exponent);
    }
    floating_inf operator+(const floating_inf &rvalue) {
        floating_inf ret = *this;
        return ret += rvalue;
    }
    void operator++() {
        uint_fast64_t offset;
        Type one = 1 << eFunc::div_rq(this->exponent,sizeof(Type),offset);
        this->value.addOffset(one,offset);
    }
    void operator-=(const floating_inf &rvalue) {
        this->exponenialShift(rvalue.exponent) -= rvalue.exponenialShift(this->exponent);
    }
    floating_inf operator-(const floating_inf &rvalue) {
        floating_inf ret = *this;
        return ret -= rvalue;
    }
    void operator--() {
        uint_fast64_t offset;
        Type one = 1 << eFunc::div_rq(this->exponent,sizeof(Type),offset);
        this->value.subOffset(one,offset);
    }
    void operator*=(const floating_inf &rvalue) {
        this->value *= rvalue.value;
        this->exponent += rvalue.exponent;
    }
    floating_inf operator*(const floating_inf &rvalue) {
        floating_inf ret = *this;
        return ret *= rvalue;
    }
    void operator<<=(const floating_inf &rvalue) {
        this.value <<= rvalue;
    }
    void operator>>=(const floating_inf &rvalue) {
        this.value >>= rvalue;
    }
    floating_inf operator>>(const floating_inf &rvalue) {
        return this.value >> rvalue;
    }
    floating_inf operator<<(const floating_inf &rvalue) {
        return this.value << rvalue;
    }
    floating_inf operator^(const floating_inf &rvalue) {
        return this.value ^ rvalue;
    }
    floating_inf operator&(const floating_inf &rvalue) {
        return this.value & rvalue;
    }
    floating_inf operator|(const floating_inf &rvalue) {
        return this.value | rvalue;
    }
    void operator^=(const floating_inf &rvalue) {
        this.value ^= rvalue;
    }
    void operator&=(const floating_inf &rvalue) {
        this.value &= rvalue;
    }
    void operator|=(const floating_inf &rvalue) {
        this.value |= rvalue;
    }
    floating_inf operator~() {
        return ~this.value;
    }





    
};// / /= %   %=   ++ --