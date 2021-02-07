import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class BasicAgent extends Agent {

//Main Agent Type for decorator. Decorations will be added to this class. All main operations are handled by this class.

    public BasicAgent(double x, double y,String givenName,String imagePathGiven){
        //TODO
        super(x,y);
        //Random number will be used for initial state determination of agent.
        agencyName = givenName;
        //Agent name
        try {
            imageForDraw = ImageIO.read(new File(imagePathGiven));
        } catch (IOException e) {
            System.out.println(e);
        }
        //Read the image to the buffer
        currentState = State.getNewState(agencyName,radius);
        //Based on random number change state

    }
    @Override
    public void draw(Graphics2D g2d){
        g2d.drawImage(imageForDraw, position.getIntX(), position.getIntY(), imageWidth, imageHeight, null);
        //Width and height of the agent will be 100.
        g2d.setColor(Color.BLACK);
        g2d.setFont(fontName);
        g2d.drawString(agencyName, position.getIntX()+10, position.getIntY()-10);
        //Positioning hardcoded values
        g2d.setColor(Color.BLUE);
        g2d.drawString(currentState.getNameOfState(), position.getIntX()+10, position.getIntY()+125);
        //Positioning hardcoded values
        g2d.setColor(Color.RED);
        g2d.drawString(Integer.toString((int) totalCash), position.getIntX()+10,position.getIntY()+150);
        //Positioning hardcoded values
    }
    @Override
    public void step(){
        //In the step function agent will change it's state, also it will move based on it's state.
        //500 is a just random value, I set it experimentally to mimic the given jar
        if (Common.getRandomGenerator().nextInt(550) == 0) {
            //For randomness
            currentState = State.getNewState(agencyName,radius);
        }
        //Agent is not aware of the type of state. It just calls do move function to get next position. doMove is overriden by states.
        position = currentState.doMove(position.getX(),position.getY());
    }

}