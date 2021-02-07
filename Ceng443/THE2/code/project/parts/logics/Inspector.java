package project.parts.logics;

import project.SimulationRunner;
import project.components.Robot;
import project.parts.Part;
import project.utility.Common;

import java.util.Iterator;
import java.util.Vector;

public class Inspector extends Logic
{
    @Override public void run ( Robot robot )
    {
        int ownSerialNo = (int) Common.get(robot,"serialNo");
        //Vector for delete
        Vector<Robot> brokenRobotsVector = new Vector<>();
        //Vector for print
        Vector<Integer> serialNums = new Vector<>();
        Robot temp = null;
        synchronized (SimulationRunner.factory.robots){
            //Traverse all robots and check whether it is broken or not by looking isWaiting parameter
            for ( Robot takenRobot : SimulationRunner.factory.robots ){
                boolean isBroken = (boolean) Common.get(takenRobot,"isWaiting");
                if(isBroken){
                    //If it is broken put it to broken robots vector
                    brokenRobotsVector.add(takenRobot);
                }
            }
        }
        int serialNo;
        synchronized (SimulationRunner.factory.brokenRobots){
            //Iterate over our deleted robots vector
            Iterator<Robot> iterateForRobots = brokenRobotsVector.iterator();
            while(iterateForRobots.hasNext()){
                temp = iterateForRobots.next();
                //If brokenRobots doesn't contain this robot, add it to the list
                if(!SimulationRunner.factory.brokenRobots.contains(temp)){
                    SimulationRunner.factory.brokenRobots.add(temp);
                    serialNo = (int) Common.get(temp,"serialNo");
                    serialNums.add(serialNo);
                }
            }
            //Check whether we put any robot into the list
            if(serialNums.size()>0){
                Iterator<Integer> iterateForSerial = serialNums.iterator();
                while (iterateForSerial.hasNext()){
                    System.out.printf( "Robot %02d : Detected a broken robot (%02d), adding it to broken robots list.%n",ownSerialNo ,iterateForSerial.next());
                }
                System.out.printf( "Robot %02d : Notifying waiting fixers.%n", ownSerialNo);
                //Notify fixers
                SimulationRunner.factory.brokenRobots.notifyAll() ;
            }
        }



        // Following messages are appropriate for this class
        // System.out.printf( "Robot %02d : Detected a broken robot (%02d), adding it to broken robots list.%n", ...);
        // System.out.printf( "Robot %02d : Notifying waiting fixers.%n", ...);
    }
}