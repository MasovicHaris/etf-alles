package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.Arrays;

public class Pawn extends ChessPiece {
    private boolean firstMove;

    public Pawn(String position, Color color) {
        super(position, color);
        firstMove = true;
    }

    @Override
    public void move(String position) throws IllegalChessMoveException, IllegalArgumentException {
        if (position == null || position.length() != 2) throw new IllegalArgumentException();
        ArrayList<Character> letters = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'));
        ArrayList<Integer> numbers = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8));
        if (!letters.contains(position.charAt(0))) throw new IllegalArgumentException();
        if (!numbers.contains(Character.getNumericValue(position.charAt(1)))) throw new IllegalArgumentException();
        if(this.position.equals(position.toUpperCase())) throw new IllegalChessMoveException("Ilegalan potez!");
        int startX = getXNumb(this.position);
        int endX = getXNumb(position);
        int startY = getYNumb(this.position);
        int endY = getYNumb(position);
        /*if (startX == endX) {
            if (startY - endY == 1) {
                if (firstMove) {
                    firstMove = false;
                }
                this.position = position;
            } else if (this.getColor() == Color.WHITE && firstMove && (endY - startY) == 2) {
                if (firstMove) {
                    firstMove = false;
                }
                this.position = position;
            } else if (this.getColor() == Color.BLACK && firstMove && (startY - endY) == 2) {
                if (firstMove) {
                    firstMove = false;
                }
                this.position = position;
            }
        }else if (Math.abs(startX - endX) == 1) {
            if (startY - endY == 1) {
                if (firstMove) {
                    firstMove = false;
                }
                this.position = position;
            }
        } else throw new IllegalChessMoveException("Ilegalna pozicija!");
    } */

        if(this.getColor() == ChessPiece.Color.WHITE){
            if(startX == endX){
                if(endY - startY == 2 && firstMove){
                    firstMove = false;
                    this.position = position;
                }
                if(endY - startY == 1){
                    if(firstMove) firstMove = false;
                    this.position = position;
                }
            }
            else if(Math.abs(endX - startX) == 1 && endY - startY == 1){
                if(firstMove) firstMove = false;
                this.position = position;
            }
        }else {
            if(startX == endX){
                if(startY - endY == 2 && firstMove){
                    firstMove = false;
                    this.position = position;
                }
                if(startY - endY == 1){
                    if(firstMove) firstMove = false;
                    this.position = position;
                }
            }
            else if(Math.abs(endX - startX) == 1 && startY - endY == 1){
                if(firstMove) firstMove = false;
                this.position = position;
            }
        }

        if(!this.position.equals(position)) throw new IllegalChessMoveException("Greska");

        }
}

