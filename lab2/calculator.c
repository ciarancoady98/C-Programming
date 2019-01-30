#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Precedence values
public static int BRACKET = 4;
public static int TOTHEPOWEROF = 3;
public static int MULTIPLY = 2;
public static int DIVIDE = 2;
public static int ADD = 1;
public static int SUBTRACT = 1;

struct LinkedList{
	double data;
	struct LinkedList *next;
};

typedef struct LinkedList *node; //define node as pointer of data type struct LinkedList

node createNode(){
	node temp; // declare a node
	temp = (node)malloc(sizeof(struct LinkedList)); // allocate memory using malloc()
	temp->next = NULL; // make next point to NULL
	return temp; //return the new node
}

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
			p = p->next; //travers the list until p is the last node. The last node always points to NULL
		}
		p->next = temp; //point the previous last node to the new node create.
	}
	return head;
}

//converting infix to RPN
char[] convertToReversePolishNotation(char[] infixExpression, int length){
	char[length] reversePolishExpression;
	int currentStringIndex = 0;
	for (int index = 0; index < length-1; index++){
  		if ( token is a number ) {
    		//append token to the output string
			
  		}
  		else if (infixExpression[index] == '(') {
   			 //push bracket to stack
			pushToStack('(');
  		}
  		else if (infixExpression[index] == '+' || infixExpression[index] == '-' || infixExpression[index] == 'X' || infixExpression[index] == '/' || infixExpression[index] == '^') {
    		while ( there is operator on top of stack with higher precedence ) {
      			//pop stack and append popped operator to output string
    		}
    		//push token operator to stack
			
  		}
  		else if (infixExpression[index] == ')') {
    		while (topOfStack() != '(') {
      			//pop operator from stack and append to output string
				popFromStack
    			//pop left bracket
  			}
		}
}

//find precedence of operator
int findPrecedence(char operator){
	if(operator == '(' || operator == ')'){
		return 4;
	}
	else if(operator == '^'){
		return 3;
	}
	else if(operator == 'X' || operator == '/'){
		return 2;
	}
	else if(operator == '+' || operator == '-'){
		return 1;
	}
	else
		return 0;
}


