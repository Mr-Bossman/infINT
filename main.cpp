
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <String>
#include "uint_inf_bits.cpp"
#include <fstream>
//#include "InfInt.h"
#include <assert.h>

//#include "extraFunc.cpp"


template <class Type>
int aksPrime(Type &P){
    Type b=P,columb=2,out=P;//,loops = (P>>1)+1;
    int checks = 0;
    while(checks < 500){ //columb<loops && 
        uint64_t size = out.realSize();
        b--;
        out *= b;
        std::cout <<"\r\rIt's taken " << checks << " checks so far. There are " << size << " Qwords in the variable. Testing.  ";
        out /= columb;
        std::cout <<"\r\rIt's taken " << checks << " checks so far. There are " << size << " Qwords in the variable. Testing.. ";
        columb++;
        Type check = (out%P);
        std::cout <<"\r\rIt's taken " << checks << " checks so far. There are " << size << " Qwords in the variable. Testing...";
        if(check != 0) return checks;
        std::cout <<"\r\rIt's taken " << checks << " checks so far. There are " << size << " Qwords in the variable. Testing   ";
        checks++;
    }
    return -1;
}
int main() {
    //start at num with the first digit 5 ever power of 16^x - 1 will end in 5 

    uint_inf<uint_fast64_t> primes = uint_inf<uint_fast64_t>(UINT64_MAX);
    primes.value[1] = UINT64_MAX;
    std::cout << (primes%7).toString10() << " " << primes.toString10();

}

//    for (int n=1;n<60;n++){uint64_t b=n,out=n,a=2;printf("\n1 %d ",n);while(out>1)b--,out*=b,out/=a++,printf("%d ",out);}




/*    for (int n=1;n<60;n++){
        uint64_t b=n,out=n,a=2;
        printf("\n1 %u ",n);
        while(out>1){
            b--;
            out*=b;
            out/=a++;
            printf("%lllu ",out);
        }
    }*/

/*int main(){
    int x[30],y[30],*a=x,*b=y,*c;
    for(int n=0;n<30;n++){
        b[n]=b[0]=1;
        for(int i=1;i<n;i++){
            b[i]=a[i]+a[i-1];
            printf("%d ",b[i]);
        }
        printf("1\n1 ");
        c=a;
        a=b;
        b=c;
        }
    }*/