#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct listNode{
	double data;
	struct listNode *next;
};

//define listNode as pointer of data type struct listNode
typedef struct listNode *listNode; 


struct list {
			listNode head;
};

//define list as pointer of data type struct list
typedef struct list *list;

/* Creates a new empty linked list */
list createNewEmptyList(){
		list stack;
		stack = (list)malloc(sizeof(struct list));
		stack->head->next = NULL;
		return stack;
}

/* Pushes a new double onto the top of the stack */
void pushToStack(list stack, double data){
		listNode newNode;
		newNode = (listNode)malloc(sizeof(struct listNode)); 
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
		if(stack->head != NULL){
			listNode tempNode;
			tempNode = stack->head->next->next;
			popped = stack->head->next->data;
			stack->head->next = tempNode;
		}
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
void printStack(list stack){
		listNode temp;
		temp = (listNode)malloc(sizeof(struct listNode));
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
}

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
			return result;
}

/* Compute the value of an expression in reverse polish notation */
void evaluateRPNExpression(char* expression, list stack){
		for (int i = 0; expression[i] != 0; i++) {
			if ( expression[i] > '0' && expression[i] <= '9' ) {
					int endOfNumber = i;
					int startIndex = i;
					while(expression[endOfNumber] != ' ')
							endOfNumber++;
					int numberLength = endOfNumber - startIndex;
					double number = evaluateNumber(expression, startIndex, numberLength);
					pushToStack(stack, number);
					i = endOfNumber;
  		}
  		else if ( expression[i] == '+' || expression[i] == '-' || expression[i] == 'X' || expression[i] == '/' || expression[i] == '^') {
						double number1 = popFromStack(stack);
						double number2 = popFromStack(stack);
						if(expression[i] == '+')
							 pushToStack(stack, number1+number2);
						else if(expression[i] == '-')
							 pushToStack(stack, number1-number2);
						else if(expression[i] == 'X')
							 pushToStack(stack, number1*number2);
						else if(expression[i] == '/')
							 pushToStack(stack, number1/number2);
						else if(expression[i] == '^')
							 pushToStack(stack, pow(number1, number2));
				}
				printf("This is loop %d\n", i);
				printStack(stack);
		}
}





/* test me code so far */

int main(){
	char fileName[] = ("expressions.txt");
	char* string = readFileToString(fileName);
	writeOutString(string);
	list stack = createNewEmptyList();
	evaluateRPNExpression(string, stack);
	pushToStack(stack, 0.4);
	pushToStack(stack, 0.3);
	pushToStack(stack, 0.2);
	printStack(stack);
	printf("popped %f\n", popFromStack(stack));
	printf("popped %f\n", popFromStack(stack));
	printf("popped %f\n", popFromStack(stack));
	printStack(stack);
	return 0;
}
