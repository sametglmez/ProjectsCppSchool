public class Cell {
    public int x,y,e;

    public Cell(int x, int y, int e){
        this.x = x;
        this.y = y;
        this.e = e;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setE(int e) {
        this.e = e;
    }

    public int getE() {
        return e;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
