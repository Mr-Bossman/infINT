
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <String>
#include "uint_inf.cpp"
//#include "InfInt.h"
#include <assert.h>

//#include "extraFunc.cpp"


template <class Type>
int aksPrime(Type &P){
    Type b=P,columb=2,out=P;
    int checks = 0; 
    while(columb<((P>>1)+1)){
        b--;
        std::cout <<'.' << std::endl;
        out *= b;
        std::cout <<'.' << std::endl;
        out /= columb;
        std::cout <<'.' << std::endl;
        columb++;
        if((out%P) != 0) return checks;
        std::cout <<"It took " << checks << " checks so far. There are " << out.realSize() << " Qwords in the variable." << std::endl;
        checks++;
    }
    return -1;
}
int main() {
    for(uint_inf primes = 67280421310717;primes < UINT_FAST64_MAX; primes += 2){
        int checks = aksPrime<uint_inf>(primes);
        if(checks == -1){
            std::cout << primes.value[0] << " is a prime number!!!" << std::endl;
        } else {
            std::cout <<"It took " << checks << "checks to find out " << primes.value[0] << " is not a prime number" << std::endl;
        }
    }

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