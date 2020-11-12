#include"Player.h"
#include <string>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Player::Player(uint id,int x, int y, Team team):id(id),coordinate(Coordinate(x,y)),team(team){
/*  this->id = id;
  this->coordinate = Coordinate(x,y);
  this->team = team; */
}

uint Player::getID() const {
  return id;
}

const Coordinate& Player::getCoord() const{
  return coordinate;
}

int Player::getHP() const{
  return HP;
}

Team Player::getTeam() const{
  return team;
}

std::string Player::getBoardID(){
  std::string returnValue;
  if(id < 10){
    returnValue = "0"+std::to_string(this->id);
  }
  else{
    returnValue = std::to_string(this->id);
  }
  return returnValue;
}

bool Player::attack(Player *enemy){
  enemy->HP = (enemy->getHP()) - (this->getAttackDamage());
  std::cout << "Player " << this->getBoardID() << " attacked Player " << enemy->getBoardID() << " (" << this->getAttackDamage() << ")" << std::endl;
  if(enemy->getHP() > 0){
        return false;
    }
  else{
      return true;
    }
  /*
  std::vector<Coordinate> moveable = this->getAttackableCoordinates();
  for(int i=0;i<moveable.size();i++){
    if(moveable[i] == enemy->getCoord()){
      enemy->HP = (enemy->getHP()) - (this->getAttackDamage());
      std::cout << "Player " << this->getBoardID() << " attacked Player " << enemy->getBoardID() << " (" << this->getAttackDamage() << ")" << std::endl;
      if(enemy->getHP() > 0){
        return false;
      }
      else{
        return true;
      }
    }
  }
  return false; */
}

void Player::heal(Player *ally){ //coord ?
  std::cout << "Player " << this->getBoardID() << " healed Player " << ally->getBoardID() << std::endl;
  if(this->getHealPower() + ally->getHP() > ally->getMaxHP()){
    ally->HP = ally->getMaxHP();
  }
  else{
    ally->HP = ally->getHP() + this->getHealPower();
  }
  /*
  std::vector<Coordinate> moveable = this->getHealableCoordinates();
  for(int i=0;i<moveable.size();i++){
    if(moveable[i] == ally->getCoord()){
      std::cout << "Player " << this->getBoardID() << " healed Player " << ally->getBoardID() << std::endl;
      if(this->getHealPower() + ally->getHP() > ally->getMaxHP()){
        ally->HP = ally->getMaxHP();
      }
      else{
        ally->HP = ally->getHP() + this->getHealPower();
      }
      break;
    }
  } */
}


void Player::movePlayerToCoordinate(Coordinate c){
  std::cout << "Player " << this->getBoardID() << " moved from " << this->getCoord() << " to " << c << std::endl;
  this->coordinate = c;
}

bool Player::isDead() const{
  if(this->getHP() <=0){
    return true;
  }
  else{
    return false;
  }
}
