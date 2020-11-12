#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head;
    int length;
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data);
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */
template <class T>
LinkedList<T>::LinkedList(){
  head = new Node<T>();
  length = 0;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
  head = new Node<T>();
  *this = ll;
}
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
  if(this != &ll){
    clear();
    const Node<T>* r = ll.first();
    Node<T>* p = head;
    while(r){
      insertNode(p,r->getData());
      r = r->getNext();
      p = p->getNext();
    }
  }
  return *this;
}
template <class T>
LinkedList<T>::~LinkedList(){
  clear();
  delete head;
}
template <class T>
Node<T>* LinkedList<T>::getHead() const{
  return head;
}
template <class T>
Node<T>* LinkedList<T>::first() const{
  return head->getNext();
}
template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
  Node<T>* pointer = getHead();
  while(pointer->getNext()){
    if(pointer->getNext()->getData() == data){
      return pointer;
    }
    pointer = pointer->getNext();
  }
  return NULL;
}
template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
  Node<T>* pointer = first();
  while(pointer){
    if(pointer->getData() == data){
      return pointer;
    }
    pointer = pointer->getNext();
  }
  return NULL;
}
template <class T>
void LinkedList<T>::insertNode(Node<T>* prev,const T& data){
  if(prev != NULL){
  Node<T>* pointer = new Node<T>(data);
  pointer->setNext(prev->getNext());
  prev->setNext(pointer);
  length++;
  }
}
template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
  if(prevNode != NULL || prevNode->getNext() != NULL){
    Node<T>* pointer = prevNode->getNext();
    prevNode->setNext(pointer->getNext());
    length--;
    delete pointer;
  }
}
template <class T>
void LinkedList<T>::clear(){
  Node<T>* dummy = getHead();

  while (dummy->getNext()){
      Node<T>* tmp = dummy->getNext();
      dummy->setNext(tmp->getNext());

      delete tmp;
  }
  length = 0;
}
template <class T>
size_t LinkedList<T>::getLength() const{
  return length;
}
template <class T>
void LinkedList<T>::swap(int index1, int index2){
  Node<T>* pointer1;
 Node<T>* pointer2;
 Node<T>* beforep1;
 Node<T>* beforep2;
 Node<T>* nextp1;
 Node<T>* nextp2;
 Node<T>* cursor = getHead();
 int indexOfCursor = 0;
 if(index1 == index2){
   return;
 }
 while(cursor){
     if(indexOfCursor == index1){
       beforep1 = cursor;
       pointer1 = cursor->getNext();
       nextp1 = pointer1->getNext();
       cursor = getHead();
       indexOfCursor = -1;
       break;
     }
     cursor = cursor->getNext();
     indexOfCursor++;
 }
 while(cursor){
     if(indexOfCursor == index2-1){
       beforep2 = cursor;
       pointer2 = cursor->getNext();
       nextp2 = pointer2->getNext();
       cursor = getHead();
       indexOfCursor = -1;
       break;
     }
     cursor = cursor->getNext();
     indexOfCursor++;
 }

 if(index1 - index2 == 1){
   beforep2->setNext(pointer1);
   pointer2->setNext(nextp1);
   pointer1->setNext(pointer2);
}

else if(index2 - index1 == 1){
   beforep1->setNext(pointer2);
   pointer1->setNext(nextp2);
   pointer2->setNext(pointer1);
}

else{
   beforep1->setNext(pointer2);
   beforep2->setNext(pointer1);
   pointer1->setNext(nextp2);
   pointer2->setNext(nextp1);
}
}

/* end of your implementations*/
#endif
