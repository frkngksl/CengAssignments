import java.awt.*;
import java.awt.image.BufferedImage;

public abstract class Agent extends Entity {
    protected BufferedImage imageForDraw = null; //Image Buffer
    protected String agencyName; //Agent Name
    protected double totalCash = 0; // Total amount of point (money) that agent gathers
    protected Font fontName = new Font("Verdana", Font.BOLD, 20);
    protected State currentState; // State
    protected int imageWidth = 100;
    protected int imageHeight = 100;
    protected int radius = imageWidth/2;

    public Agent(double x, double y){
        super(x,y);
    }
    public abstract void draw(Graphics2D g2);
    public abstract void step();
    public boolean collisionCheck(Position givenPos){
        //Collision check function for orders, it simply calculates whether given position is inside of the circle (agents are circular shape).
        if(givenPos.distanceTo(getPosition().getX()+radius, getPosition().getY()+radius) < radius ){
            //50 is the radius of agents. It simply width/2 or height/2. getPosition.getX()+50 and its y invariant pair is the coordinate of center
            //So if the distance from center to object is less than the radius, it means object is inside of the agent and the order can be considered as being caught by agents
            return true;
        }
        return false;
    }

    public double getTotalCash() {
        return totalCash;
        //return Total Point
    }

    public void setTotalCash(double totalCash) {
        this.totalCash = totalCash;
        //Set total point
    }
}