// Copyright 2021 Dario Matamoros Vega <dario.matamoros@ucr.ac.cr>
// Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
/** @struct Node
 *  @brief This structure is for a node, used later to build a linked list
 */
 // Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
struct Node {
    int64_t data;
    struct Node* next;
};
/**
 * @brief Adds a node at the end of the list
 * @param head_ref Reference to the head of the list
 * @param new_data The new data to be added
 */
 // Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
void append(struct Node** head_ref, int64_t new_data);
/**
 * @brief Free the memory that is used for the list
 * @param node Head of the list to free the memory
 */
 // Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
void freeList(struct Node *node);
/**
 * @brief Prints a simple linked list
 * @param n the node to start printing
 */
size_t isPrime(int64_t number);
/**
 * @brief Does the golbach procedure for weak and strong conjectures
 * @param number The number to find the sums
 * @param node Node to create a simple linked list with the sums
 * @param numberSums Stores how many sums are made in the process
 */
void golbach(int64_t number, struct Node *node, size_t *numberSums);
/**
 * @brief Prints the golbach sums of the strong conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param number The number that was used to find the sums
 * @param flag store if a number is negative
 */
void printGolbachStrong(struct Node *node, size_t *numberSums, int64_t number
, size_t flagNegative);
/**
 * @brief Prints the golbach sums of the weak conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param number The number that was used to find the sums
 * @param flag store if a number is negative
 */
void printGolbachWeak(struct Node *node, size_t *numberSums, int64_t number
, size_t flagNegative);
/**
 * @brief Checks if a number is negative
 * @param number The number to be checked
 * @return 1 if the number is negative and 0 if not
 */
size_t isNegative(int64_t number);
/**
 * @brief Does the golbach sums of the weak conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param numberCopy The number that was used to find the sums
 * @param flagNegative store if 1 if a number is negative
 */
void golbach_weak_conjecture(int64_t number, struct Node *node, size_t *numberSums
,int64_t numberCopy,size_t flagNegative);
/**
 * @brief Does the golbach sums of the strong conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param numberCopy The number that was used to find the sums
 * @param flagNegative store if 1 if a number is negative
 */
void golbach_strong_conjecture(int64_t number, struct Node *node, size_t *numberSums
,int64_t numberCopy, size_t flagNegative);

int main() {
    struct Node* head = NULL;
    FILE* input = stdin;
    int64_t number = 0;
    // If the number is less than 5 or greater than 5
    // just print the numb without sums 
    while (fscanf(input, "%" SCNu64, &number) == 1) {
        if (number <= 5 && number >= -5) {
            printf("%" PRId64 ": NA\n", number);
        } else {
            size_t numberSums = 0;
            size_t *ptrNumberSums = &numberSums;
            golbach(number, head, ptrNumberSums);
        }
    }
    return 0;
}
void freeList(struct Node* head) {
    struct Node* aux;
    while (head != NULL) {
       aux = head;
       head = head->next;
       free(aux);
    }
}
size_t isNegative(int64_t number) {
	size_t flag = 0;
    if (number < 0) {
        flag = 1;
    }
    return flag;
}

