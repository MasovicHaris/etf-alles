package ba.unsa.etf.rpr;

public class Knight extends ChessPiece {

    public Knight(String position, Color color){
        super(position, color);
    }
    @Override
    public void move(String position) throws IllegalArgumentException, IllegalChessMoveException {
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException("");
        position = position.substring(0, 1).toUpperCase() + position.substring(1,2);
        String oldPosition = getPosition();
        // sad treba provjeriti da se od dvije oznake vrsi promijena 1 2  ili 2 1
        if((Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 1 && Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))) == 2)
                || (Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 2 && Math.abs((int)(oldPosition.charAt(1) - position.charAt(1))) == 1))
            super.position = position;
        else throw new IllegalChessMoveException();
    }
}
