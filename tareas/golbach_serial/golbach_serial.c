// A simple C program for traversal of a linked list
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
  
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
  
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}
int isPrime(int number);

void golbach(int number,struct Node *node,int *numberSums,int flag);

void printGolbach1(struct Node *node,int *numberSums,int number,int flag);

void printGolbach2(int *array,int *numberSums,int number);

int isNegative(int number);

int prime_finder(int target, int *prime_list); 

  
// This function prints contents of linked list starting from
// the given node
void printList(struct Node* n)
{
    while (n != NULL) {
        printf(" %d ", n->data);
        n = n->next;
    }
}
  
int main()
{
    struct Node* head = NULL;
    int number = 21;
    scanf("%d",&number);
    int flag = isNegative(number);
    number = abs(number);
    int numberSums=0;
    int *ptrNumberSums = &numberSums;
    golbach(number,head,ptrNumberSums,flag);

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
void printGolbach1(struct Node *node,int *numberSums,int number,int flag){
    if(flag==1){
        printf("%d: %d summs: ",number,*numberSums);
        for(int i=0;i<=*(numberSums)*2;i+=2){
            while (node != NULL) {
                printf("%d + ", node->data);
                node = node->next;
                printf("%d,", node->data);
                node = node->next;
            }
        }
    }else{
        printf("%d: %d summs",number,*numberSums);
    }
    printf("\n");
}

void golbach(int number,struct Node *head,int *numberSums,int flag){
	int typeGolbach = number%2;
	if(typeGolbach == 0){
		//This cicle is for finding the sums of prime numbers
		//Is divided by 2 because beyond that it will repeat the sums in
		//the opposite order
		for(int i=2;i<=number/2;i++){
			if(isPrime(i)==1 && isPrime(number-i)==1){
			    append(&head,i);
				append(&head,number-i);
				*numberSums+=1;
			}
		}
		printGolbach1(head, numberSums, number,flag);
	}else{
            
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
