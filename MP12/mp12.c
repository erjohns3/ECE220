#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mp12.h"


/* delete_tree - given the root of a tree, frees the tree structure from memory
 * INPUTS: curNode - a pointer to a node who must have its subtree and self freed
 * OUTPUTS: none
 * RETURNS: none
 */
void delete_tree(node * curNode)
{
  //check if node is a leaf
  if((int)curNode->item>=48 && (int)curNode->item<=57)
    //free memory if it is a leaf
    free(curNode);
  else{
    //if not a leaf, call on delete tree on left and right branch
    delete_tree(curNode->left);
    delete_tree(curNode->right);
    free(curNode);
  }
}
/* create_postfix_tree - given an expression string creates an expression tree
 * INPUTS: exp_str - a string containing the postfix expression
 * OUTPUTS: Allocates nodes and creates a tree
 * RETURNS: A pointer to the root of the tree
 */
node * create_postfix_tree(char * exp_str)
{
  //allocate memory for stack
  stack *myStack = (stack*)malloc(sizeof(stack));
  //initialize stack
  stackInit(myStack);
  node *myNode;
  int i = 0;;
  //loop until all of expression is read
  do{
    //allocate memory for new node
    myNode = (node*)malloc(sizeof(node));
    //set item of node to next character in expression
    myNode->item = exp_str[i];
    if((int)exp_str[i]<48 || (int)exp_str[i]>57){
      //if next character is operator, pop last two nodes and set them as current nodes branches
      myNode->right = stackPop(myStack);
      myNode->left = stackPop(myStack);
    }
    //push current node onto stack
    stackPush(myStack,myNode);
    i+=2;
  }while((int)exp_str[i-1]!=0);
  //free stacks memory
  free(myStack);
  //return the root node
  return myNode;
}

/* evaluate_postfix - given an expression tree recursively evaluates it
 * INPUTS: curNode - a pointer to a node that must have its left and right subtrees evaluated
 * OUTPUTS: none
 * RETURNS: The value of the evaluated expression
 */
int evaluate_postfix(node * curNode)
{
    // YOUR CODE HERE
  //check what operator it is
  if(curNode->item == '+')
    //evaluate each branch of the operators
    return evaluate_postfix(curNode->left) + evaluate_postfix(curNode->right);
  else if(curNode->item == '-')
    return evaluate_postfix(curNode->left) - evaluate_postfix(curNode->right);
  else if(curNode->item == '*')
    return evaluate_postfix(curNode->left) * evaluate_postfix(curNode->right);
  else if(curNode->item == '/')
    return evaluate_postfix(curNode->left) / evaluate_postfix(curNode->right);
  else
    return (int)(curNode->item-'0');
}

/* postfix - given an expression string prints the solution
 *           the solution is just a number (i.e. printf("%d\n", solution); )
 * INPUTS: exp_str - a string containing the postfix expression
 * OUTPUTS: prints the solution to the expression
 * RETURNS: none
 */
void postfix(char * exp_str)
{
    // YOUR CODE HERE
  //create the tree
  node *temp = create_postfix_tree(exp_str);
  //print the solution
  printf("%d\n",evaluate_postfix(temp));
  //free up allocated memory
  delete_tree(temp);
}

/* infix - given an infix expression prints the solution
 *         must convert to a postfix expression and call postfix()
 * INPUTS: exp_str - a string containing the infix expression
 * OUTPUTS: prints the solution to the expression
 * RETURNS: none
 */
void infix(char * exp_str)
{
  // CHALLENGE CODE HERE
  
}

/* stackInit - initializes a stack structure
 * INPUTS: myStack - pointer to stack structure
 * OUTPUTS: sets top to -1
 * RETURNS: none
 */
void stackInit(stack * myStack)
{
	myStack->top = -1;
}

/* stackPush - pushes an element onto the stack
 * INPUTS: myStack - a pointer to stack structure
 *         element - the node pointer element
 * OUTPUTS: none
 * RETURNS: none
 */
void stackPush(stack * myStack, node * element)
{
	if (myStack->top >= (MAXSIZE - 1))
	{
		printf("Can't push onto stack: stack is full\n");
		return;
	}
	myStack->contents[++myStack->top] = element;
}

/* stackPop - pops an element off the stack
 * INPUTS: myStack - a pointer to stack structure
 * OUTPUTS: none
 * RETURNS: the node pointer element popped off the stack
 */
node * stackPop(stack * myStack)
{
	if(myStack->top < 0)
	{
		printf("Can't pop off stack: stack is empty\n");
		return NULL;
	}
	return myStack->contents[myStack->top--];
}
