package ba.unsa.etf.rpr;

public abstract class ChessPiece implements Cloneable{
    protected Color color = null;
    protected String position = null;
    //methods realized in child classes
    public String getPosition(){ return position; }
    public Color getColor(){ return color; }
    public void setColor(Color color){ this.color = color; }
    public void setPosition(String position) { this.position = position; }
    public abstract void move(String position) throws IllegalArgumentException, IllegalChessMoveException;
    public ChessPiece(String position, Color color) throws IllegalArgumentException{
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException();
        this.position = position.substring(0,1).toUpperCase() + position.substring(1,2);
        this.color = color;
    }
    public enum Color {
        BLACK, WHITE
    }
    @Override
    public Object clone() throws CloneNotSupportedException{
        return super.clone();
    }
}
