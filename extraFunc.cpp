#include <iostream>
#include <stdio.h>
#include <mmintrin.h>

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
    uint_fast64_t mulH(const uint_fast64_t &a, const uint_fast64_t &b)  {  
        return (uint_fast64_t)_m_pmulhw ((__m64)a,(__m64)b);
    }
    uint_fast64_t mulL(const uint_fast64_t &a, const uint_fast64_t &b)  {  
        return (uint_fast64_t)_m_pmullw ((__m64)a,(__m64)b);
    }

}