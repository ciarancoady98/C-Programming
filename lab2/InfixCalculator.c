#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* This code is a Linked List Implementation of a stack
*
*
*
*/

/*Creating a node, each node has a pointer to the
next node and a data variable */
struct listNode{
	double data;
	struct listNode *next;
};

//define listNode as pointer of data type struct listNode
typedef struct listNode *listNode;

//Defining a list which contains a head
struct list {
			listNode head;
};

//define list as pointer of data type struct list
typedef struct list *list;

/* Creates a new empty linked list */
list createNewEmptyList(){
		list stack = (list)malloc(sizeof(struct list));
		listNode head = (listNode)malloc(sizeof(struct listNode));
		head->next = NULL;
		stack->head = head;
		return stack;
}

/* Pushes a new double onto the top of the stack */
void pushToStack(list stack, double data){
		listNode newNode = (listNode)malloc(sizeof(struct listNode));
		newNode->data = data;
		newNode->next = NULL;
		if(stack->head->next == NULL){
			stack->head->next = newNode;
		}
		else{
				listNode temp;
				temp = stack->head->next;
				stack->head->next = newNode;
				newNode->next = temp;
		}
}

/* Pops the top element off the stack and returns it */
double popFromStack(list stack){
		double popped = 0;
		if(stack->head->next != NULL){
			listNode tempNode;
			tempNode = (listNode)malloc(sizeof(struct listNode));
			tempNode = stack->head->next;
			popped = stack->head->next->data;
			stack->head->next = stack->head->next->next;
			free(tempNode);
		}
		return popped;
}

/* Returns the first element of the stack without popping it off */
double topOfStack(list stack){
			double firstElement = 0;
			if(stack->head->next != NULL){
				firstElement = stack->head->next->data;
			}
			return firstElement;
}

/* Checks if the stack is empty */
int checkIsStackEmpty(list stack){
		if(stack->head == NULL){
			return 1;
		}
		return 0;
}

/* Empties a passed stack */
void emptyStack(list stack){
	while(stack->head->next != NULL){
		popFromStack(stack);
	}
}

/* Prints stack as doubles */
void printStack(list stack){
		listNode temp = (listNode)malloc(sizeof(struct listNode));
		if(stack->head->next != NULL){
			temp = stack->head->next;
			while(temp != NULL){
					double data = temp->data;
					printf("%f\n", data);
					temp = temp->next;
			}
		}
		if(stack->head->next == NULL){
			printf("The stack is empty\n");
		}
		free(temp);
}

/* Prints the stack as characters */
void printStackChar(list stack){
		listNode temp = (listNode)malloc(sizeof(struct listNode));
		if(stack->head->next != NULL){
			temp = stack->head->next;
			while(temp != NULL){
					char data = (char)temp->data;
					printf("%c\n", data);
					temp = temp->next;
			}
		}
		if(stack->head->next == NULL){
			printf("The stack is empty\n");
		}
		free(temp);
}

/* Frees a stack back to unused memory */
void freeStack(list stack){
	emptyStack(stack);
	free(stack);
}

/* File handling code
*
*
*
*/

/* Read in the expression from a file returning a string,
	 Abort progam if file cannot be opened */
	 char* readFileToString(char filename[], int currentLine)
	 {
	 	FILE * file;
	  file = fopen(filename, "r");
	 	int stringSize = 0;
	 	char *string = NULL;
	   if ( file == NULL ) {
	     printf("FATAL: Error opening file %s. Aborting program.\n", filename);
	     exit(1);
	   }
	 	else{
			//find the end of the file so we know what size to make our string
			//fseek(file, 0, SEEK_END);
			//set size of the string
			//lengthOfFile[0] = ftell(file);
			//return to the start of the file
			//rewind(file);
	 			int charactersUntilCurrentLine = 0;
	 			for(int line = currentLine; line != 0; line--){
	 				while(fgetc(file) != '\n'){
	 					charactersUntilCurrentLine++;
	 				}
	 				charactersUntilCurrentLine++;
	 			}
				while(fgetc(file) != '\n'){
		 				stringSize++;
		 		}
		 		stringSize++;
		 		rewind(file);
		 		fseek(file, charactersUntilCurrentLine, 0);
		 		string = (char*) malloc(sizeof(char) * (stringSize + 1));
				fgets(string, stringSize, file);
		 		//string[stringSize] = 0;

	 			//allocate memory for the string
	 			//string = (char*) malloc(sizeof(char) * (stringSize + 1));
	 			//read in the expression from the file

	 	}
	 	//close the file
	 	fclose(file);
	   return string;
	 }

