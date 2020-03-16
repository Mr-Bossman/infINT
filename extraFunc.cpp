#include <iostream>
#include <stdio.h>
#include <mmintrin.h>
#include <intrin.h>
#include <immintrin.h>

#pragma intrinsic(_umul128)
namespace eFunc
{
    bool addOvf(uint_fast64_t &a,const uint_fast64_t &b)  { 
        bool ret = (a > ~b);
        a+=b;
        return ret;
    }
    bool addOvf(const uint_fast64_t &a,const uint_fast64_t &b,uint_fast64_t &sum)  { 
        bool ret = (a > ~b);
        sum = a + b;
        return ret;
    }
    bool subUnf(uint_fast64_t &a,const uint_fast64_t &b)  { 
        bool ret = (a > b);
        a -= b;
        return ret;
    }
    bool subUnf(const uint_fast64_t &a,const uint_fast64_t &b,uint_fast64_t &dif)  { 
        bool ret = (a > b);
        dif = a - b;
        return ret;
    }
    uint_fast64_t mul128(const uint_fast64_t &Multiplicand, const uint_fast64_t &Multiplier,uint_fast64_t &HighProduct)  {  
        return _umul128(Multiplier, Multiplicand, &HighProduct);
    }
    uint_fast64_t div_rq(const uint_fast64_t &Dividend, const uint_fast64_t &Divisor,uint_fast64_t &Quotient)  {  
        Quotient = Dividend/Divisor;
        return Dividend%Divisor;
    }
    uint_fast64_t div_qr(const uint_fast64_t &Dividend, const uint_fast64_t &Divisor,uint_fast64_t &Remainder)  {
        Remainder = Dividend%Divisor;
        return Dividend/Divisor;
    }
    template <class Type>
    Type mul_bits(const Type &Multiplicand, const Type &Multiplier,Type &HighProduct)  {  
        return _umul128(Multiplier, Multiplicand, &HighProduct);
    }
    class newTypes {
        

    };
    /*extern __inline void
    __attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
    _mm256_add_256 (__m256i_u __A, __m256i_u __B,__m256i_u &__sum)
    {
        __sum = (__m256i_u) (__A + __B);
    }*/

}