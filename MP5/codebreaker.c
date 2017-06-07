/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * here to help you get started.
 */

#include <stdio.h>
#include <stdlib.h>
#include "codebreaker.h"

/*
 * You will need to keep track of the solution code using file scope
 * variables.  You may need others for solving the challenges.  A
 * sample for one variable of the code is shown below for you.
 */

static int peg1;

//create global variables for holding the solution numbers
static int done;
static int dtwo;
static int dthree;
static int dfour;
static int turns = 1;

/*
 * set_seed -- uses sscanf to find the random seed value, then initializes
 *             the random number generator by calling srand with the seed
 * INPUTS: seed_str -- a string entered by the user for the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (contains something
 *               other than a single integer), or 1 on success
 * SIDE EFFECTS: initializes pseudo-random number generation
 */
int set_seed (const char* seed_str)
{
  int seed;
  char s[2];
  //check if there is only a single digit number at the start
  if(sscanf(seed_str,"%d%s",&seed,&s)==1){
    //create a random number based on the seed
    srand(seed);
    return 1;
  }else{
    //state that the seed is invalid
    printf("set_seed: invalid seed\n");
    return 0;
  }

}

/*
 * start_game -- creates the solution combination using the approach
 *               described in the assignment specification (using rand)
 * INPUTS: none
 * OUTPUTS: *one -- the first color value in the code (between 1 and 8)
 *          *two -- the second color value in the code (between 1 and 8)
 *          *three -- the third color value in the code (between 1 and 8)
 *          *four -- the fourth color value in the code (between 1 and 8)
 * RETURN VALUE: 1 on success, or 0 on failure (should never fail, though)
 * SIDE EFFECTS: records the solution code for use by make_guess
 */
int start_game (int* one, int* two, int* three, int* four)
{
    // set the solution numbers to random numbers within 1-8
    *one   = rand()%8+1;
    *two   = rand()%8+1;
    *three = rand()%8+1;
    *four  = rand()%8+1;

    //set variables for each of the solution variables
    done = *one;
    dtwo = *two;
    dthree = *three;
    dfour = *four;
    return 1;
}

/*
 * make_guess -- calculates the number of perfect, high, and low matches
 *               for a given guess, relative to the solution code recorded
 *               earlier by start_game
 * INPUTS: guess_str -- a string consisting of four numbers for the guess
 * OUTPUTS: the following are only valid if the function returns 1
 *          *one -- the first color value in the guessed code (between 1 and 8)
 *          *two -- the second color value in the guessed code (between 1 and 8)
 *          *three -- the third color value in the guessed code
 *                    (between 1 and 8)
 *          *four -- the fourth color value in the guessed code
 *                    (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (represents exactly four
 *               numbers between 1 and 8), or if 0 it is not
 * SIDE EFFECTS: prints the number of matches found using printf
 *               (NOTE: the output format MUST MATCH EXACTLY)
 */

int make_guess (const char* guess_str, int* one, int* two, 
	    int* three, int* four)
{
  //declare guess variables
  int gone;
  int gtwo;
  int gthree;
  int gfour;

  //declare the match variables
  int low = 0;
  int high = 0;
  int perfect = 0;

  char s[2];

  //check to make sure guess is only 4 numbers and set guess variables to each of the numbers
  if(sscanf(guess_str,"%d%d%d%d%s",&gone,&gtwo,&gthree,&gfour,&s)==4){
    //make sure each guess number is within 1-8
    if(gone>=1 && gone<=8){
      if(gtwo>=1 && gtwo<=8){
	if(gthree>=1 && gthree<=8){
	  if(gfour>=1 && gfour<=8){
	    //check how each of the guess numbers compare to their corresponding solution numbers
	    if(gone < done)
	      low++;
	    else if(gone > done)
	      high++;
	    else
	      perfect++;
	    if(gtwo < dtwo)
	      low++;
	    else if(gtwo > dtwo)
	      high++;
	    else
	      perfect++;
	    if(gthree < dthree)
	      low++;
	    else if(gthree > dthree)
	      high++;
	    else
	      perfect++;
	    if(gfour < dfour)
	      low++;
	    else if(gfour > dfour)
	      high++;
	    else
	      perfect++;
	    //print that the guess is valid and how it compares to the solution
	    printf("With guess %d, you got %d perfect matches, %d high, and %d low.\n",turns,perfect,high,low);
	    //increment the turn count
	    turns++;
	    //set the pointers to the guess numbers
	    *one = gone;
	    *two = gtwo;
	    *three = gthree;
	    *four = gfour;
	    return 1;
	  }else{
	    //print that the guess is invalid
	    printf("make_guess: invalid guess\n",guess_str);
	    return 0;
	  }
	}else{
	  printf("make_guess: invalid guess\n",guess_str);
	  return 0;
	}
      }else{
	printf("make_guess: invalid guess\n",guess_str);
	return 0;
      }
    }else{
      printf("make_guess: invalid guess\n",guess_str);
      return 0;
    }
  }else{
    printf("make_guess: invalid guess\n",guess_str);
    return 0;
  }
}
