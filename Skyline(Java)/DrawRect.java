import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.ArrayList;
import javax.swing.*;


public class DrawRect extends JPanel {
    private static final int RECT_X = 1000;
    private static final int RECT_Y = 800;
    int cerceveBoyutu;
    Building[] buildings;

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g); 
        for (int i = 0; i < buildings.length; i++) {

            int x = buildings[i].left + 1;
            int y = buildings[i].height;
            int h = buildings[i].height;
            int w = Math.abs(buildings[i].right - buildings[i].left);
            if(i%4==0)
                g.setColor(Color.BLUE);
            else if(i%4==1)
                g.setColor(Color.RED);
            else if(i%4==2)
                g.setColor(Color.BLACK);
            else
                g.setColor(Color.GREEN);
            g.drawRect(x*30,500-(h*30),w*30,h*30);
            char[] chars1 = new char[1];
            chars1[0] = '1';
        }
    }

    @Override
    public Dimension getPreferredSize() {
        // so that our GUI is big enough
        return new Dimension(RECT_X,RECT_Y);
    }

    // create the GUI explicitly on the Swing event thread
    public static void createAndShowGui(Building[] buildings, int size) {
        DrawRect mainPanel = new DrawRect();
        mainPanel.buildings = buildings;
        mainPanel.cerceveBoyutu = size;

        JFrame frame = new JFrame("DrawRect");
        
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(mainPanel);
        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);
    }

}
