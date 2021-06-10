package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class BishopTest {

    @Test
    void move() {
        Bishop b = new Bishop("F8", ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> b.move("C5")
        );
    }

    @Test
    void move1() {
        Board b = new Board();
        assertDoesNotThrow(
                () -> b.move(Pawn.class,ChessPiece.Color.BLACK,"E5")
        );
        assertDoesNotThrow(
                () -> b.move(Bishop.class,ChessPiece.Color.BLACK,"C5")
        );
    }
    @Test
    void ilegalMove() {
        Bishop b = new Bishop("C1", ChessPiece.Color.WHITE);
        assertThrows(
                IllegalChessMoveException.class, () -> b.move("C2")
        );

    }
}