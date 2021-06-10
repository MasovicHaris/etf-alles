package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;

public class Board {
    private ChessPiece[][] board;


    public Board(){
        board = new ChessPiece[8][8];
        // sada rucno zadajemo prvobitnu postavku figura na ploci
        // Kraljevi
        board[0][4] = new King("E8", ChessPiece.Color.BLACK);
        board[7][4] = new King("E1", ChessPiece.Color.WHITE);
        // Kraljice
        board[0][3] = new Queen("D8", ChessPiece.Color.BLACK);
        board[7][3] = new Queen("D1", ChessPiece.Color.WHITE);
        // Topovi
        board[0][0] = new Rook("A8", ChessPiece.Color.BLACK);
        board[7][0] = new Rook("A1", ChessPiece.Color.WHITE);
        board[0][7] = new Rook("H8", ChessPiece.Color.BLACK);
        board[7][7] = new Rook("H1", ChessPiece.Color.WHITE);
        // Konji (divlji hehe)
        board[0][1] = new Knight("B8",ChessPiece.Color.BLACK);
        board[0][6] = new Knight("G8", ChessPiece.Color.BLACK);
        board[7][1] = new Knight("B1", ChessPiece.Color.WHITE);
        board[7][6] = new Knight("G1", ChessPiece.Color.WHITE);
        // Lovci
        board[0][2] = new Bishop("C8", ChessPiece.Color.BLACK);
        board[0][5] = new Bishop("F8", ChessPiece.Color.BLACK);
        board[7][2] = new Bishop("C1", ChessPiece.Color.WHITE);
        board[7][5] = new Bishop("F1", ChessPiece.Color.WHITE);
        // Piuni
        //crni
        board[1][0] = new Pawn("A7", ChessPiece.Color.BLACK);
        board[1][1] = new Pawn("B7", ChessPiece.Color.BLACK);
        board[1][2] = new Pawn("C7", ChessPiece.Color.BLACK);
        board[1][3] = new Pawn("D7", ChessPiece.Color.BLACK);
        board[1][4] = new Pawn("E7", ChessPiece.Color.BLACK);
        board[1][5] = new Pawn("F7", ChessPiece.Color.BLACK);
        board[1][6] = new Pawn("G7", ChessPiece.Color.BLACK);
        board[1][7] = new Pawn("H7", ChessPiece.Color.BLACK);
        // bijeli
        board[6][0] = new Pawn("A2", ChessPiece.Color.WHITE);
        board[6][1] = new Pawn("B2", ChessPiece.Color.WHITE);
        board[6][2] = new Pawn("C2", ChessPiece.Color.WHITE);
        board[6][3] = new Pawn("D2", ChessPiece.Color.WHITE);
        board[6][4] = new Pawn("E2", ChessPiece.Color.WHITE);
        board[6][5] = new Pawn("F2", ChessPiece.Color.WHITE);
        board[6][6] = new Pawn("G2", ChessPiece.Color.WHITE);
        board[6][7] = new Pawn("H2", ChessPiece.Color.WHITE);
        // Napomena - moglo je i sa for petljama ali sam se kasno sjetio :)
    }

