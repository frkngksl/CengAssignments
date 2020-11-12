#include "Race.h"
#include "Utilizer.h"
#include <iostream>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Race::Race(std::string race_name){
  this->race_name = race_name;
  this->head = new Car("");
  this->average_laptime = Laptime(Utilizer::generateAverageLaptime());
}

Race::Race(const Race& rhs){
  this->race_name = rhs.race_name;
  this->average_laptime = rhs.average_laptime;
  this->head = new Car("");
  const Car* rh = rhs.head->getNext();
  Car *p = head;
  while(rh){
    Car* newCar = new Car(rh->getDriverName(),rh->getPerformance());
    p->addCar(newCar);
    rh = rh->getNext();
    p = p->getNext();
  }
}

Race::~Race(){
  if(head != NULL){
    Car *dummy = head;
    while(dummy->getNext()){
      Car *temp = dummy->getNext();
      dummy->addCar(temp->getNext());
      delete temp;
    }
      delete head;
  }
  head = NULL;
}

std::string Race::getRaceName() const{
  return race_name;
}
void Race::addCartoRace(){
  std::string alphabet = "qwertyuiopasdfghjklmnbvcxz";
  int name = (rand() %7) + 3;
  int surname = (rand() %7) +3;
  std::string first = "";
  std::string second ="";
  std::string full;
  for(int i=0;i<name;i++){
    first += alphabet[(rand() % 26)];
    second += alphabet[(rand() % 26)];
  }
  full = first + " " + second;
  Car newCar = Car(full);
  this->addCartoRace(newCar);
}

void Race::addCartoRace(Car& car){
  Car *cursor = head;
  Car *newCar = new Car(car.getDriverName(),car.getPerformance());
  while(cursor->getNext()){
    cursor = cursor->getNext();
  }
  cursor->addCar(newCar);
}

int Race::getNumberOfCarsinRace(){
  int count=0;
  Car *cursor = head->getNext();
  while(cursor){
    count++;
    cursor = cursor->getNext();
  }
  return count;
}

void Race::goBacktoLap(int lap){
  Car *cursor = head->getNext();
  bool sorted = false;
  int totalCar = this->getNumberOfCarsinRaceConst();
  while(cursor){
    Laptime* lapCursor = cursor->getHead()->getNext();
    for(int i=0;i<lap;i++){
      lapCursor = lapCursor->getNext();
    }
    if(lapCursor != NULL){
      Laptime* dummy = lapCursor;
      while(dummy->getNext()){
        Laptime* temp = dummy->getNext();
        dummy->addLaptime(temp->getNext());
        delete temp;
      }
    }
    cursor = cursor->getNext();
  }
  for(int i=0;(i < totalCar)&& !sorted; i++){
    sorted = true;
    cursor = head->getNext();
    for(int j=1;j<totalCar-i;j++){
      if(*cursor > *(cursor->getNext())){
      cursor=cursor->getNext();
      swap(j,j-1);
      sorted = false;
      }
        cursor=cursor->getNext();
    }
  }
}

void Race::operator++(){
  Car* cursor = head->getNext();
  int totalCar = getNumberOfCarsinRace();
  bool sorted = false;
  if(cursor){
    while(cursor){
      cursor->Lap(average_laptime);
      cursor = cursor->getNext();
    }
    for(int i=0;(i < totalCar)&& !sorted; i++){
      sorted = true;
      cursor = head->getNext();
      for(int j=1;j<totalCar-i;j++){
        if(*cursor > *(cursor->getNext())){
        cursor=cursor->getNext();
        swap(j,j-1);
        sorted = false;
        }
          cursor=cursor->getNext();
      }
    }
  }
}

void Race::operator--(){
  Car* cursor = head->getNext();
  int totalCar = getNumberOfCarsinRace();
  bool sorted = false;
  if(cursor){
    while(cursor){
      Laptime* lapCursor = cursor->getHead();
      while(lapCursor->getNext()){
        if(lapCursor->getNext()->getNext() == NULL){
          Laptime* temp = lapCursor->getNext();
          lapCursor->addLaptime(NULL);
          delete temp;
          break;
        }
        lapCursor=lapCursor->getNext();
      }
      cursor = cursor->getNext();
    }
    for(int i=0;(i < totalCar)&& !sorted; i++){
      sorted = true;
      cursor = head->getNext();
      for(int j=1;j< totalCar-i;j++){
        if(*cursor > *(cursor->getNext())){
        cursor=cursor->getNext();
        swap(j,j-1);
        sorted = false;
        }
          cursor=cursor->getNext();
      }
    }
  }
}

