#include "Championship.h"
#include <ctype.h>
#include "Utilizer.h"
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Championship::Championship(){
  headForPoint = new Car("");
}

Championship::Championship(const Championship& rhs){
  int size = rhs.races.size();
  for(int i=0; i<size;i++){
      Race* newRace = new Race(*(rhs.races[i]));
      races.push_back(newRace);
  }
}

Championship::~Championship(){
  if(headForPoint != NULL){
    Car *dummy = headForPoint;
    while(dummy->getNext()){
      Car *temp = dummy->getNext();
      dummy->addCar(temp->getNext());
      delete temp;
    }
      delete headForPoint;
  }
  headForPoint = NULL;
  for(int i=1; i<races.size();i++){
      delete races[i];
  }
}

void Championship::addNewRace(Race& race){
  races.push_back(&race);
  const Car* rh = race.getHead()->getNext();
  Car *p = headForPoint;
  while(rh){
    Car* newCar = new Car(rh->getDriverName(),rh->getPerformance());
    p->addCar(newCar);
    rh = rh->getNext();
    p = p->getNext();
  }
}

void Championship::addNewRace(std::string race_name){
  Race* newRace = new Race(*(races.front()));
  newRace->setName(race_name);
  newRace->setAverageLaptime(Utilizer::generateAverageLaptime());
  races.push_back(newRace);
}

void Championship::removeRace(std::string race_name){
  int size = races.size();
  for(int i=0;i<size;i++){
    if(races[i]->getRaceName() == race_name){
      delete races[i];
      races.erase(i+races.begin());
      break;
    }
  }
}

void Championship::addLap(std::string race_name){
  int size = races.size();
  for(int i=0;i<size;i++){
    if(races[i]->getRaceName() == race_name){
      ++(*races[i]);
      break;
    }
  }
}

