#include"Scout.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Scout::Scout(uint id,int x, int y, Team team):Player(id,x,y,team){
  this->attackDamage = 25;
  this->healPower = 0;
  this->maxHP = 125;
  this->HP=125;
  goalPriorityList.push_back(CHEST);
  goalPriorityList.push_back(TO_ALLY);
  goalPriorityList.push_back(ATTACK);
  attackableCoordinates.push_back(Coordinate(x,y+1));
  attackableCoordinates.push_back(Coordinate(x,y-1));
  attackableCoordinates.push_back(Coordinate(x+1,y));
  attackableCoordinates.push_back(Coordinate(x-1,y));
  attackableCoordinates.push_back(Coordinate(x+1,y+1));
  attackableCoordinates.push_back(Coordinate(x-1,y+1));
  attackableCoordinates.push_back(Coordinate(x-1,y-1));
  attackableCoordinates.push_back(Coordinate(x+1,y-1));

  moveableCoordinates.push_back(Coordinate(x,y+1));
  moveableCoordinates.push_back(Coordinate(x,y-1));
  moveableCoordinates.push_back(Coordinate(x+1,y));
  moveableCoordinates.push_back(Coordinate(x-1,y));
  moveableCoordinates.push_back(Coordinate(x+1,y+1));
  moveableCoordinates.push_back(Coordinate(x-1,y+1));
  moveableCoordinates.push_back(Coordinate(x-1,y-1));
  moveableCoordinates.push_back(Coordinate(x+1,y-1));
  if(team == BARBARIANS){
    classAbbreviation = "SC";
  }
  else{
    classAbbreviation = "sc";
  }
}
Scout::~Scout(){};

int Scout::getAttackDamage() const{
  return attackDamage;
}
int Scout::getHealPower() const{
  return healPower;
}
int Scout::getMaxHP() const{
  return maxHP;
}
std::vector<Goal> Scout::getGoalPriorityList(){
  return goalPriorityList;
}
const std::string Scout::getClassAbbreviation() const{
  return classAbbreviation;
}
std::vector<Coordinate> Scout::getAttackableCoordinates(){
  Coordinate currentCoord = this->getCoord();
  attackableCoordinates.clear();
  attackableCoordinates.push_back(currentCoord + Coordinate(0,1));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  attackableCoordinates.push_back(currentCoord + Coordinate(1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(1,1));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,+1));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,-1));
  attackableCoordinates.push_back(currentCoord + Coordinate(+1,-1));

  return attackableCoordinates;
}
std::vector<Coordinate> Scout::getMoveableCoordinates(){
  Coordinate currentCoord = this->getCoord();
  moveableCoordinates.clear();
  moveableCoordinates.push_back(currentCoord + Coordinate(0,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,+1));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(+1,-1));

  return moveableCoordinates;
}
std::vector<Coordinate> Scout::getHealableCoordinates(){
  return healableCoordinates;
}
