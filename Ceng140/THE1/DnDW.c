/* Explanations *************************************************************************************************************************************
|
| - The dungeon consists of a "start" room, an "exit" room, one room with "gold", one or more rooms with "wumpuses", and zero or more empty rooms.
| - "Start" and "exit" rooms are empty.
| - Other rooms can be empty, or can contain only a single entity (either gold, or wumpus). A room cannot contain more than one entities.
| - At the beginning of the game, the player sets the total number of rooms, and also the number of wumpuses.
| - Player starts in room "start".
| - All rooms are magical, and they all have 2 doors.
| - Doors might appear randomly in North, East, South or West directions.
| - Doors lead to randomly selected other rooms.
| - If the player visits the room with the gold, the player grabs the gold.
| - If the player visits a room with a wumpus in it, the wumpus eats the player, and the game finishes.
| - If the player visits the "exit" room, the game finishes. If the player has the gold with her, this is a successful finish.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"
#include "Utilities.c"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>   /* For standard input/output functions */

/***************************************************************************************************************************************************/




/* Definitions *************************************************************************************************************************************/

#define AUTHOR       ( "Furkan Göksel" )  /* Author's name                                                                   */

#define MIN_ROOMS    (  2              )  /* Minimum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MAX_ROOMS    (  8              )  /* Maximum number of magical rooms in the dungeon (excluding start and exit rooms) */
#define MIN_WUMPUSES (  1              )  /* Minimum number of wumpuses in the dungeon                                       */
#define MAX_WUMPUSES (  4              )  /* Maximum number of wumpuses in the dungeon                                       */

#define START        ( 'S'             )  /* Label for the start room                                                        */
#define EXIT         ( 'X'             )  /* Label for the exit room                                                         */
#define GOLD         ( 'G'             )  /* Label for the single room containing the gold                                   */
#define WUMPUS       ( 'W'             )  /* Label for room(s) containing a wumpus                                           */
#define EMPTY        ( 'E'             )  /* Label for empty room(s)                                                         */

/***************************************************************************************************************************************************/




/* Type Definitions ********************************************************************************************************************************/

typedef unsigned char boolean ;

/***************************************************************************************************************************************************/




/* Global Variables ********************************************************************************************************************************/

int     numberOfMagicalRooms                            ;
int     numberOfWumpuses                                ;
int     currentRoomNo                                   ;
boolean playerFoundGold                                 ;
char    r0 , r1 , r2 , r3 , r4 , r5 , r6 , r7 , r8 , r9 ; /* r0 is start room, r1 is exit room, others are magical rooms (at most 8 magical rooms) */

/***************************************************************************************************************************************************/




/* Helper (Minor) Functions ************************************************************************************************************************/

/* The input is the room number, and the return value is the label for the room. */

