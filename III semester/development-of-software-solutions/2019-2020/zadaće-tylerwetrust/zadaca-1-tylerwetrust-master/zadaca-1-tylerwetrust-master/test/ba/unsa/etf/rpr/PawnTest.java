package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class PawnTest {

    @org.junit.jupiter.api.Test
    void move1() {
        Pawn p = new Pawn("E2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> p.move("E4")
        );
    }
    @Test
    void move2() {
        Pawn p = new Pawn("E2", ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> p.move("E4")
        );
        assertDoesNotThrow(
                () -> p.move("E5")
        );
    }

    @Test
    void oneMove() {
        Pawn p = new Pawn("E7", ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> p.move("E6")
        );
        assertDoesNotThrow(
                () -> p.move("E5")
        );
    }



    @org.junit.jupiter.api.Test
    void ilegalMove1() {
        Pawn p = new Pawn("A2", ChessPiece.Color.WHITE);

        assertThrows(
               IllegalChessMoveException.class, () -> p.move("E4")
        );
    }

    @org.junit.jupiter.api.Test
    void ilegalMove2() {
        Pawn p = new Pawn("E4", ChessPiece.Color.WHITE);

        assertThrows(
                IllegalChessMoveException.class, () -> p.move("E4")
        );
    }

}

