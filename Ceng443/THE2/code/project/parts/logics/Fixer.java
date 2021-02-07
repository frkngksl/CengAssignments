package project.parts.logics;

import project.SimulationRunner;
import project.components.Factory;
import project.components.Robot;
import project.parts.Arm;
import project.parts.payloads.Payload;
import project.utility.Common;

public class Fixer extends Logic
{
    @Override public void run ( Robot robot )
    {
        int serialNoOfRobot = (int) Common.get(robot,"serialNo");
        boolean foundOne = false;
        int serialNoOfBroken = 0;
        synchronized (SimulationRunner.factory.brokenRobots)  {
            //Check there exist a brokenRobot
            if(SimulationRunner.factory.brokenRobots.size() > 0){
                //Fetch the first one, and remove it
                Robot takeBrokenRobot = SimulationRunner.factory.brokenRobots.get(0);
                SimulationRunner.factory.brokenRobots.remove(takeBrokenRobot);
                //Check its parts
                serialNoOfBroken = (int) Common.get(takeBrokenRobot,"serialNo");
                Arm armOfBroken = (Arm) Common.get(takeBrokenRobot,"arm");
                Payload payloadOfBroken = (Payload) Common.get(takeBrokenRobot,"payload");
                Logic logicOfBroken = (Logic) Common.get(takeBrokenRobot,"logic");
                foundOne = true;
                //If arm is broken create a new arm
                if(armOfBroken == null){
                    Common.set( takeBrokenRobot ,"arm", Factory.createPart("Arm") ) ;
                }
                //If payload is broken
                else if(payloadOfBroken == null){
                    //Get suitable payload name using function in the Common
                    String getPayloadType = Common.getMissingPayload(logicOfBroken);
                    Common.set(takeBrokenRobot,"payload", Factory.createPart(getPayloadType));
                }
                //If logic is broken
                else if(logicOfBroken == null){
                    //Get suitable logic name using function in the Common
                    String getLogicType = Common.getMissingLogic(payloadOfBroken);
                    Common.set(takeBrokenRobot,"logic",Factory.createPart(getLogicType));
                }
                //Wake up the broken robot
                synchronized(takeBrokenRobot){
                    takeBrokenRobot.notify();
                }
            }
            //Handle output
            if(foundOne){
                System.out.printf("Robot %02d : Fixed and waken up robot (%02d).%n", serialNoOfRobot,serialNoOfBroken);
            }
            else{
                System.out.printf("Robot %02d : Nothing to fix, waiting!%n", serialNoOfRobot);
            }
            //Wait another notify from inspector after fixing or checking out
            try{
                SimulationRunner.factory.brokenRobots.wait();
            }
            catch (InterruptedException e){
                ;
            }
            System.out.printf("Robot %02d : Fixer woke up, going back to work.%n", serialNoOfRobot);
        }
        // Following messages are appropriate for this class
        // System.out.printf("Robot %02d : Fixed and waken up robot (%02d).%n", ...);
        // System.out.printf("Robot %02d : Nothing to fix, waiting!%n", ...);
        // System.out.printf("Robot %02d : Fixer woke up, going back to work.%n", ...);
    }
}