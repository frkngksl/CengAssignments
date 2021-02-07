package project.parts.logics;

import project.SimulationRunner;
import project.components.Factory;
import project.components.Robot;
import project.parts.Part;
import project.utility.Common;

public class Supplier extends Logic
{

    @Override public void run ( Robot robot )
    {
        //Take our serial no
        int serialNoOfRobot = (int) Common.get(robot,"serialNo");
        //Indicate supply flag
        boolean productFlag = false;
        synchronized (SimulationRunner.factory.productionLine.parts){
            int currentSize =  SimulationRunner.factory.productionLine.parts.size();
            int maxSize = SimulationRunner.factory.productionLine.maxCapacity;
            if(currentSize == maxSize) {
                //If production line is full
                int randomNumberForDelete = Common.random.nextInt(maxSize);
                SimulationRunner.factory.productionLine.parts.remove(randomNumberForDelete);
                //Get a random number and remove it
            }
            else {
                //If not get a random part name
                String nameOfPart = Common.getPartName();
                //Create this name using factory pattern, and add it to production line
                Part newPartToAdd = Factory.createPart(nameOfPart);
                SimulationRunner.factory.productionLine.parts.add(newPartToAdd);
                productFlag = true;
                //Product flag is used for determining output
            }
        }
        //Repaint the production Line
        SimulationRunner.productionLineDisplay.repaint();
        if(productFlag){
            //Means we generated a product
            System.out.printf( "Robot %02d : Supplying a random part on production line.%n",serialNoOfRobot);
        }
        else {
            //We removed a product
            System.out.printf( "Robot %02d : Production line is full, removing a random part from production line.%n",serialNoOfRobot);
        }
        System.out.printf( "Robot %02d : Waking up waiting builders.%n", serialNoOfRobot);
        //Notify all builders
        synchronized (SimulationRunner.factory.productionLine)  {
            SimulationRunner.factory.productionLine.notifyAll();
        }


        // Following messages are appropriate for this class
        // System.out.printf( "Robot %02d : Supplying a random part on production line.%n", ...);
        // System.out.printf( "Robot %02d : Production line is full, removing a random part from production line.%n", ...);
        // System.out.printf( "Robot %02d : Waking up waiting builders.%n", ...);
    }
}