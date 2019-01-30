#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char ** argv)
{
  unsigned char c;  // we need the character to be
                    // unsigned to use it as an index
  File * file;

  if ( argc != 2 ) {
    fprintf(stderr, "Useage: huffman <filename>\n");
    exit(1);	    // exit with error code
  }

  file = fopen(argv[1], "r");
  assert( file != NULL );
  c = fgetc(file);	// attempt to read a byte
  while( !feof(file) ) {
    printf("%c", c);
    c = fgetc(file);
  }
  fclose(file);

  return 0;  // exit without error code
}
