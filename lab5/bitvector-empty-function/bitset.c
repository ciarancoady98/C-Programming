#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "bitset.h"

/*
struct bitset {
	unsigned int * bits;
	int size_in_bits;
	int size_in_words;
	int bits_per_word;
};
*/

//return the value of bit index
int get_bit(unsigned num, int index){
	unsigned mask = 1 << index;
	unsigned value = num & mask;
	return (value >> index);
}

//set bit b of input
unsigned set_bit(unsigned input, int b){
	unsigned mask = 1 << b;
	return input | mask;
}

//clear bit b of input
unsigned clear_bit(unsigned input, int b){
	unsigned mask = ~(1<<b);
	return input & mask;
}

//create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size){
	int bits_per_word, size_in_words;
	struct bitset * result;
	result = malloc(sizeof(struct bitset));
	bits_per_word = sizeof(unsigned int)*8;
	size_in_words = size/bits_per_word;
	if(size%(sizeof(unsigned int) * 8) != 0){
		size_in_words++;
	}
	result->bits = malloc(sizeof(unsigned int) * size_in_words);
	for(int i = 0; i < size_in_words; i++){
		result->bits[i] = 0;
	}
	result->size_in_bits = size;
	result->size_in_words = size_in_words;
	result->bits_per_word = bits_per_word;
	return result;
}

//get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this){
	return this->size_in_words*(sizeof(unsigned int)*8);
}

//get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
	int cardinality = 0;
	for(int i = 0; i < this->size_in_words; i++){
		if(this->bits[i] == 1){
			cardinality++;
		}
	}
	return 1;
}

//check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
	assert(item >= 0 && item < this->size_in_bits);
	int word_index = item/this->bits_per_word;
	int bit_index = item%this->bits_per_word;

	int in_list = get_bit(this->bits[word_index], bit_index);
	return in_list;
}

//add an item, with number 'item' to the set
//has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item){
	assert(item >= 0 && item < this->size_in_bits);
	int word_index = item/this->bits_per_word;
	int bit_index = item%this->bits_per_word;

	this->bits[word_index] = set_bit(this->bits[word_index], bit_index);
}

//remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item){
	assert(item >= 0 && item < this->size_in_bits);
	int word_index = item/this->bits_per_word;
	int bit_index = item%this->bits_per_word;

	this->bits[word_index] = clear_bit(this->bits[word_index], bit_index);
}

// place the union of src1 and src2 into dest
//or operation
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2){
	for(int i = 0; i < src1->size_in_words; i++){
		dest->bits[i] = src1->bits[i];
	}

	for(int i = 0; i < src2->size_in_words; i++){
		dest->bits[i] = dest->bits[i] | src2->bits[i];
	}
}

//place the intersection of src1 and src2 into dest
//and operation
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2){
	int size = src1->size_in_words;
	if(size < src2->size_in_words){
		size = src2->size_in_words;
	}
	for(int i = 0; i < size; i++){
		dest->bits[i] = src1->bits[i] & src2->bits[i];
	}
}

//print the contents of the bitset
void bitset_print(struct bitset * this){
	int i;
	int size = bitset_size(this);
	for(i = 0; i < size; i++){
		if(bitset_lookup(this, i) == 1){
			printf("%d ", i);
		}
	}
	printf("\n");
}

/*
//add the characters from a string to a bitset
void add_chars_to_set(struct bitset * this, char * s){
	int i;
	for(i = 0; s[i] != 0; i++){
		unsigned char temp = s[i];
		bitset_add(this, temp);
	}
}
*/

/*
// small routine to test a bitset
void mytest()
{
  struct bitset * a = bitset_new(256);
  struct bitset * b = bitset_new(256);
  struct bitset * c = bitset_new(256);
  char * string1 = "What can you hear";
  char * string2 = "Nothing but the rain";

  add_chars_to_set(a, string1);
  add_chars_to_set(b, string2);

  // print the contents of the sets
  bitset_print(a);
  bitset_print(b);

  // compute and print the union of sets
  bitset_union(c, a, b);
  bitset_print(c);

  // compute and print the intersection of sets
  bitset_intersection(c, a, b);
  bitset_print(c);
}
*/
