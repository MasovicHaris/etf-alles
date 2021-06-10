package ba.unsa.etf.rpr;

public class Rook extends ChessPiece {

    public Rook(String position, Color color){
        super(position, color);
    }
    @Override
    public void move(String position) throws IllegalArgumentException, IllegalChessMoveException {
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException();
        position = position.substring(0, 1).toUpperCase() + position.substring(1,2);
        String oldPosition = getPosition();
        // provjeravamo da li je pomijeranje na jednom od parametara nula
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) != 0
                && Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))) != 0)
            throw new IllegalChessMoveException();
        super.position = position;
    }
}
