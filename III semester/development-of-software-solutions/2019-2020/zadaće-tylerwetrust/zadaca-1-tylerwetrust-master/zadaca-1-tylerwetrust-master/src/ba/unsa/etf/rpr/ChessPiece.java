package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.Arrays;

public abstract class ChessPiece{
    public static enum Color {WHITE, BLACK};
    protected String position;
    protected Color color;

    // apstrakna metoda move - jer nema smisla implementirati ovdje
    abstract public void move (String position) throws IllegalChessMoveException;
    // konstruktor
    public ChessPiece(String position, Color color){
        if(position == null || position.length() != 2) throw new IllegalArgumentException();
        ArrayList<Character> letters = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D','E','F','G','H'));
        ArrayList<Integer> numbers  = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8));
        if(!letters.contains(position.charAt(0))) throw new IllegalArgumentException();
        if(!numbers.contains(Character.getNumericValue(position.charAt(1)))) throw new IllegalArgumentException();
        this.color = color;
        this.position = position;
    }


    public  String getPosition(){
        return position;
    }

    public Color getColor(){
        return color;
    }
    // funkcije za ekstrakciju X i Y koordinata iz Stringa pozicije
    // Napomena: ove koordinate su date u odnosu na sahovsku plocu a ne matricu
    protected static int getXNumb(String position){
        char c = Character.toUpperCase(position.charAt(0));
        return (int)c - 'A' + 1;
    }

    protected static int getYNumb(String position){
        return Character.getNumericValue(position.charAt(1));
    }


}
