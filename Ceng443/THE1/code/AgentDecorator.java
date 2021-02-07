import java.awt.*;

public abstract class AgentDecorator extends Agent {
     protected Agent decoratedAgent;
    //agent inside of decorator
     public AgentDecorator(Agent givenAgent){
         super(givenAgent.getPosition().getX(),givenAgent.getPosition().getY());
         decoratedAgent = givenAgent;
     }

    @Override
    public void draw(Graphics2D g2d) {
         decoratedAgent.draw(g2d);
         //use draw function of inner agent
    }
    @Override
    public void step() {
         decoratedAgent.step();
         //use step function of inner agent
    }
    @Override
    public Position getPosition(){
         return decoratedAgent.getPosition();
         //position is taken by inner agent
    }
    @Override
    public double getTotalCash() {
        return decoratedAgent.getTotalCash();
        //total cash (point) taken by inner agent
    }
    @Override
    public void setTotalCash(double totalCash) {
        decoratedAgent.setTotalCash(totalCash);
        //set total cash (point)
    }

}