Race& Championship::operator[](std::string race_name){
  int size = races.size();
  for(int i=0;i<size;i++){
    if(races[i]->getRaceName() == race_name){
      return *(races[i]);
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Championship& championship){
  int size = championship.races.size();
  Car* cursor = championship.headForPoint->getNext();
  int totalCar = championship.races[0]->getNumberOfCarsinRace();
  const Car* cursorCar1 = championship.races[0]->getHead()->getNext();
  bool sorted = false;
  for(int i=0;i<size;i++){
    const Car* cursorCar = championship.races[i]->getHead()->getNext();
    int totalCar = championship.races[i]->getNumberOfCarsinRaceConst();
    int fastestIndex;
    int fastestTime;
    if(championship.races[i]->getHead()->getNext()->getHead()->getNext() == NULL){
      continue;
    }
    fastestIndex = 0;
    fastestTime = championship.races[i]->fastestLapFromIndex(0);
    for(int counter = 1; counter < totalCar ; counter++){
      if(fastestTime > championship.races[i]->fastestLapFromIndex(counter)){
        fastestTime = championship.races[i]->fastestLapFromIndex(counter);
        fastestIndex = counter;
      }
    }
    for(int counter = 0; counter < totalCar ; counter++){
      if(counter == 0){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+25);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
        }
      else if(counter == 1){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+18);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
    }
      else if(counter == 2){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+15);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 3){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+12);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 4){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+10);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 5){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+8);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 6){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+6);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 7){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+4);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 8){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+2);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      else if(counter == 9){
        Car* addingCar = championship.findCarByName(cursorCar->getDriverName());
        addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
        if(fastestIndex == counter){
          addingCar->setTotalPoint(addingCar->getTotalPoint()+1);
          }
      }
      cursorCar = cursorCar->getNext();
    }
  }

  for(int i=0;(i < totalCar)&& !sorted; i++){
    sorted = true;
    cursor = championship.headForPoint->getNext();
    for(int j=1;j< totalCar-i;j++){
      if(cursor->getTotalPoint() < cursor->getNext()->getTotalPoint()){
      cursor=cursor->getNext();
      championship.swap1(j,j-1);
      sorted = false;
      }
        cursor=cursor->getNext();
    }
  }
  cursor = championship.headForPoint->getNext();
  for(int counter=0;counter<totalCar;counter++){
    char first;
    int beginning =0;
    char secondN;
    char third;
    std::string driver_name = cursor->getDriverName();
    for(int i=0;;i++){
      if(driver_name[i] == ' '){
        beginning = i+1;
        break;
      }
    }
    first =  driver_name[beginning++];
    secondN =  driver_name[beginning++];
    third =  driver_name[beginning++];
    if(counter == 0){
        if(totalCar >=10000){
          os << "00001--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
        }
        else if(totalCar >= 1000){
          os << "0001--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
        }
        else if(totalCar >= 100){
          os << "001--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
        }
        else if(totalCar >= 10){
          os << "01--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
        }
        else{
            os << "1--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
        }
        os << std::endl;
    }
    else if(counter == 1){
      if(totalCar >=10000){
        os << "00002--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0002--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "002--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "02--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "2--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 2){
      if(totalCar >=10000){
        os << "00003--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0003--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "003--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "03--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "3--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 3){
      if(totalCar >=10000){
        os << "00004--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0004--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "004--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "04--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "4--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 4){
      if(totalCar >=10000){
        os << "00005--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0005--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "005--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "05--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "5--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 5){
      if(totalCar >=10000){
        os << "00006--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0006--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "006--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "06--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "6--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 6){
      if(totalCar >=10000){
        os << "00007--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0007--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "007--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "07--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "7--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 7){
      if(totalCar >=10000){
        os << "00008--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0008--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "008--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "08--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "8--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
    }
    else if(counter == 8){
      if(totalCar >=10000){
        os << "00009--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0009--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "009--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "09--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
          os << "9--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;

    }
    else if(counter == 9){
      if(totalCar >=10000){
        os << "00010--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 1000){
        os << "0010--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 100){
        os << "010--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(totalCar >= 10){
        os << "10--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      os << std::endl;
      }
    else{
    if(totalCar >=10000){
      if(counter < 100){
        os << "000" << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if( counter < 1000){
          os << "00" << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else if(counter < 10000){
        os << "0" << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
      else{
         os << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
      }
     }
     else if(totalCar >= 1000){
       if(counter < 100){
         os << "00" << counter+1 << "--"<< (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
       }
       else if(counter < 1000){
         os << "0" << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
       }
       else {
         os << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
       }
     }
     else if(totalCar >= 100){
       if(counter < 100){
            os << "0" << counter+1  << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
       }
       else{
            os  << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
       }
     }
     else if(totalCar >= 10){
       os << counter+1 << "--" << (char) toupper(first) << (char) toupper(secondN) << (char) toupper(third) << "--" << cursor->getTotalPoint();
     }
       os << std::endl;
    }
    cursor = cursor->getNext();
  }

  for(int counter = 0; counter < totalCar ; counter++){
      Car* addingCar = championship.findCarByName(cursorCar1->getDriverName());
      addingCar->setTotalPoint(0);
      cursorCar1 = cursorCar1->getNext();
  }
  return os;
  }


Car* Championship::findCarByName(std::string name) const{
  Car* cursor = headForPoint->getNext();
  while(cursor){
    if(cursor->getDriverName() == name){
      return cursor;
    }
    cursor = cursor->getNext();
  }
}

void Championship::swap1(int index1, int index2) const{
  Car* pointer1;
  Car* pointer2;
  Car* beforep1;
  Car* beforep2;
  Car* nextp1;
  Car* nextp2;
  Car* cursor = headForPoint;
  int indexOfCursor = 0;
  if(index1 == index2){
    return;
  }
  while(cursor){
     if(indexOfCursor == index1){
       beforep1 = cursor;
       pointer1 = cursor->getNext();
       nextp1 = pointer1->getNext();
       cursor = headForPoint;
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
       cursor = headForPoint;
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