    public void move(Class type , ChessPiece.Color color, String position) throws IllegalArgumentException, IllegalChessMoveException{
        // provjere validnosti stringa
        if(position == null || position.length() != 2) throw new IllegalArgumentException();
        ArrayList<Character> letters = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D','E','F','G','H'));
        ArrayList<Integer> numbers  = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8));
        position = position.toUpperCase();
        if(!letters.contains(position.charAt(0))) throw new IllegalArgumentException();
        if(!numbers.contains(Character.getNumericValue(position.charAt(1)))) throw new IllegalArgumentException();
        // provjera kojeg je tipa figura
        if(type == King.class){
            King k = null;
            for(int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j] != null && board[i][j].getClass() == King.class){
                        if (board[i][j].getColor() == color) k = (King) board[i][j];
                    }
                }
            }
            if(k == null) throw new IllegalArgumentException();
            King temp = new King(k.getPosition(),k.getColor());
            try {
                temp.move(position);
            }
            catch(IllegalChessMoveException e){
                throw new IllegalChessMoveException("Ilegalan potez!");
            }
            int startX = Board.getRow(k.getPosition());
            int startY = Board.getColumn(k.getPosition());
            int endX = Board.getRow(position);
            int endY = Board.getColumn(position);
            if(board[endX][endY] != null && board[endX][endY].getColor() == k.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
            k.move(position);
            board[endX][endY] = k;
            board[startX][startY] = null;
        }
       else if(type == Knight.class){
            ArrayList<Knight> knight = new ArrayList<>();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(board[i][j] != null && board[i][j].getClass() == Knight.class
                    && board[i][j].getColor() == color) knight.add((Knight) board[i][j]);
                }
            }
            if(knight.isEmpty()) throw new IllegalArgumentException();
            boolean flag = false;
            for(Knight k : knight){
                Knight temp = new Knight(k.getPosition(),k.getColor());
                flag = false;
                try{
                    temp.move(position);
                    flag = true;
                }
                catch(IllegalChessMoveException e){
                }
                if(flag){
                    int startX = Board.getRow(k.getPosition());
                    int startY = Board.getColumn(k.getPosition());
                    int endX = Board.getRow(position);
                    int endY = Board.getColumn(position);
                    if(board[endX][endY] != null && board[endX][endY].getColor() == k.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
                    k.move(position);
                    board[endX][endY] = k;
                    board[startX][startY] = null;
                    break;
                }
            }
            if(!flag) throw new IllegalChessMoveException("Ilegalan potez!");
        }

       else if(type == Bishop.class){
            ArrayList<Bishop> bishop = new ArrayList<>();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(board[i][j] != null && board[i][j].getClass() == Bishop.class
                            && board[i][j].getColor() == color) bishop.add((Bishop) board[i][j]);
                }
            }
            if(bishop.isEmpty()) throw new IllegalArgumentException();
            boolean flag = false;
            for(Bishop b: bishop){
                Bishop temp = new Bishop(b.getPosition(),b.getColor());
                flag = false;
                try{
                    temp.move(position);
                    flag = true;
                }
                catch(IllegalChessMoveException e){
                }
                if(flag){
                    int startX = Board.getRow(b.getPosition());
                    int startY = Board.getColumn(b.getPosition());
                    int endX = Board.getRow(position);
                    int endY = Board.getColumn(position);
                    if(board[endX][endY] != null && board[endX][endY].getColor() == b.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
                    if(this.isPiecesBetweenDiagonal(b.getPosition(), position)) throw new IllegalChessMoveException("Lovac ne moze preskakati!");
                    b.move(position);
                    board[endX][endY] = b;
                    board[startX][startY] = null;
                    break;
                }
            }
            if(!flag) throw new IllegalChessMoveException("Ilegalan potez!");
        }
       else if(type == Queen.class){
            Queen q = null;
            for(int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j] != null && board[i][j].getClass() == Queen.class){
                        if (board[i][j].getColor() == color) {
                            q = (Queen) board[i][j];
                            break;
                        }
                    }
                }
            }
            if(q == null) throw new IllegalArgumentException();
            Queen temp = new Queen(q.getPosition(),q.getColor());
            try {
                temp.move(position);
            }
            catch(IllegalChessMoveException e){
                throw new IllegalChessMoveException("Ilegalan potez!");
            }

            int startX = Board.getRow(q.getPosition());
            int startY = Board.getColumn(q.getPosition());

            int endX = Board.getRow(position);
            int endY = Board.getColumn(position);

            if(board[endX][endY] != null && board[endX][endY].getColor() == q.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
            if(startX == endX){
                if(this.isPeacesBetweenHorizontal(q.getPosition(),position)) throw new IllegalChessMoveException("Kraljica ne moze preskakat!");
            }
            else if(startY == endY){
                if(this.isPeacesBetweenVertical(q.getPosition(),position)) throw new IllegalChessMoveException("Kraljica ne moze preskakat");
            }
            else{
                if(this.isPiecesBetweenDiagonal(q.getPosition(),position)) throw new IllegalChessMoveException("Kraljica ne moze preskakat");
            }
            q.move(position);
            board[endX][endY] = q;
            board[startX][startY] = null;
        }
        else if(type == Rook.class){
            ArrayList<Rook> rook = new ArrayList<>();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(board[i][j] != null && board[i][j].getClass() == Rook.class
                            && board[i][j].getColor() == color) rook.add((Rook) board[i][j]);
                }
            }
            if(rook.isEmpty()) throw new IllegalArgumentException();
            boolean flag = false;
            for(Rook r: rook){
                Rook temp = new Rook(r.getPosition(),r.getColor());
                flag = false;
                try{
                    temp.move(position);
                    flag = true;
                }
                catch(IllegalChessMoveException e){
                }
                if(flag){
                    int startX = Board.getRow(r.getPosition());
                    int startY = Board.getColumn(r.getPosition());
                    int endX = Board.getRow(position);
                    int endY = Board.getColumn(position);
                    if(board[endX][endY] != null && board[endX][endY].getColor() == r.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
                    if(startX == endX){
                        if(this.isPeacesBetweenHorizontal(r.getPosition(),position)) throw new IllegalChessMoveException("Top ne moze preskakati!");
                    }
                    else{
                        if(this.isPeacesBetweenVertical(r.getPosition(),position)) throw new IllegalChessMoveException(("Top ne moze preskakati!"));
                    }
                    r.move(position);
                    board[endX][endY] = r;
                    board[startX][startY] = null;
                    break;
                }
            }
            if(!flag) throw new IllegalChessMoveException("Ilegalan potez!");
        }
        else if(type == Pawn.class){
            ArrayList<Pawn> pawn = new ArrayList<>();
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(board[i][j] != null && board[i][j].getClass() == Pawn.class
                            && board[i][j].getColor() == color) pawn.add((Pawn) board[i][j]);
                }
            }
            if(pawn.isEmpty()) throw new IllegalArgumentException();
            boolean flag = false;
            for(Pawn p: pawn){
                Pawn temp = new Pawn(p.getPosition(),p.getColor());
                flag = false;
                try{
                    temp.move(position);
                    flag = true;
                }
                catch(IllegalChessMoveException e){
                }
                if(flag){
                    int startX = Board.getRow(p.getPosition());
                    int startY = Board.getColumn(p.getPosition());
                    int endX = Board.getRow(position);
                    int endY = Board.getColumn(position);
                    if(board[endX][endY] != null && board[endX][endY].getColor() == p.getColor()) throw new IllegalChessMoveException("Figura iste boje!");
                    if((Math.abs(endX - startX) == 1 && Math.abs(startY - endY) == 1) && board[endX][endY] == null) continue;
                    if(startY == endY && board[endX][endY] != null) throw new IllegalChessMoveException("Piun ne može da jede vertikalno!");
                    p.move(position);
                    board[endX][endY] = p;
                    board[startX][startY] = null;
                    break;
                }
            }
            if(!flag) throw new IllegalChessMoveException("Ilegalan potez!");
        }
        else throw new IllegalArgumentException("Nepoznata figura!");


    }

    private boolean isPiecesBetweenDiagonal(String position1, String position2){
        int startX = Board.getRow(position1);
        int startY = Board.getColumn(position1);
        int endX = Board.getRow(position2);
        int endY = Board.getColumn(position2);

        int offsetX, offsetY;

        if(startX > endX && startY > endY){
            offsetX = -1; offsetY = -1;
        }
        else if(startX > endX && startY < endY){
            offsetX = -1; offsetY = 1;
        }
        else if(startX < endX && startY > endY){
            offsetX = 1; offsetY = -1;
        }
        else{
            offsetX = 1; offsetY = 1;
        }
        int x = startX;
        int y = startY;
        for(int i = 0; i < Math.abs(startX - endX) - 1; i++){
            x += offsetX;
            y += offsetY;
            if(board[x][y] != null) return true;
        }
        return false;
    }
    // pomocna funkcija za provjeru da li se nalaze figure horizontalno izmedju dvije pozicije
    private boolean isPeacesBetweenHorizontal(String position1, String position2){
        int startX = Board.getRow(position1);
        int startY = Board.getColumn(position1);
        int endY = Board.getColumn(position2);
        int yOffset;
        int y = startY;
        if(startY > endY) yOffset = -1;
        else yOffset = 1;
        for(int i = 0; i < Math.abs(startY - endY) - 1; i++){
            y += yOffset;
            if(board[startX][y] != null) return true;
        }
        return false;
    }
    // pomocna funkcija za provjeru da li se nalaze figure vertikalno izmedju dvije pozicije
    private boolean isPeacesBetweenVertical(String position1, String position2){
        int startX = Board.getRow(position1);
        int startY = Board.getColumn(position1);
        int endX = Board.getRow(position2);
        int xOffset;
        int x = startX;
        if(startX > endX) xOffset = -1;
        else xOffset = 1;
        for(int i = 0; i < Math.abs(startX - endX) - 1; i++){
            x += xOffset;
            if(board[x][startY] != null) return true;
        }
        return false;
    }


    /*
    funkcije koje ekstraktuju kooradniate x i y iz Stringa
    koordinate su obrnute jer board implementirana kao
    matrica koja je ustvari obrnuta u odnosu na pravu sahovsku plocu
    */
    private static int getColumn(String position){
        char c = Character.toUpperCase(position.charAt(0));
        return  ((int)c - 'A');
    }

    private static int getRow(String position){
        return 8 - Character.getNumericValue(position.charAt(1));
    }



    public void move(String oldPosition, String newPosition) throws IllegalChessMoveException, IllegalArgumentException{
        if(oldPosition == null || oldPosition.length() != 2) throw new IllegalArgumentException();
        oldPosition = oldPosition.toUpperCase();
        ArrayList<Character> letters = new ArrayList<>(Arrays.asList('A', 'B', 'C', 'D','E','F','G','H'));
        ArrayList<Integer> numbers  = new ArrayList<>(Arrays.asList(1,2,3,4,5,6,7,8));
        if(!letters.contains(oldPosition.charAt(0))) throw new IllegalArgumentException();
        if(!numbers.contains(Character.getNumericValue(oldPosition.charAt(1)))) throw new IllegalArgumentException();
        int x = Board.getRow(oldPosition);
        int y = Board.getColumn(oldPosition);
        if(board[x][y] == null) throw new IllegalArgumentException();
        try {
            this.move(board[x][y].getClass(), board[x][y].getColor(), newPosition);
        }
        catch(IllegalArgumentException e){
            throw e;
        }
        catch (IllegalChessMoveException m){
            throw m;
        }
    }

    public boolean isCheck(ChessPiece.Color color){
        int x = -1;
        int y = -1;
        String kingPosition = "";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] != null && board[i][j] instanceof King && board[i][j].getColor() == color){
                    x = Board.getRow(board[i][j].getPosition());
                    y = Board.getColumn(board[i][j].getPosition());
                    kingPosition = board[i][j].getPosition();
                    break;
                }
            }
        }
        King tempKing = new King(kingPosition,color);
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] != null && board[i][j].getColor() != color && !(board[i][j] instanceof King)){
                    boolean flag = false;
                   // ChessPiece tempPiece = k.getDeclaredConstructor(String.class,ChessPiece.Color.class).newInstance(board[i][j].getPosition(),board[i][j].getColor());
                    ChessPiece tempPiece = null;
                    if(board[i][j] instanceof Pawn) tempPiece = new Pawn(board[i][j].getPosition(),board[i][j].getColor());
                    if(board[i][j] instanceof Queen) tempPiece = new Queen(board[i][j].getPosition(),board[i][j].getColor());
                    if(board[i][j] instanceof Rook) tempPiece = new Rook(board[i][j].getPosition(),board[i][j].getColor());
                    if(board[i][j] instanceof Bishop) tempPiece = new Bishop(board[i][j].getPosition(),board[i][j].getColor());
                    if(board[i][j] instanceof Knight) tempPiece = new Knight(board[i][j].getPosition(),board[i][j].getColor());

                    try{
                        this.move(board[i][j].getPosition(),kingPosition);
                        flag = true;
                    }
                    catch(Exception e){}
                    if(flag){
                        board[i][j] = tempPiece;
                        board[x][y] = tempKing;
                        return true;
                    }
                }
            }
        }
        return false;
    }
}
