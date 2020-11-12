/* Explanations *************************************************************************************************************************************
|
| This file implements CengBook, which is a realistic simulation of a mini social-media application.
|
****************************************************************************************************************************************************/




/* Includes ****************************************************************************************************************************************/

#include "Utilities.h"

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/




/* Macro Definitions *******************************************************************************************************************************/

#define AUTHOR ( "Furkan Göksel" )  /* Author's name */  /* TODO: Replace with your name */

/***************************************************************************************************************************************************/




/* Global Variable Definitions *********************************************************************************************************************/

BookPtr bookPtr ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#if   defined(_WIN16) || defined(_WIN32) || defined(_WIN64)

  char operatingSystem[] = "Windows" ;  /* This is a Windows environment.                            */

#elif defined(__linux__)

  char operatingSystem[] = "Linux"   ;  /* This is a Linux environment (any GNU/Linux distribution). */

#elif defined(__APPLE__)

  char operatingSystem[] = "MacOSX"  ;  /* This is a Mac OS X environment.                           */

#endif

/***************************************************************************************************************************************************/




/* Functions ***************************************************************************************************************************************/

void printUsage ( String applicationName )
{
  NL ;

  printf( "Usage: %s <MaxNumberOfUsers> <MaxUserNameLength> <MaxNumberOfFriendsPerUser>\n\n" , applicationName ) ;
}

/*=================================================================================================================================================*/

void printBanner ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n"          ) ;
  printf( "* CengBook                                                                    *" "\n"          ) ;
  printf( "* by %-72s *"                                                                    "\n" , AUTHOR ) ;
  printf( "*******************************************************************************" "\n"          ) ;
}

/*=================================================================================================================================================*/

void printMenu ( void )
{
  NL ;

  printf( "*******************************************************************************" "\n" ) ;
  printf( "Help                       : Print this menu"                                    "\n" ) ;
  printf( "List                       : List all users"                                     "\n" ) ;
  printf( "Plot                       : Create a plot of CengBook (requires GraphViz)"      "\n" ) ;
  printf( "Quit                       : Exit application"                                   "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Register   <user>          : Create a new user and add it to CengBook"           "\n" ) ;
  printf( "Delete     <user>          : Delete user from CengBook"                          "\n" ) ;
  printf( "Find       <user>          : Search CengBook for user, display user information" "\n" ) ;
  printf( "Connect    <user1> <user2> : Add a connection from user1 to user2"               "\n" ) ;
  printf( "Disconnect <user1> <user2> : Remove connection from user1 to user2"              "\n" ) ;
  printf( "Path       <user1> <user2> : Find shortest path from user1 to user2"             "\n" ) ;
  printf( "-------------------------------------------------------------------------------" "\n" ) ;
  printf( "Sort <abc|pop> <asc|desc>  : Sort all users (alphabetically or by popularity)"   "\n" ) ;
  printf( "*******************************************************************************" "\n" ) ;
}

/*=================================================================================================================================================*/

void commandHelp ( void )
{
  printMenu();
}

/*=================================================================================================================================================*/

void commandList ( void )
{
  int i;
  NL;
  if(bookPtr->numberOfUsers == 0){
    I2; printf("CengBook is empty\n");
  }
  for(i=0;i<bookPtr->numberOfUsers;i++){
     I2 ;  printf( "%-15s : %u Follower(s) , %u Friend(s)\n" , bookPtr->userPointers[i]->name , bookPtr->userPointers[i]->numberOfFollowers , bookPtr->userPointers[i]->numberOfFriends ) ;
  }
}

/*=================================================================================================================================================*/

