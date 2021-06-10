package ba.unsa.etf.rpr;

public class IllegalChessMoveException extends Exception{
    // implementacija izuzetka - IllegalChessMoveException
    public IllegalChessMoveException(String errorMessage) {
        super(errorMessage);
    }
}
