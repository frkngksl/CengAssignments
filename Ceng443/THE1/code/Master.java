import java.awt.*;

public class Master extends AgentDecorator {
    public Master(Agent givenAgent){
        super(givenAgent);
    }
    @Override
    public void draw(Graphics2D g2d){
        //Override just this function to add badge
        g2d.setColor(Color.YELLOW);
        g2d.fillRect(getPosition().getIntX()+35, getPosition().getIntY()-50,20,20);
        //Values are hardcoded to arrange position again experimental
        super.draw(g2d);
    }
}