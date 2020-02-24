#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
struct Node{
	char* string;
	struct Node* next;
};
struct readNode{
	char c;
	struct readNode* next;
};
int main(int argc, char **argv) {
	int flag, start=0;
	char buffer;
	struct Node* firstNode=(struct Node*)malloc(sizeof(struct Node));
	struct readNode* firstReadNode=(struct readNode*)malloc(sizeof(struct readNode));
	int file=open("abc.txt", O_RDONLY);
	if(file==-1)
		printf("Error\n");
	else{
		while((flag=read(file, &buffer, sizeof(buffer)))>0){
			if(buffer==' '){
			}
			else if(buffer==','){
				start=0;
				char s[]="";
				struct readNode* tempReadNode=firstReadNode;
				while(tempReadNode->next!=NULL){
					strncat(s, &(tempReadNode->c), 1);
					tempReadNode=tempReadNode->next;
				}
				strncat(s, &(tempReadNode->c), 1);
				if(firstNode->string==NULL){
					firstNode->string=malloc(strlen(s)+1);
					strcpy(firstNode->string, s);
				}
				else{
					struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
					newNode->string=malloc(strlen(s)+1);
					strcpy(newNode->string, s);
					newNode->next=NULL;
					struct Node* tempNode=firstNode;
					while(tempNode->next!=NULL)
						tempNode=tempNode->next;
					tempNode->next=newNode;
				}
			}
			else if(start==0){
				start=1;
				firstReadNode->c=buffer;
				firstReadNode->next=NULL;
			}
			else{
				struct readNode* newReadNode=(struct readNode*)malloc(sizeof(struct readNode));
				newReadNode->c=buffer;
				newReadNode->next=NULL;
				struct readNode* tempReadNode=firstReadNode;
				while(tempReadNode->next!=NULL)
					tempReadNode=tempReadNode->next;
				tempReadNode->next=newReadNode;
			}
		}
		
		
		//prints linked list
		struct Node* tempNode=firstNode;
		while(tempNode!=NULL){
			printf("%s\n", tempNode->string);
			tempNode=tempNode->next;
		}
		
		
	}
	return EXIT_SUCCESS;
}
