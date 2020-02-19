
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <String>
#include "infINT.cpp"
//#include "InfInt.h"
#include <assert.h>

//#include "extraFunc.cpp"

#include <immintrin.h>

template <class Type>
int aksPrime(Type P){
    Type b=P,a=2,out=P;
    int checks = 0; 
    while(a<(P/2)+1){
        b--;
        out*=b;
        out/=a++;
        if((out%P) != 0)return checks;
        checks++;
    }
    return -1;
}
int main() {
    uint64_t a = UINT64_MAX;
    uint64_t b = UINT64_MAX;

    //for (int i = a.value.size-1; i >= 0 ;i--)std::cout << std::bitset<64>(a.value[i]) << ',';
    //std::cout << std::endl;
    //infINT c = a * b;
    //for (int i = c.value.size-1; i >= 0 ;i--)std::cout << std::bitset<64>(c.value[i]) << ',';
    std::cout <<  std::bitset<64>(eFunc::mulH(a,b)) << std::bitset<64>(eFunc::mulL(a,b));
    /*do {
        std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');*/
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