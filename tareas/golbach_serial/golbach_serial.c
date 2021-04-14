#include <stdio.h>
#include <math.h>
int isPrime(int number);
/*
 * This method calculates the serial golbach sums in 
 * even numbers
 */
void golbach(int number);
int main(){
	int n = 8;
	golbach(n);
    return 0;
}
void golbach(int n){
	int typeGolbach = n%2;
	if(typeGolbach == 0){
		//This cicle is for finding the sums of prime numbers
		//Is divided by 2 because beyond that it will repeat the sums in
		//the opposite order
		for(int i=0;i<=n;i++){
			if(isPrime(i)==1 && isPrime(n-i)==1){
				printf("%d = %d + %d\n",n,i,n-i);
			}
		}
	}
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

