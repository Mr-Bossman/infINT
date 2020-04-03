
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
void pascal(const Type &P){
    Type b=P, out = P;
    std::cout << "1 " << P.toString10() << ' ';
    uint_fast64_t columbs = 2;
    while(out>1){
        b--;
        out *= b;
        out /= columbs;
        columbs++;
        std::cout << out.toString10()<< ' ';
    }
    std::cout << std::endl << std::endl;
}
int main() {
    pascal<uint_inf<uint_fast64_t>>(UINT64_MAX);
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