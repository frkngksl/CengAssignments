import java.awt.*;

public class SellOrder extends Order {
    public SellOrder(double x,double y,int amountGiven,double pathGivenX,double pathGivenY ,double speedGiven, String givenCountry){
        super(x,y,amountGiven,speedGiven,pathGivenX,pathGivenY, Color.PINK,givenCountry);
    }
    public void step(){
        super.step();
        Agent ciaReference = Common.getCiaIntelligence();
        Agent mossadReference = Common.getMossadIntelligence();
        Agent mitReference = Common.getMitIntelligence();
        Agent svrReference = Common.getSvrIntelligence();
        Agent mssReference = Common.getMssIntelligence();
        Country belongCountry;
        //Countries don't know which type of order they are generating. Therefore indicator is the order's country name.
        if(countryName.equals("US")) {
            belongCountry = Common.getCountryUSA();
        }
        else if(countryName.equals("IL")) {
            belongCountry = Common.getCountryIsrael();
        }
        else if(countryName.equals("TR")) {
            belongCountry = Common.getCountryTurkey();
        }
        else if(countryName.equals("RU")) {
            belongCountry = Common.getCountryRussia();
        }
        else{
            belongCountry = Common.getCountryChina();
        }
        //Find the country reference of order. (Who produced the order)
        if(position.getIntY() <= randomPathY){
            //It hits the upper line (randomPathY is our final destination point in y axis (upper line), if the current position is lower than randomPathY it passes the line)
            double goldAmount = belongCountry.getGoldAmount();
            double cashAmount = belongCountry.getCashAmount();
            goldAmount -=randomAmount;
            cashAmount+=(randomAmount*Common.getGoldPrice().getCurrentPrice());
            if(goldAmount >= 0){
                //check new gold amount, if it is negative don't execute the order.
                belongCountry.setGoldAmount(goldAmount);
                belongCountry.setCashAmount(cashAmount);
            }
            willBeDeleted = true;
            //Flag for deletion operation
        }
        //Check order is inside of CIA agent and it does not belong to agent's country
        else if(ciaReference.collisionCheck(position) && !countryName.equals("US")){
            double oldValue = ciaReference.getTotalCash();
            double newCashForAgency = ciaReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double belongCountryNewGoldAmount = belongCountry.getGoldAmount()-randomAmount;
            if(belongCountryNewGoldAmount >=0){
                //don't execute if it is negative
                belongCountry.setGoldAmount(belongCountryNewGoldAmount);
                Common.getCountryUSA().setGoldAmount(Common.getCountryUSA().getGoldAmount()+randomAmount);
                ciaReference.setTotalCash(newCashForAgency);
                //Decorate if agent passes 2000-4000-6000 point (money).
                if(oldValue<=2000 && newCashForAgency>2000){
                    Common.setCiaIntelligence(new Novice(ciaReference));
                }
                else if(oldValue<=4000 && newCashForAgency>4000){
                    Common.setCiaIntelligence(new Master(ciaReference));
                }
                else if(oldValue <=6000 && newCashForAgency>6000){
                    Common.setCiaIntelligence(new Expert(ciaReference));
                }
            }
            willBeDeleted = true;
        }
        else if(mossadReference.collisionCheck(position) && !countryName.equals("IL")){
            double oldValue = mossadReference.getTotalCash();
            double newCashForAgency = mossadReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double belongCountryNewGoldAmount = belongCountry.getGoldAmount()-randomAmount;
            if(belongCountryNewGoldAmount >=0){
                //don't execute if it is negative
                belongCountry.setGoldAmount(belongCountryNewGoldAmount);
                Common.getCountryIsrael().setGoldAmount(Common.getCountryIsrael().getGoldAmount()+randomAmount);
                mossadReference.setTotalCash(newCashForAgency);
                //Decorate if agent passes 2000-4000-6000 point (money).
                if(oldValue<=2000 && newCashForAgency>2000){
                    Common.setMossadIntelligence(new Novice(mossadReference));
                }
                else if(oldValue<=4000 && newCashForAgency>4000){
                    Common.setMossadIntelligence(new Master(mossadReference));
                }
                else if(oldValue <=6000 && newCashForAgency>6000){
                    Common.setMossadIntelligence(new Expert(mossadReference));
                }
            }
            willBeDeleted = true;
        }
        else if(mitReference.collisionCheck(position) && !countryName.equals("TR")){
            double oldValue = mitReference.getTotalCash();
            double newCashForAgency = mitReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double belongCountryNewGoldAmount = belongCountry.getGoldAmount()-randomAmount;
            if(belongCountryNewGoldAmount >=0){
                //don't execute if it is negative
                belongCountry.setGoldAmount(belongCountryNewGoldAmount);
                Common.getCountryTurkey().setGoldAmount(Common.getCountryTurkey().getGoldAmount()+randomAmount);
                mitReference.setTotalCash(newCashForAgency);
                //Decorate if agent passes 2000-4000-6000 point (money).
                if(oldValue<=2000 && newCashForAgency>2000){
                    Common.setMitIntelligence(new Novice(mitReference));
                }
                else if(oldValue<=4000 && newCashForAgency>4000){
                    Common.setMitIntelligence(new Master(mitReference));
                }
                else if(oldValue <=6000 && newCashForAgency>6000){
                    Common.setMitIntelligence(new Expert(mitReference));
                }
            }
            willBeDeleted = true;
        }
        else if(svrReference.collisionCheck(position) && !countryName.equals("RU")){
            double oldValue = svrReference.getTotalCash();
            double newCashForAgency = svrReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double belongCountryNewGoldAmount = belongCountry.getGoldAmount()-randomAmount;
            if(belongCountryNewGoldAmount >=0){
                //don't execute if it is negative
                belongCountry.setGoldAmount(belongCountryNewGoldAmount);
                Common.getCountryRussia().setGoldAmount(Common.getCountryRussia().getGoldAmount()+randomAmount);
                svrReference.setTotalCash(newCashForAgency);
                //Decorate if agent passes 2000-4000-6000 point (money).
                if(oldValue<=2000 && newCashForAgency>2000){
                    Common.setSvrIntelligence(new Novice(svrReference));
                }
                else if(oldValue<=4000 && newCashForAgency>4000){
                    Common.setSvrIntelligence(new Master(svrReference));
                }
                else if(oldValue <=6000 && newCashForAgency>6000){
                    Common.setSvrIntelligence(new Expert(svrReference));
                }
            }
            willBeDeleted = true;
        }
        else if(mssReference.collisionCheck(position) && !countryName.equals("CN")){
            double oldValue = mssReference.getTotalCash();
            double newCashForAgency = mssReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double belongCountryNewGoldAmount = belongCountry.getGoldAmount()-randomAmount;
            if(belongCountryNewGoldAmount >=0){
                //don't execute if it is negative
                belongCountry.setGoldAmount(belongCountryNewGoldAmount);
                Common.getCountryChina().setGoldAmount(Common.getCountryChina().getGoldAmount()+randomAmount);
                mssReference.setTotalCash(newCashForAgency);
                //Decorate if agent passes 2000-4000-6000 point (money).
                if(oldValue<=2000 && newCashForAgency>2000){
                    Common.setMssIntelligence(new Novice(mssReference));
                }
                else if(oldValue<=4000 && newCashForAgency>4000){
                    Common.setMssIntelligence(new Master(mssReference));
                }
                else if(oldValue <=6000 && newCashForAgency>6000){
                    Common.setMssIntelligence(new Expert(mssReference));
                }
            }
            willBeDeleted = true;
        }
    }
}