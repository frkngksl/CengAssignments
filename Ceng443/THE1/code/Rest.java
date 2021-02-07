public class Rest extends State {
    public Rest(){
        nameOfState = "Rest";
    }
    public Position doMove(double givenX, double givenY){
        //Just return the last position don't move
        return new Position(givenX,givenY);
    }
}