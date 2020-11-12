#include"Game.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Game::Game(uint maxTurnNumber, uint boardSize, Coordinate chest):board(Board(boardSize,&players,chest)){
  this->maxTurnNumber = maxTurnNumber;
  this->turnNumber = 0;
}
Game::~Game(){
  for(int i=0; i< players.size();i++){
          delete players[i];
    }
}
void Game::addPlayer(int id, int x, int y, Team team, std::string cls){
  bool sorted = false;
  if(cls == "ARCHER"){
    Player* newPlayer = new Archer(id,x,y,team);
    players.push_back(newPlayer);
  }
  else if(cls == "FIGHTER"){
    Player* newPlayer = new Fighter(id,x,y,team);
    players.push_back(newPlayer);
  }
  else if(cls == "PRIEST"){
    Player* newPlayer = new Priest(id,x,y,team);
    players.push_back(newPlayer);
  }
  else if(cls == "SCOUT"){
    Player* newPlayer = new Scout(id,x,y,team);
    players.push_back(newPlayer);
  }
  else if(cls == "TANK"){
    Player* newPlayer = new Tank(id,x,y,team);
    players.push_back(newPlayer);
  }
  for(int i=0; (i<players.size()-1) && !sorted; i++){
    sorted = true;
    for(int j=0; j< players.size()-j-1;j++){
      if(players[i]->getID() > players[i+1]->getID()){
        Player* temp = players[i];
        players[i] = players[i+1];
        players[i+1] = temp;
        sorted = false;
      }
    }
  }
}
bool Game::isGameEnded(){
  Coordinate chestCoord = board.getChestCoordinates();
  std::vector<Player*> barbarians;
  std::vector<Player*> knights;
  bool barbariansLive = false;
  bool knightsLive = false;
  for(int i=0; i<players.size();i++){
    if(players[i]->getTeam() == BARBARIANS){
      barbarians.push_back(players[i]);
    }
    else{
      knights.push_back(players[i]);
    }
  }
  if(knights.size() != 0){
    knightsLive = true;
  }
  if(barbarians.size() != 0){
    barbariansLive = true;
  }
/*  for(int i=0; i<knights.size();i++){

    if(knights[i]->isDead() == false){
      knightsLive = true;
      break;
    }
  } */
/*  for(int i=0; i<barbarians.size();i++){
    if(barbarians[i]->isDead() == false){
      barbariansLive = true;
      break;
    }
  } */
  if(this->turnNumber == this->maxTurnNumber){
    std::cout << "Game ended at turn " << this->turnNumber << ". Maximum turn number reached. Knight victory." << std::endl;
    return true;
  }
  else if(barbariansLive == false){
    std::cout << "Game ended at turn " << this->turnNumber << ". All barbarians dead. Knight victory." << std::endl;
    return true;
  }
  else if(knightsLive == false){
    std::cout << "Game ended at turn " << this->turnNumber << ". All knights dead. Barbarian victory." << std::endl;
    return true;
  }
  else{
    for(int i=0; i< players.size();i++){
        if(players[i]->getCoord() == chestCoord){
          if(players[i]->getTeam() == BARBARIANS){
            std::cout << "Game ended at turn " << this->turnNumber << ". Chest captured. Barbarian victory." << std::endl;
            return true;
          }
        }
      }
  }
  return false;
}

void Game::playTurn(){
  this->turnNumber = this->turnNumber + 1;
  std::cout << "Turn " << this->turnNumber << " has started." << std::endl;
  for(int i=0;(i<players.size());i++){
    if(players[i]->isDead()){
      this->playTurnForPlayer(players[i]);
      i--;
    }
    else{
        this->playTurnForPlayer(players[i]);
    }
  }
}

