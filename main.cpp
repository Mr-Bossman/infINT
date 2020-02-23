
#include <iostream>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <String>
#include "uint_inf.cpp"
#include <fstream>
//#include "InfInt.h"
#include <assert.h>

//#include "extraFunc.cpp"


template <class Type>
int aksPrime(uint_inf &P){
    uint_inf b=P,columb=2,out=P,loops = (P>>1)+1;
    int checks = 0;
    while(columb<loops && checks < 100){
        b--;
        std::cout <<'.  ';
        out *= b;
        std::cout <<'.. ';
        out /= columb;
        std::cout <<'...';
        columb++;
        uint_inf check = (out%P);
        std::cout <<"\r\rIt's taken " << checks << " checks so far. There are " << out.realSize() << " Qwords in the variable. Testing";
        if(check != 0) return checks;
        checks++;
    }
    return -1;
}
int main() {
    std::ofstream file1,file2;
    file1.open ("out.txt");
    file2.open ("primes.txt");
    int size = 100; 
    //start at num with the first digit 5 ever power of 16^x - 1 will end in 5 i think

    uint8_t fives = 0;
    uint_inf primes = uint_inf(UINT64_MAX ,2);
    //for(int i = 100; i > 1; i--)primes *= i;
    for(int i = 1; i < size; i++)primes.value[i] = UINT64_MAX;
    while(true){
        if(fives == 5)primes += 2,fives = 1; 
        int checks = aksPrime<uint_inf>(primes);
        if(checks == -1){
            std::string prime = primes.toString10();
            std::cout  << '\r' << prime << " has a high chance it's a prime number!!!                                                          "<< std::endl;
            file2 << prime << std::endl;
        } else {
            std::cout  << '\r' <<"It took " << checks << " checks to find out it's not a prime number                                  " << std::endl;
            file1 << checks << std::endl;
        }
        primes += 2,fives++;
    }
    file1.close();
    file2.close();
    do {
        std::cout << '\n' << "Press enter to continue...";
    } while (std::cin.get() != '\n');
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