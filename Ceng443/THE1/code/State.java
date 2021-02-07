public abstract class State {
    protected String nameOfState;
    public abstract Position doMove(double givenX, double givenY);
    public String getNameOfState(){
        return nameOfState;
    }
    public static State getNewState(String agencyName, int radius){
        int randomNumber = Common.getRandomGenerator().nextInt(4);
        switch (randomNumber){
            case 0:
                return new Rest();
            case 1:
                return new Shake();
            case 2:
                return new GotoXY();
            case 3:
                return new ChaseClosest(agencyName,radius);
        }
        return null;
    }
}