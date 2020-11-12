#include"InputParser.h"
#include <iostream>
#include <string>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Game* InputParser::parseGame(){
  std::string sizeForBoard,coordForChest,x,y,numberOfPlayers,maximumTurn;
  int counterx,countery,numberOfAdd;
  std::getline(std::cin, sizeForBoard);
  std::getline(std::cin, coordForChest);
  counterx = coordForChest.find(" ");
  x = coordForChest.substr(0,counterx);
  coordForChest = coordForChest.substr(counterx+1,coordForChest.size()-1);
  countery = coordForChest.find(" ");
  y = coordForChest.substr(0,countery);
  std::getline(std::cin, maximumTurn);
  Game* newGame = new Game(std::stoi(maximumTurn),std::stoi(sizeForBoard),Coordinate(std::stoi(x),std::stoi(y)));
  std::getline(std::cin, maximumTurn);
  numberOfAdd = std::stoi(maximumTurn);
  for(int i=0;i<numberOfAdd;i++){
    std::string parsingString,idOfPlayer,classOfplayer,teamOfPlayer,xCord,yCord;
    int indexOfSpace;
    Team teamof;
    std::getline(std::cin, parsingString);
    indexOfSpace = parsingString.find(" ");
    idOfPlayer=parsingString.substr(0,indexOfSpace);
    parsingString = parsingString.substr(indexOfSpace+1,parsingString.size()-1);
    indexOfSpace = parsingString.find(" ");
    classOfplayer=parsingString.substr(0,indexOfSpace);
    parsingString = parsingString.substr(indexOfSpace+1,parsingString.size()-1);
    indexOfSpace = parsingString.find(" ");
    teamOfPlayer=parsingString.substr(0,indexOfSpace);
    parsingString = parsingString.substr(indexOfSpace+1,parsingString.size()-1);
    indexOfSpace = parsingString.find(" ");
    xCord=parsingString.substr(0,indexOfSpace);
    parsingString = parsingString.substr(indexOfSpace+1,parsingString.size()-1);
    indexOfSpace = parsingString.find(" ");
    yCord=parsingString.substr(0,indexOfSpace);
    if(teamOfPlayer == "BARBARIAN"){
      teamof = BARBARIANS;
    }
    else{
      teamof = KNIGHTS;
    }
    newGame->addPlayer(std::stoi(idOfPlayer),std::stoi(xCord),std::stoi(yCord),teamof,classOfplayer);
  }
  return newGame;
}
