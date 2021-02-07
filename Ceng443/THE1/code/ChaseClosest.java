import java.util.Vector;

public class ChaseClosest extends State {
    //Chase closest state
    private Order targetOrder = null;
    //Order that will be followed
    private double randomSpeedX;
    private double randomSpeedY;
    private String agencyName;
    private int radiusOfAgent;
    //Chase Closest shouldn't try to choose orders that belong to agent country. Therefore, I'm using this variable that contains abbreviation to discriminate orders.
    public ChaseClosest(String givenAgencyName,int radiusGiven){
        randomSpeedX = Common.getRandomGenerator().nextInt(750)+500; //Random
        randomSpeedY = Common.getRandomGenerator().nextInt(750)+500; //Random
        randomSpeedX = randomSpeedX/1000;
        randomSpeedY = randomSpeedY/1000;
        //Above operations is made to just getting a floating point random value
        nameOfState = "ChaseClosest";
        agencyName = givenAgencyName;
        radiusOfAgent = radiusGiven;
    }

    public Position doMove(double givenX, double givenY){
        //Calculate and return the new position
        setNewPosition(givenX+radiusOfAgent,givenY+radiusOfAgent);
        //Find and set order that will be chased. givenX+50(radius) and givenY+50(radius) represents the center of circular shape (Agents)
        Position targetPosition;
        if(targetOrder == null || targetOrder.getWillBeDeleted()){
            //Initial case or couldn't find any other, don't move until finding new one
            targetPosition = new Position(givenX,givenY);
            return targetPosition;
        }
        else{
            //Otherwise take the position of order
             targetPosition = targetOrder.getPosition();
        }
        Position returningPosition = new Position(0,0);
        if(targetPosition.getX() >= givenX+radiusOfAgent){
            //Determine direction on the x axis with respect to center
            returningPosition.setX(givenX+randomSpeedX);
        }
        else{
            returningPosition.setX(givenX-randomSpeedX);
        }
        if(targetPosition.getY() >= givenY+radiusOfAgent) {
            //Determine direction on the y axis with respect to center
            returningPosition.setY(givenY + randomSpeedY);
        }
        else{
            returningPosition.setY(givenY-randomSpeedY);
        }
        return returningPosition;
    }
    private void setNewPosition(double givenX, double givenY){
        //Find a new target and set it to the target variable.
        if(targetOrder == null || targetOrder.getWillBeDeleted()){
            double minDistance = 9999999;
            double tempDistance = 0;
            Vector<Order> orderList = Common.getOrderVector();
            for(Order temp : orderList){
                if(temp!=null && checkOrder(temp) && !temp.getWillBeDeleted()) {
                    tempDistance = temp.getPosition().distanceTo(givenX, givenY);
                    if (tempDistance < minDistance && !temp.getWillBeDeleted()) {
                        targetOrder = temp;
                        minDistance = tempDistance;
                    }
                }
            }
        }
    }

    private boolean checkOrder(Order givenOrder){
        //function that is used to discriminate agent's country order
        switch (givenOrder.getCountryName()){
            case "US":
                return !agencyName.equals("CIA");
            case "IL":
                return !agencyName.equals("Mossad");
            case "TR":
                return !agencyName.equals("MIT");
            case "RU":
                return !agencyName.equals("SVR");
            case "CN":
                return !agencyName.equals("MSS");
        }
        return false;
    }
}