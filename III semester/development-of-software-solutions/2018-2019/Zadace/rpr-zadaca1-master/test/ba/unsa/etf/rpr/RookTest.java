package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class RookTest {

    @Test
    void moveUp() {
        Rook rook = new Rook("D1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> rook.move("D5")
        );
    }
    @Test
    void moveDown() {
        Rook rook = new Rook("A3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> rook.move("A1")
        );
    }
    @Test
    void moveRight() {
        Rook rook = new Rook("A3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> rook.move("E3")
        );
    }@Test
    void moveLeft() {
        Rook rook = new Rook("H1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> rook.move("A1")
        );
    }
    @Test
    void move(){
        Rook rook = new Rook("C5", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> rook.move("C5")
        );
    }
    @Test
    void moveIllegal1() {
        Rook rook = new Rook("C5", ChessPiece.Color.WHITE);
        assertThrows(IllegalChessMoveException.class,
                () -> rook.move("D4")
        );
    }

    @Test
    void moveIllegal2() {
        Rook rook = new Rook("C5", ChessPiece.Color.WHITE);
        assertThrows(IllegalArgumentException.class,
                () -> rook.move("I2")
        );
    }

    @Test
    void moveIllegal3() {
        Rook rook = new Rook("C5", ChessPiece.Color.WHITE);
        assertThrows(IllegalArgumentException.class,
                () -> rook.move("")
        );
    }
}