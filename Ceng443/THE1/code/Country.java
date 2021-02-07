import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.Stack;
import java.util.Vector;

import javax.imageio.ImageIO;

public class Country extends Entity {
    private String nameOfCountry;
    private String acronymCountry;
    private double goldAmount;
    private double cashAmount;
    private double goldWorth;
    private BufferedImage imageForDraw = null;
    private Font fontName = new Font("Verdana", Font.BOLD, 20);
    private int countryWidth = 150;
    private int countryHeight = 150;


    public Country(double positionX, double positionY,int goldGiven,int cashGiven, String imagePath, String givenName,String givenAcronym) {
        super(positionX, positionY);
        goldAmount = goldGiven;
        cashAmount = cashGiven;
        nameOfCountry = givenName;
        acronymCountry = givenAcronym;
        setGoldWorth(Common.getGoldPrice().getCurrentPrice());
        //Initial worth (50 is the initial gold price hardcoded)
        BufferedImage img = null;
        try {
            imageForDraw = ImageIO.read(new File(imagePath));
        } catch (IOException e) {
            System.out.println(e);
        }
        //Buffer the image
    }
    @Override
    public void draw(Graphics2D g2d){
        g2d.drawImage(imageForDraw, position.getIntX(), position.getIntY(), countryWidth, countryHeight, null);
        //Hardcoded width and height, experimental values
        g2d.setColor(Color.BLACK);
        g2d.setFont(fontName);
        g2d.drawString(nameOfCountry, position.getIntX()+40, position.getIntY()+180);
        //Hardcoded positions
        g2d.setColor(Color.YELLOW);
        g2d.drawString(String.format("%d gold",(int) goldAmount), position.getIntX()+25, position.getIntY()+210);
        //Hardcoded positions
        g2d.setColor(Color.GREEN);
        g2d.drawString(String.format("%d cash",(int) cashAmount), position.getIntX()+25, position.getIntY()+240);
        //Hardcoded positions
        g2d.setColor(Color.BLUE);
        g2d.drawString(String.format("Worth: %d",(int) goldWorth),position.getIntX()+25, position.getIntY()+270);
        //Hardcoded positions
    }
    @Override
    public void step(){
        OrderFactory factoryCreated = OrderFactory.produceFactory();
        Order newOrder = factoryCreated.getOrder(position.getIntX()+75, position.getIntY()+25, acronymCountry);
        //Initial order spawn position hardcoded and experimental
        Common.getOrderVector().add(newOrder);
        //Add to the vector
        //Factory pattern
        //1- Country doesn't know the factory type
        //2- Country doesn't know the order type
    }

    public double getGoldAmount() {
        return goldAmount;
    }

    public double getCashAmount(){
        return cashAmount;
    }

    public void setGoldAmount(double givenGold){
        goldAmount = givenGold;
        setGoldWorth(Common.getGoldPrice().getCurrentPrice());
        //Update worth
    }

    public void setCashAmount(double givenCash){
        cashAmount = givenCash;
        setGoldWorth(Common.getGoldPrice().getCurrentPrice());
        //Update worth
    }

    public void setGoldWorth(double givenGoldPrice){
        goldWorth = givenGoldPrice*goldAmount+cashAmount;
    }

}