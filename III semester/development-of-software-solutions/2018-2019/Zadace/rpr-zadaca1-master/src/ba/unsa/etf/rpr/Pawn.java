package ba.unsa.etf.rpr;

public class Pawn extends ChessPiece {

    public Pawn(String position, Color color){
        super(position, color);
    }

    private boolean whitePawnMove(String position){
        //provajera validnosti za white
        String oldPosition = getPosition();
        // pomijeranje naprijed
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 0
                && ((int)(position.charAt(1) - oldPosition.charAt(1)) == 1 || (int)(position.charAt(1) - oldPosition.charAt(1)) == 2))
            return true;
        //pomijeranje u koso
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 1 && position.charAt(1) - oldPosition.charAt(1) == 1)
            return true;
        else return false;
    }
    private boolean blackPawnMove(String position){
        //provjera validnosti za black
        String oldPosition = getPosition();
        //pomijeranje naprijed
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 0
                && ((int)(oldPosition.charAt(1) - position.charAt(1)) == 1 || (int)(oldPosition.charAt(1) - position.charAt(1)) == 2))
            return true;
        //pomijeranje u koso
        if(Math.abs((int)(oldPosition.charAt(0) - position.charAt(0))) == 1 && oldPosition.charAt(1) - position.charAt(1) == 1)
            return true;
        else return false;
    }
    @Override
    public void move(String position) throws IllegalArgumentException, IllegalChessMoveException {
        if(!CheckPositionFormat.checkPositionFormat(position)) throw new IllegalArgumentException("");
        position = position.substring(0,1).toUpperCase() + position.substring(1,2);
        switch (color){
            case WHITE:
                if(whitePawnMove(position)) {
                    super.position = position;
                    return;
                }
                break;
            case BLACK:
                if(blackPawnMove(position)) {
                    super.position = position;
                    return;
                }
                break;
        }
        throw new IllegalChessMoveException();
    }
}
