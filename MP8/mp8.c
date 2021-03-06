#include "mp8.h"
#include <math.h>
/*This function calcuates the index of a given cell in the board */
/*n is the size of the sub-region                                */
/* row and col are the coordinates of the cell                   */
int indexCal(int n, int row, int col) {
  return (n*n*row+col);
}


 
/*Bubble sort is a sorting algorithm that sorts a given array    */
/*subboard is the array pointer, size is the size of the array   */
void bubblesort(int *subboard, int size) {
  int i,temp,swap;
  do {
    swap = 0;
    for(i=0;i<size-1;i++){
      //if the later number is before than swap them
      if(subboard[i]>subboard[i+1]){
	temp=subboard[i];
	subboard[i]=subboard[i+1];
	subboard[i+1]=temp;
	swap=1;
      }
    }
  } while(swap);
}



/*Check if Sudoku board is valid                                                    */
/*return ILLEGAL_STATE when you have two same number in a row, or col or sub-region */
/*reutrn INCOMPLETE_STATE when the board is not completely filled with valid numbers     */
/*return GOAL_STATE if the board is solved                                          */
int CheckSudoku(int n, int *board, int indicator) {
  int i,j,k,l;
  //copy is used as a temp array to store a row, or col, or sub-region of numbers.
  //the memory for copy is dynamically allocated
  int *copy = malloc(n*n*sizeof(int));
  
  //check each row, colum and sub-region for duplicates
  //copy the row, colum or sub-region to the array named copy 
  //sort copy with bubble sort and then check for duplicates
  //check the rows
  for(i=0;i<n*n;i++){
    for(j=0;j<n*n;j++)
      //copy the values of the row into copy array
      copy[j]=board[indexCal(n,i,j)];
    bubblesort(copy,n*n);
    for(j=0;j<n*n-1;j++){
      if(copy[j]==copy[j+1]&&copy[j]!=0)
	return ILLEGAL_STATE;
    }
  }
  //check the columns
  for(i=0;i<n*n;i++){
    for(j=0;j<n*n;j++)
      //copy the values of the column into copy array
      copy[j]=board[indexCal(n,j,i)];
    bubblesort(copy,n*n);
    for(j=0;j<n*n-1;j++){
      if(copy[j]==copy[j+1]&&copy[j]!=0)
	return ILLEGAL_STATE;
    }
  }
  //check the subregions
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      for(k=0;k<n;k++){
	for(l=0;l<n;l++)
	  //copy the values of the subregion into copy array
	  copy[k*n+l]=board[indexCal(n,i*n+k,j*n+l)];
      }
      bubblesort(copy,n*n);
      for(l=0;l<n*n-1;l++){
	if(copy[l]==copy[l+1]&&copy[l]!=0)
	  return ILLEGAL_STATE;
      }
    }
  }
  
  //check the diagonals if indicator is 1
  if(indicator==1){
    for(i=0;i<n*n;i++)
      //copy the values of the diagonal into copy array
      copy[i]=board[indexCal(n,i,i)];
     bubblesort(copy,n*n);
    for(i=0;i<n*n-1;i++){
      if(copy[i]==copy[i+1]&&copy[i]!=0)
	return ILLEGAL_STATE;
    }   
    for(i=0;i<n*n;i++)
      //copy the values of the diagonal into copy array
      copy[i]=board[indexCal(n,i,n*n-1-i)];
    bubblesort(copy,n*n);
    for(i=0;i<n*n-1;i++){
      if(copy[i]==copy[i+1]&&copy[i]!=0)
	return ILLEGAL_STATE;
    }   
  }

  //check to see if the given places have even values
  if(board[n*n*n*n]!='\0'){
    for(i=n*n*n*n;i<2*n*n*n*n;i++){
      if(board[i]==1 && board[i-n*n*n*n]%2==1)
	return ILLEGAL_STATE;
    }
  }
    
  //If there is no duplicates in the board, check if the board is complete
  for(i=0;i<n*n*n*n;i++){
    if(board[i]==0)
      return INCOMPLETE_STATE;
  }
  //else the board is complete and valid, thus we found the solution.
  return GOAL_STATE;
}



/* This function solves the board with recursion                             */
/* Base case is when you have GOAL_STATE and ILLEGAL_STATE                  */
int SolveSudoku(int n, int *board,int indicator) {
  //intitialize for loop counter
  int a;
  //check the board
  switch(CheckSudoku(n,board,indicator)) {
  case GOAL_STATE: return 1;
  case ILLEGAL_STATE: return 0;
  }
  //do this if the board isn't complete
  for(a=0;a<n*n*n*n;a++){
    if(board[a]==0){
      for(board[a]=1;SolveSudoku(n,board,indicator)!=1;board[a]++){
	//reset value to 0 if dead end is reached and revert back to last place
	if(board[a]==n*n){
	  board[a]=0;
	  return 0;
	}
      }
      return 1;
    }
  }
  return 0;
}


