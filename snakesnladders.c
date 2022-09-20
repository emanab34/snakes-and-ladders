//Eman Albadri R00196017
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

   //gameSquare acts as a node 
struct gameSquare
{
  int pos;//holds the position of the square
  
  struct gameSquare *next;	//pointer to next square
}*head,*tail;

struct gameBoard
{
  struct gameSquare *squares;
};
//struct for player
struct player{
    int playerNo;
    int currentPos;
};
//struct for snakes and ladders
struct snake{
    int position;
    int backtrack; //store the number of backward movement
};
struct ladder{
    int position;
    int forward; //store number of forward movement;
};

//game board implementation
//function to call random numbers
int randomNumber (int min, int max)
{
  int randomNo = random () % (max + 1 - min) + min;
 // printf("Random number: %d \n ", randomNo);
  return randomNo;
}

//function to create list depending on size
void createlist (int size)
{
  struct gameSquare *newSquare, *temp;
  int pos, i;
  	
  head = (struct gameSquare *) malloc (sizeof (struct gameSquare)); //to signifybeginning of board
  tail = (struct gameSquare *) malloc (sizeof (struct gameSquare)); // to signify end of board
  
  pos = 1;
  //make head of position size
  head->pos = pos;
  head->next = NULL;


  temp = head;
  //add numbers in reverse to beginning number is smallest value
  for (i = 2; i <= size + 1 ; i++)
    {
      newSquare = (struct gameSquare *) malloc (sizeof (struct gameSquare));
      newSquare->pos = i;
      newSquare->next = NULL;

      temp->next = newSquare;	//link nodes together
      temp = temp->next;

      if (newSquare->pos == size)
	{
	  tail = newSquare;
	}

    }

}

//function to show board
void showBoard (int size)
{
  struct gameSquare *temp;
  struct gameBoard *board;

  //to get row and column number
  int row, col, i;
  i = (int) round(sqrt(size));


  if (head == NULL)
    {
      printf ("No board has been created");
    }
  temp = head;
  
  
  while (temp != NULL)
    //print as a square
    {
      for (row = 1; row <= i ; row++)
	{
	  for (col = 1; col <= i ; col++)
	    {
	      printf ("| %d |", temp->pos);
	      board->squares = temp; //save into gameboard struct
	      temp = temp->next;
	    }
	    printf("\n"); //move to next line
	}
	if(temp->next == NULL){
	    break;
	}
    }

}

