#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


struct bitfile{
  FILE * file;
  unsigned char buffer;
  int index;
};

struct bitfile * bitfile_new(char * filename, char * rw){
  struct bitfile * result = malloc(sizeof(bitfile));
  result->buffer = 0;
  result->index = 0;
  result->file = fopen(filename, rw);
}

void bitfile_write(struct bitfile * this, int bit){
  if(bit == 1){
    this->buffer = this->buffer | (1<<index);
  }
  this->index++;
  assert(this->index <= 8);
  if(this->index == 8){
    fputchar(this->file, this->buffer);
    this->index = 0;
    this->buffer = 0;
  }
}

void bitfile_read(struct bitfile * this){
  struct huffchar * current = root;
  while(current->is_compound == 1){
    int nit = get_next_bit();
    if(bit == 0){//go left
      current = current->u.compound.left;
    }
    else{
      current = current->u.compound.right;
    }
  }
  assert(current->is_compound == 0)
  //letter found save it
}
