#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int isPrime(int number);
/*
 * This method calculates the serial golbach sums in 
 * even numbers
 */
void golbach(int number,int* array,int *numberSums);
int numberItemsArray(int n);
void printGolbach1(int *array,int numberSums,int number,int itemsArray);
void printGolbach2(int numberSums,int number);
int isNegative(int number);

int main(){
    int number =-70;
    int flag = isNegative(number);
    number = abs(number);
    int numberSums=0;
    int *ptrNumberSums = &numberSums;
    int itemsArray = numberItemsArray(number);
    int *array =(int*)malloc(itemsArray * sizeof(int*));
    golbach(number,array,ptrNumberSums);
    if(flag == 1){
        printGolbach1(array,numberSums,number,itemsArray);    
	}else{
        printGolbach2(numberSums,number);
	}
    return 0;
}
int isNegative(int number){
    if(number<0){
        return 1;
    }
    return 0;
}
void printGolbach2(int numberSums,int number){
     printf("%d: %d summs\n",number,numberSums);
}
void printGolbach1(int *array,int numberSums,int number,int itemsArray){
    printf("%d: %d summs: ",number,numberSums);
    for(int i=0;i<itemsArray*2;i+=2){
		printf("%d + %d,",array[i],array[i+1]);
    }
    printf("\n");
}
void golbach(int n,int *array,int *numberSums){
    int arrayAux = 0;
	int typeGolbach = n%2;
	if(typeGolbach == 0){
		//This cicle is for finding the sums of prime numbers
		//Is divided by 2 because beyond that it will repeat the sums in
		//the opposite order
		for(int i=2;i<=n/2;i++){
			if(isPrime(i)==1 && isPrime(n-i)==1){
				array[arrayAux] = i;
				array[arrayAux+1] = n-i;
				arrayAux+=2;
				*numberSums+=1;
			}
		}
	}
}
int isPrime(int number){
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
int numberItemsArray(int n){
    int items = 0;
    for(int i=2;i<=n/2;i++){
		if(isPrime(i)==1 && isPrime(n-i)==1){
			items++;
		}	
	}
	return items;
}
