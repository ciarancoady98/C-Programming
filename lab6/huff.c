// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"


// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
	struct huffcoder * huffcoder = malloc(sizeof(struct huffcoder));
	return huffcoder;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{
	unsigned char c;  // we need the character to be
                    // unsigned to use it as an index
  FILE * file;
  file = fopen(filename, "r");
  assert( file != NULL );
  c = fgetc(file);	// attempt to read a byte
  while( !feof(file) ) {
    //printf("%c", c);
		unsigned index = (unsigned) c;
		this->freqs[index]++;
    c = fgetc(file);
  }
  fclose(file);

	for(int i = 0; i < NUM_CHARS; i++){
		if(this->freqs[i] == 0){
			this->freqs[i] = 1;
		}
	}
}

void swap(int index1, int index2, struct huffchar ** char_list){
	struct huffchar * temp = char_list[index1];
	char_list[index1] = char_list[index2];
	char_list[index2] = temp;
}

struct huffchar * find_smallest(struct huffchar ** char_list){
	//struct huffchar * smallest = malloc(sizeof(struct huffchar));
	struct huffchar * smallest = char_list[0];
	int index_of_smallest = 0;
	for(int i = 1; i < NUM_CHARS; i++){
		if(smallest != NULL && char_list[i] != NULL){
			if((char_list[i]->freq < smallest->freq) ||
			((char_list[i]->freq == smallest->freq) &&
			(char_list[i]->seqno < smallest->seqno))){
				smallest = char_list[i];
				index_of_smallest = i;
			}
			/*
			else if(char_list[i]->freq == smallest->freq){
				if(char_list[i]->seqno < smallest->seqno){
					smallest = char_list[i];
					index_of_smallest = i;
				}
			}
			*/
		}
		else if(smallest == NULL){
			smallest = char_list[i];
			index_of_smallest = i;
		}
	}
	//swap with first element then remove
	if(index_of_smallest != 0){
		swap(0, index_of_smallest, char_list);
	}
	char_list[0] = NULL;
	return smallest;
}

struct huffchar * make_compound(struct huffchar * smallest, struct huffchar * secondSmallest){
	struct huffchar * compound = malloc(sizeof(struct huffchar));
	if(secondSmallest != NULL){
		compound->freq = smallest->freq + secondSmallest->freq;
		compound->is_compound = 1;
		compound->u.compound.left = smallest;
		compound->u.compound.right = secondSmallest;
	}
	else{
		compound = smallest;
	}
	return compound;
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
	struct huffchar * char_list[NUM_CHARS];
	for(int i = 0; i < NUM_CHARS; i++){
		char_list[i] = malloc(sizeof(struct huffchar));
		char_list[i]->freq = this->freqs[i];
		char_list[i]->is_compound = 0;
		char_list[i]->seqno = i;
		char_list[i]->u.c = i;
	}
	int seqno = 255;
	for(int i = 0; i < (NUM_CHARS-1); i++){
		struct huffchar * smallest = find_smallest(char_list);
		struct huffchar * secondSmallest = find_smallest(char_list);
		/*
		if(smallest != NULL ){
			printf("smallest freq : %d\n", smallest->freq);
		}
		if(secondSmallest != NULL){
			printf("secondSmallest freq : %d\n", secondSmallest->freq);
		}
		*/
		struct huffchar * compound = make_compound(smallest, secondSmallest);
		seqno = seqno+1;
		compound->seqno = seqno;
		char_list[0] = compound;
	}
	printf("tree has been built\n");
	for(int i = 0; i < NUM_CHARS; i++){
		if(char_list[i] != NULL)
			printf("%d\n", char_list[i]->seqno);
	}
	this->tree = char_list[0];
}

// recursive function to convert the Huffman tree into a table of
// Huffman codes
void tree2table_recursive(struct huffcoder * this, struct huffchar * node,
		 unsigned long long path, int depth)
{
	if(node->is_compound == 1){
		tree2table_recursive(this, node->u.compound.left, path<<1, depth+1);
		tree2table_recursive(this, node->u.compound.right, ((path<<1) | 1), depth+1);
	}
	else {
		this->code_lengths[node->u.c] = depth;
		this->codes[node->u.c] = path;
	}
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
	struct huffchar * root = this->tree;
	unsigned long long path = 0;
	tree2table_recursive(this, root, path, 0);

}


// print the Huffman codes for each character in order
void huffcoder_print_codes(struct huffcoder * this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for ( i = 0; i < NUM_CHARS; i++ ) {
    // put the code into a string
    for ( j = this->code_lengths[i]-1; j >= 0; j--) {
      buffer[j] = ((this->codes[i] >> j) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';

    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);
  }
}
