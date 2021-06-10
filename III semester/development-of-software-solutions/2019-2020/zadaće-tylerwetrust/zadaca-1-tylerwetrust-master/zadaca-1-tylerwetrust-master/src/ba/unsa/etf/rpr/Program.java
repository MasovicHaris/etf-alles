package ba.unsa.etf.rpr;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Program {
    public static void main(String[] args){
        Board board = new Board();
        boolean flag = true;
        Scanner ulaz = new Scanner(System.in);
        Map<String, ChessPiece> figure = new HashMap<>();
        figure.put("K", new King("A1", ChessPiece.Color.WHITE));
        figure.put("Q", new Queen("A1", ChessPiece.Color.WHITE));
        figure.put("N", new Knight("A1", ChessPiece.Color.WHITE));
        figure.put("R", new Rook("A1", ChessPiece.Color.WHITE));
        figure.put("B", new Bishop("A1", ChessPiece.Color.WHITE));

        for(;;){
            if(flag){
                System.out.println("White move: ");
                String potez = ulaz.nextLine();
                if(potez.equals("X")){
                    System.out.println("Don't give up :( Game over.");
                    break;
                }
                if(potez.length() == 2){
                 if(!(potez.charAt(0) >= 'a' && potez.charAt(1) <= 'h') || !(potez.charAt(1) >= '1' && potez.charAt(1) <= '8') ){
                     System.out.println("Ponovite unos!");
                     continue;
                 }
                 try {
                     board.move(Pawn.class, ChessPiece.Color.WHITE, potez);
                     flag = false;
                     if(board.isCheck(ChessPiece.Color.BLACK)){
                         System.out.println("CHECK!");
                     }
                 }
                 catch(Exception e){
                     System.out.println("Ilegal move!");
                     continue;
                 }
                }
                else if(potez.length() == 3){
                    if(!figure.containsKey(Character.toString(potez.charAt(0)))
                    || !(potez.charAt(1) >= 'a' && potez.charAt(1) <= 'h') || !(potez.charAt(2) >= '1' && potez.charAt(2) <= '8')){
                        System.out.print("Ponovi unos!");
                        continue;
                    }
                    ChessPiece klasa = figure.get(Character.toString(potez.charAt(0)));
                    String pos = potez.substring(1);
                    try{
                        board.move(klasa.getClass(),ChessPiece.Color.WHITE, pos);
                        flag = false;
                        if(board.isCheck(ChessPiece.Color.BLACK)){
                            System.out.println("CHECK!");
                        }
                    }
                    catch(Exception e){
                        System.out.println("Ilegal move!");
                    }

                }else{
                    System.out.println("Ponovite unos!");
                    continue;
                }
            }
            else{
                System.out.println("Black move: ");
                String potez = ulaz.nextLine();
                if(potez.equals("X")){
                    System.out.println("Don't give up :( Game over.");
                    break;
                }
                if(potez.length() == 2){
                    if(!(potez.charAt(0) >= 'a' && potez.charAt(1) <= 'h') || !(potez.charAt(1) >= '1' && potez.charAt(1) <= '8') ){
                        System.out.println("Ponovite unos!");
                        continue;
                    }
                    try {
                        board.move(Pawn.class, ChessPiece.Color.BLACK, potez);
                        flag = true;
                        if(board.isCheck(ChessPiece.Color.WHITE)){
                            System.out.println("CHECK!");
                        }
                    }
                    catch(Exception e){
                        System.out.println("Ilegal move!");
                        continue;
                    }
                }
                else if(potez.length() == 3){
                    if(!figure.containsKey(Character.toString(potez.charAt(0)))
                            || !(potez.charAt(1) >= 'a' && potez.charAt(1) <= 'h') || !(potez.charAt(2) >= '1' && potez.charAt(2) <= '8')){
                        System.out.print("Ponovi unos!");
                        continue;
                    }
                    ChessPiece klasa = figure.get(Character.toString(potez.charAt(0)));
                    String pos = potez.substring(1).toUpperCase();
                    try{
                        board.move(klasa.getClass(),ChessPiece.Color.BLACK, pos);
                        flag = true;
                        if(board.isCheck(ChessPiece.Color.WHITE)){
                            System.out.println("CHECK!");
                        }
                    }
                    catch(Exception e){
                        System.out.println("Ilegal move!");
                    }

                }else{
                    System.out.println("Ponovite unos!");
                    continue;
                }
            }

        }

    }
}
