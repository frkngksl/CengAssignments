public class SellOrderFactory extends OrderFactory {
    public Order getOrder(double startPosition, double endPosition,String givenCountry){
        //Create a Sell order and set its destination,amount and random here randomly.
        int lowerBound = 1;
        int randomAmount = Common.getRandomGenerator().nextInt(5)+lowerBound;
        int randomFinishX = Common.getRandomGenerator().nextInt(Common.getWindowWidth());
        int speedRandom = Common.getRandomGenerator().nextInt(200)+500;
        //Similar to Buy Order Factory
        return new SellOrder(startPosition,endPosition,randomAmount,randomFinishX,Common.getUpperLineY(),speedRandom,givenCountry);
    }
}