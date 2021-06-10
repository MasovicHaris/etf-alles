package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class PawnTest {

    @Test
    void move1() {
        Pawn p = new Pawn("E2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> p.move("E4")
        );
    }
    @Test
    void move2() {
        Pawn p = new Pawn("A2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> p.move("A3")
        );
    }
    @Test
    void move3() {
        Pawn p = new Pawn("E7", ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> p.move("E6")
        );
    }
    @Test
    void move4() {
        Pawn p = new Pawn("E7", ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> p.move("E5")
        );
    }
    @org.junit.jupiter.api.Test
    void move5() {
        Pawn p = new Pawn("D2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> p.move("E3")
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal1() {
        Pawn p = new Pawn("E2", ChessPiece.Color.WHITE);
        assertThrows(
                IllegalChessMoveException.class,
                () -> p.move("F4")
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal2() {
        Pawn p = new Pawn("E2", ChessPiece.Color.WHITE);
        assertThrows(
                IllegalChessMoveException.class,
                () -> p.move("E1")
        );
    }
    @org.junit.jupiter.api.Test
    void moveIllegal3() {
        Pawn p = new Pawn("E2", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalChessMoveException.class,
                () -> p.move("E3")
        );
    }
    @org.junit.jupiter.api.Test
    void move6() {
        Pawn p = new Pawn("E2", ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> p.move("D1")
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal4() {
        Pawn p = new Pawn("E3", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalChessMoveException.class,
                () -> p.move("D1")
        );
    }



}