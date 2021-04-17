
// Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
/** @struct Node
 *  @brief This structure is for a node, used later to build a linked list
 */
struct Node {
    int32_t data;
    struct Node* next;
};
/**
 * @brief Adds a node at the end of the list
 * @param head_ref Reference to the head of the list
 * @param new_data The new data to be added
 */
void append(struct Node** head_ref, int32_t new_data);
/**
 * @brief Free the memory that is used for the list
 * @param node Head of the list to free the memory
 */
void freeList(struct Node *node);
/**
 * @brief Prints a simple linked list
 * @param n the node to start printing
 */
void printList(struct Node* n);
/**
 * @brief Makes sure a number is prime
 * @param number The number to be checked
 * @return 1 if is prime, 0 if it isnt
 */
int isPrime(int32_t number);
/**
 * @brief Does the golbach procedure for weak and strong conjectures
 * @param number The number to find the sums
 * @param node Node to create a simple linked list with the sums
 * @param numberSums Stores how many sums are made in the process
 */
void golbach(int32_t number, struct Node *node, int32_t *numberSums);
/**
 * @brief Prints the golbach sums of the strong conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param number The number that was used to find the sums
 * @param flag store if a number is negative
 */
void printGolbachStrong(struct Node *node, int32_t *numberSums, int32_t number, int32_t flag);
/**
 * @brief Prints the golbach sums of the weak conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param number The number that was used to find the sums
 * @param flag store if a number is negative
 */
void printGolbachWeak(struct Node *node, int32_t *numberSums, int32_t number, int32_t flag);
/**
 * @brief Checks if a number is negative
 * @param number The number to be checked
 * @return 1 if the number is negative and 0 if not
 */
int32_t isNegative(int32_t number);

int main() {
    struct Node* head = NULL;
    FILE* input = stdin;
    int32_t number = 0;
	while(fscanf(input, "%" SCNu32, &number) == 1) {
		if(number <= 5 && number >= -5){
			printf("%" PRId32 ": NA\n",number);
		}else {
			int32_t numberSums=0;
			int32_t *ptrNumberSums = &numberSums;
			golbach(number,head,ptrNumberSums);
		}
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
void printGolbachWeak(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag){
    if(flag==1){
		printf("%" PRId32 ": %" PRIu32 " summs: ",number,*numberSums);
        for(int32_t i=0;i<(*(numberSums)*2);i+=2){
            while (node != NULL) {
                printf("%" PRIu32 " + ",node->data);
                node = node->next;
                printf("%" PRIu32 " + ",node->data);
                node = node->next;
                if(node->next != NULL){
					printf("%" PRIu32 " , ",node->data);
					node = node->next;
				}else{
					printf("%" PRIu32 ,node->data);
					node = node->next;
				}
            }
            
        }
    }else{
		printf("%" PRId32 ": %" PRIu32 " summs",number,*numberSums);
    }
    printf("\n");
}
void printGolbachStrong(struct Node *node,int32_t *numberSums,int32_t number,int32_t flag){
    if(flag==1){
		printf("%" PRId32 ": %" PRIu32 " summs: ",number,*numberSums);
        for(int32_t i=0;i<*(numberSums)*2;i+=2){
            while (node != NULL) {
                printf("%" PRIu32 " + ",node->data);
                node = node->next;
                if(node->next != NULL){
					printf("%" PRIu32 " , ",node->data);
					node = node->next;
				}else{
					printf("%" PRIu32 ,node->data);
					node = node->next;
				}
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
		printGolbachStrong(head, numberSums, number,flag);
		freeList(head);
	}else{
	    int32_t  flagWeak, count=0, *primes;
	    //Here a list of prime numbers before the number for golbach is created
        primes = (int32_t *) malloc (sizeof(int32_t)*numberCopy/2);
        for(int32_t i = 2; i < numberCopy; ++i) {
            flagWeak = isPrime(i);
            if(flagWeak == 1){
                primes[count] = i;
                count = count+1;
            }
        }
        //Does 3 cicles to check if the sums of them are equal to the number
        for (int32_t i = 0; i < count; i++){
            for (int32_t j = i; j < count; j++){
                for (int32_t k = j; k < count; k++){
                    if (primes[i] + primes[j] + primes[k] == numberCopy){
                        //Appends the primes to the list to be printed later
                        append(&head,primes[i]);
				        append(&head,primes[j]);
				        append(&head,primes[k]);
				        *numberSums+=1;
                    }
                }
            }
        }
        printGolbachWeak(head, numberSums, number,flag);
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
void append(struct Node** head_ref, int32_t new_data){
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
