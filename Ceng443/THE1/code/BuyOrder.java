import java.awt.*;

public class BuyOrder extends Order {
    public BuyOrder(double x,double y,int amountGiven,int pathGivenX,int pathGivenY, double speedGiven, String givenCountry) {
        super(x, y, amountGiven, speedGiven, pathGivenX,pathGivenY, Color.GREEN,givenCountry);
    }

    @Override
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
            goldAmount +=randomAmount;
            cashAmount-=(randomAmount*Common.getGoldPrice().getCurrentPrice());
            if(cashAmount >= 0){
                //check new cash amount, if it is negative don't execute the order.
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
            double cashAmount = randomAmount*Common.getGoldPrice().getCurrentPrice();
            //cashAmount: Cash value of the order
            double belongCountryNewCashAmount  = belongCountry.getCashAmount()-cashAmount;
            if(belongCountryNewCashAmount >=0){
                //don't execute if it is negative
                belongCountry.setCashAmount(belongCountryNewCashAmount);
                Common.getCountryUSA().setCashAmount(Common.getCountryUSA().getCashAmount()+cashAmount);
                //Add money to country of agent
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
            //Flag for deletion operation
        }
        //Check order is inside of Mossad agent and it is not belong to agent's country
        else if(mossadReference.collisionCheck(position) && !countryName.equals("IL")){
            double oldValue = mossadReference.getTotalCash();
            double newCashForAgency = mossadReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double cashAmount = randomAmount*Common.getGoldPrice().getCurrentPrice();
            //cashAmount: Cash value of the order
            double belongCountryNewCashAmount  = belongCountry.getCashAmount()-cashAmount;
            if(belongCountryNewCashAmount >=0){
                //don't execute if it is negative
                belongCountry.setCashAmount(belongCountryNewCashAmount);
                Common.getCountryIsrael().setCashAmount(Common.getCountryIsrael().getCashAmount()+cashAmount);
                //Add money to country of agent
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
            //Flag for deletion operation
        }
        //Check order is inside of Mit agent and it is not belong to agent's country
        else if(mitReference.collisionCheck(position) && !countryName.equals("TR")){
            double oldValue = mitReference.getTotalCash();
            double newCashForAgency = mitReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double cashAmount = randomAmount*Common.getGoldPrice().getCurrentPrice();
            //cashAmount: Cash value of the order
            double belongCountryNewCashAmount  = belongCountry.getCashAmount()-cashAmount;
            if(belongCountryNewCashAmount >=0){
                //don't execute if it is negative
                belongCountry.setCashAmount(belongCountryNewCashAmount);
                Common.getCountryTurkey().setCashAmount(Common.getCountryTurkey().getCashAmount()+cashAmount);
                //Add money to country of agent
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
            //Flag for deletion operation
        }
        //Check order is inside of Svr agent and it is not belong to agent's country
        else if(svrReference.collisionCheck(position) && !countryName.equals("RU")){
            double oldValue = svrReference.getTotalCash();
            double newCashForAgency = svrReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double cashAmount = randomAmount*Common.getGoldPrice().getCurrentPrice();
            //cashAmount: Cash value of the order
            double belongCountryNewCashAmount  = belongCountry.getCashAmount()-cashAmount;
            if(belongCountryNewCashAmount >=0){
                //don't execute if it is negative
                belongCountry.setCashAmount(belongCountryNewCashAmount);
                Common.getCountryRussia().setCashAmount(Common.getCountryRussia().getCashAmount()+cashAmount);
                //Add money to country of agent
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
            //Flag for deletion operation
        }
        //Check order is inside of MSS agent and it is not belong to agent's country
        else if(mssReference.collisionCheck(position) && !countryName.equals("CN")){
            double oldValue = mssReference.getTotalCash();
            double newCashForAgency = mssReference.getTotalCash()+randomAmount*Common.getGoldPrice().getCurrentPrice();
            double cashAmount = randomAmount*Common.getGoldPrice().getCurrentPrice();
            //cashAmount: Cash value of the order
            double belongCountryNewCashAmount  = belongCountry.getCashAmount()-cashAmount;
            if(belongCountryNewCashAmount >=0){
                //don't execute if it is negative
                belongCountry.setCashAmount(belongCountryNewCashAmount);
                Common.getCountryChina().setCashAmount(Common.getCountryChina().getCashAmount()+cashAmount);
                //Add money to country of agent
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
            //Flag for deletion operation
        }

    }
}