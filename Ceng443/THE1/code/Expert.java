import java.awt.*;

public class Expert extends AgentDecorator {
    public Expert(Agent givenAgent){
        super(givenAgent);
    }
    @Override
    public void draw(Graphics2D g2d){
        //Override this method just for adding badge
        g2d.setColor(Color.RED);
        g2d.fillRect(getPosition().getIntX()+60, getPosition().getIntY()-50,20,20);
        //Experimental values
        //Hardcoded badge values
        super.draw(g2d);
    }
}