void commandPlot ( void )
{
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  UserPtr   userPtr             , friendPtr              ;
  int       userIndex           , friendIndex            ;
  String    runDotSystemCommand , openImageSystemCommand ;

  FILE    * file = fopen( "CengBook.dot" , "w" )         ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "digraph CengBook"                                                       "\n"                            ) ;
  fprintf( file , "{"                                                                      "\n"                            ) ;
  fprintf( file , "  graph [label=\"CengBook\\nNumber of users = %d\" , labelloc=t] ;"     "\n\n" , bookPtr->numberOfUsers ) ;
  fprintf( file , "  node  [shape=ellipse , fontcolor=black , color=red , penwidth=2.0] ;" "\n\n"                          ) ;
  fprintf( file , "  edge  [color=blue , penwidth=2.0] ;"                                  "\n\n"                          ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    fprintf( file , "  %s [label=\"%s\\n%d Friend(s)\\n%d Follower(s)\"] ;\n" ,
             userPtr->name                                                    ,
             userPtr->name                                                    ,
             userPtr->numberOfFriends                                         ,
             userPtr->numberOfFollowers                                       ) ;
  }

  if ( bookPtr->numberOfUsers > 0 )  { fprintf( file , "\n" ) ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  for ( userIndex = 0 ; userIndex < bookPtr->numberOfUsers ; userIndex++ )
  {
    userPtr = bookPtr->userPointers[ userIndex ] ;

    for ( friendIndex = 0 ; friendIndex < userPtr->numberOfFriends ; friendIndex++ )
    {
      friendPtr = userPtr->friendPointers[ friendIndex ] ;

      fprintf( file , "  %s -> %s ;\n" , userPtr->name , friendPtr->name ) ;
    }
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fprintf( file , "}\n" ) ;
  fclose ( file         ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  if ( strcmp( operatingSystem , "Windows" ) == 0 )
  {
    runDotSystemCommand    = "CMD /C dot -Tgif CengBook.dot -o CengBook.gif" ;
    openImageSystemCommand = "CMD /C START CengBook.gif"                     ;
  }
  else  /* Assumption: Linux */
  {
    runDotSystemCommand    = "dot -Tgif CengBook.dot -o CengBook.gif"        ;
    openImageSystemCommand = "xdg-open CengBook.gif &"                       ;
  }

  if ( system( runDotSystemCommand    ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
  if ( system( openImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */

  NL ;  I2 ;  printf( "Plot prepared\n" ) ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/*=================================================================================================================================================*/

void commandQuit ( void )
{
  deallocateBook(bookPtr);
  NL;
  I2; printf("Have a nice day\n\n");
  exit(0);
}

/*=================================================================================================================================================*/

void commandRegister ( String userName )
{
    boolean inList = FALSE;
    int i;
    for(i=0;i<bookPtr->numberOfUsers;i++){
        if(strcmp(userName,bookPtr->userPointers[i]->name) == 0) {
          inList = TRUE;
          break; /* after writing this code part, I realized that you have already implement a function for that and I don't want to delete :( */
         }
    }
    if(inList == TRUE){
      NL;
      I2; printf("User '%s' already registered!\n",userName);
    }
    else if(strlen(userName)>getMaxUserNameLength()){
      NL;
      I2; printf("User name is longer than %d characters!\n",getMaxUserNameLength());
    }
    else if(bookPtr->numberOfUsers>=getMaxNumberOfUsers()){
      NL;
      I2; printf("CengBook is full, cannot register any new users!\n");
    }
    else{
      bookPtr->userPointers[bookPtr->numberOfUsers]=allocateUser(userName);
      if(bookPtr->userPointers[bookPtr->numberOfUsers]==NULL){
        NL;
        I2; printf("User '%s' cannot be allocated!\n",userName);
      }
      else{
      bookPtr->numberOfUsers++;
      NL;
      I2; printf("User '%s' registered successfully\n",userName);}
    }
}

/*=================================================================================================================================================*/

void commandDelete ( String userName )
{
  UserPtr userNamePtr = getUserPtrByName(bookPtr,userName);
  NL;
  if(userNamePtr == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName);
  }
  else{
      int userNameIndex = getUserIndexByPtr(bookPtr,userNamePtr);
      int i = 0;
      while(i < bookPtr->numberOfUsers){
        if(isConnected(bookPtr->userPointers[i],userNamePtr)){
          removeConnection(bookPtr->userPointers[i],userNamePtr);
          I2; printf("User '%s' is removed from friends of user '%s'\n",userName,bookPtr->userPointers[i]->name);
          i++;
        }
        else{
          i++; }
      }
      i=0;
      while(i < userNamePtr->numberOfFriends){
       (userNamePtr->friendPointers[i]->numberOfFollowers)--;
       I2; printf("User '%s' is discounted from followers of user '%s'\n",userName,userNamePtr->friendPointers[i]->name);
       i++;
        }
      for ( i = userNameIndex ; i < bookPtr->numberOfUsers - 1 ; i++ )
      {
        bookPtr->userPointers[i] = bookPtr->userPointers[i+1] ;
      }

      bookPtr->userPointers[ --(bookPtr->numberOfUsers) ] = NULL ;
      deallocateUser(userNamePtr);
      I2; printf("User '%s' is deleted from CengBook\n",userName);
  }
}

/*=================================================================================================================================================*/

void commandFind ( String userName )
{
  int i;
  boolean isFind = FALSE;
  NL;
  for(i=0;i<bookPtr->numberOfUsers;i++){
    if(strcmp(userName,bookPtr->userPointers[i]->name)==0){
      printUser(bookPtr->userPointers[i]);
      isFind = TRUE;
      break;
    }
  }
  if(isFind == FALSE){
    I2;   printf("User '%s' not found in CengBook!\n",userName);
  }
}

/*=================================================================================================================================================*/

void commandConnect ( String userName1 , String userName2 )
{
  UserPtr userNamePtr1 = getUserPtrByName(bookPtr,userName1);
  UserPtr userNamePtr2 = getUserPtrByName(bookPtr,userName2);
  int limit = getMaxNumberOfFriendsPerUser();
  NL;
  if(userNamePtr1 == NULL || userNamePtr2 == NULL){
    if(userNamePtr1 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName1);}
    if(userNamePtr2 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName2);}
  }
  else if(strcmp(userName1,userName2) == 0){
    I2; printf("Connection to self is not allowed!\n");
  }
  else if(isConnected(userNamePtr1,userNamePtr2)){
    I2; printf("User '%s' is already connected to user '%s'!\n",userName1,userName2);
  }
  else if(userNamePtr1->numberOfFriends>=limit){
    I2; printf("Friend capacity of user '%s' is full!\n",userName1);
  }
  else{
    userNamePtr1->friendPointers[userNamePtr1->numberOfFriends] = userNamePtr2;
    userNamePtr1->numberOfFriends++;
    userNamePtr2->numberOfFollowers++;
    I2; printf("User '%s' successfully connected to user '%s'\n",userName1,userName2);
  }
}

/*=================================================================================================================================================*/

void commandDisconnect ( String userName1 , String userName2 )
{
  UserPtr userNamePtr1 = getUserPtrByName(bookPtr,userName1);
  UserPtr userNamePtr2 = getUserPtrByName(bookPtr,userName2);
  NL;
  if(userNamePtr1 == NULL || userNamePtr2 == NULL){
    if(userNamePtr1 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName1);}
    if(userNamePtr2 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName2);}
  }
  else if(strcmp(userName1,userName2) == 0){
    I2; printf("Disconnecting from self is not allowed!\n");
  }
  else if(isConnected(userNamePtr1,userNamePtr2) == FALSE){
    I2; printf("User '%s' and user '%s' are not connected!\n",userName1,userName2);
  }
  else{
    if(removeConnection(userNamePtr1,userNamePtr2)){
    I2; printf("User '%s' successfully disconnected from user '%s'\n",userName1,userName2);}
  }
}

/*=================================================================================================================================================*/

void commandPath ( String userName1 , String userName2 )
{
  UserPtr userNamePtr1 = getUserPtrByName(bookPtr,userName1);
  UserPtr userNamePtr2 = getUserPtrByName(bookPtr,userName2);
  int i = 0;
  NL;
  if(userNamePtr1 == NULL || userNamePtr2 == NULL){
    if(userNamePtr1 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName1);}
    if(userNamePtr2 == NULL){
    I2; printf("User '%s' not found in CengBook!\n",userName2);}
  }
  else if(strcmp(userName1,userName2) == 0){
    I2; printf("Path to self queried!\n");
  }
  else{
    UserPtrArray pathList = shortestPath(bookPtr,userNamePtr1,userNamePtr2);
    if(pathList == NULL){
    I2; printf("There is no path from user '%s' to user '%s'\n",userName1,userName2); }
    else{
      I2;
        while(TRUE){
          if(pathList[i+1]==NULL){
          printf("'%s'\n",pathList[i]->name);
          break;  }
          printf("'%s' -> ",pathList[i++]->name);
      }
    }
  }
}

/*=================================================================================================================================================*/

void commandSort ( String criterion , String order )
{
    NL;
    if(strcmp(criterion,"abc") == 0){
      if(strcmp(order,"asc") == 0){
        sortBook(bookPtr,compareByName,TRUE);
        I2; printf("CengBook sorted 'alphabetically' in 'ascending' order\n");
      }
      else if(strcmp(order,"desc") == 0){
        sortBook(bookPtr,compareByName,FALSE);
        I2; printf("CengBook sorted 'alphabetically' in 'descending' order\n");
      }
      else{
        I2; printf("Invalid sort order '%s'!\n",order);
      }
    }
    else if(strcmp(criterion,"pop") == 0){
      if(strcmp(order,"asc") == 0){
        sortBook(bookPtr,compareByPopularity,TRUE);
        I2; printf("CengBook sorted 'by popularity' in 'ascending' order\n");
      }
      else if(strcmp(order,"desc") == 0){
        sortBook(bookPtr,compareByPopularity,FALSE);
        I2; printf("CengBook sorted 'by popularity' in 'descending' order\n");
      }
      else{
        I2; printf("Invalid sort order '%s'!\n",order);
      }
    }
    else{
      I2; printf("Invalid sort criterion '%s'!\n",criterion);
      if(strcmp(order,"asc") == 0){;}
      else if(strcmp(order,"desc") == 0){;}
      else{
        I2; printf("Invalid sort order '%s'!\n",order);
      }
    }
}

/*=================================================================================================================================================*/

void processInput ( String input )
{
  int         i                                                    ;
  int         numberOfTokens = 0                                   ;
  StringArray tokens         = tokenize( input , &numberOfTokens ) ;
  String      command                                              ;

  if ( numberOfTokens < 1 )  { return ; }

  command = tokens[0] ;

  for ( i = 0 ; i < strlen( command ) ; i++ )  { if ( ( command[i] >= 'A' ) && ( command[i] <= 'Z' ) )  { command[i] += 'a' - 'A' ; } }

  if      ( strcmp( command , "help"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandHelp      (                       ) ;  return ; } }
  else if ( strcmp( command , "list"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandList      (                       ) ;  return ; } }
  else if ( strcmp( command , "plot"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandPlot      (                       ) ;  return ; } }
  else if ( strcmp( command , "quit"       ) == 0 )  { if ( numberOfTokens == 1 ) { commandQuit      (                       ) ;  return ; } }
  else if ( strcmp( command , "register"   ) == 0 )  { if ( numberOfTokens == 2 ) { commandRegister  ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "delete"     ) == 0 )  { if ( numberOfTokens == 2 ) { commandDelete    ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "find"       ) == 0 )  { if ( numberOfTokens == 2 ) { commandFind      ( tokens[1]             ) ;  return ; } }
  else if ( strcmp( command , "connect"    ) == 0 )  { if ( numberOfTokens == 3 ) { commandConnect   ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "disconnect" ) == 0 )  { if ( numberOfTokens == 3 ) { commandDisconnect( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "path"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandPath      ( tokens[1] , tokens[2] ) ;  return ; } }
  else if ( strcmp( command , "sort"       ) == 0 )  { if ( numberOfTokens == 3 ) { commandSort      ( tokens[1] , tokens[2] ) ;  return ; } }
  else                                               { NL ;  I2 ;  printf( "Invalid command!\n" ) ;                               return ;   }

  /* If we reach here, the user must have provided incorrect number of arguments to a valid command */

  command[0] += 'A' - 'a' ;

  NL ;  I2 ;  printf( "Incorrect number of arguments provided for the command '%s'!\n" , command ) ;
}

/***************************************************************************************************************************************************/




/* Main Function ***********************************************************************************************************************************/

int main ( int argc , char * argv[] )
{
  char input [ MAX_INPUT_LENGTH ] ;

  if ( argc < 4 )  { printUsage( argv[0] ) ;  return 0 ; }

  configureCengBook( /* maxNumberOfUsers          */ atoi( argv[1] ) ,
                     /* maxUserNameLength         */ atoi( argv[2] ) ,
                     /* maxNumberOfFriendsPerUser */ atoi( argv[3] ) ) ;

  bookPtr = allocateBook() ;

  if ( bookPtr == NULL )  { NL ;  printf( "Error: Cannot allocate memory to store CengBook! Exiting!\n\n" ) ;  exit( 0 ) ; }

  printBanner() ;
  printMenu  () ;

  while ( TRUE )
  {
    NL                        ;  /* New line     */
    printf( "[CENGBOOK] > " ) ;  /* Print prompt */

    if ( fgets( input , MAX_INPUT_LENGTH , stdin ) == NULL )  /* Read input line, 'fgets' is safer than 'gets'. */
    {
      /* In the following two lines, the "if" statements surrounding the "freopen" function calls are used to eliminate warnings. */

      if   ( strcmp( operatingSystem , "Windows" ) == 0 )  { if ( freopen( "CON"      , "r" , stdin ) == NULL ) ; }
      else /* Assumption:               Linux          */  { if ( freopen( "/dev/tty" , "r" , stdin ) == NULL ) ; }

      continue ;
    }

    processInput( input ) ;  /* Tokenize and process the input command */
  }

  return 0 ;
}

/***************************************************************************************************************************************************/
