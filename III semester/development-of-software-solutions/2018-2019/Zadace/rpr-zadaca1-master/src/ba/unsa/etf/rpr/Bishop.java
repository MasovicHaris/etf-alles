package ba.unsa.etf.rpr;

public class Bishop extends ChessPiece {

    public Bishop(String position, Color color){
        super(position, color);
    }
    @Override
    public void move(String position) throws IllegalArgumentException, IllegalChessMoveException {
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException("");
        position = position.substring(0, 1).toUpperCase() + position.substring(1,2);
        String oldPosition = getPosition();
        // ovdje se treba samo provjeriti da li se mijenjaju slovo i broj po dijagonali
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0)))
                != Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))))
            throw new IllegalChessMoveException();
        super.position = position;
    }
}
