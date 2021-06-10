package ba.unsa.etf.rpr;

import java.util.ArrayList;

public class Board {
    private ArrayList<ChessPiece> activeFigures = new ArrayList<>();
    public ArrayList<ChessPiece> getActiveFgures() { return this.activeFigures; }
    public void setActiveFigures(ArrayList<ChessPiece> activeFigures) { this.activeFigures = activeFigures; }
    public Board(){
        //dodavanje pijuna
        for(char i = 'A'; i <= 'H'; i++)
            activeFigures.add(new Pawn(Character.toString(i) + "2", ChessPiece.Color.WHITE));
        for(char i = 'A'; i <= 'H'; i++)
            activeFigures.add(new Pawn(Character.toString(i) + "7", ChessPiece.Color.BLACK));

        //dodvanje ostalih figura
        activeFigures.add(new King("E1", ChessPiece.Color.WHITE));
        activeFigures.add(new Queen("D1", ChessPiece.Color.WHITE));
        activeFigures.add(new Bishop("C1", ChessPiece.Color.WHITE));
        activeFigures.add(new Bishop("F1", ChessPiece.Color.WHITE));
        activeFigures.add(new Rook("A1", ChessPiece.Color.WHITE));
        activeFigures.add(new Rook("H1", ChessPiece.Color.WHITE));
        activeFigures.add(new Knight("B1", ChessPiece.Color.WHITE));
        activeFigures.add(new Knight("G1", ChessPiece.Color.WHITE));

        activeFigures.add(new King("E8", ChessPiece.Color.BLACK));
        activeFigures.add(new Queen("D8", ChessPiece.Color.BLACK));
        activeFigures.add(new Bishop("C8", ChessPiece.Color.BLACK));
        activeFigures.add(new Bishop("F8", ChessPiece.Color.BLACK));
        activeFigures.add(new Rook("A8", ChessPiece.Color.BLACK));
        activeFigures.add(new Rook("H8", ChessPiece.Color.BLACK));
        activeFigures.add(new Knight("B8", ChessPiece.Color.BLACK));
        activeFigures.add(new Knight("G8", ChessPiece.Color.BLACK));
    }

    public void move(Class type, ChessPiece.Color color, String position) throws IllegalChessMoveException{
        position = position.substring(0,1).toUpperCase() + position.substring(1,2);
        String oldPosition = null;
        ChessPiece figure = null;
        for(int i = 0; i < activeFigures.size(); i++){
            if(activeFigures.get(i).getClass() == type && activeFigures.get(i).getColor().equals(color)){
                try {
                    figure = activeFigures.get(i);
                    oldPosition = figure.getPosition();
                    figure.move(position);
                    validateFigureMovement(figure, oldPosition, position);
                    if(isCheck(color)){
                        throw new IllegalChessMoveException();
                    }
                    return;
                }catch (IllegalChessMoveException e){
                    figure.setPosition(oldPosition);
                    if(i == activeFigures.size() - 1) throw new IllegalChessMoveException();
                    continue;
                }
            } else if(i == activeFigures.size() - 1) throw new IllegalChessMoveException();
        }
    }
    public void move(String oldPosition, String newPosition) throws IllegalArgumentException, IllegalChessMoveException{
        oldPosition = oldPosition.substring(0,1).toUpperCase() + oldPosition.substring(1,2);
        newPosition = newPosition.substring(0,1).toUpperCase() + newPosition.substring(1,2);
        ChessPiece figure = null;
        for(ChessPiece c: activeFigures){
            if(c.getPosition().equalsIgnoreCase(oldPosition)){
                figure = c;
                break;
            }
        }
        if(figure == null) throw new IllegalArgumentException();
        figure.move(newPosition);
        validateFigureMovement(figure, oldPosition, newPosition);
        if(isCheck(figure.getColor()))
            throw new IllegalChessMoveException();
    }

    public boolean isCheck(ChessPiece.Color color){
        String enemyKingPosition = null;
        // nadjemo poziciju neprijateljkog kralja
        for(ChessPiece c : activeFigures)
            if(c instanceof King && c.getColor().equals(color)){
                enemyKingPosition = c.getPosition();
                break;
            }
            //onda provjeravamo da li i jedna figura moze ici na njegovu poziciju
        for(int i = 0; i < activeFigures.size(); i++){
            try{
                Board board = new Board();
                cloneFigures(board);
                if(!board.getActiveFgures().get(i).getColor().equals(color)) board.move(board.getActiveFgures().get(i).getPosition(), enemyKingPosition);
                else continue;
            }catch(IllegalChessMoveException e){
                continue;
            }
            return true;
        }
        return false;
    }