Goal Game::playTurnForPlayer(Player* player){
  if(player->isDead()){
    std::cout << "Player " << player->getBoardID() << " has died." << std::endl;
    for(int i=0;i<players.size();i++){
      if(players[i] == player){
        players.erase(players.begin()+i);
        break;
      }
    }
    delete player;
    return NO_GOAL;
  }
  else{
    std::vector<Goal> playerGoalList = player->getGoalPriorityList();
    for(int i=0;i<playerGoalList.size();i++){
      if(playerGoalList[i] == ATTACK){
        std::vector<Coordinate> attackable = player->getAttackableCoordinates();
        std::vector<Player*> deathMenWalking;
        for(int i=0;i<attackable.size();i++){
          if(board.isCoordinateInBoard(attackable[i]) && board.isPlayerOnCoordinate(attackable[i])){
            if(player->getTeam() != board[attackable[i]]->getTeam()){
                deathMenWalking.push_back(board[attackable[i]]);
            }
          }
        }
        if(deathMenWalking.size() == 0){
          continue;
        }
        else{
          Player* oldunCiq = deathMenWalking[0];
          for(int i=1;i<deathMenWalking.size();i++){
            if(deathMenWalking[i]->getID() < oldunCiq->getID()){
              oldunCiq = deathMenWalking[i];
            }
          }
          player->attack(oldunCiq);
          return ATTACK;
        }
      }
      else if(playerGoalList[i] == HEAL){
        std::vector<Coordinate> healableCoordinates = player->getHealableCoordinates();
        std::vector<Player*> healMen;
        for(int i=0;i<healableCoordinates.size();i++){
          if(board.isCoordinateInBoard(healableCoordinates[i])){
            if(board.isPlayerOnCoordinate(healableCoordinates[i])){
              if(board[healableCoordinates[i]]->getTeam() == player->getTeam()){
                  healMen.push_back(board[healableCoordinates[i]]);
              }
            }
          }
        }
        if(healMen.size() == 0){
          continue;
        }
        else{
          for(int i=0;i<healMen.size();i++){
            player->heal(healMen[i]);
          }
          return HEAL;
        }
      }
      else if(playerGoalList[i] == TO_ALLY){
        std::vector<Coordinate> moveableCoordinates = player->getMoveableCoordinates();
        std::vector<Coordinate> realCoordinates;
        for(int i=0;i<moveableCoordinates.size();i++){
          if(board.isCoordinateInBoard(moveableCoordinates[i])){
            if(board.isPlayerOnCoordinate(moveableCoordinates[i]) == false){
              realCoordinates.push_back(moveableCoordinates[i]);
            }
          }
        }
        if(realCoordinates.size() == 0){
          continue;
        }
        else{
          std::vector<Player*> allies;
          for(int i=0;i<players.size();i++){
            if(players[i]->getTeam() == player->getTeam() && players[i] != player){
              allies.push_back(players[i]);
            }
          }
          if(allies.size() == 0){
            continue;
          }
          else{
            Player* gidilecekAdam = allies[0];
            Coordinate gidilecekYer = realCoordinates[0];
            for(int i=1;i<allies.size();i++){
              if((gidilecekAdam->getCoord()-player->getCoord()) > (allies[i]->getCoord() - player->getCoord())){
                gidilecekAdam = allies[i];
              }
              else if((gidilecekAdam->getCoord()-player->getCoord()) == (allies[i]->getCoord() - player->getCoord())){
                if(gidilecekAdam->getID()> allies[i]->getID()){
                  gidilecekAdam = allies[i];
                }
              }
            }
            if(gidilecekAdam->getCoord() - player->getCoord() == 1){
              continue;
            }
            for(int i=1;i<realCoordinates.size();i++){
              if((gidilecekAdam->getCoord()-gidilecekYer) > (gidilecekAdam->getCoord()-realCoordinates[i])){
                gidilecekYer = realCoordinates[i];
              }
              else if((gidilecekAdam->getCoord()-gidilecekYer) == (gidilecekAdam->getCoord()-realCoordinates[i])){
                if(player->getCoord().y == realCoordinates[i].y){
                  gidilecekYer = realCoordinates[i];
                }
              }
            }
            if((player->getCoord() - gidilecekAdam->getCoord()) <= (gidilecekYer - gidilecekAdam->getCoord())){
              continue;
            }
            else{
              player->movePlayerToCoordinate(gidilecekYer);
              return TO_ALLY;
            }
            //player->movePlayerToCoordinate(gidilecekYer);
            //return TO_ALLY;
          }
        }
      }
      else if(playerGoalList[i] == TO_ENEMY){
        std::vector<Coordinate> moveableCoordinates = player->getMoveableCoordinates();
        std::vector<Coordinate> realCoordinates;
        for(int i=0;i<moveableCoordinates.size();i++){
          if(board.isCoordinateInBoard(moveableCoordinates[i])){
            if(board.isPlayerOnCoordinate(moveableCoordinates[i]) == false){
              realCoordinates.push_back(moveableCoordinates[i]);
            }
          }
        }
        if(realCoordinates.size() == 0){
          continue;
        }
        else{
          std::vector<Player*> enemies;
          for(int i=0;i<players.size();i++){
            if(players[i]->getTeam() != player->getTeam()){
              enemies.push_back(players[i]);
            }
          }
          if(enemies.size() == 0){
            continue;
          }
          else{
            Player* gidilecekAdam = enemies[0];
            Coordinate gidilecekYer = realCoordinates[0];
            for(int i=1;i<enemies.size();i++){
              if((gidilecekAdam->getCoord()-player->getCoord()) > (enemies[i]->getCoord() - player->getCoord())){
                gidilecekAdam = enemies[i];
              }
              else if((gidilecekAdam->getCoord()-player->getCoord()) == (enemies[i]->getCoord() - player->getCoord())){
                if(gidilecekAdam->getID()> enemies[i]->getID()){
                  gidilecekAdam = enemies[i];
                }
              }
            }
            if(gidilecekAdam->getCoord() - player->getCoord() == 1){
              continue;
            }
            for(int i=1;i<realCoordinates.size();i++){
              if((gidilecekAdam->getCoord()-gidilecekYer) > (gidilecekAdam->getCoord()-realCoordinates[i])){
                gidilecekYer = realCoordinates[i];
              }
              else if((gidilecekAdam->getCoord()-gidilecekYer) == (gidilecekAdam->getCoord()-realCoordinates[i])){
                if(player->getCoord().y == realCoordinates[i].y){
                  gidilecekYer = realCoordinates[i];
                }
              }
            }
            if((player->getCoord() - gidilecekAdam->getCoord()) <= (gidilecekYer - gidilecekAdam->getCoord())){
              continue;
            }
            else{
              player->movePlayerToCoordinate(gidilecekYer);
              return TO_ENEMY;
            }
            //player->movePlayerToCoordinate(gidilecekYer);
            //return TO_ENEMY;
          }
        }
      }
      else if(playerGoalList[i] == CHEST){
        Coordinate playerCoord = player->getCoord();
        std::vector<Coordinate> moveable = player->getMoveableCoordinates();
        std::vector<Coordinate> realMoveable;
        Coordinate chestCoord = board.getChestCoordinates();
        for(int i=0;i<moveable.size();i++){
          if(board.isCoordinateInBoard(moveable[i])){
            if(board.isPlayerOnCoordinate(moveable[i]) == false){
              realMoveable.push_back(moveable[i]);
            }
          }
        }
          if(realMoveable.size() == 0){
            continue;
          }
          else{
            Coordinate moveCoord = realMoveable[0];
            for(int i=1;i<realMoveable.size();i++){
              if((moveCoord-chestCoord) > (realMoveable[i]-chestCoord)){
                moveCoord = realMoveable[i];
              }
              else if((moveCoord-chestCoord) == (realMoveable[i]-chestCoord)){
                if(playerCoord.y == realMoveable[i].y){
                  moveCoord = realMoveable[i];
                }
              }
            }
            if((player->getCoord()-chestCoord) <= (moveCoord - chestCoord)){
              continue;
            }
            else{
              player->movePlayerToCoordinate(moveCoord);
              return CHEST;
            }
          }
        }
      }
    }
    return NO_GOAL;
  }

void Game::printBoardID(){
  board.printBoardwithID();
}
void Game::printBoardClass(){
  board.printBoardwithClass();
}
