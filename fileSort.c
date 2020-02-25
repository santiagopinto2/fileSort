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
	int flag, start=0, count=0, letter=0, number=0, nonletter=0;
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
			//if the token hasn't started yet
			else if(start==0){
				//if it is an empty token
				if(buffer==','){
					if(firstNode->string==NULL)
						firstNode->string="";
					else{
						struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
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
				if(buffer==','){
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
					count=0;
				}
				//add to the token
				else{
					count++;
					struct readNode* newReadNode=(struct readNode*)malloc(sizeof(struct readNode));
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
				letter=1;
			else if(buffer>='0'&&buffer<='9')
				number=1;
			else if(buffer!=' '&&buffer!=','&&buffer!=0&&buffer!=10)
				nonletter=1;
		}
		//specifically for the last token (does not need to check for empty token)
		char* s=malloc(count);
		count=0;
		struct readNode* tempReadNode=firstReadNode;
		while(tempReadNode->next!=NULL){
			s[count]=tempReadNode->c;
			count++;
			tempReadNode=tempReadNode->next;
		}
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
		
		
		//prints token
		struct Node* tempNode=firstNode;
		while(tempNode!=NULL){
			printf("%s\n", tempNode->string);
			tempNode=tempNode->next;
		}
		
		
	}
	return EXIT_SUCCESS;
}