void printGolbachWeak(struct Node *node, size_t *numberSums, int64_t number, size_t flagNegative) {
	// If the number is negative prints all the sums
    if (flagNegative == 1) {
        printf("%" PRId64 ": %zu sums: ", number, *numberSums);
        for (size_t i=0; i < (*(numberSums)*2); i+=2) {
            while (node != NULL) {
                printf("%" PRId64 " + ", node->data);
                node = node->next;
                printf("%" PRId64 " + ", node->data);
                node = node->next;
                if (node->next != NULL) {
                    printf("%" PRId64 ", ", node->data);
                    node = node->next;
                } else {
                    printf("%" PRId64 , node->data);
                    node = node->next;
                }
            }
        }
    } else {
		// If it isnt negative prints just the number of sums
        printf("%" PRIu64 ": %zu sums", number, *numberSums);
    }
    printf("\n");
}
void printGolbachStrong(struct Node *node, size_t *numberSums, int64_t number, size_t flagNegative) {
     if (flagNegative == 1) {
		// If the number is negative prints all the sums
        printf("%" PRId64 ": %zu sums: ", number, *numberSums);
        for (size_t i=0; i < *(numberSums)*2; i+=2) {
            while (node != NULL) {
                printf("%" PRId64 " + ", node->data);
                node = node->next;
                if (node->next != NULL) {
                    printf("%" PRId64 ", ", node->data);
                    node = node->next;
                } else {
                    printf("%" PRId64 , node->data);
                    node = node->next;
                }
            }
        }
    } else {
		// If it isnt negative prints just the number of sums
        printf("%" PRId64 ": %zu sums", number, *numberSums);
    }
    printf("\n");
}
void golbach_weak_conjecture(int64_t number, struct Node *head, size_t *numberSums
, int64_t numberCopy, size_t flagNegative) {
        // Does 3 cicles to check if the sums of them are equal to the number
        for (int64_t i = 0; i < numberCopy; i++) {
            for (int64_t j = i; j < numberCopy; j++) {
                for (int64_t k = j; k < numberCopy; k++) {
                    // Checks if the sum of the 3 iterations equals the number
                    if (i + j + k == numberCopy ) {
                        // Appends the primes to the list to be printed later
                        if(isPrime(i)==1 && isPrime(j)==1 &&
                             isPrime(k)==1){
                             append(&head, i);
                             append(&head, j);
                             append(&head, k);
                             *numberSums+=1;
                    }
                }
            }
        }
       }
        // Sends the linked list to print and then frees it
        printGolbachWeak(head, numberSums, number, flagNegative);
        freeList(head);
    }
void golbach_strong_conjecture(int64_t number, struct Node *head, size_t *numberSums
,int64_t numberCopy,size_t flagNegative) {
     // This cicle is for finding the sums of prime numbers
     // Is divided by 2 because beyond that it will repeat the sums in
     // the opposite order
     for (int64_t i=2; i <= numberCopy/2; i++) {
        if (isPrime(i) == 1 && isPrime(numberCopy-i) == 1) {
           append(&head, i);
           append(&head, numberCopy-i);
           *numberSums+=1;
        }
     }
     // Sends the linked list to print and then frees it
     printGolbachStrong(head, numberSums, number, flagNegative);
     freeList(head);
}
void golbach(int64_t number, struct Node *head, size_t *numberSums) {
    int64_t numberCopy = labs(number);
    // If golbach is 0 is because the number is odd number and then does 
    // strong conjecture if it is 1 the number is even an does weak conjecture
    size_t typeGolbach = number%2;
    size_t flagNegative = isNegative(number);
    if (typeGolbach == 0) {
        golbach_strong_conjecture(number,head,numberSums,numberCopy,flagNegative);
    } else {
		golbach_weak_conjecture(number,head,numberSums,numberCopy,flagNegative); 
    }
}

size_t isPrime(int64_t number) {
	// The variable prime returns 0 if it isnt prime and 1 if is prime
    size_t prime = 1;
    if (number <= 1) {
		prime = 0;
    } else {
        for (int64_t i=2; i<=sqrt(number); i++) {
             if (number % i == 0) {
			     prime = 0;
             }
        }
    }
    return prime;
}
void append(struct Node** head_ref, int64_t new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    if(new_node == NULL) {
		    printf("Memory allocation failed");
            return;
    } else {
            struct Node *last = *head_ref;
            new_node->data  = new_data;
            new_node->next = NULL;
            if (*head_ref == NULL) {
                 *head_ref = new_node;
                 return;
            }
            while (last->next != NULL) {
            last = last->next;
            }
            last->next = new_node;
    }
    return;
}
