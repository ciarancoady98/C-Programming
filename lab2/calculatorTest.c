#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct LinkedList{
	double data;
	struct LinkedList *next;
};

//define node as pointer of data type struct LinkedList
typedef struct LinkedList *node; 

node createNode(){
	node temp; // declare a node
	temp = (node)malloc(sizeof(struct LinkedList)); // allocate memory using malloc()
	temp->next = NULL; // make next point to NULL
	return temp; //return the new node
}

/* Add a node to the linked list (push item to the top of the stack */
node addNode(node head, double value){
	node temp, p; //declare two nodes temp and p
	temp = createNode(); //createNode will return a new node with data = value and next pointing to NULL.
	temp->data = value; //add element's value to data part of node
	if(head==NULL){
		head = temp;
	}
	else{
		p = head; //assign head to p
		while(p->next != NULL){
			p = p->next; //travels the list until p is the last node. The last node always points to NULL
		}
		p->next = temp; //point the previous last node to the new node create.
	}
	return head;
}

/* Pop the top element from the stack and return the double it holds */
double popNode(node head){
		double popped = 0;
		node p;
		p = head;
		int noOfElems = 0;
		while(p->next != NULL){
				p = p->next; //increment through the nodes in the stack until we get to the end
				noOfElems++;
		}
		popped = p->data; //pop off the data in the last element
		p = head;
		for(int i; i<noOfElems; i++){
			p = p->next; //go to the new last element of the stack
		}
		p->next = NULL; //set its pointer to null
		return popped;
}


/* Read in the expression from a file returning a string,
	 Abort progam if file cannot be opened */
char* readFileToString(char filename[])
{
	FILE * file;
  file = fopen(filename, "r");
	int stringSize;
	char *string = NULL;
	
  if ( file == NULL ) {
    printf("FATAL: Error opening file %s. Aborting program.\n", filename);
    exit(1);
  }
	else{
			//find the end of the file so we know what size to make our string
			fseek(file, 0, SEEK_END);
			//set size of the string
			stringSize = ftell(file);
			//return to the start of the file
			rewind(file);
			//allocate memory for the string
			string = (char*) malloc(sizeof(char) * (stringSize + 1));
			//read in the expression from the file
			fgets(string, stringSize, file);
			
	}
	//close the file
	fclose(file);
  return string;
}

/* Prints out a well formed string to the console */
void writeOutString(char string[]){
		int i = 0;
		while(string[i] != 0){
				printf("%c", string[i]);
				i++;
		}
		printf("\n");
}

/* Print stack */
void printStack(node head){
		node temp;
		temp = (node)malloc(sizeof(struct LinkedList));
		temp->data = head->data;
		temp->next = head->next;
		while(temp->next != NULL){
				double data = temp->data;
				printf("%f\n", data);
				temp = temp->next;
		}
		if(head->next == NULL){
			printf("The stack is empty\n");
		}
}



/* test me code so far */

int main(){
	char fileName[] = ("expressions.txt");
	char* string = readFileToString(fileName);
	writeOutString(string);
	node head = createNode();
	head = addNode(head, 0.4);
	head = addNode(head, 0.3);
	head = addNode(head, 0.2);
	printStack(head);
	popNode(head);
	popNode(head);
	printStack(head);
	
	return 0;
}
