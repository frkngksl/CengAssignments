#include "hw3.h"

AccessControl::AccessControl(int table1Size, int table2Size){
  regUsers.resize(table1Size);
  this->regUsersSize = table1Size;
  for(int i=0;i<table1Size;i++){
    regUsers[i].first = EMPTY;
    regUsers[i].second = EMPTY;
  }
  activeUsers.resize(table2Size);
  this->activeUsersSize = table2Size;
  for(int i=0;i<table2Size;i++){
    activeUsers[i] = EMPTY;
  }
  this->regUsersNum = 0;
  this->activeUserNum = 0;
}
int AccessControl::checkPrime(int number){
  for(int i=2; i<= number/2; i++){
    if(number%i == 0){
      return 0;
    }
  }
  return 1;
}
int AccessControl::newSize(int tableSize1){
  int newSize = 2*tableSize1 + 1;
  while(1){
    if(checkPrime(newSize) == 1){
      return newSize;
    }
    newSize++;
  }
}
int AccessControl::checkIn(std::string aranacak, std::vector<std::string>& listUsers){
  for(int i=0;i<listUsers.size();i++){
    if(aranacak == listUsers[i]){
      return 1;
    }
  }
  return 0;
}
void AccessControl::resizeTheTable(int newSize,int oldSize){
  std::vector< std::pair<std::string, std::string> > temp;
  std::vector < std::string > userList;
  temp.resize(oldSize);
    for(int i=0;i<oldSize;i++){
    temp[i].first = EMPTY;
    temp[i].second = EMPTY;
  }
  for(int i=0;i<oldSize;i++){
    temp[i].first = regUsers[i].first;
    temp[i].second = regUsers[i].second;
  }
  regUsers.resize(newSize);
  this->regUsersSize = newSize;
  for(int i=0;i<newSize;i++){
    if(regUsers[i].first != DELETED){
      regUsers[i].first = EMPTY;
      regUsers[i].second = EMPTY;
    }
  }
  for(int i=0;i<oldSize;i++){
    if(temp[i].first != DELETED && temp[i].first != EMPTY){
      if(checkIn(temp[i].first,userList) == 0){
        userList.push_back(temp[i].first);
      }
    }
  }
  for(int i=0;i<userList.size();i++){
      for(int j=0;j<oldSize;j++){
          int hashValforOld = hashFunction(userList[i],oldSize,j);
          if(temp[hashValforOld].first == EMPTY || temp[hashValforOld].first == DELETED){
              break;
          }
          else if(temp[hashValforOld].first == userList[i]){
              for(int k=0;k<newSize;k++){
                  int hashValforNew = hashFunction(userList[i],newSize,k);
                  if(regUsers[hashValforNew].first == EMPTY || regUsers[hashValforNew].first == DELETED){
                      regUsers[hashValforNew].first = temp[hashValforOld].first;
                      regUsers[hashValforNew].second = temp[hashValforOld].second;
                      break;
                  }
              }
          }
      }
  }

}

int AccessControl::addUser(std::string username, std::string pass){
  for(int i=0;i<regUsersSize;i++){
  int hashVal = hashFunction(username,regUsersSize,i);

 if(regUsers[hashVal].first == username){
    return 0;
  }
  else if(regUsers[hashVal].first == EMPTY || regUsers[hashVal].first == DELETED){
    float loadFactor;
    regUsers[hashVal].first  = username;
    regUsers[hashVal].second = pass;
    regUsersNum++;
    loadFactor = (float) regUsersNum/regUsersSize;
    if(loadFactor>MAX_LOAD_FACTOR){
      int paramForResize = newSize(regUsersSize);
      resizeTheTable(paramForResize,regUsersSize);
    }
    return 1;
    }
    else{
      continue;
    }
  }
  return 0;
}
int AccessControl::addUsers(std::string filePath){
const char* filename = filePath.c_str();
  std::ifstream file;
  file.open(filename);
  int count = 0;
  int check;
  while(true){
      std::string whole;
      std::string username;
      std::string password;
      getline(file,whole);
      if(!file.good()){
          break;
      }
      username = whole.substr(0,whole.find(" "));
      whole = whole.substr(whole.find(" ")+1);
      password = whole;
      check = addUser(username,password);
      if(check == 1){
        count++;
      }
  }
  file.close();
  return count;
}
float AccessControl::printPasswords(){

  for (int i=0;i<regUsersSize;i++)
	{
		std::cout << regUsers[i].first << " " << regUsers[i].second << std::endl;
	}
	return (float) regUsersNum/regUsersSize;
}
int AccessControl::delUser(std::string username, std::vector<std::string>& oldPasswords){
    int flag = 0;
  for(int i=0;i<regUsersSize;i++){
    int hashVal = hashFunction(username,regUsersSize,i);
    if(regUsers[hashVal].first == username){
      flag = 1;
      break;
    }
  }
  if(flag == 0){
    return 0;
  }
  else{
    for(int i=0;i<regUsersSize;i++){
      int hashVal = hashFunction(username,regUsersSize,i);
      if(regUsers[hashVal].first == username){
        for(int k=0;k<regUsersSize;k++){
          int hashValNew = hashFunction(username,regUsersSize,i+k);
          if(regUsers[hashValNew].first == username){
            oldPasswords.push_back(regUsers[hashValNew].second);
            regUsers[hashValNew].first = DELETED;
            regUsers[hashValNew].second = DELETED;
            regUsersNum--;
          }
          else if(regUsers[hashValNew].first == EMPTY){
            return 1;
          }
        }
      }
    }
  }
}
int AccessControl::changePass(std::string username, std::string oldpass, std::string newpass){
int flag = 0;
for(int i=0;i<regUsersSize;i++){
  int hashVal = hashFunction(username,regUsersSize,i);
  if(regUsers[hashVal].first == username){
    flag = 1;
    break;
  }
}
if(flag == 0){
  //  std::cout << "Kullanıcı adını bulamadı" << std::endl;
    return 0;
}
else{
  for(int i=0;i<regUsersSize;i++){
    int hashVal = hashFunction(username,regUsersSize,i);
    int hashVal2 = hashFunction(username,regUsersSize,i+1);
    if(regUsers[hashVal].second == oldpass && regUsers[hashVal2].first != username){
      for(int k=1;k<regUsersSize;k++){
        int newHash = hashFunction(username,regUsersSize,i+k);
        if(regUsers[newHash].first == EMPTY || regUsers[newHash].first == DELETED){
          float loadFactor;
          regUsers[newHash].first  = username;
          regUsers[newHash].second = newpass;
          regUsersNum++;
          loadFactor = (float) regUsersNum/regUsersSize;
          if(loadFactor>MAX_LOAD_FACTOR){
            int paramForResize = newSize(regUsersSize);
            resizeTheTable(paramForResize,regUsersSize);
            }
          return 1;
        }
      }
      }
    else if(regUsers[hashVal].first == EMPTY || regUsers[hashVal].first == DELETED){
      return 0;
    }
  }
}
}

