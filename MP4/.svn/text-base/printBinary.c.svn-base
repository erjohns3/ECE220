#include <stdio.h>
/*
 * Prints an integer in binary, assumes little endian
 * @param value The value to convert
 * @param size The size of an integer in bytes ( sizeof(int) )
 */
void printBinary(int value, int size){
  int i = 0;                 //initialize counter
  for(i=0;i<size*8;i++){     //loop through for all bits of value
    if(value<0)              //check the MSB
      printf("1");           //if MSB is 1, print 1
    else
      printf("0");           //if MSB is 0, print 0
    value = value<<1;        //bit shift to the left
  }
}


