package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class QueenTest {

    @Test
    void moveUp() {
        Queen queen = new Queen("D1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("D2")
        );
    }
    @Test
    void moveDown() {
        Queen queen = new Queen("A5", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("A2")
        );
    }
    @Test
    void moveRight() {
        Queen queen = new Queen("A5", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("E5")
        );
    }@Test
    void moveLeft() {
        Queen queen = new Queen("C2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("B2")
        );
    }
    @Test
    void move(){
        Queen queen = new Queen("C2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("C2")
        );
    }
    @Test
    void moveDiagonally1() {
        Queen queen = new Queen("C2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("F5")
        );
    }
    @Test
    void moveDiagonally2() {
        Queen queen = new Queen("F3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("C6")
        );
    }
    @Test
    void moveDiagonally3() {
        Queen queen = new Queen("C4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("E2")
        );
    }
    @Test
    void moveDiagonally4() {
        Queen queen = new Queen("D3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> queen.move("B1")
        );
    }
    // posto je konstruktor zajednicki ne treba se opet testirati
    @Test
    void moveIllegal1() {
        Queen queen = new Queen("C1", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalChessMoveException.class,
                () -> queen.move("E2")
        );
    }

    @Test
    void moveIllegal2() {
        Queen queen = new Queen("H1", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalChessMoveException.class,
                () -> queen.move("C5")
        );
    }

    @Test
    void moveIllegal3() {
        Queen queen = new Queen("C1", ChessPiece.Color.BLACK);
        assertThrows(
                IllegalArgumentException.class,
                () -> queen.move("")
        );
    }
}