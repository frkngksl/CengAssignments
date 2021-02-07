public class GotoXY extends State {
    private Position targetPosition;
    private int randomSpeed;
    public GotoXY() {
        setNewPositionAndSpeed();
        nameOfState = "GoToXY";

    }
    public Position doMove(double givenX, double givenY){
        //I just wanted to set error margin. In the given jar file speed was not constant and I wanted to implement this type
        //Since speed is relatively decreasing, after certain distance I just wanted to assume that it reached the destination and find the new destination
        int errorMargin = 5;
        if(targetPosition.distanceTo(givenX,givenY) < 5){
            setNewPositionAndSpeed();
        }
        double velocityX = (targetPosition.getIntX() - givenX)/randomSpeed;
        double velocityY = (targetPosition.getIntY()-givenY)/randomSpeed;
        //Dynamic velocity to mimic behaviour of given jar file.
        return new Position(givenX+velocityX,givenY+velocityY);
    }
    private void setNewPositionAndSpeed(){
        //Randomly create position and speed
        randomSpeed = Common.getRandomGenerator().nextInt(500)+250; //100
        //Again experimental values
        int upperAreaY = Common.getCountryRussia().getPosition().getIntY();//Upper Line with respect to country flags
        int lowerAreaY = Common.getUpperLineY();
        int targetX = Common.getRandomGenerator().nextInt(Common.getWindowWidth());
        int targetY = Common.getRandomGenerator().nextInt(upperAreaY-lowerAreaY)+lowerAreaY;
        targetPosition = new Position(targetX,targetY);
    }
}