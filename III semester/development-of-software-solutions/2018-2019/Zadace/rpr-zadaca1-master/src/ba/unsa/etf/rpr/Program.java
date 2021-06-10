package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.Scanner;

public class Program {
    public static final String X = "x";
    public static final String ILLEGAL_MOVE = "Illegal move";
    public static final String CRNI_IGRAC_JE_PREDAO_PARTIJU = "White player has won by default";
    public static final String BIJELI_IGRAC_JE_PREDAO_PARTIJU = "Black player has won by default";
    public static final String WHITE_MOVE = "White move: ";
    public static final String BLACK_MOVE = "Black move: ";
    public static final String CHECK = "CHECK!!!";
    Board board = new Board();
    ChessPiece.Color color = null;

     public static void main(String[] args) {
        Program program = new Program();
         while(true){
             Scanner scanner = new Scanner(System.in);
             String input = scanner.nextLine();
             input.trim(); // ciscenje blankova na krajevima
             // provjera ispravnosti unosa
             if(input.length() != 14 && input.length() != 15 && input.length() != 1){
                 System.out.println(ILLEGAL_MOVE);
                 continue;
             }
             // Provjera predavanja partije;
             if(input.equalsIgnoreCase(X)){
                 if(program.color.equals(ChessPiece.Color.WHITE)) System.out.println(CRNI_IGRAC_JE_PREDAO_PARTIJU);
                 else System.out.println(BIJELI_IGRAC_JE_PREDAO_PARTIJU);
                 break;
             }
             String inputColor = input.substring(0, 12);
             if(inputColor.equalsIgnoreCase(WHITE_MOVE) && (program.color == null || program.color.equals(ChessPiece.Color.BLACK)))
                 program.color = ChessPiece.Color.WHITE;
             else if(inputColor.equalsIgnoreCase(BLACK_MOVE) && (program.color == null || program.color.equals(ChessPiece.Color.WHITE)))
                 program.color = ChessPiece.Color.BLACK;
             else {
                 System.out.println(ILLEGAL_MOVE);
                 continue;
             }
            Class classType = null;
            String position = null;
            if(input.length() == 14) {
                position = input.substring(12,14);
                classType = Pawn.class;
            }
            else if(input.length() == 15){
                position = input.substring(13, 15);
                switch (input.substring(12, 13)){
                    case "K":
                        classType = King.class;
                        break;
                    case "Q":
                        classType = Queen.class;
                        break;
                    case "R":
                        classType = Rook.class;
                        break;
                    case "B":
                        classType = Bishop.class;
                        break;
                    case "N":
                        classType = Knight.class;
                        break;

                }
            }
             try{ //  treba prvo provjeriti da li se moze isvrsiti pomijeranje vazno
                 Board board = new Board();
                 ArrayList<ChessPiece> kopija = new ArrayList<>();
                 for(ChessPiece c: program.board.getActiveFgures())
                     kopija.add((ChessPiece) c.clone());
                 board.setActiveFigures(kopija);
                 // provjera
                 board.move(classType, program.color, position);
                 // posla je provjera sad je stvarno pomijeranje
                 program.board.move(classType, program.color, position);
             } catch (CloneNotSupportedException e) {
                 e.printStackTrace();
             } catch (IllegalChessMoveException e) {
                 System.out.println(ILLEGAL_MOVE);
                 continue;
             }
             // sad treba provjeriti da li je sah
             ChessPiece.Color color = null;
             if(program.color.equals(ChessPiece.Color.WHITE)) color = ChessPiece.Color.BLACK;
             else color = ChessPiece.Color.WHITE;
             if(program.board.isCheck(color))
                 System.out.println(CHECK);
         }

    	/*System.out.println("Klasa Program sadrži metodu main koja omogućuje igračima da povlače poteze. " +
                "Korisnik unosi naizmjenično poteze bijelog i crnog igrača koristeći skraćenu (algebarsku) " +
                "notaciju uz oznake figura na engleskom jeziku: K, Q, R, B i N, dok se polja označavaju malim slovom. " +
                "U metodi main treba biti kreiran objekat tipa Board te koristiti prvu varijantu metode move za povlačenje poteza. " +
                "U slučaju neispravnog poteza ispisati poruku \"Illegal move\" i tražiti ponovni unos. " +
                "U slučaju da je nakon nekog poteza došlo do šaha treba ispisati poruku \"CHECK!!!\" što se saznaje pomoću metode isCheck.\n" +
                "Korisnik može unijeti slovo X da preda partiju. Primjer ulaza i izlaza:\n" +
                "\tWhite move: e4\n" +
                "\tBlack move: e5\n" +
                "\tWhite move: Nf3\n" +
                "\tBlack move: Nc6\n" +
                "\tWhite move: Bb5\n" +
                "\tBlack move: a6\n" +
                "\tWhite move: Ba4\n" +
                "\tBlack move: Nf6\n" +
                "\n" +
                "Zadaću treba realizirati tako što će se najprije napraviti fork projekta \"rpr-zadaca1\" koji sadrži dio testova, a zatim implementirati klase i preostale testove kako bi pokrivenost koda testovima bila 100%.\n" +
                "\n" +
                "U zadaći je obavezno pridržavati se svih pravila koja su do sada obrađena na predmetu, te će po tim pravilima biti i ocjenjivano. To uključuje:\n" +
                "ispravno imenovanje paketa, klasa, metoda i promjenljivih,\n" +
                "primjenu komentara,\n" +
                "atomic commits.\n");*/
    }
}
