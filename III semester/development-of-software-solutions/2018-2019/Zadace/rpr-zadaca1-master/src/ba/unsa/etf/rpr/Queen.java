package ba.unsa.etf.rpr;

public class Queen extends ChessPiece {

    public Queen(String position, Color color){
        super(position, color);
    }

    @Override
    public void move(String position) throws IllegalArgumentException, IllegalChessMoveException {
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException();
        position = position.substring(0, 1).toUpperCase() + position.substring(1,2);
        String oldPosition = getPosition();
        /* Ovdje gledamo ako se kraljica ne pomijera po visini ili sirini i
        ako se ne pomijera po dijagonali onda pomijeranje nije dobro*/
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) != 0 && Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))) != 0
                && Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) != Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))))
            throw new IllegalChessMoveException();
        super.position = position;
    }
}
