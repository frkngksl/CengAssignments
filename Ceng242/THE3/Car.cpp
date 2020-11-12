#include "Car.h"
#include "Utilizer.h"
#include <iostream>
#include <ctype.h>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/
Car::Car(std::string driver_name){
  this->driver_name = driver_name;
  this->performance = Utilizer::generatePerformance();
  this->next = NULL;
  this->head = new Laptime(0);
  this->totalPoint = 0;
}

Car::Car(std::string driver_name,double performance){
  this->driver_name = driver_name;
  this->performance = performance;
  this->next = NULL;
  this->head = new Laptime(0);
  this->totalPoint = 0;
}

Car::Car(const Car& rhs){
  this->driver_name = rhs.driver_name;
  this->performance = rhs.performance;
  this->next = rhs.next;
  this->head = new Laptime(0);
  const Laptime *r = rhs.head->getNext();
  Laptime *p = head;
  while(r){
    Laptime *newLap = new Laptime(r->getLaptime());
    p->addLaptime(newLap);
    r = r->getNext();
    p = p->getNext();
  }
  /*if(rhs.head == NULL){
    this->head = NULL;
  }
  else{
    const Laptime *r = rhs.head->getNext()
    this->head = new Laptime(rhs.head->getLaptime());
    Laptime *p = head;
    while(r){
      Laptime *newLap = new Laptime(r->getLaptime());
      p->addLaptime(newLap);
      r = r->getNext();
      p = p->getNext();
    }
  }
 */
 this->totalPoint = 0;
}

Car::~Car(){
  if(head !=NULL){
    Laptime* dummy = head;

    while (dummy->getNext()){
        Laptime* tmp = dummy->getNext();
        dummy->addLaptime(tmp->getNext());
        delete tmp;
    }
    delete dummy;
  }
}

std::string Car::getDriverName() const{
  return driver_name;
}

double Car::getPerformance() const{
  return performance;
}

void Car::addCar(Car *next){
  this->next = next;
}

bool Car::operator<(const Car& rhs) const{
  int totalCurrent = 0;
  int totalRhs = 0;
  const Laptime *curr = head->getNext();
  const Laptime *rhsCursor = rhs.head->getNext();
  while(rhsCursor){
    totalRhs = totalRhs + rhsCursor->getLaptime();
    rhsCursor = rhsCursor->getNext();
    }
  while(curr){
    totalCurrent = totalCurrent + curr->getLaptime();
    curr = curr->getNext();
    }
  if(totalCurrent < totalRhs){
    return true;
    }
  else {
    return false;
    }
}

bool Car::operator>(const Car& rhs) const{
  int totalCurrent = 0;
  int totalRhs = 0;
  const Laptime *curr = head->getNext();
  const Laptime *rhsCursor = rhs.head->getNext();
  while(rhsCursor){
    totalRhs = totalRhs + rhsCursor->getLaptime();
    rhsCursor = rhsCursor->getNext();
    }
  while(curr){
    totalCurrent = totalCurrent + curr->getLaptime();
    curr = curr->getNext();
    }
  if(totalCurrent > totalRhs){
    return true;
    }
  else {
    return false;
    }
}

Laptime Car::operator[](const int lap) const{
  const Laptime* cursor = head->getNext();
  int counter = 0;
  Laptime returnLaptime = Laptime(0);
  while(cursor){
    if(counter == lap){
      return *cursor;
    }
    counter++;
    cursor = cursor->getNext();
  }
  return returnLaptime;
}

void Car::Lap(const Laptime& average_laptime){
  int variance = Utilizer::generateLaptimeVariance(performance);
  int newTime = variance + average_laptime.getLaptime();
  Laptime* newLaptime = new Laptime(newTime);
  Laptime* cursor = head;
  while(cursor->getNext()){
    cursor = cursor->getNext();
    }
  cursor->addLaptime(newLaptime);
}
std::ostream& operator<<(std::ostream& os, const Car& car){
  const Laptime* cursor = car.head->getNext();
  const Laptime* fastest = cursor;
  if(cursor){
    int totalLap=0;
    int minute=0;
    int second=0;
    int beginning;
    char first;
    char secondN;
    char third;
    std::string driver_name = car.getDriverName();
    for(int i=0;;i++){
      if(driver_name[i] == ' '){
        beginning = i+1;
        break;
      }
    }
    first =  driver_name[beginning++];
    secondN =  driver_name[beginning++];
    third =  driver_name[beginning++];
    while(cursor){
      totalLap+=cursor->getLaptime();
      if(*cursor < *fastest){
        fastest = cursor;
      }
      if(cursor->getNext() == NULL){
        break;
      }
      else{
        cursor = cursor->getNext();
      }
    }
    if(*cursor < *fastest){
      fastest = cursor;
    }
    minute = totalLap/60000;
    if(minute != 0){
        totalLap = totalLap -(minute*60000);
    }
    second = totalLap/1000;
    if(second != 0){
        totalLap = totalLap - second*1000;
    }
    if(second<10){
      if(totalLap < 10){
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":0" << second << ".00" << totalLap;
      }
      else if(totalLap <100){
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":0" << second << ".0" << totalLap;
      }
      else{
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":0" << second << "." << totalLap;
      }
    }
    else{
      if(totalLap < 10){
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":" << second << ".00" << totalLap;
      }
      else if(totalLap <100){
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":" << second << ".0" << totalLap;
      }
      else{
        os << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << *cursor << "--" << *fastest << "--" << minute << ":" << second << "." << totalLap;
      }
    }
  }

  return os;
}

Car* Car::getNext() const{
  return this->next;
}

Laptime* Car::getHead() const{
  return this->head;
}

int Car::getFastest() const{
  const Laptime* cursor = head->getNext();
  const Laptime* fastest = cursor;
  if(cursor){
    while(cursor){
      if(*cursor < *fastest){
        fastest = cursor;
      }
      if(cursor->getNext() == NULL){
        break;
      }
      else{
        cursor = cursor->getNext();
      }
    }
    if(*cursor < *fastest){
      fastest = cursor;
    }
    return fastest->getLaptime();
  }
}

int Car::getTotalPoint() const{
  return this->totalPoint;
}
void Car::setTotalPoint(int point){
  this->totalPoint=point;
}
