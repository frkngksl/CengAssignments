#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "monitor.h"
#include <vector>


using namespace std;

long travelTime;
long idleTime;
long inOutTime;

class ElevatorMonitor;

struct personThreadParams{
    int personID;
    int destinationFloor;
    int sourceFloor;
    int priority;
    int weight;
    ElevatorMonitor *monitorPtr;
};

class ElevatorMonitor:public Monitor{

    Condition upwardPerson;
    Condition downwardPerson;
    Condition capacityCV;
    Condition waitReq;
    Condition floorsVariableInElevator;
    Condition lowWaitOnFloor;
    Condition highWaitOnFloor;
    int numberOfPersonLeft;
    int currentPerson;
    int currentWeight;
    int totalWeightCapacity;
    int totalPersonCapacity;
    enum state {idle,movingUp,movingDown}stateOfElevator;
    bool *personsEntrance;
    bool *requestOnFloor;
    int *highPriorityWaitersOnFloor;
    int *lowPriorityWaitersOnFloor;
    int currentFloor;
    int currentRequests;
    int numberOfFloors;
    public:
        ElevatorMonitor(int totalWeight,int totalFloor,int totalPerson):upwardPerson(this),downwardPerson(this),capacityCV(this),waitReq(this),floorsVariableInElevator(this),lowWaitOnFloor(this),highWaitOnFloor(this){
            stateOfElevator = idle;
            this->numberOfFloors = totalFloor;
            this->totalWeightCapacity = totalWeight;
            requestOnFloor = new bool[totalFloor];
            highPriorityWaitersOnFloor = new int[totalFloor];
            lowPriorityWaitersOnFloor = new int[totalFloor];
            for(int i=0;i<totalFloor;i++){
                requestOnFloor[i] = false;
                highPriorityWaitersOnFloor[i] = 0;
                lowPriorityWaitersOnFloor[i] = 0;
            }
            totalPersonCapacity = totalPerson;
            currentFloor = 0;
            currentPerson = 0;
            currentWeight = 0;
            currentRequests = 0;
            numberOfPersonLeft = totalPerson;
            personsEntrance = new bool[totalPerson];
            for(int i=0;i<totalPerson;i++){
                personsEntrance[i] = false;
            }
        }
        ~ElevatorMonitor(){
            delete[] requestOnFloor;
            delete[] highPriorityWaitersOnFloor;
            delete[] lowPriorityWaitersOnFloor;
            delete[] personsEntrance;
        }
        bool canEnter(int weight){
            if((currentPerson+1 <= totalPersonCapacity) && weight+currentWeight <=totalWeightCapacity){
                return true;
            }
            return false;
        }
        void printElevatorState(){
            bool firstTime = true;
            if(stateOfElevator == idle){
                    cout << "Elevator (Idle, " << currentWeight << ", " << currentPerson << ", " << currentFloor << " ->";
                    for(int i=0;i<numberOfFloors;i++){
                        if(requestOnFloor[i]){
                            if(firstTime){
                                cout << " "<< i;
                                firstTime = false;
                            }
                            else{
                                cout << "," << i;
                            }
                        }
                    }
                    cout << ")" << endl;
            }
            else if(stateOfElevator == movingUp){
                cout << "Elevator (Moving-up, " << currentWeight << ", " << currentPerson << ", " << currentFloor << " ->";
                for(int i=0;i<numberOfFloors;i++){
                    if(requestOnFloor[i]){
                        if(firstTime){
                            cout << " " << i;
                            firstTime = false;
                        }
                        else{
                            cout << "," << i;
                        }
                    }
                }
                cout << ")" << endl;
            }
            else if(stateOfElevator == movingDown){
                cout << "Elevator (Moving-down, " << currentWeight << ", " << currentPerson << ", " << currentFloor <<  " ->";
                for(int i=numberOfFloors-1;i>=0;i--){
                    if(requestOnFloor[i]){
                        if(firstTime){
                            cout << " " <<i;
                            firstTime = false;
                        }
                        else{
                            cout << "," << i;
                        }
                    }
                }
                cout << ")" << endl;
            }
        }
        void printRequest(int personId,int weight, int source, int destination,int priority){
            if(priority == 1){
                cout << "Person (" << personId << ", hp, " << source << " -> " << destination << ", " << weight << ") made a request" << endl;

            }
            else if(priority == 2){
                cout << "Person (" << personId << ", lp, " << source << " -> " << destination << ", " << weight << ") made a request" << endl;
            }
        }
        void printEntrance(int personId,int weight,int source, int destination, int priority){
            if(priority == 1){
                cout << "Person (" << personId << ", hp, " << source << " -> " << destination << ", " << weight << ") entered the elevator" << endl;

            }
            else if(priority == 2){
                cout << "Person (" << personId << ", lp, " << source << " -> " << destination << ", " << weight << ") entered the elevator" << endl;
            }
        }
        void printExit(int personId,int weight,int source, int destination, int priority){
            if(priority == 1){
                cout << "Person (" << personId << ", hp, " << source << " -> " << destination << ", " << weight << ") has left the elevator" << endl;

            }
            else if(priority == 2){
                cout << "Person (" << personId << ", lp, " << source << " -> " << destination << ", " << weight << ") has left the elevator" << endl;
            }
        }
        bool isDestQueueEmpty(){
            for(int i=0;i<numberOfFloors;i++){
                if(requestOnFloor[i]){
                    return false;
                }
            }
            return true;
        }
        void highPriorityEnterance(int personId,int weight, int source, int destination,int priority){
            currentPerson++;
            currentWeight += weight;
            personsEntrance[personId] = true;
            highPriorityWaitersOnFloor[source]--;
            if(isDestQueueEmpty()){
                if(destination > source){
                    stateOfElevator = movingUp;
                }
                else{
                    stateOfElevator = movingDown;
                }
            }
            requestOnFloor[destination] = true;
            printEntrance(personId,weight,source,destination,priority);
            printElevatorState();

        }
        void highPriorityCannotEnter(int personId,int weight, int source, int destination,int priority){
            highPriorityWaitersOnFloor[source]--;
        }
        void lowPriorityEnterance(int personId, int weight, int source, int destination, int priority){
            currentPerson++;
            currentWeight += weight;
            personsEntrance[personId] = true;
            lowPriorityWaitersOnFloor[source]--; // is this required?
            if(isDestQueueEmpty()){
                if(destination > source){
                    stateOfElevator = movingUp;
                }
                else{
                    stateOfElevator = movingDown;
                }
            }
            requestOnFloor[destination] = true;
            printEntrance(personId,weight,source,destination,priority);
            printElevatorState();
        }
        void makeRequest(int personId,int weight, int source, int destination,int priority){
            __synchronized__;
            while(personsEntrance[personId] == false){
                if(stateOfElevator == idle){
                    /* makeRequest */
                    if(destination > source){
                        //Yukarı çıkcam
                        if(currentFloor > source){
                            //Asansörün inmesi gerek
                            requestOnFloor[source] = true;
                            stateOfElevator = movingDown;
                            currentRequests++;
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            downwardPerson.notifyAll();
                            upwardPerson.wait();
                            currentRequests--;
                        }
                        else if(source > currentFloor){
                            //Asansörün çıkması gerek
                            requestOnFloor[source] = true;
                            stateOfElevator = movingUp;
                            currentRequests++;
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            upwardPerson.notifyAll();
                            if(priority == 1){ // high priority
                                highPriorityWaitersOnFloor[source]++;
                                while(1){
                                    //cout << "Beklemeye geçiyorum" << endl;
                                    highWaitOnFloor.wait();
                                    //cout << "Ben uyandım" << endl;
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                    //cout << "geri uyuyom" << endl;
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                while(1){
                                    lowWaitOnFloor.wait();
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                        else { //source == currentFloor
                            //Asansörle Aynı yerdeyiz
                            //priority Difference ?
                            //idle olsa bile controller threadde uyandırsın
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            currentRequests++;
                            //requestOnFloor[source] = true; TODO
                            if(priority == 1){ // high priority SORUN: IDLE OLDU KIM İSTEK ATACAK
                                highPriorityWaitersOnFloor[source]++;
                                /*while(1){
                                    //cout << "Beklemeye geçiyorum" << endl;
                                    highWaitOnFloor.wait();
                                    //cout << "Ben uyandım" << endl;
                                    if(currentFloor == source){
                                        break;
                                    }
                                    //cout << "geri uyuyom" << endl;
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                /*
                                while(1){
                                    //cout << "Beklemeye geçiyorum" << endl;
                                    lowWaitOnFloor.wait();
                                    //cout << "Ben uyandım" << endl;
                                    if(currentFloor == source){
                                        break;
                                    }
                                    //cout << "geri uyuyom" << endl;
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                    }
                    else if(source > destination){
                        //Aşağı incem
                        if(currentFloor > source){
                            //Asansör aşağı incek
                            requestOnFloor[source] = true;
                            stateOfElevator = movingDown;
                            currentRequests++;
                            downwardPerson.notifyAll();
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            if(priority == 1){ // high priority
                                highPriorityWaitersOnFloor[source]++;
                                while(1){
                                    highWaitOnFloor.wait();
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                while(1){
                                    lowWaitOnFloor.wait();
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                        else if(source > currentFloor){
                            //asansör yukarı çıkcak
                            requestOnFloor[source] = true;
                            stateOfElevator = movingUp;
                            currentRequests++;
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            upwardPerson.notifyAll();
                            downwardPerson.wait();
                            currentRequests--;
                        }
                        else{
                            //eşitiz
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            currentRequests++;
                            //requestOnFloor[source] = true; TODO
                            if(priority == 1){ // high priority
                                highPriorityWaitersOnFloor[source]++;
                                /*while(1){
                                    highWaitOnFloor.wait();
                                    if(currentFloor == source){
                                        break;
                                    }
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                /*
                                while(1){
                                    lowWaitOnFloor.wait();
                                    if(currentFloor == source){
                                        break;
                                    }
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                    }
                    //----------------
                }
                else if(stateOfElevator == movingUp){
                    if(destination > source){
                            //Ben yukarı çıkcam
                            if(currentFloor > source){
                                //asansör yukarımda kaldı inmeyecek
                                upwardPerson.wait();
                            }
                            else if(source > currentFloor){
                                //asansörden üstteyim
                                requestOnFloor[source] = true;
                                currentRequests++;
                                printRequest(personId,weight,source,destination,priority);
                                printElevatorState();
                                if(priority == 1){ // high priority
                                    highPriorityWaitersOnFloor[source]++;
                                    while(1){
                                        highWaitOnFloor.wait();
                                        if(currentFloor == source || stateOfElevator == idle){
                                            break;
                                        }
                                    }
                                    currentRequests--;
                                    if(stateOfElevator == idle){
                                        continue;
                                    }
                                    if(canEnter(weight)){
                                        highPriorityEnterance(personId,weight,source,destination,priority);
                                        if(highPriorityWaitersOnFloor[source] == 0){
                                            lowWaitOnFloor.notifyAll();
                                        }
                                    }
                                    else{
                                        highPriorityCannotEnter(personId,weight,source,destination,priority);
                                        if(highPriorityWaitersOnFloor[source] == 0){
                                            lowWaitOnFloor.notifyAll();
                                        }
                                        capacityCV.wait();
                                    }
                                }
                                else if(priority == 2){ //low priority
                                    lowPriorityWaitersOnFloor[source]++;
                                    while(1){
                                        lowWaitOnFloor.wait();
                                        if(currentFloor == source || stateOfElevator == idle){
                                            break;
                                        }
                                    }
                                    currentRequests--;
                                    if(stateOfElevator == idle){
                                        continue;
                                    }
                                    if(canEnter(weight)){
                                        //cout << "Can enter" << endl;
                                        lowPriorityEnterance(personId,weight,source,destination,priority);
                                    }
                                    else{
                                        //cout << "Can't" << endl;
                                        lowPriorityWaitersOnFloor[source]--;
                                        capacityCV.wait();
                                    }
                                }
                            }
                            else{
                                //asansörle aynı kattayım
                                //TODO
                                printRequest(personId,weight,source,destination,priority);
                                printElevatorState();
                                currentRequests++;
                                //requestOnFloor[source] = true; TODO
                                if(priority == 1){ // high priority SORUN: IDLE OLDU KIM İSTEK ATACAK
                                    highPriorityWaitersOnFloor[source]++;
                                    /*while(1){
                                        //cout << "Beklemeye geçiyorum" << endl;
                                        highWaitOnFloor.wait();
                                        //cout << "Ben uyandım" << endl;
                                        if(currentFloor == source || stateOfElevator == idle){
                                            break;
                                        }
                                        //cout << "geri uyuyom" << endl;
                                    }

                                    if(stateOfElevator == idle){
                                        continue;
                                    }*/
                                    currentRequests--;
                                    if(canEnter(weight)){
                                        highPriorityEnterance(personId,weight,source,destination,priority);
                                        if(highPriorityWaitersOnFloor[source] == 0){
                                            lowWaitOnFloor.notifyAll();
                                        }
                                    }
                                    else{
                                        highPriorityCannotEnter(personId,weight,source,destination,priority);
                                        if(highPriorityWaitersOnFloor[source] == 0){
                                            lowWaitOnFloor.notifyAll();
                                        }
                                        capacityCV.wait();
                                    }
                                }
                                else if(priority == 2){ //low priority
                                    lowPriorityWaitersOnFloor[source]++;
                                    /*while(1){
                                        //cout << "Beklemeye geçiyorum" << endl;
                                        lowWaitOnFloor.wait();
                                        //cout << "Ben uyandım" << endl;
                                        if(currentFloor == source || stateOfElevator == idle){
                                            break;
                                        }
                                        //cout << "geri uyuyom" << endl;
                                    }

                                    if(stateOfElevator == idle){
                                        continue;
                                    }*/
                                    currentRequests--;
                                    if(canEnter(weight)){
                                        //cout << "Can enter" << endl;
                                        lowPriorityEnterance(personId,weight,source,destination,priority);
                                    }
                                    else{
                                        //cout << "Can't" << endl;
                                        lowPriorityWaitersOnFloor[source]--;
                                        capacityCV.wait();
                                    }
                                }
                            }
                    }
                    else if(source > destination){
                        //Ben aşağı incem bu yüzden beklemeliyim
                        downwardPerson.wait();
                    }
                }
                else if(stateOfElevator == movingDown){
                    if(destination > source){
                            //Ben yukarı çıkcam bu yüzden beklemeliyim
                            upwardPerson.wait();
                    }
                    else if(source > destination){
                        //Ben aşağı incem
                        if(currentFloor > source){
                            //asansör zaten aşağı incek beni de alsın
                            requestOnFloor[source] = true;
                            currentRequests++;
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            if(priority == 1){ // high priority
                                highPriorityWaitersOnFloor[source]++;
                                while(1){
                                    highWaitOnFloor.wait();
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                while(1){
                                    lowWaitOnFloor.wait();
                                    if(currentFloor == source || stateOfElevator == idle){
                                        break;
                                    }
                                }
                                currentRequests--;
                                if(stateOfElevator == idle){
                                    continue;
                                }
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                        else if(source > currentFloor){
                            //asansörden üstteyim bu yüzden beklemeliyim
                            downwardPerson.wait();
                        }
                        else{
                            //asansörle aynı kattayım
                            //TODO
                            printRequest(personId,weight,source,destination,priority);
                            printElevatorState();
                            currentRequests++;
                            //requestOnFloor[source] = true; TODO
                            if(priority == 1){ // high priority SORUN: IDLE OLDU KIM İSTEK ATACAK
                                highPriorityWaitersOnFloor[source]++;
                               /*
                                while(1){
                                    //cout << "Beklemeye geçiyorum" << endl;
                                    highWaitOnFloor.wait();
                                    //cout << "Ben uyandım" << endl;
                                    if(currentFloor == source || stateOfElevator){
                                        break;
                                    }
                                    //cout << "geri uyuyom" << endl;
                                }

                                if(stateOfElevator == idle){
                                    continue;
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    highPriorityEnterance(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                }
                                else{
                                    highPriorityCannotEnter(personId,weight,source,destination,priority);
                                    if(highPriorityWaitersOnFloor[source] == 0){
                                        lowWaitOnFloor.notifyAll();
                                    }
                                    capacityCV.wait();
                                }
                            }
                            else if(priority == 2){ //low priority
                                lowPriorityWaitersOnFloor[source]++;
                                /*
                                while(1){
                                    //cout << "Beklemeye geçiyorum" << endl;
                                    lowWaitOnFloor.wait();
                                    //cout << "Ben uyandım" << endl;
                                    if(currentFloor == source){
                                        break;
                                    }
                                    //cout << "geri uyuyom" << endl;
                                }*/
                                currentRequests--;
                                if(canEnter(weight)){
                                    //cout << "Can enter" << endl;
                                    lowPriorityEnterance(personId,weight,source,destination,priority);
                                }
                                else{
                                    //cout << "Can't" << endl;
                                    lowPriorityWaitersOnFloor[source]--;
                                    capacityCV.wait();
                                }
                            }
                        }
                    }
                }
            }
            while(1){
                floorsVariableInElevator.wait();
                if(currentFloor == destination){
                    break;
                }
            }
            currentPerson--;
            currentWeight -= weight;
            numberOfPersonLeft--;
            /*bool flag = true;
            for(int i=0;i<numberOfFloors;i++){
                if(requestOnFloor[i]){
                    flag = false;
                }
            }
            if(flag){
                stateOfElevator = idle;
                upwardPerson.notifyAll();
                downwardPerson.notifyAll();
            }*/
            capacityCV.notifyAll();
            printExit(personId,weight,source,destination,priority);
            printElevatorState();
        }



        void moveUpTheElevator(){
            waitReq.timedWait(travelTime);
            currentFloor++;

        }
        void moveDownTheElevator(){
            waitReq.timedWait(travelTime);
            currentFloor--;
        }
        void handleRequests(){
            __synchronized__;
            while(numberOfPersonLeft != 0){
                if(stateOfElevator == idle){
                    if(highPriorityWaitersOnFloor[currentFloor] != 0){
                        //cout << "Ben de highı uyandırdım: inOutTime: " <<inOutTime << endl;
                        highWaitOnFloor.notifyAll(); // barrier
                        waitReq.timedWait(idleTime);
                    }
                    else if (highPriorityWaitersOnFloor[currentFloor] != 0){
                        //cout << "Ben de lowu uyandırdım" << endl;
                        lowWaitOnFloor.notifyAll(); // barrier
                        waitReq.timedWait(idleTime);
                    }
                    else if(currentRequests){
                        //cout << "Ben 3.yüm" << endl;
                        upwardPerson.notifyAll();
                        downwardPerson.notifyAll();
                        floorsVariableInElevator.notifyAll();
                        highWaitOnFloor.notifyAll();
                        lowWaitOnFloor.notifyAll();
                        waitReq.timedWait(idleTime);
                    }
                    if(currentRequests == 0 && numberOfPersonLeft){
                        //cout << "düz Wait" << endl;
                        upwardPerson.notifyAll();
                        downwardPerson.notifyAll();
                        waitReq.timedWait(idleTime);
                    }
                }
                else if(stateOfElevator == movingUp){
                    //movingUp
                    bool isFinished = true;
                    for(int i=currentFloor;i<numberOfFloors;i++){
                        if(requestOnFloor[i]){
                            isFinished= false;
                            break;
                        }
                    }
                    while(!isFinished){
                        moveUpTheElevator();
                        //cout << "moving up" << endl;
                        if(requestOnFloor[currentFloor]){
                            requestOnFloor[currentFloor] = false;
                            //printElevatorState();
                            //cout << "Ben durdum" << endl;
                            break;
                        }
                        printElevatorState();
                    }
                    isFinished = true;
                    for(int i=currentFloor;i<numberOfFloors;i++){
                        if(requestOnFloor[i]){
                            isFinished= false;
                            break;
                        }
                    }
                    //cout << "Durmadık mı yav" << endl;
                    if(currentPerson){
                        floorsVariableInElevator.notifyAll();
                    }
                    if(highPriorityWaitersOnFloor[currentFloor] != 0){
                        //cout << "Ben de highı uyandırdım: inOutTime: " <<inOutTime << endl;
                        highWaitOnFloor.notifyAll(); // barrier
                        if(isFinished){
                            stateOfElevator = idle;
                        }
                        printElevatorState();
                        waitReq.timedWait(inOutTime);
                    }
                    else{
                        //cout << "Ben de lowu uyandırdım" << endl;
                        lowWaitOnFloor.notifyAll(); // barrier
                        if(isFinished){
                            stateOfElevator = idle;
                        }
                        printElevatorState();
                        waitReq.timedWait(inOutTime);
                    }
                    //cout << "Time: " << inOutTime;
                }
                else if(stateOfElevator == movingDown){
                    //movingDown
                    bool isFinished = true;
                    for(int i=currentFloor;i>=0;i--){
                        if(requestOnFloor[i]){
                            isFinished = false;
                            break;
                        }
                    }
                    while(!isFinished){
                        moveDownTheElevator();
                        if(requestOnFloor[currentFloor]){
                            requestOnFloor[currentFloor] = false;
                            //cout << "Ben durdum" << endl;
                            //printElevatorState();
                            break;
                        }
                        printElevatorState();
                    }
                    //cout << "Durmadık mı yav" << endl;
                    isFinished = true;
                    for(int i=currentFloor;i>=0;i--){
                        if(requestOnFloor[i]){
                            isFinished= false;
                            break;
                        }
                    }
                    if(currentPerson){
                        floorsVariableInElevator.notifyAll();
                    }
                    if(highPriorityWaitersOnFloor[currentFloor] != 0){
                        //cout << "Ben de highı uyandırdım" << endl;
                        highWaitOnFloor.notifyAll(); // barrier
                        if(isFinished){
                            stateOfElevator = idle;
                        }
                        printElevatorState();
                        waitReq.timedWait(inOutTime);
                    }
                    else{
                        //cout << "Ben de lowu uyandırdım" << endl;
                        lowWaitOnFloor.notifyAll(); // barrier
                        if(isFinished){
                            stateOfElevator = idle;
                        }
                        printElevatorState();
                        waitReq.timedWait(inOutTime);
                    }
            }
        }
    }
};


void handleFirstLine(string line,int *numberOfFloors,int *numberOfPeople,int *weightCapacity,int *personCapacity){
    size_t positionOfSpace = 0;
    int index = 0;
    string parsedInput;
    while((positionOfSpace = line.find(" ")) != string::npos){
        parsedInput = line.substr(0,positionOfSpace);
        line.erase(0,parsedInput.length()+1);
        switch(index){
            case 0:
                *numberOfFloors = stoi(parsedInput);
                break;
            case 1:
                *numberOfPeople = stoi(parsedInput);
                break;
            case 2:
                *weightCapacity = stoi(parsedInput);
                break;
            case 3:
                *personCapacity = stoi(parsedInput);
                break;
            case 4:
                travelTime = (long) stoi(parsedInput);
                break;
            case 5:
                idleTime = (long) stoi(parsedInput);
                break;
            case 6:
                inOutTime = (long) stoi(parsedInput);
                break;
        }
        index++;
    }
}

void personThreadParser(string line, int *personWeight,int *initialFloor,int *destinationFloor,int *priorityOfThread){
    size_t positionOfSpace = 0;
    int index = 0;
    string parsedInput;
    while((positionOfSpace = line.find(" ")) != string::npos){
        parsedInput = line.substr(0,positionOfSpace);
        line.erase(0,parsedInput.length()+1);
        switch(index){
            case 0:
                *personWeight = stoi(parsedInput);
                break;
            case 1:
                *initialFloor = stoi(parsedInput);
                break;
            case 2:
                *destinationFloor = stoi(parsedInput);
                break;
            case 3:
                *priorityOfThread = stoi(parsedInput);
                break;
        }
        index++;
    }
}

void *elevatorControllerThread(void *ptr){
    ElevatorMonitor *elevatorMon = (ElevatorMonitor *) ptr;
    elevatorMon->handleRequests();
    return NULL;
}

void *personThreadRoutine(void *ptr){
    struct personThreadParams *params = (struct personThreadParams *) ptr;
    int personID = params->personID;
    int weight = params->weight;
    int sourceFloor = params->sourceFloor;
    int destinationFloor = params->destinationFloor;
    int priority = params->priority;
    ElevatorMonitor *elevatorMon = params->monitorPtr;
    elevatorMon->makeRequest(personID,weight,sourceFloor,destinationFloor,priority);
    //cout << "Person " << personID << " Weight: " << weight << " initialFloor: " << sourceFloor << " destinationFloor: " << destinationFloor << " priority: " << priority << endl;
    return NULL;
}

int main(int argc, char *argv[]){
    int numberOfFloors;
    int numberOfPeople;
    int weightCapacity;
    int personCapacity;
    pthread_t elevatorController;
    ifstream inputFile(argv[1]);
    string oneLine;
    getline(inputFile,oneLine);
    handleFirstLine(oneLine,&numberOfFloors,&numberOfPeople,&weightCapacity,&personCapacity);
    ElevatorMonitor elevatorMon(weightCapacity,numberOfFloors,numberOfPeople);
    pthread_t personThreads[numberOfPeople];
    struct personThreadParams personThreadParams[numberOfPeople];
    pthread_create(&elevatorController,NULL,elevatorControllerThread,&elevatorMon);
    for(int i=0;i<numberOfPeople;i++){
        getline(inputFile,oneLine);
        personThreadParser(oneLine,&(personThreadParams[i].weight),&(personThreadParams[i].sourceFloor),&(personThreadParams[i].destinationFloor),&(personThreadParams[i].priority));
        //cout << "Person " << i << " Weight: " << personThreadWeight << " initialFloor: " << initialFloor << " destinationFloor: " << destinationFloor << " priority: " << priorityOfThread << endl;
        personThreadParams[i].personID = i;
        personThreadParams[i].monitorPtr = &elevatorMon;
        pthread_create(&(personThreads[i]), NULL,personThreadRoutine, &personThreadParams[i]);
    }
    inputFile.close();
    for(int i=0;i<numberOfPeople;i++){
        pthread_join(personThreads[i],NULL);
    }
    pthread_join(elevatorController,NULL);
    return 0;
}
