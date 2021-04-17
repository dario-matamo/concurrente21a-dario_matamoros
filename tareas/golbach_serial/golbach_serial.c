// A simple C program for traversal of a linked list
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
struct Node {
    int32_t data;
    struct Node* next;
};
void append(struct Node** head_ref, int new_data);

void freeList(struct Node *node);

void printList(struct Node* n);

int isPrime(int32_t number);

void golbach(int32_t number,struct Node *node,int32_t *numberSums);

void printGolbach1(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag);

void printGolbach2(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag);

int32_t isNegative(int32_t number);

int32_t prime_finder(int32_t target, int32_t *prime_list); 

  
int main(){
    struct Node* head = NULL;
    FILE* input = stdin;
    FILE* output = stdout;
    int32_t number = 0;
	while(fscanf(input,"%" SCNu32,&number)==1){
		int32_t numberSums=0;
		int32_t *ptrNumberSums = &numberSums;
		golbach(number,head,ptrNumberSums);
	}
    return 0;
}
void freeList(struct Node* head){
   struct Node* aux;
   while (head != NULL){
       aux = head;
       head = head->next;
       free(aux);
    }

}
int32_t isNegative(int32_t number){
    if(number<0){
        return 1;
    }
    return 0;
}
void printGolbach2(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag){
    if(flag==1){
		printf("%" PRId32 ": %" PRIu32 " summs: ",number,*numberSums);
        for(int32_t i=0;i<=*(numberSums)*2;i+=2){
            while (node != NULL) {
                printf("%" PRIu32 " + ",node->data);
                node = node->next;
                printf(" %" PRIu32 " + ",node->data);
                node = node->next;
                printf("%" PRIu32 " , ",node->data);
                node = node->next;
            }
        }
    }else{
		printf("%" PRId32 ": %" PRIu32 " summs",number,*numberSums);
    }
    printf("\n");
}
void printGolbach1(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag){
    if(flag==1){
		printf("%" PRId32 ": %" PRIu32 " summs: ",number,*numberSums);
        for(int32_t i=0;i<=*(numberSums)*2;i+=2){
            while (node != NULL) {
                printf("%" PRIu32 " + ",node->data);
                node = node->next;
                printf("%" PRIu32 " , ",node->data);
                node = node->next;
            }
        }
    }else{
		printf("%" PRId32 ": %" PRIu32 " summs",number,*numberSums);
    }
    printf("\n");
}

void golbach(int32_t number,struct Node *head,int32_t *numberSums){
	int32_t numberCopy = abs(number);
	int typeGolbach = number%2;
	int32_t flag = isNegative(number);
	if(typeGolbach == 0){
		//This cicle is for finding the sums of prime numbers
		//Is divided by 2 because beyond that it will repeat the sums in
		//the opposite order
		for(int32_t i=2;i<=numberCopy/2;i++){
			if(isPrime(i)==1 && isPrime(numberCopy-i)==1){
			    append(&head,i);
				append(&head,numberCopy-i);
				*numberSums+=1;
			}
		}
		printGolbach1(head, numberSums, number,flag);
		freeList(head);
	}else{
	    int32_t  flagWeak, count=0, *primes;
        primes = (int32_t *) malloc (sizeof(int32_t)*numberCopy/2);
        for(int32_t i = 2; i < numberCopy; ++i) {
            flagWeak = isPrime(i);
            if(flagWeak == 1){
                primes[count] = i;
                count = count+1;
            }
        }
        for (int32_t i = 0; i < count; i++){
            for (int32_t j = i; j < count; j++){
                for (int32_t k = j; k < count; k++){
                    if (primes[i] + primes[j] + primes[k] == numberCopy){
                        append(&head,primes[i]);
				        append(&head,primes[j]);
				        append(&head,primes[k]);
				        *numberSums+=1;
                    }
                }
            }
        }
        printGolbach2(head, numberSums, number,flag);
		freeList(head);
		free(primes);
    }	    
}

int32_t isPrime(int32_t number){
	if(number > 0){
		int32_t sqrRootNumber = sqrt(number);
		for(int32_t i=2; i<=sqrRootNumber;i++){
			if(number % i == 0){
				return 0;
			}
		}
	}
	return 1;
}
void append(struct Node** head_ref, int new_data){
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *head_ref;  
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL){
       *head_ref = new_node;
       return;
    }
    while (last->next != NULL){
        last = last->next;
	}
    last->next = new_node;
    return;
}
void printList(struct Node* n){
    while (n != NULL) {
		printf("%" PRIu32 ,n->data);
       
        n = n->next;
    }
}
