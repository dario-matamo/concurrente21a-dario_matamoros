// Copyright 2021 Dario Matamoros Vega <dario.matamoros@ucr.ac.cr>
// Code of the simple linked list adapted from https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
/** @struct Node
 *  @brief This structure is for a node, used later to build a linked list
 */
struct Node {
    int64_t data;
    struct Node* next;
};
/**
 * @brief Adds a node at the end of the list
 * @param head_ref Reference to the head of the list
 * @param new_data The new data to be added
 */
void append(struct Node** head_ref, int64_t new_data);
/**
 * @brief Free the memory that is used for the list
 * @param node Head of the list to free the memory
 */
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
void printGolbachStrong(struct Node *node, size_t *numberSums, int64_t number, size_t flag);
/**
 * @brief Prints the golbach sums of the weak conjecture
 * @param node Node to create a simple linked list with the sums
 * @param numberSums has the number of sums made in golbach
 * @param number The number that was used to find the sums
 * @param flag store if a number is negative
 */
void printGolbachWeak(struct Node *node, size_t *numberSums, int64_t number, size_t flag);
/**
 * @brief Checks if a number is negative
 * @param number The number to be checked
 * @return 1 if the number is negative and 0 if not
 */
size_t isNegative(int64_t number);

void golbach_weak_conjecture(int64_t number, struct Node *node, size_t *numberSums
,int64_t numberCopy,size_t flag);

void golbach_strong_conjecture(int64_t number, struct Node *node, size_t *numberSums
,int64_t numberCopy, size_t flag);

int main() {
    struct Node* head = NULL;
    FILE* input = stdin;
    int64_t number = 0;
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
    if (number < 0) {
        return 1;
    }
    return 0;
}

void printGolbachWeak(struct Node *node, size_t *numberSums, int64_t number, size_t flag) {
    if (flag == 1) {
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
        printf("%" PRIu64 ": %zu sums", number, *numberSums);
    }
    printf("\n");
}
void printGolbachStrong(struct Node *node, size_t *numberSums, int64_t number, size_t flag) {
     if (flag == 1) {
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
        printf("%" PRId64 ": %zu sums", number, *numberSums);
    }
    printf("\n");
}
void golbach_weak_conjecture(int64_t number, struct Node *head, size_t *numberSums
, int64_t numberCopy, size_t flag) {
        // Does 3 cicles to check if the sums of them are equal to the number
        for (int64_t i = 0; i < numberCopy; i++) {
            for (int64_t j = i; j < numberCopy; j++) {
                for (int64_t k = j; k < numberCopy; k++) {
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
        printGolbachWeak(head, numberSums, number, flag);
        freeList(head);
    }
void golbach_strong_conjecture(int64_t number, struct Node *head, size_t *numberSums
,int64_t numberCopy,size_t flag) {
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
     printGolbachStrong(head, numberSums, number, flag);
     freeList(head);
}
void golbach(int64_t number, struct Node *head, size_t *numberSums) {
    int64_t numberCopy = labs(number);
    size_t typeGolbach = number%2;
    size_t flag = isNegative(number);
    if (typeGolbach == 0) {
        golbach_strong_conjecture(number,head,numberSums,numberCopy,flag);
    } else {
		golbach_weak_conjecture(number,head,numberSums,numberCopy,flag);
        
    }
}


size_t isPrime(int64_t number) {
    if (number <= 1) return 0; 
    for (int64_t i=2; i<=sqrt(number); i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}
void append(struct Node** head_ref, int64_t new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
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
    return;
}
