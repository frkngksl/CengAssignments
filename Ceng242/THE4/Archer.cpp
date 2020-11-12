#include"Archer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Archer::Archer(uint id,int x, int y, Team team):Player(id,x,y,team){
  this->attackDamage = 50;
  this->healPower = 0;
  this->maxHP = 200;
  this->HP = 200;
  goalPriorityList.push_back(ATTACK);
  attackableCoordinates.push_back(Coordinate(x,y+1));
  attackableCoordinates.push_back(Coordinate(x,y+2));
  attackableCoordinates.push_back(Coordinate(x,y-1));
  attackableCoordinates.push_back(Coordinate(x,y-2));
  attackableCoordinates.push_back(Coordinate(x+1,y));
  attackableCoordinates.push_back(Coordinate(x+2,y));
  attackableCoordinates.push_back(Coordinate(x-1,y));
  attackableCoordinates.push_back(Coordinate(x-2,y));
  if(team == BARBARIANS){
    classAbbreviation = "AR";
  }
  else{
    classAbbreviation = "ar";
  }
};

Archer::~Archer(){};

int Archer::getAttackDamage() const{
  return attackDamage;
}
int Archer::getHealPower() const{
  return healPower;
}
int Archer::getMaxHP() const{
  return maxHP;
}
std::vector<Goal> Archer::getGoalPriorityList(){
  return goalPriorityList;
}
const std::string Archer::getClassAbbreviation() const{
  return classAbbreviation;
}
std::vector<Coordinate> Archer::getAttackableCoordinates(){
  Coordinate currentCoord = this->getCoord();
  attackableCoordinates.clear();

  attackableCoordinates.push_back(currentCoord + Coordinate(0,1));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,2));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,-2));
  attackableCoordinates.push_back(currentCoord + Coordinate(1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(2,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(-2,0));
  return attackableCoordinates;
}
std::vector<Coordinate> Archer::getMoveableCoordinates(){
  return moveableCoordinates;
}
std::vector<Coordinate> Archer::getHealableCoordinates(){
  return healableCoordinates;
}
