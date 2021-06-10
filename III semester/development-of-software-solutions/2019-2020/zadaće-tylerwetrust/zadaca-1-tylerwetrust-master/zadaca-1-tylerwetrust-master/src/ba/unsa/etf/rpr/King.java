package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.Arrays;

public class King extends ChessPiece {

    public King(String position, Color color){
        super(position,color);
    }
    @Override
    public void move(String position) throws IllegalChessMoveException, IllegalArgumentException{
        if(position == null || position.length() != 2) throw new IllegalArgumentException();
        ArrayList<Character> letters = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D','E','F','G','H','a','b','c','d','e','f','g','h'));
        ArrayList<Integer> numbers  = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8));
        if(!letters.contains(position.charAt(0))) throw new IllegalArgumentException();
        if(!numbers.contains(Character.getNumericValue(position.charAt(1)))) throw new IllegalArgumentException();
        if(this.position.equals(position.toUpperCase())) throw new IllegalChessMoveException("Ilegalan potez!");
        int startX = getXNumb(this.position);
        int endX = getXNumb(position);
        int startY = getYNumb(this.position);
        int endY = getYNumb(position);
        if (Math.abs(startX- endX) <= 1 &&
                Math.abs(startY - endY) <= 1) this.position = position;
        else throw new IllegalChessMoveException("Ilegalna pozicija!");
    }


}
