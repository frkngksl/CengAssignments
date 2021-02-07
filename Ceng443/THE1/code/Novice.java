import java.awt.*;

public class Novice extends AgentDecorator {
    public Novice(Agent givenAgent){
        super(givenAgent);
    }
    @Override
    public void draw(Graphics2D g2d){
        //Override just this function to add badge
        g2d.setColor(Color.WHITE);
        g2d.fillRect(getPosition().getIntX()+10, getPosition().getIntY()-50,20,20);
        //Values are hardcoded to arrange position and experimental
        super.draw(g2d);
    }

}