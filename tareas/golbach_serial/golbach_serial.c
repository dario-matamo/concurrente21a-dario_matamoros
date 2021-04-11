#include <stdio.h>
#include <math.h>
int isPrime(int number);

int main(){
    for(int i=0; i<100;i++){
		if(isPrime(i)==0){
			printf("%d is not prime\n",i);
		}else{
			printf("%d is prime\n",i);
		}
	}
    return 0;
}
int isPrime(int number){
	int flag = 0;
	if(number > 0){
		int sqrRootNumber = sqrt(number);
		for(int i=2; i<=sqrRootNumber;i++){
			if(number % i == 0){
				return 0;
			}
		}
	}
	return 1;
}
