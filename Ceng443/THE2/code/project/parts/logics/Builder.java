package project.parts.logics;

import project.SimulationRunner;
import project.components.ProductionLine;
import project.components.Robot;
import project.parts.Arm;
import project.parts.Base;
import project.parts.Part;
import project.parts.payloads.Payload;
import project.utility.Common;

import java.io.Console;
import java.util.Iterator;
import java.util.Vector;

public class Builder extends Logic
{
    @Override public void run ( Robot robot ){
        int serialNoOfRobot = (int) Common.get(robot,"serialNo");
        boolean storageFull = false;
        boolean repaintRobots = false;
        boolean operationDone = false;
        boolean oneRobotIsCompleted = false;
        boolean putToStorage = false;
        boolean repaintStorage = false;
        Part tempPart = null;
        Vector<Part> deletedIndexes = new Vector<>();
        synchronized (SimulationRunner.factory.productionLine.parts){
            int currentSize =  SimulationRunner.factory.productionLine.parts.size();
            //Iterate over production line
            for(int i=0;(i<currentSize && !operationDone);i++){
                tempPart = SimulationRunner.factory.productionLine.parts.get(i);
                //First of all check whether it is base (because all parts will be integrated to base)
                if (tempPart instanceof Base) {
                    //If it is base, get its components
                    Arm armOfBase = (Arm) Common.get(tempPart, "arm");
                    Payload payloadOfBase = (Payload) Common.get(tempPart, "payload");
                    Logic logicOfBase = (Logic) Common.get(tempPart, "logic");
                    //If the arm missing, find an arm and if possible, attach the arm and remove it from production line
                    if (armOfBase == null) {
                        for (int j = 0; j < currentSize; j++) {
                            if (i != j) { //not check itself
                                if (SimulationRunner.factory.productionLine.parts.get(j) instanceof Arm) {
                                    Common.set(tempPart, "arm", SimulationRunner.factory.productionLine.parts.get(j));
                                    deletedIndexes.add(SimulationRunner.factory.productionLine.parts.get(j));
                                    operationDone = true;
                                    break;
                                }
                            }
                        }
                    }
                    //If the payload missing, find a payload and if possible, attach the payload and remove it from the production line
                    else if (payloadOfBase == null) {
                        for (int j = 0; j < currentSize; j++) {
                            if (i != j) { //not check itself
                                if (SimulationRunner.factory.productionLine.parts.get(j) instanceof Payload) {
                                    Common.set(tempPart, "payload", SimulationRunner.factory.productionLine.parts.get(j));
                                    deletedIndexes.add(SimulationRunner.factory.productionLine.parts.get(j));
                                    operationDone = true;
                                    break;
                                }
                            }
                        }
                    }
                    //If the logic missing, find a "proper" logic using payload part by calling function in the common, it just checks
                    else if (logicOfBase == null) {
                        for (int j = 0; j < currentSize; j++) {
                            if (i != j) { //not check itself
                                //If the part is logic
                                if (SimulationRunner.factory.productionLine.parts.get(j) instanceof Logic) {
                                    Logic logicComponent = (Logic) SimulationRunner.factory.productionLine.parts.get(j);
                                    //If the found part is compatible with payload
                                    if (Common.compatibleLogic(payloadOfBase, logicComponent)) {
                                        Common.set(tempPart, "logic", SimulationRunner.factory.productionLine.parts.get(j));
                                        deletedIndexes.add(SimulationRunner.factory.productionLine.parts.get(j));
                                        operationDone = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    //Else, it means robot is completed put it on storage or working robots
                    else{
                        deletedIndexes.add(SimulationRunner.factory.productionLine.parts.get(i));
                        operationDone = true;
                        oneRobotIsCompleted = true;
                    }
                }
            }
            //Remove from productionline after iteration
            Iterator<Part> iterate = deletedIndexes.iterator();
            while(iterate.hasNext()){
                SimulationRunner.factory.productionLine.parts.remove(iterate.next());
                //Remove orders from order list.
            }
        }
        //If operationDone is true it means there is a change on productionLine so repaint
        if(operationDone){
            SimulationRunner.productionLineDisplay.repaint() ;
        }
        //If one robot is completed it means we should put it on as a working robot or storage
        if(oneRobotIsCompleted){
            synchronized (SimulationRunner.factory.robots){
                //If working robots not full, add it and start it.
                if(SimulationRunner.factory.robots.size() != SimulationRunner.factory.maxRobots){
                    SimulationRunner.factory.robots.add((Robot) tempPart);
                    new Thread( (Robot) tempPart ).start() ;
                    repaintRobots = true;
                }
                //If not put it into storage
                else{
                    putToStorage = true;
                }
            }
        }
        //If newly added robot to working robots just repaint
        if(repaintRobots){
            SimulationRunner.robotsDisplay.repaint();
        }
        //Put to new one into storage but not start it, if it is full finish program without adding
        if(putToStorage){
            synchronized (SimulationRunner.factory.storage.robots){
                if(SimulationRunner.factory.storage.robots.size() != SimulationRunner.factory.storage.maxCapacity){
                    SimulationRunner.factory.storage.robots.add((Robot) tempPart);
                    repaintStorage = true;
                    if(SimulationRunner.factory.storage.robots.size() == SimulationRunner.factory.storage.maxCapacity){
                        storageFull = true;
                    }
                }
            }
        }
        //Repaint if we put it onto storage
        if(repaintStorage){
            SimulationRunner.storageDisplay.repaint();
        }
        //Finish the program
        if(storageFull) {
            SimulationRunner.factory.stopProduction = true;
        }
        else{
            //If it hasn't finished yet, give outputs.
            if(operationDone){

                System.out.printf("Robot %02d : Builder attached some parts or relocated a completed robot.%n", serialNoOfRobot);
            }
            else{
                System.out.printf("Robot %02d : Builder cannot build anything, waiting!%n", serialNoOfRobot);
            }
            //Wait for supplier notification
            synchronized (SimulationRunner.factory.productionLine)  {
                try{
                    SimulationRunner.factory.productionLine.wait();
                }
                catch (InterruptedException e){
                    ;
                }
            }

            System.out.printf("Robot %02d : Builder woke up, going back to work.%n", serialNoOfRobot);
        }

        // Following messages are appropriate for this class
        // System.out.printf("Robot %02d : Builder cannot build anything, waiting!%n", ...);
        // System.out.printf("Robot %02d : Builder woke up, going back to work.%n", ...);
        // System.out.printf("Robot %02d : Builder attached some parts or relocated a completed robot.%n", ...);

    }
}