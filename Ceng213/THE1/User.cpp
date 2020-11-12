#include <iostream>
#include "User.hpp"
#include "Video.hpp"

void User::printSubscriptions() {
    Node< Video*> * first = subscriptions.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

void User::printFriends() {
    Node< User*> * first = friends.first();
    while (first) {
        cout << *(first->getData());
        first = first->getNext();
    }
    cout << std::endl;
}

ostream& operator<<(ostream& out, const User & user) {
    string st = (user.status == ACTIVE) ? "active" : "suspended";
    out << "username:" << user.username << ",name:" << user.name << ",surname:" << user.surname << ",Status:" << st << endl;
    return out;
}

/* TO-DO: method implementations below */

User::User(){
  username = "";
  name = "";
  surname = "";
  status = ACTIVE;
  subscriptions = LinkedList<Video*>();
  friends = LinkedList<User*>();
}
User::User(string p_username,string p_name,string p_surname){
  username = p_username;
  name = p_name;
  surname = p_surname;
  status = ACTIVE;
  subscriptions = LinkedList<Video*>();
  friends = LinkedList<User*>();
}
const string& User::getUsername() const{
  return username;
}
const string& User::getName() const{
  return name;
}
const string& User::getSurname() const{
  return surname;
}
Status User::getStatus() const{
  return status;
}
void User::updateStatus(Status st){
  if(st == ACTIVE || st == SUSPENDED ){
    status = st;
  }
}
bool User::operator==(const User& rhs) const{
  if(this == &rhs){
    return true;
  }
  else{
    if(username == rhs.username){
      return true;
    }
    else{
      return false;
    }
  }
}
LinkedList<Video*>* User::getSubscriptions(){
  return &subscriptions;
}
LinkedList<User*>* User::getFriends(){
  return &friends;
}
void User::subscribe(Video *video){
  Node<Video*>* header = subscriptions.getHead();
  subscriptions.insertNode(header,video);
}
void User::unSubscribe(Video *video){
  Node<Video*>* pointer = subscriptions.findPrev(video);
  subscriptions.deleteNode(pointer);
}
void User::addFriend(User *user){
  Node<User*>* header = friends.getHead();
  friends.insertNode(header,user);
}
void User::removeFriend(User *user){
  Node<User*>* pointer = friends.findPrev(user);
  friends.deleteNode(pointer);
}
User::~User(){

}
