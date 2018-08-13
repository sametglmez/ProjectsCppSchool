import java.io.File;
import java.util.ArrayList;
import java.io.*;
import java.util.StringTokenizer;
import java.util.Vector;


public class SkyLine {

        public int boardSize = Main.BoardSize*2;
        
        Cell [][] board = new Cell[boardSize][boardSize];
        ArrayList<Edge> edges = new ArrayList<>();
        ArrayList<Edge> sortedEdges = new ArrayList<>();
        public SkyLine(){
            for (int i = 0; i <boardSize ; i++) {
                for (int j = 0; j <boardSize ; j++) {
                    board[i][j] = new Cell(i,j,0);
                }
            }
        }
        public void printBoard(){
            for (int i = 0; i <boardSize ; i++) {
                for (int j = 0; j < boardSize; j++) {
                    System.out.print(board[i][j].getE()+" ");

                }
                System.out.println("");
            }
        }
        public void printSortedEdges(){
            System.out.println("size of sorted edge: " + sortedEdges.size());
            for (int i = 0; i < sortedEdges.size() ; i++) {
                System.out.println("(" +sortedEdges.get(i).x + " " +sortedEdges.get(i).y + ")");
            }
        }
        public void printEdges(){
            for (int i = 0; i < edges.size() ; i++) {
                System.out.print( "(" + edges.get(i).y + ", " +edges.get(i).x + ")");
                if(i != edges.size()-1)
                    System.out.print( ", " );

            }
        }
        public void sortEdges(){

            for (int i = 0; i <edges.size()-1 ; i++) {
                for (int j = 0; j < edges.size()-1-i; j++) {

                    if( edges.get(j).distance > edges.get(j+1).distance){
                        int x  = edges.get(j+1).x;
                        int y  = edges.get(j+1).y;
                        double dist  = edges.get(j+1).distance;
                        int flag = edges.get(j+1).flag;
                        edges.get(j+1).setX(edges.get(j).x);
                        edges.get(j+1).setY(edges.get(j).y);
                        edges.get(j+1).setDistance(edges.get(j).distance);
                        edges.get(j+1).setFlag(edges.get(j).flag);

                        edges.get(j).setX(x);
                        edges.get(j).setY(y);
                        edges.get(j).setDistance(dist);
                        edges.get(j).setFlag(flag);
                    }
                }
            }

            for (int j = 0; j < edges.size() ; j++) {
                if(edges.get(j).flag==1){

                    int x  = edges.get(j).x;
                    int y  = edges.get(j).y;
                    double dist  = edges.get(j).distance;
                    int flag = edges.get(j).flag;

                    edges.get(j).setX(edges.get(j-1).x);
                    edges.get(j).setY(edges.get(j-1).y);
                    edges.get(j).setDistance(edges.get(j-1).distance);
                    edges.get(j).setFlag(0);

                    edges.get(j-1).setX(x);
                    edges.get(j-1).setY(y);
                    edges.get(j-1).setDistance(dist);
                    edges.get(j-1).setFlag(0);
                }

            }
        }
        public void addBuilding(Building building){
            for (int i = (boardSize-1); i >= (boardSize-1)-building.height ; i--) {
                for (int j = building.left; j <= building.right  ; j++) {
                    board[i][j].setE(2);
                }
            }
        }
        public void findEdges(){
            
            for (int i = 0; i < boardSize ; i++) {
                for (int j = 0; j < boardSize ; j++) {
                    if(board[i][j].getE() == 2){
                        
                        if( j >= 1)
                            if(i==(boardSize-1) && board[i][j-1].getE()==0 && board[i][j].getE()==2){
                                int x = (boardSize-1)-i;
                                int y = j;
                                Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                edges.add(edge);

                            }
                            else if(i==(boardSize-1) && board[i][j].getE()==2 && board[i][j+1].getE()==0){
                                int x = (boardSize-1)-i;
                                int y = j;
                                Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                edges.add(edge);
                            }
                            else if(i>=1 && j >=1) {

                                if (board[i][j].getE() == 2 && board[i][j - 1].getE() == 0 && board[i - 1][j - 1].getE() == 0 && board[i - 1][j].getE() == 0) {
                                    int x = (boardSize-1) - i;
                                    int y = j;
                                    Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                    edges.add(edge);

                                }
                                if (board[i][j].getE() == 2 && board[i][j - 1].getE() == 2 && board[i - 1][j - 1].getE() == 0 && board[i - 1][j].getE() == 2) {
                                    int x = (boardSize-1) - i;
                                    int y = j;
                                    Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                    edges.add(edge);

                                } else if (board[i][j].getE() == 2 && board[i][j + 1].getE() == 0 && board[i - 1][j + 1].getE() == 0 && board[i - 1][j].getE() == 0) {
                                    int x = (boardSize-1) - i;
                                    int y = j;
                                    Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                    edge.setFlag(1);
                                    edges.add(edge);

                                } else if (board[i][j].getE() == 2 && board[i][j + 1].getE() == 2 && board[i - 1][j + 1].getE() == 0 && board[i - 1][j].getE() == 2) {
                                    int x = (boardSize-1) - i;
                                    int y = j;
                                    Edge edge = new Edge(x,y,(Math.sqrt(x*x+y*y)+y));
                                    edges.add(edge);
                                }
                        }
                    }
                }
            }
        }
    }