int howManyLinesAreInFile(char* fileName){
	 FILE *file = fopen(fileName,"r");
	 int numberOfLines = 0;
	 char ch = getc(file);
	 while( ch != EOF)
	 {
	     if( ch == '\n')
	     {
	         numberOfLines++;
	     }
	     ch = getc(file);
	 }
	 return numberOfLines;
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



/* Converts a number from a character array to a double */
double evaluateNumber(char* number, int startIndex, int numberLength){
			char* numberAsString = (char*) malloc(sizeof(char) * (numberLength+1));
			int index = startIndex;
			int newIndex = 0;
			while(number[index] != ' '){
					numberAsString[newIndex] = number[index];
					index++;
					newIndex++;
			}
			numberAsString[newIndex] = 0;
			double result = atof(numberAsString);
			free(numberAsString);
			return result;
}

/* Compute the value of an expression in reverse polish notation */
void evaluateRPNExpression(char* expression, list stack){
		for (int i = 0; expression[i] != 0; i++) {
			if ( expression[i] >= '0' && expression[i] <= '9' ) {
					int endOfNumber = i;
					int startIndex = i;
					while(expression[endOfNumber] != ' ')
							endOfNumber++;
					int numberLength = endOfNumber - startIndex;
					double number = evaluateNumber(expression, startIndex, numberLength);
					pushToStack(stack, number);
					i = endOfNumber;
  		}
  		else if ( expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
						double number1 = popFromStack(stack);
						double number2 = popFromStack(stack);
						if(expression[i] == '+')
							 pushToStack(stack, number2+number1);
						else if(expression[i] == '-')
							 pushToStack(stack, number2-number1);
						else if(expression[i] == '*')
							 pushToStack(stack, number2*number1);
						else if(expression[i] == '/')
							 pushToStack(stack, number2/number1);
						else if(expression[i] == '^')
							 pushToStack(stack, pow(number2, number1));
				}
				//printf("This is loop %d\n", i);
				printStack(stack);
		}
}

/* Find precedence of operator */
int findPrecedence(char operator){
	if(operator == '^'){
		return 3;
	}
	else if(operator == '*' || operator == '/'){
		return 2;
	}
	else if(operator == '+' || operator == '-'){
		return 1;
	}
	else
		return 0;
}

/* Prints an array of characters to the console */
void printArray(char* charArray){
			int index = 0;
			while(charArray[index] != 0){
						printf("%c", charArray[index]);
						index++;
			}
			printf("\n");
}

/* Checks if a character is an operator or not */
int isOperator(char operator){
						if(operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == '^'){
							return 1;
						}
						return 0;
}

/* Convert Infix Expression To Postfix notation */
char* infixToPostFix(char* infixExpression, list stack){
			//find the length of the expression and make space for it in memory
			int stringLength = 0;
			while(infixExpression[stringLength] != 0){
					stringLength++;
			}
			char* postfixExpression = (char*) malloc(sizeof(char) * (stringLength+1));
			postfixExpression[stringLength] = 0;
			printf("%d\n", stringLength);

			int outputIndex = 0;

			for (int index = 0; infixExpression[index] != 0; index++) {
					printf("for loop\n");
					printf("%c\n", infixExpression[index]);
					//if token is a number append it to the output string
  				if ( infixExpression[index] >= '0' && infixExpression[index] <= '9' ) {
    				postfixExpression[outputIndex] = infixExpression[index];
						outputIndex++;
						printf("number appended to string\n");
						printArray(infixExpression);
						printArray(postfixExpression);
  				}
					//if token is a left bracket push it to the stack
  				else if (infixExpression[index] == '(') {
    				pushToStack(stack, (double)infixExpression[index]);
						printf("left bracket pushed to stack\n");
						printStackChar(stack);
  				}
					//if token is a space append it to the output string
					else if (infixExpression[index] == ' ' && outputIndex != 0 && postfixExpression[outputIndex - 1] != ' '){
								postfixExpression[outputIndex] = infixExpression[index];
								outputIndex++;
								printf("space appended to string\n");
								printArray(infixExpression);
								printArray(postfixExpression);
					}
					//if token is an operator
  				else if ( isOperator(infixExpression[index]) == 1 ) {
    					while ( isOperator((char)topOfStack(stack)) == 1 && findPrecedence((char)topOfStack(stack)) > findPrecedence(infixExpression[index])) {
									printf("while loop 1\n");
			 						postfixExpression[outputIndex] = (char)popFromStack(stack);
									outputIndex++;
    					}
							pushToStack(stack, (double)infixExpression[index]);
							printf("operation carried out\n");
							printStackChar(stack);
					}
									/*
									if(postExpression[outputIndex-1] != ' '){
										postfixExpression[outputIndex] = ' ';
										outputIndex++;
									}
									else {
											postfixExpression[outputIndex] = (char)popFromStack(stack);
											outputIndex++;
									}*/
					//if token is a right bracket
  				else if ( infixExpression[index] == ')' /*|| infixExpression[index] == 0*/ ) {
   				 		while ( (char)topOfStack(stack) != '(' ) {
									printf("while loop 2\n");
									postfixExpression[outputIndex] = (char)popFromStack(stack);
									printf("%c\n", (char)topOfStack(stack));
									outputIndex++;
  						}
							//pop left bracket
							popFromStack(stack);
					}
			}
			while ( isOperator((char)topOfStack(stack)) == 1 ){
					if(postfixExpression[outputIndex-1] != ' '){
						postfixExpression[outputIndex] = ' ';
						outputIndex++;
					}
					postfixExpression[outputIndex] = (char)popFromStack(stack);
					outputIndex++;
			}
			postfixExpression[outputIndex] = 0;
			//popFromStack(stack);
			return postfixExpression;
}

/* Parses the raw line input from the file and
returns 1 if infix and 0 if postfix */
int parseLine(char* rawLine, char* parsedLine){
	printf("parsing\n");
	if(rawLine[0] == 'i'){
		int rawIndex = 6;
		int parsedIndex = 0;
		while(rawLine[rawIndex] != 0){
			parsedLine[parsedIndex] = rawLine[rawIndex];
			parsedIndex++;
			rawIndex++;
		}
		parsedLine[parsedIndex] = 0;
		return 1;
	}
	else if(rawLine[0] == 'p'){
		int rawIndex = 8;
		int parsedIndex = 0;
		while(rawLine[rawIndex] != 0){
			parsedLine[parsedIndex] = rawLine[rawIndex];
			parsedIndex++;
			rawIndex++;
		}
		parsedLine[parsedIndex] = 0;
		return 0;
	}
	else
		return -1;
}

/* test me code so far */

int main(int argc, char ** argv){
	char * fileName;
  if ( argc == 1 ) {
    printf("Error: No input filename provided\n");
    printf("Usage: %s <input filename>\n", argv[0]);
    //exit(1);
  }
  else if ( argc > 2 ) {
    printf("Error: Too many command line parameters\n");
    printf("Usage: %s <input filename>\n", argv[0]);
    //exit(1);
  }
  else {
    fileName = argv[1];
  }

	fileName = "expressions.txt";

	int numberOfLines = howManyLinesAreInFile(fileName);
	int currentLine = 0;
	char* parsedString;
	char* rawString;
	list stack = createNewEmptyList();
	while(currentLine <= numberOfLines){
		printf("currentLine = %d\n", currentLine);
		parsedString = (char*) malloc(sizeof(char) * (200));
		rawString  = readFileToString(fileName, currentLine++);
		printf("rawString:%s\n", rawString);

		int parsed = parseLine(rawString, parsedString);
		if(parsed == 1){
			char* postFix = infixToPostFix(parsedString, stack);
			writeOutString(postFix);
			evaluateRPNExpression(postFix, stack);
			//free(postFix);
		}
		else if(parsed == 0){
			evaluateRPNExpression(parsedString, stack);
		}
		free(parsedString);
		free(rawString);
		//freeStack(stack);
	}

	//evaluateRPNExpression(string, stack);
	//pushToStack(stack, 0.4);
	//pushToStack(stack, 0.3);
	//pushToStack(stack, 0.2);
	//printStack(stack);
	//printf("popped %f\n", popFromStack(stack));
	//printf("popped %f\n", popFromStack(stack));
	//printf("popped %f\n", popFromStack(stack));
	//printStack(stack);
	return 0;
}
