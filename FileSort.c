#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
struct voidNode{
	void* data;
	struct voidNode* next;
};
struct Node{
	char* string;
	struct Node* next;
};
struct readNode{
	char c;
	struct readNode* next;
};

struct voidNode* getTail(struct voidNode* front) {
	if (front == NULL) {
		return NULL;
	} else if (front->next == NULL) {
		return front;
	}
	struct voidNode* ptr = front;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	return ptr;
}

void printList(struct voidNode* front) {
	struct voidNode* tempVoidNode2 = front;
	if (front == NULL) {
		printf("\n");
		return;
	}
	while(tempVoidNode2!=NULL){
		printf("%s\n", (char*)(tempVoidNode2->data));
		tempVoidNode2=tempVoidNode2->next;
	}
}

int compare(void* first, void* second) {
	
	
	char* token = first;
	int i = 0;
	for (i = 0; i < strlen(token); i++) {
		if (token[i] >= '0' && token[i] <= '9') {
			return compareNum(atoi((char*)first), atoi((char*)second));
		}
	}
	token = second;
	for (i = 0; i < strlen(token); i++) {
		if (token[i] >= '0' && token[i] <= '9') {
			return compareNum(atoi((char*)first), atoi((char*)second));
		}
	}
	//return compareNum(*((int*)first), *((int*)second));
	return compareStr((char*)first, (char*)second);

}

int compareNum(int first, int second) {
	//printf("int compare %d and %d\n\n", first, second);
	long int dif = first - second;
	if (dif < 0) return -1;
	if (dif > 0) return 1;
	return 0;
}

int compareStr(char* first, char* second) {
	
	//printf("string compare %s and %s\n\n", first, second);
	int minLen = strlen(first);
	int longer = 0;
	if (strlen(first) < strlen(second)) {
		minLen = strlen(first);
		longer = 2;
	} else if (strlen(first) > strlen(second)) {
		minLen = strlen(second);
		longer = 1;
	}

	int i;
	for (i = 0; i < minLen; i++) {
		if (first[i] > second[i]) {
			return 1;
		} else if (first[i] < second[i]) {
			return -1;
		}
	}

	if (longer == 1) {
		return 1;
	} else if (longer == 2) {
		return -1;
	}

	return 0;

}
//Assumed input is a void pointer, pointing at a voidNode
int insertionSort(void* toSort, int (*comparator) (void*, void*)) {

	if ((struct voidNode*)toSort == NULL) return 0;
	struct voidNode* current = toSort;
	if (current->next == NULL) return 0;
	
	struct voidNode* head = toSort;
	struct voidNode* ptr = current->next;
	
	while (current->next != NULL) {
		ptr = current->next;
		while (ptr != NULL) {
			if (comparator(current->data, ptr->data) == 1) {
				char* temp = (char*) malloc(sizeof(char) * 300);
				if (temp == NULL) temp = malloc(sizeof(char) * 200);
				if (temp == NULL) temp = malloc(sizeof(char) * 100);
				if (temp == NULL) temp = malloc(sizeof(char) * 50);
				strcpy(temp, (char*)current->data);
				strcpy((char*)(current->data), (char*)(ptr->data));
				strcpy(ptr->data, temp);
				sortBack(head, current, comparator);
				break;
			}
			ptr = ptr->next;
		}
		current = current->next;
	}
	
	return 1;

}

//Used by insertionSort to finish insertion after the inserted node is identified
int sortBack(struct voidNode* start, struct voidNode* end, int (*comparator) (void*, void*)) {
	if (compareStr((char*)(start->data), (char*)(end->data)) == 0) return 0;
	sortBack(start->next, end, comparator);
	if (comparator(start->data, start->next->data) == 1) {
		char* temp = (char*) malloc(sizeof(char) * 300);
		if (temp == NULL) temp = malloc(sizeof(char) * 200);
		if (temp == NULL) temp = malloc(sizeof(char) * 100);
		if (temp == NULL) temp = malloc(sizeof(char) * 50);
		strcpy(temp, (char*)start->data);
		strcpy((char*)(start->data), (char*)(start->next->data));
		strcpy(start->next->data, temp);
	}
	return 0;
}
//First item always pivots
int quickSort(void* toSort, int (*comparator) (void*, void*)) {

	insertionSort(toSort, comparator);

	return 0;

}

