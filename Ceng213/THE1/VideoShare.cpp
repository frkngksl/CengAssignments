#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "VideoShare.hpp"
#include "User.hpp"

using namespace std;

void VideoShare::printAllVideos() {
    videos.print();
}

void VideoShare::printAllUsers() {
    users.print();
}

/* TO-DO: method implementations below */

VideoShare::VideoShare(){
  users = LinkedList<User>();
  videos = LinkedList<Video>();
}

void VideoShare::createUser(const string & userName,const string & name,const string & surname){
  if (userName != "") {
    User user(userName,name,surname);
    Node<User>* head = users.getHead();
    users.insertNode(head,user);
  }
}
void VideoShare::createVideo(const string & title, const string & genre){
  if (title != "") {
    Video video(title,genre);
    Node<Video>* head = videos.getHead();
    videos.insertNode(head,video);
  }
}
void VideoShare::addFriendship(const string & userName1, const string & userName2){
    Node<User>* username1 = users.findNode(userName1);
    Node<User>* username2 = users.findNode(userName2);
    if(username1 && username2){
      username1->getDataPtr()->addFriend(username2->getDataPtr());
      username2->getDataPtr()->addFriend(username1->getDataPtr());
    }
}
void VideoShare::removeFriendship(const string & userName1, const string & userName2){
    Node<User>* username1 = users.findNode(userName1);
    Node<User>* username2 = users.findNode(userName2);
    if(username1 && username2){
      username1->getDataPtr()->removeFriend(username2->getDataPtr());
      username2->getDataPtr()->removeFriend(username1->getDataPtr());
    }
}
void VideoShare::updateUserStatus(const string & userName,Status newStatus){
  Node<User>* userNode = users.findNode(userName);
  if(userNode){
    userNode->getDataPtr()->updateStatus(newStatus);
  }
}
void VideoShare::subscribe(const string & userName,const string & videoTitle){
  Node<User>* user = users.findNode(userName);
  Node<Video>* video = videos.findNode(videoTitle);
  if(user && video && user->getDataPtr()->getStatus() != SUSPENDED){
    user->getDataPtr()->subscribe(video->getDataPtr());
  }
}
void VideoShare::unSubscribe(const string & userName, const string & videoTitle){
  Node<User>* user = users.findNode(userName);
  Node<Video>* video = videos.findNode(videoTitle);
  if(user && video && user->getDataPtr()->getStatus() != SUSPENDED){
    user->getDataPtr()->unSubscribe(video->getDataPtr());
  }
}
void VideoShare::loadUsers(const string & fileName){
    const char* filename = fileName.c_str();
    ifstream file;
    file.open(filename);

    while(true){
        string whole;
        string username;
        string name;
        string surname;
        getline(file,whole);
        if(!file.good()){
            break;
        }
        username = whole.substr(0,whole.find(";"));
        whole = whole.substr(whole.find(";")+1);
        name = whole.substr(0,whole.find(";"));
        surname = whole.substr(whole.find(";")+1);
        createUser(username,name,surname);
    }
    file.close();
}
void VideoShare::loadVideos(const string & fileName){
    const char* filename = fileName.c_str();
    ifstream file;
    file.open(filename);
    while(true){
        string whole;
        string title;
        string genre;
        getline(file,whole);
        if(!file.good()){
            break;
        }
        title = whole.substr(0,whole.find(";"));
        genre = whole.substr(whole.find(";")+1);
        createVideo(title,genre);
    }
    file.close();
}
void VideoShare::deleteUser(const string & userName){
  Node <User>* user = users.findNode(userName);
  LinkedList<User*>* friendsUser = user->getDataPtr()->getFriends();
  Node<User*>* cursor = friendsUser->first();
  Node <User>* prev = users.findPrev(user->getData());
  User* addr =user->getDataPtr();
  while(cursor){
    cursor->getData()->removeFriend(user->getDataPtr());
    //removeFriendship(userName,cursor->getData()->getUsername());
    cursor = cursor->getNext();
  }
  users.deleteNode(prev);
}
void VideoShare::sortUserSubscriptions(const string & userName){
  Node <User>* user = users.findNode(userName);
  LinkedList<Video* >* videosUser = user->getDataPtr()->getSubscriptions();
  Node<Video*>* cursor1 = videosUser->first();
  bool sorted = false;
  for(int i=0;(i < videosUser->getLength()-1)&& !sorted; i++){
    sorted = true;
    cursor1 = videosUser->first();
    for(int j=1; j<= videosUser->getLength()-i-1;j++){
      if(((cursor1->getData()->getTitle()).compare(cursor1->getNext()->getData()->getTitle())) > 0){
      cursor1=cursor1->getNext();
      videosUser->swap(j,j-1);
      sorted = false;
      }
        cursor1=cursor1->getNext();
    }
  }
}
void VideoShare::printUserSubscriptions(const string& userName){
  Node<User>* user = users.findNode(userName);
  if(user){
  user->getDataPtr()->printSubscriptions();
  }
}
void VideoShare::printFriendsOfUser(const string & userName){
  Node<User>* user = users.findNode(userName);
  if(user){
  user->getDataPtr()->printFriends();
  }
}
void VideoShare::printCommonSubscriptions(const string & userName1,const string & userName2){
  Node<User>* user1 = users.findNode(userName1);
  Node<User>* user2 = users.findNode(userName2);
  LinkedList<Video*>* video1 = user1->getDataPtr()->getSubscriptions();
  LinkedList<Video*>* video2 = user2->getDataPtr()->getSubscriptions();
  Node<Video*>* cursor1 = video1->getHead();
  Node<Video*>* cursor2 = video2->first();
  for(int i=0; i < video1->getLength();i++){
        cursor1 = cursor1->getNext();
        cursor2 = video2->first();
    for(int j=0; j < video2->getLength();j++){
      if((cursor1->getData()->getTitle()).compare(cursor2->getData()->getTitle()) == 0){
        cout << *(cursor1->getData());
        break;
      }
      cursor2 = cursor2->getNext();
    }
  }
  cout << endl;
}
void VideoShare::printFriendSubscriptions(const string & userName){
  Node<User>* user1 = users.findNode(userName);
  LinkedList<User*>* userFriends = user1->getDataPtr()->getFriends();
  Node<User*>* cursor1 = userFriends->first();
  LinkedList<Video*> distinct = LinkedList<Video*>();
  Node<Video*>* cursor2;
  bool sorted = false;
  for(int i=0; i < userFriends->getLength();i++){
    LinkedList<Video*>* friendSubs = cursor1->getData()->getSubscriptions();
    cursor2 = friendSubs->first();
    for(int j=0; j < friendSubs->getLength();j++){
      if(distinct.findNode(cursor2->getData()) == NULL){
        distinct.insertNode(distinct.getHead(),cursor2->getData());
      }
      cursor2 = cursor2->getNext();
    }
    cursor1 = cursor1->getNext();
  }
  cursor2 = distinct.first();
  for(int i=0;(i < distinct.getLength()-1)&& !sorted; i++){
    sorted = true;
    cursor2 = distinct.first();
    for(int j=1; j<= distinct.getLength()-i-1;j++){
      if(((cursor2->getData()->getTitle()).compare(cursor2->getNext()->getData()->getTitle())) > 0){
      cursor2=cursor2->getNext();
      distinct.swap(j,j-1);
      sorted = false;
      }
        cursor2=cursor2->getNext();
    }
  }
  cursor2 = distinct.first();
  for(int i=0;i < distinct.getLength();i++){
      cout << *(cursor2->getData());
      cursor2 = cursor2->getNext();
  }
  cout << endl;
}