//snakes and ladders function
void snakesAndLadders(int laddersNo, int snakesNo, int size){
   //arrays to identify the positions of snakes and ladders on the board
   //and avoid collision between snakes and ladders
   struct snake* snakes[snakesNo];
   struct ladder* ladders[laddersNo];
   int snakeRandom, ladderRandom, numCols;
   struct snake *newSnake;
   struct ladder *newLadder;
   *snakes = (struct snake*)malloc(sizeof(struct snake));
   *ladders = (struct ladder*)malloc(sizeof(struct ladder));
   numCols = (int) round(sqrt(size));
   FILE *fileptr;
    fileptr = fopen("SnakesandLadders.txt","a+"); //open file connection
    if(fileptr == NULL){
        printf("Error! Cannot open file ");
        return;
    }
    
    
   // randomly assign positions for snakes between number of columns+1 and size-1 as snakes cannot be 
   //on the first row and cannot be on the last square
   for (int i = 0; i<snakesNo;i++){
    
        newSnake = (struct snake*) malloc (sizeof (struct snake));
        snakes[i] = newSnake;
        //check if the position of current is same as previous change the valuse
        if(i > 1 && snakes[i]->position == snakes[i-1]->position){
            snakeRandom = randomNumber((numCols+1),(size-1));
            snakes[i]->position = snakeRandom;
        }

    else{
        newSnake = (struct snake*) malloc (sizeof (struct snake));
        snakes[i] = newSnake;
        snakeRandom = randomNumber((numCols+1),(size-1)); 
        snakes[i]->position = snakeRandom;
    }
    
    }
    printf("Snakes list maade\n");
    //randomly assign positions for ladders between 2 to size-num cols because ladders cannot start at first square or last row
    
    for (int i = 0; i<laddersNo;i++){
    
        newLadder = (struct ladder*) malloc (sizeof (struct ladder));
        ladders[i] = newLadder;
        //check if the position of current is same as previous change the value
        if(i > 1 && ladders[i]->position == ladders[i-1]->position){
            ladderRandom = randomNumber(2,(size-numCols));
            ladders[i]->position = ladderRandom;
        }
        
    
    else{
        newLadder = (struct ladder*) malloc (sizeof (struct ladder));
        ladders[i] = newLadder;
        ladderRandom = randomNumber(2,(size-numCols)); 
        ladders[i]->position = ladderRandom;
    }
    }
    printf("ladder list made \n");
    //check for duplicates between snakes and ladders
    for(int s=0;s<snakesNo;s++){
        for(int l=0;l<laddersNo;l++){
            if(snakes[s]->position == ladders[l]->position){
                //if equal change the value to another random position
                ladderRandom = randomNumber(2,size-numCols);
                ladders[l]->position = ladderRandom;
            }
            
        }
    }
    
    for(int s=0;s<snakesNo;s++){
        snakes[s]->backtrack = randomNumber(1,10); //assign a random number between 1-10
        //print snakes position
        printf("Snake %d: from position %d to position %d \n", s+1, snakes[s]->position, (snakes[s]->position - snakes[s]->backtrack));
        //copy into file
        fprintf(fileptr,"Snake %d: from position %d to position %d \n", s+1, snakes[s]->position, (snakes[s]->position - snakes[s]->backtrack) );
    }
    
    for(int l=0; l<laddersNo; l++){
        ladders[l]->forward = randomNumber(1,10);
         printf("ladder %d: from position %d to position %d \n", l+1, ladders[l]->position, (ladders[l]->position + ladders[l]->forward));
         fprintf(fileptr,"ladder %d: from position %d to position %d \n", l+1, ladders[l]->position, (ladders[l]->position + ladders[l]->forward));
    }
    
  
  struct player *playerOne;
  struct player *playerTwo;
  
  //initialise current pos and player number
  playerOne = (struct player*) malloc (sizeof (struct player));
  playerTwo = (struct player*) malloc (sizeof (struct player));
  playerOne->currentPos = 1;
  playerOne->playerNo = 1;
  playerTwo->currentPos = 1;
  playerTwo->playerNo = 2;
  
  printf("The game consists of two players, first player to cross the last square wins! \n");
  
  printf("Player 1 starts\n");
  fprintf(fileptr, "Player 1 starts\n");
  while(1){
      
      getchar();
      int diceRoll, diceRoll2;
      diceRoll=randomNumber(1,6);
      int prevPos, nextPos;
      prevPos = playerOne->currentPos;
      nextPos = prevPos + diceRoll;
      playerOne->currentPos = nextPos;
      printf("Player one has rolled: %d, and was moved from %d to %d \n", diceRoll, prevPos, nextPos);
      fprintf(fileptr, "Player one has rolled: %d, and was moved from %d to %d \n", diceRoll, prevPos, nextPos);
      //check for snakes 
      for(int s=0;s<snakesNo;s++){
         if(playerOne->currentPos == snakes[s]->position ){
             playerOne->currentPos -= snakes[s]->backtrack;
             printf("Oh no player has encountered a snake and has moved back %d steps to square %d \n", snakes[s]->backtrack, playerOne->currentPos);
             fprintf(fileptr,"Oh no player has encountered a snake and has moved back %d steps to square %d \n", snakes[s]->backtrack, playerOne->currentPos);
         }
           
         } 
      
      //check for LADDERS
      
      for(int l=0;l<laddersNo;l++){
         if(playerOne->currentPos == ladders[l]->position ){
             playerOne->currentPos += ladders[l]->forward;
             printf("yay! player has encountered a ladder and has moved forward %d steps to square %d \n", ladders[l]->forward, playerOne->currentPos);
             fprintf(fileptr, "yay! player has encountered a ladder and has moved forward %d steps to square %d \n", ladders[l]->forward, playerOne->currentPos);
         }
           
         } 
    
      
      if(playerOne-> currentPos>=size){
          printf("Player one has won the game!");
          fprintf(fileptr, "Player one has won the game!");
          break;
      }
      
      //repeat for player two
       getchar();
      diceRoll2=randomNumber(1,6);
      //int prevPos, nextPos;
      prevPos = playerTwo->currentPos;
      nextPos = prevPos + diceRoll2;
      playerTwo->currentPos = nextPos;
      printf("Player two has rolled: %d, and was moved from %d to %d \n", diceRoll2, prevPos, nextPos);
      fprintf(fileptr,"Player two has rolled: %d, and was moved from %d to %d \n", diceRoll2, prevPos, nextPos);
      //check for snakes 
      for(int s=0;s<snakesNo;s++){
         if(playerTwo->currentPos == snakes[s]->position ){
             playerTwo->currentPos -= snakes[s]->backtrack;
             printf("Oh no player has encountered a snake and has moved back %d steps to square %d \n", snakes[s]->backtrack, playerTwo->currentPos);
             fprintf(fileptr,"Oh no player has encountered a snake and has moved back %d steps to square %d \n", snakes[s]->backtrack, playerTwo->currentPos);
         }
           
         } 
     
      //check for LADDERS
      
      for(int l=0;l<laddersNo;l++){
         if(playerTwo->currentPos == ladders[l]->position ){
             playerTwo->currentPos += ladders[l]->forward;
             printf("yay! player has encountered a ladder and has moved forward %d steps to square %d \n", ladders[l]->forward, playerTwo->currentPos);
             fprintf(fileptr, "yay! player has encountered a ladder and has moved forward %d steps to square %d \n", ladders[l]->forward, playerTwo->currentPos);
         }
           
         } 
      
      
      if(playerTwo-> currentPos>=size){
          printf("Player two has won the game!");
          fprintf(fileptr, "Player two has won the game!");
          break;
      }
      
  }
  fclose(fileptr); //close file connection
  
}

//main function
int main ()
{
    int rndmNo,size;
    
    
    printf("=======SNAKES AND LADDERS GAME!======= \n");
     
     rndmNo = randomNumber(1,100);
  //check if rndmNo is odd, if so size is 32 square if even size is 64
  if(rndmNo % 2 == 0){
      size = 64;
  }
  else{
      size = 32;
  }
  
  createlist(size);
  showBoard(size);
  getchar();
  snakesAndLadders(5,5,size);
  
   
  return 0;
}

