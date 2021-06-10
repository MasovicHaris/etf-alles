package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class QueenTest {

    @Test
    void move1() {
        Queen q = new Queen("D1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> q.move("E2")
        );
    }
    @Test
    void move2() {
        Queen q = new Queen("A1", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> q.move("H8")
        );
    }

    @Test
    void move3() {
        Queen q = new Queen("E2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> q.move("E8")
        );
    }

    @Test
    void ilegalMove1() {
        Queen q = new Queen("A1", ChessPiece.Color.WHITE);
        assertThrows(
              IllegalChessMoveException.class , () -> q.move("G3")
        );
    }
}