#include"Priest.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Priest::Priest(uint id,int x, int y, Team team):Player(id,x,y,team){
  this->attackDamage = 0;
  this->healPower = 50;
  this->maxHP = 150;
  this->HP = 150;
  goalPriorityList.push_back(HEAL);
  goalPriorityList.push_back(TO_ALLY);
  goalPriorityList.push_back(CHEST);
  healableCoordinates.push_back(Coordinate(x,y+1));
  healableCoordinates.push_back(Coordinate(x,y-1));
  healableCoordinates.push_back(Coordinate(x+1,y));
  healableCoordinates.push_back(Coordinate(x-1,y));
  healableCoordinates.push_back(Coordinate(x+1,y+1));
  healableCoordinates.push_back(Coordinate(x-1,y+1));
  healableCoordinates.push_back(Coordinate(x-1,y-1));
  healableCoordinates.push_back(Coordinate(x+1,y-1));

  moveableCoordinates.push_back(Coordinate(x,y+1));
  moveableCoordinates.push_back(Coordinate(x,y-1));
  moveableCoordinates.push_back(Coordinate(x+1,y));
  moveableCoordinates.push_back(Coordinate(x-1,y));
  moveableCoordinates.push_back(Coordinate(x+1,y+1));
  moveableCoordinates.push_back(Coordinate(x-1,y+1));
  moveableCoordinates.push_back(Coordinate(x-1,y-1));
  moveableCoordinates.push_back(Coordinate(x+1,y-1));
  if(team == BARBARIANS){
    classAbbreviation = "PR";
  }
  else{
    classAbbreviation = "pr";
  }
}
Priest::~Priest(){};

int Priest::getAttackDamage() const{
  return attackDamage;
}
int Priest::getHealPower() const{
  return healPower;
}
int Priest::getMaxHP() const{
  return maxHP;
}
std::vector<Goal> Priest::getGoalPriorityList(){
  return goalPriorityList;
}
const std::string Priest::getClassAbbreviation() const{
  return classAbbreviation;
}
std::vector<Coordinate> Priest::getAttackableCoordinates(){
  return attackableCoordinates;
}
std::vector<Coordinate> Priest::getMoveableCoordinates(){
  moveableCoordinates.clear();
  Coordinate currentCoord = this->getCoord();

  moveableCoordinates.push_back(currentCoord + Coordinate(0,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,-1));
  return moveableCoordinates;
}
std::vector<Coordinate> Priest::getHealableCoordinates(){
  healableCoordinates.clear();
  Coordinate currentCoord = this->getCoord();

  healableCoordinates.push_back(currentCoord + Coordinate(0,1));
  healableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  healableCoordinates.push_back(currentCoord + Coordinate(1,0));
  healableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  healableCoordinates.push_back(currentCoord + Coordinate(1,1));
  healableCoordinates.push_back(currentCoord + Coordinate(-1,1));
  healableCoordinates.push_back(currentCoord + Coordinate(-1,-1));
  healableCoordinates.push_back(currentCoord + Coordinate(1,-1));
  return healableCoordinates;
}
