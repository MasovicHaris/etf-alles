package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class KnightTest {

    @Test
    void move() {
        Knight k = new Knight("B1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("C3")
        );

    }
    @Test
    void move1() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("E6")
        );

    }
    @Test
    void move2() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("F5")
        );

    }
    @Test
    void move3() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("F3")
        );

    }
    @Test
    void move4() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("E2")
        );

    }
    @Test
    void move5() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("C2")
        );

    }
    @Test
    void move6() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("B3")
        );

    }
    @Test
    void move7() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("B5")
        );

    }
    @Test
    void move8() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> k.move("C6")
        );

    }
    @Test
    void moveIllegal1() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertThrows(IllegalArgumentException.class,
                () -> k.move("")
        );
    }

    @Test
    void moveIllegal2() {
        Knight k = new Knight("D4", ChessPiece.Color.WHITE);
        assertThrows(IllegalChessMoveException.class,
                () -> k.move("E3")
        );
    }

    @Test
    void moveIllegal3() {
        Knight k = new Knight("H8", ChessPiece.Color.WHITE);
        assertThrows(IllegalChessMoveException.class,
                () -> k.move("F6")
        );
    }
}