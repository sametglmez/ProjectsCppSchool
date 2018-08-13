public class Edge {
    
    int x;
    int y;
    double distance;
    int flag=0;

    public Edge(int x,int y,double distance){
        this.x = x;
        this.y = y;
        this.distance = distance;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }

    public int getY() {
        return y;
    }

    public int getX() {
        return x;
    }

    public double getDistance() {
        return distance;
    }

    public void setFlag(int flag) {
        this.flag = flag;
    }

    public int getFlag() {
        return flag;
    }
}
