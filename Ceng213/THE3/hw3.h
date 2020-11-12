#ifndef _HW3_H
#define _HW3_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>  // use just for std::pair< >
#include <fstream>

#define MAX_LOAD_FACTOR 0.65
#define EMPTY "EMPTY"
#define DELETED "DELETED"


class AccessControl
{
public:
	AccessControl(int table1Size, int table2Size);
	~AccessControl();

	int addUser(std::string username, std::string pass);
	int addUsers(std::string filePath);
	int delUser(std::string username, std::vector<std::string>& oldPasswords);
	int changePass(std::string username, std::string oldpass, std::string newpass);

	int login(std::string username, std::string pass);
	int logout(std::string username);

	float printActiveUsers();
	float printPasswords();
private:
//<<your hash class>> activeUsers;	// hash(username) -> username
	std::vector< std::pair<std::string, std::string> > regUsers;
	std::vector<std::string> activeUsers;
	int activeUserNum;
	int activeUsersSize;
	int regUsersSize;
	int regUsersNum;
	int newSize(int tableSize1);
	int checkPrime(int number);
	void resizeTheTable(int newSize,int oldSize);
	void resizeTheTable2(int newSize,int oldSize);
	int checkIn(std::string aranacak, std::vector<std::string>& listUsers);
	//<<your hash class>> regUsers;  		// hash(username) -> username,password
	int hashFunction(std::string key, int tableSize, int i) {
	   int length = key.length();
	   int newK = 0;
	   for (int j = 0; j < length; j++)
	     newK += (int) key[j];

		 // hash function 1 -> (newK % tableSize)
		 // hash function 2 -> (newK * tableSize - 1) % tableSize)

	   return ((newK % tableSize) + i * ((newK * tableSize - 1) % tableSize)) % tableSize;
	}
};

#endif
