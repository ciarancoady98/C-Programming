// C code file for  a file ADT where we can read a single bit at a
// time, or write a single bit at a time

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "bitfile.h"

// open a bit file in "r" (read) mode or "w" (write) mode
struct bitfile * bitfile_open(char * filename, char * mode)
{
  struct bitfile * result = malloc(sizeof(struct bitfile));
  if(strcmp(mode, "r") == 0){
    result->is_read_mode = 0;
    result->index = -1;
  }
  else if(strcmp(mode, "w") == 0){
    result->is_read_mode = 1;
    result->index = 0;
  }
  result->buffer = 0;
  result->is_EOF = 0;
  result->file = fopen(filename, mode);
  assert( result->file != NULL );
  return result;
}

// write a bit to a file; the file must have been opened in write mode
void bitfile_write_bit(struct bitfile * this, int bit)
{
  if(this->is_read_mode == 1){
    this->buffer = this->buffer | (bit << this->index);
    this->index = this->index + 1;
    assert(this->index <= 8);
    if(this->index == 8){
      fputc(this->buffer, this->file);
      this->index = 0;
      this->buffer = 0;
    }
  }
}

// read a bit from a file; the file must have been opened in read mode
int bitfile_read_bit(struct bitfile * this)
{
  int bit = 0;
  if(this->is_read_mode == 0){
    if(this->index < 0){
      this->buffer = fgetc(this->file);
      this->index = 7;
    }
    bit = this->buffer & 1;
    this->index--;
    this->buffer = this->buffer >> 1;
  }
  return bit;
}

// close a bitfile; flush any partially-filled buffer if file is open
// in write mode
void bitfile_close(struct bitfile * this) {
  if(this->is_read_mode == 1 && this->index >= 0){
    fputc(this->buffer, this->file);
    this->buffer = 0;
    this->index = 0;
  }
  fclose(this->file);
}

// check for end of file
int bitfile_end_of_file(struct bitfile * this)
{
  if(this->is_EOF == 1){
    return 1;
  }
  else{
    return 0;
  }
}