int main(int argc, char **argv) {
	int flag, start=0, count=0, hasLetter=0, hasNumber=0, hasNonletter=0;
	char buffer;
	struct voidNode* firstVoidNode=(struct voidNode*)malloc(sizeof(struct voidNode));
	if(firstVoidNode==NULL){
		perror("");
		goto voidNodeNULL;
	}
	struct Node* firstNode=(struct Node*)malloc(sizeof(struct Node));
	if(firstNode==NULL){
		perror("");
		goto NodeNULL;
	}
	struct readNode* firstReadNode=(struct readNode*)malloc(sizeof(struct readNode));
	if(firstReadNode==NULL){
		perror("");
		goto readNodeNULL;
	}
	int file=open(argv[2], O_RDONLY);
	if(file==-1){
		perror("Fatal Error");
		goto close;
	}
	if(argc!=3){
		printf("Fatal Error: Expected 2 arguments, had %d\n", argc-1);
		goto close;
	}
	
	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * fix this if statement **FIXED**
	 */
	if(compareStr(argv[1], "-i") != 0 && compareStr(argv[1], "-q") != 0){
		printf("Fatal Error: Sort type not properly selected\n");
		goto close;
	}
	while((flag=read(file, &buffer, sizeof(buffer)))>0){
		if(buffer==' '||buffer==9){
		}
		//if the token hasn't started yet
		else if(start==0){
			//if it is an empty token
			if(buffer==10){
			}
			else if(buffer==','){
				if(firstNode->string==NULL)
					firstNode->string="";
				else{
					struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
					if(newNode==NULL){
						perror("");
						goto close;
					}
					newNode->string="";
					newNode->next=NULL;
					struct Node* tempNode=firstNode;
					while(tempNode->next!=NULL)
						tempNode=tempNode->next;
					tempNode->next=newNode;
				}
			}
			//start the token
			else{
				start=1;
				count++;
				firstReadNode->c=buffer;
				firstReadNode->next=NULL;
			}
		}
		//if the token has started
		else{
			//if the token is ending
			if(buffer==','||buffer==10){
				start=0;
				char* s=malloc(count);
				count=0;
				struct readNode* tempReadNode=firstReadNode;
				while(tempReadNode->next!=NULL){
					s[count]=tempReadNode->c;
					count++;
					tempReadNode=tempReadNode->next;
				}
				s[count]=tempReadNode->c;
				if(firstNode->string==NULL){
					firstNode->string=malloc(strlen(s)+1);
					strcpy(firstNode->string, s);
				}
				else{
					struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
					if(newNode==NULL){
						perror("");
						goto close;
					}
					newNode->string=malloc(strlen(s)+1);
					strcpy(newNode->string, s);
					newNode->next=NULL;
					struct Node* tempNode=firstNode;
					while(tempNode->next!=NULL)
						tempNode=tempNode->next;
					tempNode->next=newNode;
				}
				count=0;
			}
			//add to the token
			else{
				count++;
				struct readNode* newReadNode=(struct readNode*)malloc(sizeof(struct readNode));
				if(newReadNode==NULL){
					perror("");
					goto close;
				}
				newReadNode->c=buffer;
				newReadNode->next=NULL;
				struct readNode* tempReadNode=firstReadNode;
				while(tempReadNode->next!=NULL)
					tempReadNode=tempReadNode->next;
				tempReadNode->next=newReadNode;
			}
		}
		//letter/number/nonletter check
		if(buffer>='a'&&buffer<='z')
			hasLetter=1;
		else if(buffer>='0'&&buffer<='9')
			hasNumber=1;
		else if(buffer!=' '&&buffer!=','&&buffer!=0&&buffer!=10&&buffer!=9)
			hasNonletter=1;
	}
	//if file is empty
	if(firstNode->string==NULL){
		printf("The file is empty\n");
		goto close;
	}
	//converts to void*
	firstVoidNode->data=firstNode->string;
	firstVoidNode->next=NULL;
	struct voidNode* tempVoidNode=firstVoidNode;
	struct Node* tempNode=firstNode;
	while(tempNode->next!=NULL){
		struct voidNode* newVoidNode=(struct voidNode*)malloc(sizeof(struct voidNode));
		newVoidNode->data=tempNode->next->string;
		newVoidNode->next=NULL;
		tempVoidNode->next=newVoidNode;
		tempVoidNode=tempVoidNode->next;
		tempNode=tempNode->next;
	}
	
	
	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * this prints the void* linked list just for testing
	 */
	 
	
	
	/*struct voidNode* tempVoidNode2=firstVoidNode;
	while(tempVoidNode2!=NULL){
		printf("%s\n", (char*)(tempVoidNode2->data));
		tempVoidNode2=tempVoidNode2->next;
	}*/
	
	void* thetime = firstVoidNode;
	int (*comparator) (void*, void*) = compare;
	quickSort(firstVoidNode, comparator);
	
	printList(firstVoidNode);
	
	/*
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * sorting here
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 */
	
	
	
	
	
	
	//freeing and closing everything
close:
	close(file);
readNodeNULL:;
	struct readNode* t1=firstReadNode;
	struct readNode* t2;
	while(t1!=NULL){
		t2=t1;
		t1=t1->next;
		free(t2);
	}
NodeNULL:;
	struct Node* t3=firstNode;
	struct Node* t4;
		while(t3!=NULL){
		t4=t3;
		t3=t3->next;
		free(t4);
	}
voidNodeNULL:;
	struct voidNode* t5=firstVoidNode;
	struct voidNode* t6;
	while(t5!=NULL){
		t6=t5;
		t5=t5->next;
		free(t6);
	}
	return EXIT_SUCCESS;
}
