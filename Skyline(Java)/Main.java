
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;
import java.awt.*;

public class Main extends Component {
    public static int BoardSize;
    public static int SIZE;
    public static void main(String[] args) throws IOException {
        
        int counter = 0;
        int temp = 0;
        int x=0,y=0;
        Vector<Integer> position = new Vector<>();
        Vector<Integer> width = new Vector<>();
        Vector<Integer> height = new Vector<>();
        File file = new File("data.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        String st;
        
        while ((st = br.readLine()) != null){
            counter++;
            String[] Tok = st.split(" ");
            
            int p = Integer.parseInt(Tok[2]);
            int h = Integer.parseInt(Tok[1]);
            int w = Integer.parseInt(Tok[0]);
            
            x += p+w;
            y += h;
                      
            if(BoardSize < p+w )
                BoardSize = p+w ;
            if(BoardSize < h)
                BoardSize = h;
            
            width.add(Integer.parseInt(Tok[0]));
            height.add(Integer.parseInt(Tok[1]));
            position.add(Integer.parseInt(Tok[2]));
        }
        
        if(SIZE < x)
            SIZE = x;
        if(SIZE < y)
            SIZE = y;
 
        Building[] buildings = new Building[counter];

        for (int i = 0; i < counter; i++) {
            Building singleBuilding = new Building(position.get(i),position.get(i)+width.get(i), height.get(i));
            buildings[i] = singleBuilding;
        }

        SkyLine skyline = new SkyLine();
        for (int i = 0; i < buildings.length ; i++) {
            skyline.addBuilding(buildings[i]);
        }
        skyline.findEdges();
        skyline.sortEdges();
        skyline.printEdges();
        DrawRect m = new DrawRect();
        m.createAndShowGui(buildings,20);
    }
}