    private void cloneFigures(Board board){
        board.activeFigures = new ArrayList<>();
        for(int i = 0; i < activeFigures.size(); i++){
            try {
                board.activeFigures.add((ChessPiece) activeFigures.get(i).clone());
            } catch (CloneNotSupportedException e) {// ovdje fali line coverage
                throw new InternalError();
            }
        }
    }

    // nakon pomijeranja figure provjeri da li se figura mogla pomijeriti na to mijesto!
    private void validateFigureMovement(ChessPiece figure, String oldPosition, String newPosition) throws IllegalChessMoveException{
        ChessPiece naOdredistu = checkDestination(activeFigures.indexOf(figure), newPosition, figure.getColor());
        if(naOdredistu != null) activeFigures.remove(naOdredistu);
        if(figure instanceof King &&  // king se ne smije pomijeriti na poziciju na kojoj ga moze pojesti neprijateljska figura
                (figure.getColor().equals(ChessPiece.Color.WHITE) && isCheck(ChessPiece.Color.WHITE)
                        || figure.getColor().equals(ChessPiece.Color.BLACK) && isCheck(ChessPiece.Color.BLACK)))
            throw new IllegalChessMoveException();

        //kraljica, lovac, top i pijuni
        if(figure instanceof Rook) checkRookPath(oldPosition, newPosition);
        if(figure instanceof Bishop) checkBishopPath(oldPosition, newPosition);
        if(figure instanceof Pawn) checkPawnPath(oldPosition, newPosition, figure.getColor());
        if(figure instanceof Queen){
            if(oldPosition.charAt(0) == newPosition.charAt(0)
                    || oldPosition.charAt(1) == newPosition.charAt(1))
                checkRookPath(oldPosition, newPosition);
            else checkBishopPath(oldPosition, newPosition);
        }
        // treba se provijeriti koso kretanje kod pijuna
        if(figure instanceof Pawn && naOdredistu != null && !naOdredistu.getColor().equals(figure.getColor()))
            checkPawnDiagonal(oldPosition, newPosition, figure.getColor());
    }
    // metoda za provjeru validnosti pomijeranja pijuna za dva polja
    private void checkIfPawnDoubleMoveIsLegal(String oldPosition, ChessPiece.Color color) throws IllegalChessMoveException{
        if(color.equals(ChessPiece.Color.WHITE) && oldPosition.charAt(1) != '2'
            || color.equals(ChessPiece.Color.BLACK) && oldPosition.charAt(1) != '7')
            throw new IllegalChessMoveException();

    }
    //metoda za provjeru odredista
    private ChessPiece checkDestination(Integer index, String position, ChessPiece.Color color) throws IllegalChessMoveException{
        for(int i = 0; i < activeFigures.size(); i++){
            //ako vec ima figura na odredistu
            if(i != index && activeFigures.get(i).getPosition().equals(position)) {
                // ako je iste boje ne valja
                if (activeFigures.get(i).getColor().equals(color))
                    throw new IllegalChessMoveException();
                    //ako je druge boje vrati tu figuru
                else return activeFigures.get(i);
            }
        }
        //ako nema nista na odreistu onda je OK
        return null;
    }
    // metoda za provjeru putanje topa
    private void checkRookPath(String oldPosition, String newPosition) throws IllegalChessMoveException {
        if(oldPosition.charAt(0) == newPosition.charAt(0)){ //krecemo se po y osi
            char poc, kraj;
            if(oldPosition.charAt(1) > newPosition.charAt(1)){
                poc =  newPosition.charAt(1); poc++;
                kraj = oldPosition.charAt(1);
            }
            else {
                poc =  oldPosition.charAt(1); poc++;
                kraj = newPosition.charAt(1);
            }
            for(; poc < kraj; poc++)
                for(ChessPiece c : activeFigures)
                    if(c.getPosition().equals(oldPosition.substring(0,1) + Character.toString(poc)))
                        throw new IllegalChessMoveException();
        }else {  // krecemo se po x osi
            char poc, kraj;
            if(oldPosition.charAt(0) > newPosition.charAt(0)){
                poc =  newPosition.charAt(0); poc++;
                kraj = oldPosition.charAt(0);
            }
            else {
                poc =  oldPosition.charAt(0); poc++;
                kraj = newPosition.charAt(0);
            }
            for(; poc < kraj; poc++)
                for(ChessPiece c : activeFigures)
                    if(c.getPosition().equals(Character.toString(poc) + oldPosition.substring(1,2)))
                        throw new IllegalChessMoveException();
        }
    }
    //metoda za provjeru putanje lovca
    private void checkBishopPath(String oldPosition, String newPosition) throws IllegalChessMoveException {
        char poc1, poc2, kraj1;
        if(oldPosition.charAt(0) < newPosition.charAt(0) && oldPosition.charAt(1) < newPosition.charAt(1)
            || oldPosition.charAt(0) > newPosition.charAt(0) && oldPosition.charAt(1) > newPosition.charAt(1)){
            // kredanje x>0 i y>0
            if(oldPosition.charAt(0) < newPosition.charAt(0) && oldPosition.charAt(1) < newPosition.charAt(1)){
                poc1 = oldPosition.charAt(0); poc1++;
                poc2 = oldPosition.charAt(1); poc2++;
                kraj1 = newPosition.charAt(0);
            }
            // kretanje x<0 i y<0
            else{
                poc1 = newPosition.charAt(0); poc1++;
                poc2 = newPosition.charAt(1); poc2++;
                kraj1 = oldPosition.charAt(0);
            }
            for (; poc1 < kraj1; poc1++, poc2++)
                for(ChessPiece c: activeFigures)
                    if(c.getPosition().equals(Character.toString(poc1) + Character.toString(poc2)))
                        throw new IllegalChessMoveException();
        }
        else {
            //kretanje x>0 i y<0
            if(oldPosition.charAt(0) < newPosition.charAt(0)
                    && oldPosition.charAt(1) > newPosition.charAt(1)){
                poc1 = oldPosition.charAt(0); poc1++;
                poc2 = oldPosition.charAt(1); poc2--;
                kraj1 = newPosition.charAt(0);
            }
            //kreatanje x<0 i y>0
            else {
                poc1 = newPosition.charAt(0); poc1++;
                poc2 = newPosition.charAt(1); poc2--;
                kraj1 = oldPosition.charAt(0);
            }
            for (; poc1 < kraj1; poc1++, poc2--)
                for(ChessPiece c: activeFigures)
                    if(c.getPosition().equals(Character.toString(poc1) + Character.toString(poc2)))
                        throw new IllegalChessMoveException();
        }
    }
    // metoda za provjeru putanja pijuna kod dvostrukog pomijeranja
    private void checkPawnPath(String oldPosition, String newPosition, ChessPiece.Color color) throws IllegalChessMoveException {
        if(Math.abs(newPosition.charAt(1) - oldPosition.charAt(1)) == 2){
            checkIfPawnDoubleMoveIsLegal(oldPosition, color); // provjera legalnosti double move pijuna
            char character;
            if(color == ChessPiece.Color.WHITE){
                character = oldPosition.charAt(1);
                character++;
            }
            else {
                character = newPosition.charAt(1);
                character++;
            }
            for(ChessPiece c : activeFigures)
                if(c.getPosition().equals(oldPosition.substring(0,1) + Character.toString(character)))
                    throw new IllegalChessMoveException();
        }
    }
    // metoda za provjeru validnosti kosog pomijeranja pijuna
    private void checkPawnDiagonal(String oldPosition, String newPosition, ChessPiece.Color color)throws IllegalChessMoveException{
        if(color.equals(ChessPiece.Color.WHITE) && !(Math.abs(oldPosition.charAt(0) - newPosition.charAt(0)) == 1
            && newPosition.charAt(1) - oldPosition.charAt(1) == 1)) throw new IllegalChessMoveException();
        else if(color.equals(ChessPiece.Color.BLACK) && !(Math.abs(oldPosition.charAt(0) - newPosition.charAt(0)) == 1
                && oldPosition.charAt(1) - newPosition.charAt(1) == 1)) throw new IllegalChessMoveException();
    }
}
