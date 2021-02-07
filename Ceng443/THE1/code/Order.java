import java.awt.*;

public abstract class Order extends Entity {
    protected boolean willBeDeleted = false; //deleted flag
    protected String countryName;
    protected int randomAmount;
    protected double randomSpeed;
    protected double randomPathX;
    protected double randomPathY; //Destinations
    protected Color colorOfCircle;
    private Font fontName = new Font("Verdana", Font.BOLD, 15);
    private double velocityX;
    private double velocityY;

    public Order(double positionX, double positionY, int amountGiven,double speedGiven, double pathGivenX,double pathGivenY,Color givenColor,String givenCountry){
        super(positionX, positionY);
        randomAmount = amountGiven;
        randomSpeed = speedGiven;
        randomPathX = pathGivenX;
        randomPathY = pathGivenY;
        colorOfCircle = givenColor;
        countryName = givenCountry;
        velocityCalculation();
    }
    @Override
    public void draw(Graphics2D g2d){
        int widthAndHeight = 20; //experimental
        g2d.setColor(colorOfCircle);
        g2d.setFont(fontName);
        g2d.drawString(countryName, position.getIntX(), position.getIntY()-8);
        fontName = new Font("Verdana", Font.PLAIN, 20);
        g2d.fillOval(position.getIntX(), position.getIntY(),widthAndHeight, widthAndHeight);
        //Centerize the string
        FontMetrics fontMetrics = g2d.getFontMetrics(fontName);
        int stringX = position.getIntX() + (widthAndHeight - fontMetrics.stringWidth(Integer.toString(randomAmount))) / 2;
        int stringY = position.getIntY() + ((widthAndHeight - fontMetrics.getHeight()) / 2) + fontMetrics.getAscent();
        // Set the font
        g2d.setFont(fontName);
        g2d.setColor(Color.BLACK);
        // Draw the String
        g2d.drawString(Integer.toString(randomAmount), stringX, stringY);
    }

    @Override
    public void step(){
        //Step is move the order
        position.setX(position.getX()+velocityX);
        position.setY(position.getY()+velocityY);
    }
    public boolean getWillBeDeleted(){
        return willBeDeleted;
    }
    private void velocityCalculation(){
        //Calculate the velocity
        velocityX = (randomPathX - position.getIntX())/randomSpeed;
        velocityY = (randomPathY - position.getIntY())/randomSpeed;
    }

    public String getCountryName() {
        return countryName;
    }
}