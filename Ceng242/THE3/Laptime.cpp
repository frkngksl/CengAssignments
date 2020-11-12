#include "Laptime.h"



/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Laptime::Laptime(int laptime){
  this->laptime = laptime;
  this->next = NULL;
}

Laptime::Laptime(){
  laptime = 0;
  next = NULL;
}

Laptime::Laptime(const Laptime& rhs){
  laptime = rhs.laptime;
  next = rhs.next;

}

Laptime::~Laptime(){
  ;
}

void Laptime::addLaptime(Laptime *next){
    this->next = next;
}

bool Laptime::operator<(const Laptime& rhs) const {
  if(laptime < rhs.laptime){
    return true;
  }
  else{
    return false;
  }
}

bool Laptime::operator>(const Laptime& rhs) const {
  if(laptime > rhs.laptime){
    return true;
  }
  else {
    return false;
  }
}

Laptime& Laptime::operator+(const Laptime& rhs){
  this->laptime = this->laptime + rhs.laptime;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Laptime& laptime){
  int givenLaptime = laptime.laptime;
  int minute=0;
  int second=0;
  minute = givenLaptime / 60000;
  if(minute != 0){
    givenLaptime = givenLaptime-(minute*60000);
  }
  second = givenLaptime / 1000;
  if(second != 0){
      givenLaptime = givenLaptime - (second*1000);
  }
  if(second<10){
    if(givenLaptime < 10){
      os << minute << ":0" << second << ".00" << givenLaptime;
    }
    else if(givenLaptime <100){
      os << minute << ":0" << second << ".0" << givenLaptime;
    }
    else{
      os << minute << ":0" << second << "." << givenLaptime;
    }
  }
  else{
    if(givenLaptime < 10){
      os << minute << ":" << second << ".00" << givenLaptime;
    }
    else if(givenLaptime <100){
      os << minute << ":" << second << ".0" << givenLaptime;
    }
    else{
      os << minute << ":" << second << "." << givenLaptime;
    }
  }
  return os;
}

int Laptime::getLaptime() const {
  return laptime;
}
Laptime* Laptime::getNext() const {
  return next;
};
