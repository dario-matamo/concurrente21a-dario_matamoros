#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int isPrime(int number);
/*
 * This method calculates the serial golbach sums in 
 * even numbers
 */
void golbach(int number,int *numberSums,int itemsArray,int flag);
int numberItemsArray(int n);
void printGolbach1(int *array,int *numberSums,int number);
void printGolbach2(int *array,int *numberSums,int number);
int isNegative(int number);
int prime_finder(int target, int *prime_list);

int main(){
	for(int i=0;i<10;i++){
		int number = 21;
        scanf("%d",&number);
        int flag = isNegative(number);
        number = abs(number);
        int numberSums=0;
        int *ptrNumberSums = &numberSums;
        int itemsArray = numberItemsArray(number);
        golbach(number,ptrNumberSums,itemsArray,flag);
    }  
    return 0;
}
int isNegative(int number){
    if(number<0){
        return 1;
    }
    return 0;
}
void printGolbach2(int *array,int *numberSums,int number){
    printf("%d: %d summs: ",number,*numberSums);
    for(int i=0;i<*(numberSums)*3;i+=3){
		printf("%d + %d + %d,",array[i],array[i+1],array[i+2]);
    }
    printf("\n");
}
void printGolbach1(int *array,int *numberSums,int number){
    printf("%d: %d summs: ",number,*numberSums);
    for(int i=0;i<*(numberSums)*2;i+=2){
		printf("%d + %d, ",array[i],array[i+1]);
    }
    printf("\n");
}
int prime_finder(int target, int *prime_list){
    *prime_list = 2;
    int i = 1;
    int check = 3;
    while(1){
        for (int j = 0; j < i; j++){
            if (!(check % *(prime_list + j))){
                break;
            }
            else if (j == i - 1){
                *(prime_list + i) = check;
                i++;
            }
        }
        if (check == target - 4){
            break;
        }
        check++;
    }
    return i;
}
void golbach(int number,int *numberSums,int itemsArray,int flag){
    int arrayAux = 0;
	int typeGolbach = number%2;
	if(typeGolbach == 0){
		int *array =(int*)malloc(itemsArray * sizeof(int*));
		//This cicle is for finding the sums of prime numbers
		//Is divided by 2 because beyond that it will repeat the sums in
		//the opposite order
		for(int i=2;i<=number/2;i++){
			if(isPrime(i)==1 && isPrime(number-i)==1){
				array[arrayAux] = i;
				array[arrayAux+1] = number-i;
				arrayAux+=2;
				*numberSums+=1;
			}
		}
		printGolbach1(array,numberSums,number);
		free(array);
	}else{

		int *prime_list = malloc(sizeof(int) * number/2);
		int *arrayPairs = malloc(sizeof(int) * number);
		int num_primes = prime_finder(number, prime_list);
		for (int i = 0; i < num_primes; i++){
			for (int j = i; j < num_primes; j++){
				for (int k = j; k < num_primes; k++){
					if (*(prime_list + i) + *(prime_list + j) + *(prime_list + k) == number){
						arrayPairs[arrayAux] =*(prime_list + i);
						arrayPairs[arrayAux+1] =*(prime_list + j);
						arrayPairs[arrayAux+2] =*(prime_list + k);
						arrayAux += 3;
						*numberSums+=1;
						//printf("%d = %d + %d + %d\n", number, *(prime_list + i), *(prime_list + j), *(prime_list + k));
					}
				}
			}
		}
			printGolbach2(arrayPairs,numberSums,number);
			free(prime_list);
			free(arrayPairs);
		
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
