public class BuyOrderFactory extends OrderFactory {
    public Order getOrder(double startPosition, double endPosition, String givenCountry){
        //Create a Buy order and set its destination,amount and random here randomly.
        int lowerBound = 1;
        int randomAmount = Common.getRandomGenerator().nextInt(5)+lowerBound;
        //nextInt gives [0,specifiedValue) so add a lower bound to get [1,5]
        int randomFinishX = Common.getRandomGenerator().nextInt(Common.getWindowWidth());
        int speedRandom = Common.getRandomGenerator().nextInt(200)+500;
        //Again experimental [500,700)
        return new BuyOrder(startPosition,endPosition,randomAmount,randomFinishX,Common.getUpperLineY(),speedRandom,givenCountry);
    }
}