char getRoomInformation ( int roomNo )
{
  switch ( roomNo )
  {
    default :
    case 0  : return r0 ;
    case 1  : return r1 ;
    case 2  : return r2 ;
    case 3  : return r3 ;
    case 4  : return r4 ;
    case 5  : return r5 ;
    case 6  : return r6 ;
    case 7  : return r7 ;
    case 8  : return r8 ;
    case 9  : return r9 ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room label. The function prints out the information associated with the label. */

void printRoomInformation1 ( char room )
{
  switch ( room )
  {
    case START  : printf( "START"  ) ;  break ;
    case EXIT   : printf( "EXIT"   ) ;  break ;
    case GOLD   : printf( "GOLD"   ) ;  break ;
    case WUMPUS : printf( "WUMPUS" ) ;  break ;
    case EMPTY  : printf( "EMPTY"  ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the room number. The function prints out the information associated with the room. */

void printRoomInformation2 ( int roomNo )
{
  switch ( roomNo )
  {
    case 0 : printRoomInformation1( r0 ) ;  break ;
    case 1 : printRoomInformation1( r1 ) ;  break ;
    case 2 : printRoomInformation1( r2 ) ;  break ;
    case 3 : printRoomInformation1( r3 ) ;  break ;
    case 4 : printRoomInformation1( r4 ) ;  break ;
    case 5 : printRoomInformation1( r5 ) ;  break ;
    case 6 : printRoomInformation1( r6 ) ;  break ;
    case 7 : printRoomInformation1( r7 ) ;  break ;
    case 8 : printRoomInformation1( r8 ) ;  break ;
    case 9 : printRoomInformation1( r9 ) ;  break ;
  }
}

/*=================================================================================================================================================*/

/* The input is the direction. The function prints out the direction as a word, as an acronym and also displays an arrowhead. */

void printDirection ( int direction )
{
  switch ( direction )
  {
    case 0 : printf( "NORTH (N) ^" ) ;  break ;
    case 1 : printf( "EAST (E) >"  ) ;  break ;
    case 2 : printf( "SOUTH (S) v" ) ;  break ;
    case 3 : printf( "WEST (W) <"  ) ;  break ;
  }
}

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

/* Prints a banner including the author name. */

void printBanner ( void )
{
  printf(                                                                                   "\n"          ) ;
  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* Dungeons and Dragons with Wumpuses                                          *" "\n"          ) ;
  printf( "* by %-72s  *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

/* Initializes all global variables.                                                                                    */
/* The number of magical rooms and the number of wumpuses are set by the player as part of the configuration process.   */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */

void configureWorld ( void )
{
  /* TODO */
  /* ...  */
    int check_value; /* Checking values for scanf, if it is 0 incorrect input, if it is 1 valid input */
    r0=START;
    r1=EXIT;
    r2=GOLD;
    currentRoomNo = 0;
    playerFoundGold = FALSE;
    printf("Let's configure the DnDW World first!\n");
    printf("Enter number of magical rooms [%d,%d] : ",MIN_ROOMS,MAX_ROOMS);
    check_value = scanf(" %d",&numberOfMagicalRooms);
    while(check_value == 0 || numberOfMagicalRooms < MIN_ROOMS || numberOfMagicalRooms > MAX_ROOMS){
      clearInputBuffer();
      printf("Incorrect input! Please try again.\n");
      printf("Enter number of magical rooms [%d,%d] : ",MIN_ROOMS,MAX_ROOMS);
      check_value = scanf(" %d",&numberOfMagicalRooms);
    }
    printf("Enter number of wumpuses [%d,%d]      : ",MIN_WUMPUSES,MAX_WUMPUSES);
    check_value = scanf(" %d",&numberOfWumpuses);
    while(check_value == 0 || numberOfWumpuses< MIN_WUMPUSES || numberOfWumpuses > MAX_WUMPUSES || numberOfWumpuses >= numberOfMagicalRooms){
      clearInputBuffer();
      printf("Incorrect input! Please try again.\n");
      printf("Enter number of wumpuses [%d,%d]      : ",MIN_WUMPUSES,MAX_WUMPUSES);
      check_value = scanf(" %d",&numberOfWumpuses);
    }
    switch(numberOfMagicalRooms){
      case 2:
        r3=EMPTY;
        break;
      case 3:
        r3=r4=EMPTY;
        break;
      case 4:
        r3=r4=r5=EMPTY;
        break;
      case 5:
        r3=r4=r5=r6=EMPTY;
        break;
      case 6:
        r3=r4=r5=r6=r7=EMPTY;
        break;
      case 7:
        r3=r4=r5=r6=r7=r8=EMPTY;
        break;
      case 8:
        r3=r4=r5=r6=r7=r8=r9=EMPTY;
        break;
    }
    switch(numberOfWumpuses){
      case 1:
        r3=WUMPUS;
        break;
      case 2:
        r3=r4=WUMPUS;
        break;
      case 3:
        r3=r4=r5=WUMPUS;
        break;
      case 4:
        r3=r4=r5=r6=WUMPUS;
        break;
    }
    printf("Configuration is finished. Good luck with the game play!\n\n");
    clearInputBuffer();
}

/*=================================================================================================================================================*/

/* Prints the configured world. */

void printWorld ( void )
{
  int i;
  printf("DnD World:\n");
  printf("----------\n");
  for(i=0;i<numberOfMagicalRooms+2;i++){
    printf("Room %d : ",i);
    printRoomInformation2(i);
    printf("\n");
  }

}

/*=================================================================================================================================================*/

/* Prints the current room information and the doors of the current room.                                               */
/* Gets player's door choice as one of 'N', 'E', 'S', 'W' (small letters should also be accepted).                      */
/* All possible errors in input should be handled by clearing the input buffer and asking the user again for the input. */
/* Prints where the doors were actually opening to.                                                                     */
/* Updates current room number.                                                                                         */
/* If the current room contains gold, lets the player know that she now has gold in her posession.                      */

void getNextMove ( void )
{
  int randomNumber1,randomNumber2,randomRoom1,randomRoom2,check_value,maxnum; /* check_value for checking scanf's value ( as I said before)  */
  char playerChoice,checkcoord1_1,checkcoord1_2,checkcoord2_1,checkcoord2_2; /* checking input direction is correct and avoiding case sensitivity */
  maxnum = numberOfMagicalRooms + 1;
  randomNumber1=randomIntegerMinMaxUnBiased(0,3); /* it is for direction */
  randomNumber2=randomIntegerMinMaxUnBiasedExcept1(0,3,randomNumber1); /* it is for direction2 */
  randomRoom1=randomIntegerMinMaxUnBiasedExcept1(0,maxnum,currentRoomNo);
  randomRoom2=randomIntegerMinMaxUnBiasedExcept2(0,maxnum,currentRoomNo,randomRoom1);
  checkcoord1_1 = checkcoord1_2 = checkcoord2_1 = checkcoord2_2 = ' ';
  switch(randomNumber1){
    case 0:
      checkcoord1_1 = 'N';
      checkcoord1_2 = 'n';
      break;
    case 1:
      checkcoord1_1 = 'E';
      checkcoord1_2 = 'e';
      break;
    case 2:
      checkcoord1_1 = 'S';
      checkcoord1_2 = 's';
      break;
    case 3:
      checkcoord1_1 = 'W';
      checkcoord1_2 = 'w';
      break;
  }
  switch(randomNumber2){
    case 0:
      checkcoord2_1 = 'N';
      checkcoord2_2 = 'n';
      break;
    case 1:
      checkcoord2_1 = 'E';
      checkcoord2_2 = 'e';
      break;
    case 2:
      checkcoord2_1 = 'S';
      checkcoord2_2 = 's';
      break;
    case 3:
      checkcoord2_1 = 'W';
      checkcoord2_2 = 'w';
      break;
  }

  printf("\nYou are in Room %d\n",currentRoomNo);
  printf("Room information : ");
  printRoomInformation2(currentRoomNo);
  printf("\n");
  printf("There is a door to your ");
  printDirection(randomNumber1);
  printf("\n");
  printf("And, there is another door to your ");
  printDirection(randomNumber2);
  printf("\nWhich one will you choose? : ");
  check_value = scanf(" %c",&playerChoice);
  while((playerChoice != checkcoord1_1 && playerChoice != checkcoord1_2 && playerChoice != checkcoord2_1 && playerChoice != checkcoord2_2)|| check_value == 0){
      clearInputBuffer();
      printf("Incorrect input! Please try again : ");
      check_value = scanf(" %c",&playerChoice);
  }
  printf("Room to your ");
  printDirection(randomNumber1);
  printf(" was Room %d\n",randomRoom1);
  printf("Room to your ");
  printDirection(randomNumber2);
  printf(" was Room %d\n",randomRoom2);
  if(playerChoice == checkcoord1_1 || playerChoice == checkcoord1_2){
    currentRoomNo = randomRoom1;
  }
  else if(playerChoice == checkcoord2_1 || playerChoice == checkcoord2_2){
    currentRoomNo = randomRoom2;
  }
  if(currentRoomNo == 2){
    if(playerFoundGold == FALSE){
    playerFoundGold = TRUE;
    printf("You have GOLD now!\n"); }
  }

  clearInputBuffer();
}

/*=================================================================================================================================================*/

/* Checks if the current room that the player is in is the exit room.                                           */
/* If so, checks if the player already has the gold or not, and prints out an appropriate message in each case. */
/* Also checks if the player is in a room with a wumpus.                                                        */
/* If so, informs the player about the unhappy ending of the game.                                              */
/* Returns TRUE if the game ended, otherwise, does not print anything and just returns FALSE.                   */

boolean checkAndPrintGameResult ( void )
{
  if(currentRoomNo == 1){
    if(playerFoundGold){
      printf("You are safely out of the dungeon with the GOLD! Congratulations!\n");
      return TRUE;
    }
    else{
      printf("You are safely out of the dungeon, but you did not find the GOLD! Better luck next time!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 2){
    if(r2 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 3){
    if(r3 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 4){
    if(r4 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 5){
    if(r5 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 6){
    if(r6 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 7){
    if(r7 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 8){
    if(r8 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  if(currentRoomNo == 9){
    if(r9 == WUMPUS){
      printf("Wumpus is full, and you are in heaven! What a pity!\n");
      return TRUE;
    }
  }
  return FALSE;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

/* Prints banner.                                                                */
/* Configures the dungeon world.                                                 */
/* Prints the configured world.                                                  */
/* Asks the player to make a move until the game finishes .                      */
/* Prints the game result.                                                       */
/* Prints a goodbye message.                                                     */
/* Prints the number of random numbers that were generated during the game play. */

int main ( void )
{
  /* TODO */
  /* ...  */
  printBanner();
  configureWorld();
  printWorld();
  do{
    getNextMove();
    if(checkAndPrintGameResult()){
      break;
    }
  }while(1);
  printf( "\nGood game. Have a nice day!\n\n" ) ;
  printf( "%d random numbers were generated during the game play.\n\n" , numberOfRandomNumbersGenerated ) ;
  return 0;
}

/***************************************************************************************************************************************************/
