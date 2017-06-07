/*! File module

    Provides level loading functionality through a function that creates a game from a
    level file.  Also provides a function for destroying the game instance for use during
    teardown.
*/

#include "game.h"
#include "file.h"

#include <stdio.h>
#include <stdlib.h>

game * create_game(const char * file_name)
/*! Load an input level file with given file_name with format specified in levels/README.txt,
    and transform the serialized data within into a game data structure, specified in game.h
    Return a pointer to the game instance on success, NULL on failure.

    Note that error handling is not required for credit, but may help with testing.

    The game and structures it points to should be allocated with the malloc family of
    functions.  Make sure to take advantage of allocation functions provided by the game module.
*/
{
  //open the file and make sure it can open
  FILE *f;
  if((f = fopen(file_name,"r")) == NULL){
    printf("UNABLE TO OPEN FILE");
    return NULL;
  }
  //allocate memory for the game
  game *my_game;
  if((my_game = (game*)malloc(sizeof(game))) == NULL){
    printf("Insufficient memory for game");
    return NULL;
  }
  int rows =- 1;
  int cols =- 1;
  //get information about the game from the file
  fscanf(f,"%i%i%f%f%i\n",&rows,&cols, &my_game->time_step, &my_game->food_probability, &my_game->growth_per_food);
  my_game->board = create_board(rows,cols);
  char c = fgetc(f);
  int row = 0;
  int col = 0;
  while(c != EOF){
    
    switch(c){
      //set up the board
    case 'X':
      *board_cell(my_game->board,row,col) = CELL_WALL;
      break;
    case '-':
      *board_cell(my_game->board,row,col) = CELL_OPEN;
      break;
      //create the human snake
    case 'n':
      my_game->human_snake = create_snake(my_game->board,row,col,NORTH,0);
      break;
    case 's':
      my_game->human_snake = create_snake(my_game->board,row,col,SOUTH,0);
      break;     
    case 'e':
      my_game->human_snake = create_snake(my_game->board,row,col,EAST,0);
      break;   
    case 'w':
      my_game->human_snake = create_snake(my_game->board,row,col,WEST,0);
      break;  
      //create the computer snake
    case 'N':
      my_game->computer_snake = create_snake(my_game->board,row,col,NORTH,0);
      break;
    case 'S':
      my_game->computer_snake = create_snake(my_game->board,row,col,SOUTH,0);
      break;     
    case 'E':
      my_game->computer_snake = create_snake(my_game->board,row,col,EAST,0);
      break;   
    case 'W':
      my_game->computer_snake = create_snake(my_game->board,row,col,WEST,0);
      break; 
    }
    //move to next cell
    if(c != '\n'){
      col++;
      if(col >= cols){
	col = 0;
	row++;
	if(row >= rows){
	  break;
	}
      } 
    }
    //get next character
    c = fgetc(f);
  }
  //close the file and return the game
  fclose(f);
  return my_game; 
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains.  Make sure to take
    advantage of deallocation functions provided by the game module. */
{
  //free each component of the game then free the game
  destroy_snake(cur_game->computer_snake);
  destroy_snake(cur_game->human_snake);
  destroy_board(cur_game->board);
  free(cur_game);
}
