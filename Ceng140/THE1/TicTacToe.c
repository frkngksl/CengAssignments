/* Explanations *************************************************************************************************************************************
|
| The Tic-Tac-Toe board has 9 cells. We will assume that the cell numbering is as follows:
|
|   c0 | c1 | c2
|   ------------
|   c3 | c4 | c5
|   ------------
|   c6 | c7 | c8
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"
#include "Utilities.c"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR  ( "Furkan Göksel" )  /* Author's name                                   */

#define EMPTY   ( ' '             )  /* Label for empty cells                           */
#define PLAYER1 ( 'X'             )  /* Label for player 1 and cells marked by player 1 */
#define PLAYER2 ( 'O'             )  /* Label for player 2 and cells marked by player 2 */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

char c0 , c1 , c2 , c3 , c4 , c5 , c6 , c7 , c8 ;  /* Cells of the Tic-Tac-Toe board */

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Initializes the global variables. */

void initializeGlobalVariables ( void )
{
  /* TODO */
  /* ...  */
  c0 = c1 = c2 = c3 = c4 = c5 = c6 = c7 = c8 = EMPTY;
}

/*=================================================================================================================================================*/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Tic-Tac-Toe                                                                 *" "\n"          ) ;
  printf( "* by %-72s  *"                                                                     "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

/* Prints the current board configuration. */
/* TODO */
/* ...  */
void printBoard ( void )
{
  int i,k,number=0;
  printf("\n");
  for(i=0;i<4;i++){
    printf(" ");
  }
  printf("Cells");
  for(i=0;i<20;i++){
    printf(" ");
  }
  printf("Board\n");
  printf(".");
  for(i=0;i<=10;i++){
    printf("-");}
  printf(".");
  for(i=0;i<12;i++){
    printf(" ");}
  printf(".");
  for(i=0;i<=10;i++){
    printf("-");}
  printf(".\n");
  /* alt kısım */
  for(k=0;k<3;k++){
    for(i=0;i<=3;i++){
      if(i==3){
      printf("|   ");
      }else {
      printf("| %d ",number); /* cell number */
      number++;
        }
      }
      for(i=0;i<9;i++){
        printf(" ");} /* Boşluk */
      for(i=0;i<=3;i++){
        if(k == 0){
          if(i == 0){
            printf("| %c ",c0 );
          }
          else if (i == 1){
            printf("| %c ",c1 );
          }
          else if (i == 2){
            printf("| %c ",c2 );
          }
          else {
            printf("|   ");}
          }
        if(k == 1){
          if(i == 0){
              printf("| %c ",c3 );
          }
          else if (i == 1){
              printf("| %c ",c4 );
          }
          else if (i == 2){
              printf("| %c ",c5 );
          }
          else {
            printf("|   ");}
          }
          if(k == 2){
            if(i == 0){
              printf("| %c ",c6 );
            }
            else if (i == 1){
              printf("| %c ",c7 );
            }
            else if (i == 2){
              printf("| %c ",c8 );
            }
            else {
              printf("|   ");}
            }
        }
      printf("\n");
      if(k==2){
        printf("'");
      }else{
      printf("|");} /* Board */
      for(i=0;i<=10;i++){
        printf("-");}
        if(k==2){
          printf("'");
        }else{
        printf("|");};
      for(i=0;i<12;i++){
        printf(" ");}
        if(k==2){
          printf("'");
        }else{
        printf("|");}
      for(i=0;i<=10;i++){
        printf("-");}
        if(k==2){
          printf("'\n");
        }else{
        printf("|\n");}
  }
  printf("\n");
}

/*=================================================================================================================================================*/

/* Gets the next move of "player", and marks it on the board.                     */
/* Loops (and asks again) if the input is not valid, or if the cell is not empty. */

void getNextMove ( char player )
{
  int check_input; /* Checking values for scanf, if it is 0 incorrect input, if it is 1 valid input */
  int cell;
  printf("Player %c, enter your next move (0-8) : ", player );
  check_input = scanf(" %d",&cell);
  while(TRUE){
    if(check_input == 0){
      printf("\nIncorrect input! Please try again.\n\n");
      clearInputBuffer();
      printf("Player %c, enter your next move (0-8) : ", player );
      check_input = scanf(" %d",&cell);
      continue;
    }
    else if(cell == 0){
      if(c0 == EMPTY){
        c0 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 1){
      if(c1 == EMPTY){
        c1 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 2){
      if(c2 == EMPTY){
        c2 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 3){
      if(c3 == EMPTY){
        c3 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 4){
      if(c4 == EMPTY){
        c4 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 5){
      if(c5 == EMPTY){
        c5 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 6){
      if(c6 == EMPTY){
        c6 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 7){
      if(c7 == EMPTY){
        c7 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else if(cell == 8){
      if(c8 == EMPTY){
        c8 = player;
        clearInputBuffer();
        break;
      }
      else{
        printf("\nCell is not empty! Please try again.\n\n");
        clearInputBuffer();
        printf("Player %c, enter your next move (0-8) : ", player );
        check_input = scanf(" %d",&cell);
        continue;
      }
    }
    else{
      printf("\nIncorrect input! Please try again.\n\n");
      clearInputBuffer();
      printf("Player %c, enter your next move (0-8) : ", player );
      check_input = scanf(" %d",&cell);
      continue;
    }
  }
}

/*=================================================================================================================================================*/

/* Checks if one of the players wins the game, or if the board is full and the game ended with a draw. Prints how the game ended. */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                                     */

boolean checkAndPrintGameResult ( void )
{
  /* TODO */
  /* ...  */
  if(c0 == c1 && c1 == c2){
    if(c0 != EMPTY && c1 != EMPTY && c2 != EMPTY){
    printf("Player %c WINS (top row)!\n",c0);
    return TRUE;}
  }
  if(c3 == c4 && c4 == c5){
    if(c3 != EMPTY && c4 != EMPTY && c5 != EMPTY){
    printf("Player %c WINS (middle row)!\n",c3);
    return TRUE;}
  }
  if(c6 == c7 && c7 == c8){
    if(c6 != EMPTY && c7 != EMPTY && c8 != EMPTY){
    printf("Player %c WINS (bottom row)!\n",c6);
    return TRUE;}
  }
  if(c0 == c3 && c3 == c6){
    if(c0 != EMPTY && c3 != EMPTY && c6 != EMPTY){
    printf("Player %c WINS (left column)!\n",c0);
    return TRUE;}
  }
  if(c2 == c5 && c5 == c8){
    if(c2 != EMPTY && c5 != EMPTY && c8 != EMPTY){
    printf("Player %c WINS (right column)!\n",c2);
    return TRUE;}
  }
  if (c1 == c4 && c4 == c7){
    if(c1 != EMPTY && c4 != EMPTY && c7 != EMPTY){
    printf("Player %c WINS (middle column)!\n",c1);
    return TRUE;}
  }
  if (c0 == c4 && c4 == c8){
    if(c0 != EMPTY && c4 != EMPTY && c8 != EMPTY){
    printf("Player %c WINS (primary diagonal)!\n",c0);
    return TRUE;}
  }
  if (c2 == c4 && c4 == c6){
    if(c2 != EMPTY && c4 != EMPTY && c6 != EMPTY){
    printf("Player %c WINS (secondary diagonal)!\n",c2);
    return TRUE;}
  }
  if(c0 != EMPTY && c1 != EMPTY && c2 != EMPTY && c3 != EMPTY && c4 != EMPTY && c5 != EMPTY && c6 != EMPTY && c7 != EMPTY && c8 != EMPTY){
    printf("DRAW!\n");
    return TRUE;
  }
  return FALSE;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Initializes the global variables.                                                                                                          */
/* Prints banner.                                                                                                                             */
/* Randomly chooses one of the players to start first.                                                                                        */
/* Asks each player to make a move in turn until the game finishes (prints the board configuration each time before a player makes her move). */
/* Prints the game result.                                                                                                                    */
/* Prints a goodbye message.                                                                                                                  */
/* Prints the number of random numbers that were generated during the game play.                                                              */

int main ( void )
{
  char currentPlayer = ( ( randomIntegerMinMaxUnBiased( 0 , 1 ) == 0 ) ? PLAYER1 : PLAYER2 ) ;

  initializeGlobalVariables() ;
  printBanner              () ;
  printBoard               () ;

  do
  {
    getNextMove( currentPlayer ) ;
    printBoard (               ) ;

    if   ( currentPlayer == PLAYER1 )  { currentPlayer = PLAYER2 ; }
    else                               { currentPlayer = PLAYER1 ; }
  }
  while ( checkAndPrintGameResult() == FALSE ) ;

  printf( "\nGood game. Have a nice day!\n" ) ;

  printf( "\n%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/
