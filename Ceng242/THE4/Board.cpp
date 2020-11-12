#include"Board.h"
#include <iostream>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Board::Board(uint _size, std::vector<Player*>* _players, Coordinate chest):chest(chest){
  this->size = _size;
  this->players = _players;
}
Board::~Board(){
/*for(int i=0; i< players->size();i++){
    delete (*players)[i];
  }
  delete players; */
}

bool Board::isCoordinateInBoard(const Coordinate& c){
  if(c.x <= (this->size -1) && c.x >= 0 && c.y <= (this->size -1) && c.y >= 0){
    return true;
  }
  else{
    return false;
  }
}
bool Board::isPlayerOnCoordinate(const Coordinate& c){
  for(int i=0; i< players->size();i++){
    if((*players)[i]->getCoord() == c){
      return true;
    }
  }
  return false;
}
Player *Board::operator [](const Coordinate& c){
  for(int i=0; i< players->size();i++){
    if((*players)[i]->getCoord() == c){
      return (*players)[i];
    }
  }
  return NULL;
}

Coordinate Board::getChestCoordinates(){
  return this->chest;
}
void Board::printBoardwithID(){
  int sizeForBoard = this->size;
  for(int y=0;y<sizeForBoard;y++){
    for(int x=0;x<sizeForBoard;x++){
      if((*this)[Coordinate(x,y)]){
          std::cout << ((*this)[Coordinate(x,y)])->getBoardID();
      }
      else if(chest == Coordinate(x,y)){
        std::cout << "Ch";
      }
      else{
        std::cout << "__";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}
void Board::printBoardwithClass(){
  int sizeForBoard = this->size;
  for(int y=0;y<sizeForBoard;y++){
    for(int x=0;x<sizeForBoard;x++){
      if((*this)[Coordinate(x,y)]){
          std::cout << ((*this)[Coordinate(x,y)])->getClassAbbreviation();
      }
      else if(chest == Coordinate(x,y)){
        std::cout << "Ch";
      }
      else{
        std::cout << "__";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}
