#include "uint_inf_bits.cpp"
template <class Type>
class floating_inf {
    uint_fast64_t exponent = 0;
    uint_inf<Type> value = uint_inf<Type>(1,1,1);
    uint_inf<Type> exponenialShift(uint_fast64_t &new_exponent) const { // cant shift more than 64  
        return (new_exponent < this->exponent)?this->value << (new_exponent - this->exponent):this->value;//error becuse we dont want it smaller
    }
    uint_inf<Type> exponenialShift(uint_fast64_t &new_exponent){
        return (new_exponent < this->exponent)?this->value <<= (new_exponent - this->exponent):this->value;//error becuse we dont want it smaller
    }
    bool operator==(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) == rvalue.exponenialShift(this->exponent)
    }
    bool operator!=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) != rvalue.exponenialShift(this->exponent)
    }
    bool operator<=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) <= rvalue.exponenialShift(this->exponent)
    }
    bool operator>=(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) >= rvalue.exponenialShift(this->exponent)
    }
    bool operator<(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) < rvalue.exponenialShift(this->exponent)
    }
    bool operator>(const floating_inf &rvalue)const{
        return this->exponenialShift(rvalue.exponent) > rvalue.exponenialShift(this->exponent)
    }
    void operator+=(const floating_inf &rvalue) {
        this->exponenialShift(rvalue.exponent) += rvalue.exponenialShift(this->exponent);
    }
    void operator-=(const floating_inf &rvalue) {
        this->exponenialShift(rvalue.exponent) -= rvalue.exponenialShift(this->exponent);
    }
    void operator*=(const floating_inf &rvalue) {
        this->value *= rvalue.value;
        this->exponent += rvalue.exponent;
    }



    
};//  % ^ & | ~ ! = < >  %= ^= &= |= << >> >>= <<=  && || ++ --