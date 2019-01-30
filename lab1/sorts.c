/* Program that reads in a text file of integers
   and outputs the numbers in sorted order. */

#include <stdio.h>
#include <stdlib.h>

/* find smallest element between start and end of array */
int findMin(int a[], int size, int start) {
  int min = a[start];
  int result = start;
  int i;

  for ( i = start; i < size; i++ ) {
    if ( a[i] < min ) {
      min = a[i];
      result = i;
    }
  }
  return result;
}

/* swap two elements in an array */
void swapElements(int a[], int size, int element1, int element2) {
   int temp;
   if (element1 < size && element2 < size) {
    temp = a[element1];
    a[element1] = a[element2];
    a[element2] = temp;
   }
}

/* selection sort algorithm: repeatedly find smallest
   element and place at start of unsorted section. */
static int selectionSort(int a[], int size) {
	int i, smallest, noOfExecutions;
	noOfExecutions = 0;
	for (i = 0; i < size; i++){
		smallest = findMin(a, size, i);
		if( smallest > i){
			swapElements(a, size, i, smallest);
		}
		noOfExecutions++;
	}
	return noOfExecutions;
}

/* insertion sort algorithm: place unsorted array
   elements into the correct location in an initially
   empty sorted part.*/
int insertionSort(int a[], int size) {
	int i, testElement, noOfExecutions, sorting;
	noOfExecutions = 0;
	for(i = 1; i < size; i++){
		sorting = 1;
		testElement = i;
		while (sorting == 1 && testElement > 0){
			if(a[testElement] < a[testElement - 1]){
				swapElements(a, size, testElement, (testElement - 1));
				testElement--;
			}
			else {
				sorting = 0;
			}
		}
		noOfExecutions++;
	}
	return noOfExecutions;
}

/* bubble sort algorithm: repeatedly compare and swap
   adjacent array elements. */
int bubbleSort(int a[], int size) {
	int i, noOfExecutions, swapped;
	swapped = 1;
	noOfExecutions = 0;
	while (swapped == 1){
		swapped = 0;
		for ( i = 0; i < size - 1; i++ ) {
			if ( a[i] > a[i+1] ) {
			swapElements(a, size, i, (i+1));
			swapped = 1;
			}
			noOfExecutions++;
		}
	}
	return noOfExecutions;
}

/* funny sort algorithm: like bubble sort only we
   go back to the start every time we find a pair
   out of order. */
int funnySort(int a[], int size) {
  int j, temp, noOfExecutions;
  noOfExecutions = 0;
  j = 0;
  while ( j < size - 1 ) {
    if ( a[j] > a[j+1] ) {
      temp = a[j];
      a[j] = a[j+1];
      a[j+1] = temp;
      j = 0;
    }
    else {
      j++;
    }
    noOfExecutions++;
  }
  return noOfExecutions;
}

/* Open a file. Abort progam if file cannot be opened */
FILE * open_file(char filename[])
{
  FILE * file;

  file = fopen(filename, "r");
  if ( file == NULL ) {
    printf("FATAL: Error opening file %s. Aborting program.\n", filename);
    exit(1);
  }

  return file;
}

/* read a stream of up to 'size' integers from a text file.
   return number of integers */
int read_in(int a[], int size, char filename[])
{
  const int max_line = 1024;
  char line[max_line];
  int i;
  FILE * file;
  char * eof;

  file = open_file(filename);

  /* read in the ints - one per line */
  i = 0;
  eof = fgets(line, max_line, file);
  while ( eof != NULL && i < size ) {     /* eof == NULL => end of file */
    sscanf(line, "%d", &(a[i]));
    i++;
    eof = fgets(line, max_line, file);
  }
  fclose(file);
  return i;
}

/* write out an array of integers up to 'size' */
void write_out(int a[], int size)
{
  int i;

  for ( i = 0; i < size; i++ ) {
    printf("%d\n", a[i]);
  }
}


/* read in a file of numbers, sort them, and
   write them out to the screen */
int main()
{
  const int size = 1024;
  int nums[size];
  int nnums;
  int noOfExecutions;

  nnums = read_in(nums, size, "numbers.txt");
  noOfExecutions = funnySort(nums, nnums);
  printf("FunnySort:%d\n", noOfExecutions);
  nnums = read_in(nums, size, "numbers.txt");
  noOfExecutions = insertionSort(nums, nnums);
  printf("InsertionSort:%d\n", noOfExecutions);
  nnums = read_in(nums, size, "numbers.txt");
  noOfExecutions = bubbleSort(nums, nnums);
  printf("BubbleSort:%d\n", noOfExecutions);
  nnums = read_in(nums, size, "numbers.txt");
  noOfExecutions = selectionSort(nums, nnums);
  printf("SelectionSort:%d\n", noOfExecutions);
  //write_out(nums, nnums);
  /* flush output buffer, so all output appears on screen */
  fflush(stdout);

  return 0;
}
