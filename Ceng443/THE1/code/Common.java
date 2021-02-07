import java.util.Iterator;
import java.util.Random;
import java.util.Stack;
import java.util.Vector;

/*
Brings together animation parameters, instances of entities,
and other utility fields/methods that are required for running the application.
 */
public class Common {
    private static final String title = "Gold Wars";
    private static final int windowWidth = 1650;
    private static final int windowHeight = 1000;

    private static final GoldPrice goldPrice = new GoldPrice(588, 62);

    private static final Random randomGenerator = new Random(1234);
    private static final int upperLineY = 100;

    private static final Country countryUSA;
    private static final Country countryIsrael;
    private static final Country countryTurkey;
    private static final Country countryRussia;
    private static final Country countryChina;
    private static Agent ciaIntelligence;
    private static Agent mossadIntelligence;
    private static Agent mitIntelligence;
    private static Agent svrIntelligence;
    private static Agent mssIntelligence;
    private static Vector<Order> orderVector;
    //Vector that holds all orders
    static  {
        // TODO: Here, you can initialize the fields you have declared
        countryUSA = new Country(150,650,50,10000,"images/usa.jpg","USA","US");
        countryIsrael = new Country(450,650,50,10000,"images/israel.jpg","Israel","IL");
        countryTurkey = new Country(750,650,50,10000,"images/turkey.jpg","Turkey","TR");
        countryRussia = new Country(1050,650,50,10000,"images/russia.jpg","Russia","RU");
        countryChina = new Country(1350,650,50,10000,"images/china.jpg","China","CN");
        ciaIntelligence = new BasicAgent(175,350,"CIA","images/cia.png");
        mossadIntelligence = new BasicAgent(475,350,"Mossad","images/mossad.png");
        mitIntelligence = new BasicAgent(775,350,"MIT","images/mit.png");
        svrIntelligence = new BasicAgent(1075,350,"SVR","images/svr.png");
        mssIntelligence = new BasicAgent(1375,350,"MSS","images/mss.png");
        orderVector = new Vector<Order>();
    }

    // getters
    public static String getTitle() { return title; }
    public static int getWindowWidth() { return windowWidth; }
    public static int getWindowHeight() { return windowHeight; }

    // getter
    public static GoldPrice getGoldPrice() { return goldPrice; }
    public static Country getCountryUSA(){
        return countryUSA;
    }
    public static Country getCountryIsrael(){
        return countryIsrael;
    }
    public static Country getCountryTurkey(){
        return countryTurkey;
    }
    public static Country getCountryRussia(){
        return countryRussia;
    }
    public static Country getCountryChina(){
        return countryChina;
    }
    public static Agent getCiaIntelligence() {return ciaIntelligence; }
    public static Agent getMossadIntelligence() {return mossadIntelligence; }
    public static Agent getMitIntelligence() {return mitIntelligence; }
    public static Agent getSvrIntelligence() {return svrIntelligence; }
    public static Agent getMssIntelligence() {return mssIntelligence; }
    public static Vector<Order> getOrderVector() {return orderVector; }

    // getters
    public static Random getRandomGenerator() { return randomGenerator; }
    public static int getUpperLineY() { return upperLineY; }

    public static void setCiaIntelligence(Agent givenAgency){
        ciaIntelligence = givenAgency;
    }

    public static void setMossadIntelligence(Agent givenAgecy) {
        mossadIntelligence = givenAgecy;
    }

    public static void setMitIntelligence(Agent givenAgecy) {
        mitIntelligence = givenAgecy;
    }

    public static void setMssIntelligence(Agent givenAgecy) {
        mssIntelligence = givenAgecy;
    }

    public static void setSvrIntelligence(Agent givenAgecy) {
        svrIntelligence = givenAgecy;
    }
    //Setters for agents (decoration cases)
    public static void stepAllEntities() {

        if (randomGenerator.nextInt(200) == 0) {
            goldPrice.step(); //What it achieves
            countryUSA.setGoldWorth(goldPrice.getCurrentPrice());
            countryIsrael.setGoldWorth(goldPrice.getCurrentPrice());
            countryTurkey.setGoldWorth(goldPrice.getCurrentPrice());
            countryRussia.setGoldWorth(goldPrice.getCurrentPrice());
            countryChina.setGoldWorth(goldPrice.getCurrentPrice());
        }
        //Values are experimental
        if(randomGenerator.nextInt(400) == 0){
            countryUSA.step();
        }
        if(randomGenerator.nextInt(400) == 0){
            countryIsrael.step();
        }
        if(randomGenerator.nextInt(400) == 0){
            countryTurkey.step();
        }
        if(randomGenerator.nextInt(400) == 0){
            countryRussia.step();
        }
        if(randomGenerator.nextInt(300) == 0){
            countryChina.step();
        }
        //randomly call step functions of countries. Responsible for creating orders.
        ciaIntelligence.step();
        mossadIntelligence.step();
        mitIntelligence.step();
        svrIntelligence.step();
        mssIntelligence.step();
        //Move and randomly change state
        Vector<Order> deletedIndexes = new Vector<>();
        //Vector that holds indexes that will be deleted from order Vector
        for(Order tempOrder : orderVector) {
            tempOrder.step();
            //Move order
            if(tempOrder.getWillBeDeleted()){
                //Check whether it should be deleted or not
                deletedIndexes.add(tempOrder);
            }
        }
        Iterator<Order> iterate = deletedIndexes.iterator();
        while(iterate.hasNext()){
            orderVector.remove(iterate.next());
            //Remove orders from order list.
        }
    }
}