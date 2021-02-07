public class Shake extends State {
    public Shake(){
        nameOfState = "Shake";
    }
    @Override
    public Position doMove(double givenX, double givenY){
        int randomX = Common.getRandomGenerator().nextInt(3)-1; //[-1,1] range
        int randomY = Common.getRandomGenerator().nextInt(3)-1;
        //Check for not crossing the line and area
        if(randomY+givenY < Common.getUpperLineY() || randomY+givenY > Common.getWindowHeight()){
            randomY = 0;
        }
        if(randomX+givenX < 0 || randomX+givenX > Common.getWindowWidth()){
            randomX = 0;
        }
        return new Position(givenX+randomX,givenY+randomY);
    }
}