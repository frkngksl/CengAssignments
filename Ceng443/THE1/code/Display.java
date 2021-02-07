import javax.swing.*;
import java.awt.*;

public class Display extends JPanel {
    public Display() { this.setBackground(new Color(180, 180, 180)); }
    int x = 0;
    @Override
    public Dimension getPreferredSize() { return super.getPreferredSize(); }

    @Override
    protected void paintComponent(Graphics g) {
        //Draw agents orders and countries
        super.paintComponent(g);
        //double goldPrice = Common.getGoldPrice().getCurrentPrice();
        Common.getGoldPrice().draw((Graphics2D) g);
        g.drawLine(0, Common.getUpperLineY(), Common.getWindowWidth(), Common.getUpperLineY());
        // TODO
        Country usaReference = Common.getCountryUSA();
        Country israelReference = Common.getCountryIsrael();
        Country turkeyReference = Common.getCountryTurkey();
        Country russiaReference = Common.getCountryRussia();
        Country chinaReference = Common.getCountryChina();

        Agent ciaReference = Common.getCiaIntelligence();
        Agent mossadReference = Common.getMossadIntelligence();
        Agent mitReference = Common.getMitIntelligence();
        Agent svrReference = Common.getSvrIntelligence();
        Agent mssReference = Common.getMssIntelligence();

        //Draw all orders
        for(Order tempOrder : Common.getOrderVector()){
            tempOrder.draw((Graphics2D) g);
        }

        usaReference.draw((Graphics2D) g);
        israelReference.draw((Graphics2D) g);
        turkeyReference.draw((Graphics2D) g);
        russiaReference.draw((Graphics2D) g);
        chinaReference.draw((Graphics2D) g);

        ciaReference.draw((Graphics2D) g);
        mossadReference.draw((Graphics2D) g);
        mitReference.draw((Graphics2D) g);
        svrReference.draw((Graphics2D) g);
        mssReference.draw((Graphics2D) g);
    }

}