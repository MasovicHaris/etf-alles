package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class BishopTest {
    @Test
    void moveDiagonally1() {
        Bishop bishop = new Bishop("C2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> bishop.move("F5")
        );
    }
    @Test
    void moveDiagonally2() {
        Bishop bishop = new Bishop("F3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> bishop.move("C6")
        );
    }
    @Test
    void moveDiagonally3() {
        Bishop bishop = new Bishop("C4", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> bishop.move("E2")
        );
    }
    @Test
    void moveDiagonally4() {
        Bishop bishop = new Bishop("D3", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> bishop.move("B1")
        );
    }
    // posto je konstruktor zajednicki ne treba se opet testirati
    @Test
    void moveIllegal1() {
        Bishop bishop = new Bishop("B1", ChessPiece.Color.WHITE);
        assertThrows(IllegalArgumentException.class,
                () -> bishop.move("")
        );
    }

    @Test
    void moveIllegal2() {
        Bishop bishop = new Bishop("H7", ChessPiece.Color.WHITE);
        assertThrows(IllegalChessMoveException.class,
                () -> bishop.move("H6")
        );
    }

    @Test
    void moveIllegal3() {
        Bishop bishop = new Bishop("A4", ChessPiece.Color.WHITE);
        assertThrows(IllegalArgumentException.class,
                () -> bishop.move("H9")
        );
    }
}