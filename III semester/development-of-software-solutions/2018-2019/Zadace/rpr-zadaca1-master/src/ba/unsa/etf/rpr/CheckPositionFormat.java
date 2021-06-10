package ba.unsa.etf.rpr;

public class CheckPositionFormat {
    public static boolean checkPositionFormat(String position){
        if(position == null || position.length() != 2) return false;
        position = position.substring(0,1).toUpperCase() + position.substring(1,2);
        if(position.charAt(0) < 'A' || position.charAt(0) > 'H' || position.charAt(1) < '1' || position.charAt(1) > '8') return false;
        return true;
    }
}
