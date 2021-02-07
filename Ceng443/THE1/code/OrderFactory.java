public abstract class OrderFactory {
    public abstract Order getOrder(double startPosition, double endPosition, String givenCountry);
    public static OrderFactory produceFactory(){
        //Based on random value return the factory type
        boolean randomValue = Common.getRandomGenerator().nextBoolean();
        if(randomValue){
            return new BuyOrderFactory();
        }
        else{
            return new SellOrderFactory();
        }
    }
}