bool VideoShare::isConnected(const string & userName1,const string & userName2){
 Node<User>* user1 = users.findNode(userName1);
 Node<User>* user2 = users.findNode(userName2);
  if(user1 && user2){
    LinkedList<User*> gezilen = LinkedList<User*>();
    LinkedList<User*> gezilecek = LinkedList<User*>();
    gezilecek.insertNode(gezilecek.getHead(),user1->getDataPtr());
    while(gezilecek.getLength() != 0){
      Node<User*>* cursor = gezilecek.first();
      Node<User*>* cursor2;
      LinkedList<User*>* friendList = cursor->getData()->getFriends();
      gezilen.insertNode(gezilen.getHead(),cursor->getData());
      gezilecek.deleteNode(gezilecek.findPrev(cursor->getData()));
      cursor2 = friendList->first();
      for(int i=0; i < friendList->getLength();i++){
        if(cursor2->getData() == user2->getDataPtr()){
          return true;
        }
        else{
          if(gezilen.findNode(cursor2->getData()) == NULL){
            gezilecek.insertNode(gezilecek.getHead(),cursor2->getData());
          }
          cursor2 = cursor2->getNext();
        }
      }
    }
    return false;
  }
  else{
      return false;
    }
}

VideoShare::~VideoShare(){

}