void AccessControl::resizeTheTable2(int newSize,int oldSize){
      std::vector< std::string> temp;
  std::vector < std::string > userList;
  temp.resize(oldSize);
    for(int i=0;i<oldSize;i++){
    temp[i] = EMPTY;
  }
  for(int i=0;i<oldSize;i++){
    temp[i] = activeUsers[i];
  }
  activeUsers.resize(newSize);
  this->activeUsersSize = newSize;
  for(int i=0;i<newSize;i++){
      activeUsers[i] = EMPTY;
  }
 /* for(int i=0;i<oldSize;i++){
      if(temp[i] == EMPTY || temp[i] == DELETED){
      activeUsers[i] = temp[i];
    }
  } */
  for(int i=0;i<oldSize;i++){
    if(temp[i] != DELETED && temp[i] != EMPTY){
      if(checkIn(temp[i],userList) == 0){
        userList.push_back(temp[i]);
      }
    }
  }
  for(int i=0;i<userList.size();i++){
      for(int j=0;j<oldSize;j++){
          int hashValforOld = hashFunction(userList[i],oldSize,j);
          if(temp[hashValforOld] == EMPTY || temp[hashValforOld] == DELETED){
              break;
          }
          else if(temp[hashValforOld] == userList[i]){
              for(int k=0;k<newSize;k++){
                  int hashValforNew = hashFunction(userList[i],newSize,k);
                  if(activeUsers[hashValforNew] == EMPTY || activeUsers[hashValforNew] == DELETED){
                      activeUsers[hashValforNew] = temp[hashValforOld];
                      break;
                  }
              }
          }
      }
  }
}

int AccessControl::login(std::string username, std::string pass){
 int flag = 0;
for(int i=0;i<regUsersSize;i++){
  int hashVal = hashFunction(username,regUsersSize,i);
  if(regUsers[hashVal].first == username){
    flag = 1;
    break;
  }
}
if(flag == 0){
  //  std::cout << "Kullanıcı adını bulamadı" << std::endl;
    return 0;
}
else{
  for(int i=0;i<regUsersSize;i++){
    int hashVal = hashFunction(username,regUsersSize,i);
    int hashVal2 = hashFunction(username,regUsersSize,i+1);
    if(regUsers[hashVal].second == pass && regUsers[hashVal2].first != username){
      for(int k=0;k<activeUsersSize;k++){
        int newHash = hashFunction(username,activeUsersSize,k);
        if(activeUsers[newHash] == username){
           return 0;
         }
        else if(activeUsers[newHash] == EMPTY || activeUsers[newHash] == DELETED){
          float loadFactor;
          activeUsers[newHash] = username;
          activeUserNum++;
          loadFactor = (float) activeUserNum/activeUsersSize;
          if(loadFactor>MAX_LOAD_FACTOR){
            int paramForResize = newSize(activeUsersSize);
            resizeTheTable2(paramForResize,activeUsersSize);
          }
          return 1;
          }
          else{
            continue;
          }
        }
      }
    else if(regUsers[hashVal].first == EMPTY || regUsers[hashVal].first == DELETED){
      return 0;
    }
  }
} }


int AccessControl::logout(std::string username){
    for(int i=0;i<activeUsersSize;i++){
    int hashVal = hashFunction(username,activeUsersSize,i);
    if(activeUsers[hashVal] == username){
      activeUsers[hashVal] = DELETED;
      activeUserNum--;
      return 1;
    }
    else if(activeUsers[hashVal] == EMPTY){
        return 0;
    }
  }
  return 0;
}
float AccessControl::printActiveUsers(){
    for (int i=0;i<activeUsersSize;i++)
	{
		std::cout << activeUsers[i] << std::endl;
	}
	return (float) activeUserNum/activeUsersSize;
}
AccessControl::~AccessControl(){
  ;
}
