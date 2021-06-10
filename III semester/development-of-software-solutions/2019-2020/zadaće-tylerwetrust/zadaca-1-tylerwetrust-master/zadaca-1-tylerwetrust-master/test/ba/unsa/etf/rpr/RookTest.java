package ba.unsa.etf.rpr;

import static org.junit.jupiter.api.Assertions.*;

class RookTest {
    @org.junit.jupiter.api.Test
    void moveDiagonal() {
        Rook r = new Rook("A1", ChessPiece.Color.WHITE);
        assertThrows(
                IllegalChessMoveException.class, () -> r.move("B2")
        );
    }

    @org.junit.jupiter.api.Test
    void moveDiagonal2() {
        Rook r = new Rook("A8", ChessPiece.Color.BLACK);
        assertThrows( IllegalChessMoveException.class,
                () -> r.move("B7")
        );
    }

    @org.junit.jupiter.api.Test
    void moveBack() {
        Rook r = new Rook("D5", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> r.move("D1")
        );
    }

    @org.junit.jupiter.api.Test
    void constructor1() {
        assertThrows(
                IllegalArgumentException.class,
                () -> new Rook("I2", ChessPiece.Color.WHITE)
        );
    }

    @org.junit.jupiter.api.Test
    void constructor2() {
        assertThrows(
                IllegalArgumentException.class,
                () -> new Rook("B9", ChessPiece.Color.WHITE)
        );
    }

    @org.junit.jupiter.api.Test
    void constructor3() {
        assertThrows(
                IllegalArgumentException.class,
                () -> new Rook("", ChessPiece.Color.WHITE)
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal1() {
        Rook r = new Rook("C1", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalArgumentException.class,
                () -> r.move("C0")
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal2() {
        Rook r = new Rook("H8", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalArgumentException.class,
                () -> r.move("I1")
        );
    }

    @org.junit.jupiter.api.Test
    void moveIllegal3() {
        Rook r = new Rook("H8", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalArgumentException.class,
                () -> r.move("")
        );
    }


}