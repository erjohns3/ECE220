#include <stdio.h>
#include "printBinary.h"

// FUNCTION DECLARATIONS
void convert(int value, int key);

int main(void)
{
    int value, key;
    char inCheck;

    // Get integer and check for valid
    printf("Enter an integer: ");
    if (scanf("%d%c", &value, &inCheck) != 2 || inCheck != '\n')
    {
        printf("Invalid input\n");
        return -1;
    }

    // Get conversion key
    printf("0: Binary\n1: Octal\n2: Decimal\n3: Hex\n");
    printf("Enter conversion: ");
    scanf("%d", &key);

    // Convert base and print
    convert(value, key);
    return 0;
}

/*
 * Converts a value to a different base representation and prints it
 * @param value The value to convert
 * @param key The key that indicates the conversion operation
 * @return none
 */
void convert(int value, int key){
    // YOUR CODE GOES HERE.
  //switch statement to do a certain thing for each key
    switch(key){

        //if key=0, call on printBinary function with the value
        case 0: printBinary(value,sizeof(int));
		printf("\n");
        break;

	//if key=1, print value in octal
        case 1: printf("%o\n",value);
        break;

	//if key=2, print value in decimal
        case 2: printf("%d\n",value);
        break;

	//if key=3, print value in hexadecimal
        case 3: printf("%x\n",value);
        break;

	//if key isn't 0-3, it is invalid
        default: printf("Invalid Key\n");
    }
}