Car Race::operator[](const int car_in_position){
  Car* cursor = head->getNext();
  int counter = 0;
  while(cursor){
    if(counter == car_in_position){
      return *cursor;
    }
    ++counter;
    cursor = cursor->getNext();
  }
}

Car Race::operator[](std::string driver_name){
  Car* cursor = head->getNext();
  while(cursor){
    if((cursor->getDriverName()).compare(driver_name) == 0){
      return *cursor;
    }
    cursor = cursor->getNext();
  }
}

Race& Race::operator=(const Race& rhs){
  if(head != NULL){
    Car *dummy = head;
    while(dummy->getNext()){
      Car *temp = dummy->getNext();
      dummy->addCar(temp->getNext());
      delete temp;
    }
  }
  this->head = rhs.head;
}

std::ostream& operator<<(std::ostream& os, const Race& race){
  int totalCar = race.getNumberOfCarsinRaceConst();
  const Car* cursorCar = race.head->getNext();
  int fastestIndex;
  int fastestTime;
  if(cursorCar == NULL){
    return os;
  }
  if(cursorCar->getHead()->getNext() == NULL){
    return os;
  }
  fastestIndex = 0;
  fastestTime = race.fastestLapFromIndex(0);
  for(int counter = 1; counter < totalCar ; counter++){
    if(fastestTime > race.fastestLapFromIndex(counter)){
      fastestTime = race.fastestLapFromIndex(counter);
      fastestIndex = counter;
    }
  }
  for(int counter = 0; counter < totalCar ; counter++){
    if(counter == 0){
      if(fastestIndex == counter){
        if(totalCar >=10000){
          os << "00001--" << *cursorCar << "--25--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0001--" << *cursorCar << "--25--" << "1";
        }
        else if(totalCar >= 100){
          os << "001--" << *cursorCar << "--25--" << "1";
        }
        else if(totalCar >= 10){
          os << "01--" << *cursorCar << "--25--" << "1";
        }
        else{
            os << "1--" << *cursorCar << "--25--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00001--" << *cursorCar << "--25";
        }
        else if(totalCar >= 1000){
          os << "0001--" << *cursorCar << "--25";
        }
        else if(totalCar >= 100){
          os << "001--" << *cursorCar << "--25";
        }
        else if(totalCar >= 10){
          os << "01--" << *cursorCar << "--25";
        }
        else{
            os << "1--" << *cursorCar << "--25";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 1){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00002--" << *cursorCar << "--18--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0002--" << *cursorCar << "--18--" << "1";
        }
        else if(totalCar >= 100){
          os << "002--" << *cursorCar << "--18--" << "1";
        }
        else if(totalCar >= 10){
          os << "02--" << *cursorCar << "--18--" << "1";
        }
        else{
            os << "2--" << *cursorCar << "--18--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00002--" << *cursorCar << "--18";
        }
        else if(totalCar >= 1000){
          os << "0002--" << *cursorCar << "--18";
        }
        else if(totalCar >= 100){
          os << "002--" << *cursorCar << "--18";
        }
        else if(totalCar >= 10){
          os << "02--" << *cursorCar << "--18";
        }
        else{
            os << "2--" << *cursorCar << "--18";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 2){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00003--" << *cursorCar << "--15--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0003--" << *cursorCar << "--15--" << "1";
        }
        else if(totalCar >= 100){
          os << "003--" << *cursorCar << "--15--" << "1";
        }
        else if(totalCar >= 10){
          os << "03--" << *cursorCar << "--15--" << "1";
        }
        else{
            os << "3--" << *cursorCar << "--15--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00003--" << *cursorCar << "--15";
        }
        else if(totalCar >= 1000){
          os << "0003--" << *cursorCar << "--15";
        }
        else if(totalCar >= 100){
          os << "003--" << *cursorCar << "--15";
        }
        else if(totalCar >= 10){
          os << "03--" << *cursorCar << "--15";
        }
        else{
            os << "3--" << *cursorCar << "--15";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 3){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00004--" << *cursorCar << "--12--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0004--" << *cursorCar << "--12--" << "1";
        }
        else if(totalCar >= 100){
          os << "004--" << *cursorCar << "--12--" << "1";
        }
        else if(totalCar >= 10){
          os << "04--" << *cursorCar << "--12--" << "1";
        }
        else{
            os << "4--" << *cursorCar << "--12--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00004--" << *cursorCar << "--12";
        }
        else if(totalCar >= 1000){
          os << "0004--" << *cursorCar << "--12";
        }
        else if(totalCar >= 100){
          os << "004--" << *cursorCar << "--12";
        }
        else if(totalCar >= 10){
          os << "04--" << *cursorCar << "--12";
        }
        else{
            os << "4--" << *cursorCar << "--12";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 4){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00005--" << *cursorCar << "--10--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0005--" << *cursorCar << "--10--" << "1";
        }
        else if(totalCar >= 100){
          os << "005--" << *cursorCar << "--10--" << "1";
        }
        else if(totalCar >= 10){
          os << "05--" << *cursorCar << "--10--" << "1";
        }
        else{
            os << "5--" << *cursorCar << "--10--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00005--" << *cursorCar << "--10";
        }
        else if(totalCar >= 1000){
          os << "0005--" << *cursorCar << "--10";
        }
        else if(totalCar >= 100){
          os << "005--" << *cursorCar << "--10";
        }
        else if(totalCar >= 10){
          os << "05--" << *cursorCar << "--10";
        }
        else{
            os << "5--" << *cursorCar << "--10";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 5){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00006--" << *cursorCar << "--8--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0006--" << *cursorCar << "--8--" << "1";
        }
        else if(totalCar >= 100){
          os << "006--" << *cursorCar << "--8--" << "1";
        }
        else if(totalCar >= 10){
          os << "06--" << *cursorCar << "--8--" << "1";
        }
        else{
            os << "6--" << *cursorCar << "--8--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00006--" << *cursorCar << "--8";
        }
        else if(totalCar >= 1000){
          os << "0006--" << *cursorCar << "--8";
        }
        else if(totalCar >= 100){
          os << "006--" << *cursorCar << "--8";
        }
        else if(totalCar >= 10){
          os << "06--" << *cursorCar << "--8";
        }
        else{
            os << "6--" << *cursorCar << "--8";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 6){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00007--" << *cursorCar << "--6--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0007--" << *cursorCar << "--6--" << "1";
        }
        else if(totalCar >= 100){
          os << "007--" << *cursorCar << "--6--" << "1";
        }
        else if(totalCar >= 10){
          os << "07--" << *cursorCar << "--6--" << "1";
        }
        else{
            os << "7--" << *cursorCar << "--6--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00007--" << *cursorCar << "--6";
        }
        else if(totalCar >= 1000){
          os << "0007--" << *cursorCar << "--6";
        }
        else if(totalCar >= 100){
          os << "007--" << *cursorCar << "--6";
        }
        else if(totalCar >= 10){
          os << "07--" << *cursorCar << "--6";
        }
        else{
            os << "7--" << *cursorCar << "--6";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 7){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00008--" << *cursorCar << "--4--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0008--" << *cursorCar << "--4--" << "1";
        }
        else if(totalCar >= 100){
          os << "008--" << *cursorCar << "--4--" << "1";
        }
        else if(totalCar >= 10){
          os << "08--" << *cursorCar << "--4--" << "1";
        }
        else{
            os << "8--" << *cursorCar << "--4--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00008--" << *cursorCar << "--4";
        }
        else if(totalCar >= 1000){
          os << "0008--" << *cursorCar << "--4";
        }
        else if(totalCar >= 100){
          os << "008--" << *cursorCar << "--4";
        }
        else if(totalCar >= 10){
          os << "08--" << *cursorCar << "--4";
        }
        else{
            os << "8--" << *cursorCar << "--4";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 8){
      if(fastestIndex == counter){
        if(totalCar >=10000){
          os << "00009--" << *cursorCar << "--2--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0009--" << *cursorCar << "--2--" << "1";
        }
        else if(totalCar >= 100){
          os << "009--" << *cursorCar << "--2--" << "1";
        }
        else if(totalCar >= 10){
          os << "09--" << *cursorCar << "--2--" << "1";
        }
        else{
            os << "9--" << *cursorCar << "--2--" << "1";
        }
      }
      else{
       if(totalCar >=10000){
          os << "00009--" << *cursorCar << "--2";
        }
        else if(totalCar >= 1000){
          os << "0009--" << *cursorCar << "--2";
        }
        else if(totalCar >= 100){
          os << "009--" << *cursorCar << "--2";
        }
        else if(totalCar >= 10){
          os << "09--" << *cursorCar << "--2";
        }
        else{
            os << "9--" << *cursorCar << "--2";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else if(counter == 9){
      if(fastestIndex == counter){
         if(totalCar >=10000){
          os << "00010--" << *cursorCar << "--1--" << "1";
        }
        else if(totalCar >= 1000){
          os << "0010--" << *cursorCar << "--1--" << "1";
        }
        else if(totalCar >= 100){
          os << "010--" << *cursorCar << "--1--" << "1";
        }
        else if(totalCar >= 10){
          os << "10--" << *cursorCar << "--1--" << "1";
        }
      }
      else{
         if(totalCar >=10000){
          os << "00010--" << *cursorCar << "--1";
        }
        else if(totalCar >= 1000){
          os << "0010--" << *cursorCar << "--1";
        }
        else if(totalCar >= 100){
          os << "010--" << *cursorCar << "--1";
        }
        else if(totalCar >= 10){
          os << "10--" << *cursorCar << "--1";
        }
      }
      if(counter + 1 != totalCar){
        os << std::endl;
      }
    }
    else{
    if(totalCar >=10000){
      if(counter < 100){
        os << "000" << counter+1 << "--" << *cursorCar << "--0";
      }
      else if( counter < 1000){
          os << "00" << counter+1 << "--" << *cursorCar << "--0";
      }
      else if(counter < 10000){
        os << "0" << counter+1 << "--" << *cursorCar << "--0";
      }
      else{
         os << counter+1 << "--" << *cursorCar << "--0";
      }
     }
     else if(totalCar >= 1000){
       if(counter < 99){
         os << "00" << counter+1 << "--"<< *cursorCar << "--0";
       }
       else if(counter < 999){
         os << "0" << counter+1 << "--" << *cursorCar << "--0";
       }
       else {
         os << counter+1 << "--" << *cursorCar << "--0";
       }
     }
     else if(totalCar >= 100){
       if(counter < 99){
            os << "0" << counter+1  << "--" << *cursorCar << "--0";
       }
       else{
            os  << counter+1 << "--" << *cursorCar << "--0";
       }
     }
     else if(totalCar >= 10){
       os << counter+1 << "--" << *cursorCar << "--0";
     }
     if(counter + 1 != totalCar){
       os << std::endl;
     }
    }
    cursorCar = cursorCar->getNext();
  }
  return os;
}

void Race::swap(int index1, int index2){
  Car* pointer1;
  Car* pointer2;
  Car* beforep1;
  Car* beforep2;
  Car* nextp1;
  Car* nextp2;
  Car* cursor = head;
  int indexOfCursor = 0;
  if(index1 == index2){
    return;
  }
  while(cursor){
     if(indexOfCursor == index1){
       beforep1 = cursor;
       pointer1 = cursor->getNext();
       nextp1 = pointer1->getNext();
       cursor = head;
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
       cursor = head;
       indexOfCursor = -1;
       break;
     }
     cursor = cursor->getNext();
     indexOfCursor++;
 }

 if(index1 - index2 == 1){
   beforep2->addCar(pointer1);
   pointer2->addCar(nextp1);
   pointer1->addCar(pointer2);
 }
 else if(index2 - index1 == 1){
   beforep1->addCar(pointer2);
   pointer1->addCar(nextp2);
   pointer2->addCar(pointer1);
 }
 else{
   beforep1->addCar(pointer2);
   beforep2->addCar(pointer1);
   pointer1->addCar(nextp2);
   pointer2->addCar(nextp1);
 }
}

int Race::getNumberOfCarsinRaceConst() const{
  int count=0;
  Car *cursor = head->getNext();
  while(cursor){
    count++;
    cursor = cursor->getNext();
  }
  return count;
}

int Race::fastestLapFromIndex(int index) const{
  int counter = 0;
  Car* cursor = head->getNext();
  while(cursor){
    if(counter == index){
      return cursor->getFastest();
    }
    cursor = cursor->getNext();
    counter++;
  }
  /*while(cursor){
    if((*cursor)[index] < fastest){
      fastest = (*cursor)[index];
      first = counter;
    }
    if(cursor->getNext() == NULL){
      break;
    }
    else{
      cursor = cursor->getNext();
      counter++;
    }
  }
  return fastest.getLaptime(); */
}
void Race::setName(std::string name){
  race_name = name;
}

Car* Race::getHead(){
  return head;
}

void Race::setAverageLaptime(int number){
    this->average_laptime = Laptime(number);
  }
