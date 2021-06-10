package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class BoardTest {

    @Test
    // Is the board usable after isCheck
    void someLegalMoves() {
        Board b = new Board();
        boolean no = b.isCheck(ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> {
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
                    b.move(Bishop.class, ChessPiece.Color.WHITE, "A6");
                    b.move(Knight.class, ChessPiece.Color.WHITE, "C3");
                    b.move(King.class, ChessPiece.Color.WHITE, "E2");
                    b.move(King.class, ChessPiece.Color.WHITE, "E3");
                }
        );
    }

    @Test
    // Pawn eats diagonally, check by queen
    void pawnDiagonal() {
        Board b = new Board();
        assertDoesNotThrow(
            () -> {
                b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
                b.move(Pawn.class, ChessPiece.Color.WHITE, "E5");
                b.move(Pawn.class, ChessPiece.Color.WHITE, "E6");
                b.move(Pawn.class, ChessPiece.Color.WHITE, "D7");
                b.move(Pawn.class, ChessPiece.Color.WHITE, "C8");
            }
        );
    }

    @Test
    // Check by queen
    void isCheck() {
        Board b = new Board();
        try {
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E5");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E6");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "D7");
        } catch(Exception e) {
            // Do nothing
        }
        assertTrue(b.isCheck(ChessPiece.Color.BLACK));
    }

    @Test
    // Will queen be moved by isCheck
    void isCheckUsable() {
        Board b = new Board();
        try {
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E5");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E6");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "D7");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "C8");
            b.move(Queen.class, ChessPiece.Color.WHITE, "E2");
        } catch(Exception e) {
            // Do nothing
        }
        b.isCheck(ChessPiece.Color.BLACK);
        assertDoesNotThrow(
            () -> {
                b.move(Queen.class, ChessPiece.Color.WHITE, "D3");
            }
        );
    }

    @Test
    // Queen, bishop and rook can't jump pieces
    void jumpPiece() {
        Board b = new Board();
        assertAll(
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move(Rook.class, ChessPiece.Color.BLACK, "H6")
                ),
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move(Bishop.class, ChessPiece.Color.BLACK, "H6")
                ),
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move(Queen.class, ChessPiece.Color.BLACK, "A5")
                )
        );
    }


    // Same test with other move method

    @Test
    // Is the board usable after isCheck
    void someLegalMoves1() {
        Board b = new Board();
        boolean no = b.isCheck(ChessPiece.Color.WHITE);
        assertDoesNotThrow(
                () -> {
                    b.move("E2", "E4");
                    b.move("F1", "A6");
                    b.move("B1", "C3");
                    b.move("E1", "E2");
                    b.move("E2", "E3");
                }
        );
    }

    @Test
    // Pawn eats diagonally, check by queen
    void pawnDiagonal1() {
        Board b = new Board();
        assertDoesNotThrow(
                () -> {
                    b.move("E2", "E4");
                    b.move("E4", "E5");
                    b.move("E5", "E6");
                    b.move("E6", "D7");
                    b.move("D7", "C8");
                }
        );
    }
    @Test
        // No check
    void isCheck2() {
        Board b = new Board();
        try {
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E5");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E6");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "D7");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "C8");
            b.move(Queen.class, ChessPiece.Color.WHITE, "E2");
        } catch(Exception e) {
            // Do nothing
        }
        assertFalse(b.isCheck(ChessPiece.Color.BLACK));
    }
    @Test
        // Check by queen
    void isCheck3() {
        Board b = new Board();
        try {
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E5");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E6");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "D7");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "C8");
            b.move(Queen.class, ChessPiece.Color.WHITE, "E2");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "F4");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "F5");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "F6");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "E7");
            b.move(Pawn.class, ChessPiece.Color.WHITE, "F8");
        } catch(Exception e) {
            // Do nothing
        }
        assertTrue(b.isCheck(ChessPiece.Color.BLACK));
    }

    @Test
    // Check by queen
    void isCheck1() {
        Board b = new Board();
        try {
            b.move("E2", "E4");
            b.move("E4", "E5");
            b.move("E5", "E6");
            b.move("E6", "D7");
        } catch(Exception e) {
            // Do nothing
        }
        assertTrue(b.isCheck(ChessPiece.Color.BLACK));
    }

    @Test
    // Queen, bishop and rook can't jump pieces
    void jumpPiece1() {
        Board b = new Board();
        assertAll(
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move("H8", "H6")
                ),
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move("F8", "H6")
                ),
                () -> assertThrows(
                        IllegalChessMoveException.class,
                        () -> b.move("D8", "A5")
                )
        );
    }

    @Test
    // Check by queen
    void isCheckUsable1() {
        Board b = new Board();
        try {
            b.move("E2", "E4");
            b.move("E4", "E5");
            b.move("E5", "E6");
            b.move("E6", "D7");
            b.move("D7", "C8");
            b.move("D1", "E2");
        } catch(Exception e) {
            // Do nothing
        }
        b.isCheck(ChessPiece.Color.BLACK);
        assertDoesNotThrow(
                () -> {
                    b.move("E2", "D3");
                }
        );
    }

    @Test
    //getting that line coverage
    // koso, horizontalno, vertikalno pomijeranje
    void gettingLineCoverage1(){
        Board board = new Board();
        assertDoesNotThrow(
                () -> {
                    board.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "E2");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "E3");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "H3");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "H7");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "G7");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "G4");
                }
        );
    }
    // zabranjeno pomijeranje na svoju figuru
    @Test
    void gettingLineCoverage2(){
        Board board = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    board.move(Pawn.class, ChessPiece.Color.WHITE, "E4");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "E2");
                    board.move(Queen.class, ChessPiece.Color.WHITE, "E4");
                }
        );
    }
    // zabranjeno pomijeranje preko figure
    @Test
    void gettingLineCoverage3(){
        Board board = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    board.move("E2", "E4");
                    board.move("D1", "G4");
                    board.move("G4", "A4");
                }
        );
    }
    // zabranjeno dvostruko pomijeranje pijuna osim iz pocetne pozicije
    @Test
    void gettingLineCoverage4(){
        Board board = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    board.move("A7", "A6");
                    board.move("C7", "C5");
                    board.move("D8", "A5");
                    board.move("A6", "A4");
                }
        );
    }
    // pijun ne moze jesti pravo , samo u koso
    @Test
    void gettingLineCoverage5(){
        Board board = new Board();
        assertThrows(IllegalChessMoveException.class, () -> {
            board.move("A7", "A5");
            board.move("A5", "A4");
            board.move("A4", "A3");
            board.move("A3", "A2");
        });

    }
    // piijun moze dva polja samo kad krece iz pocetne pozicije
    @Test
    void test1(){
        Board board = new Board();
        assertThrows(IllegalChessMoveException.class, () -> {
            board.move("A7", "A5");
            board.move("A5", "A3");
        });
    }

    // preskakanje s pijunima !
    @Test
    void test5(){
        Board b = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    b.move(Pawn.class, ChessPiece.Color.BLACK, "A5");
                    b.move(Pawn.class, ChessPiece.Color.BLACK, "A4");
                    b.move(Pawn.class, ChessPiece.Color.BLACK, "A3");
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "A4");
                });
    }
    // kralj ne smije stati na poziciju na kojoj ga moze neprijatelj pojesti
    @Test
    void test6(){
        Board b = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    b.move("E2", "E4");
                    b.move("E4", "E5");
                    b.move("E5", "E6");
                    b.move("E6", "D7");
                    b.move("D1", "E2");
                    b.move("E2", "E3");
                    b.move("E3", "D3");
                    b.move("E8", "D7");
                });
    }
    // legalna pomijeranja pijuna
    @Test
    void test7(){
        Board b= new Board();
        assertDoesNotThrow(() -> {
            b.move("A2", "A4");
            b.move("B2", "B4");
            b.move("G2", "G4");
            b.move(Pawn.class, ChessPiece.Color.BLACK, "G5");
            b.move(Pawn.class, ChessPiece.Color.BLACK, "C5");
            b.move(Pawn.class, ChessPiece.Color.BLACK, "H5");

        });
    }
    @Test
    void isCheckCantMoveOther1(){
        Board b = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "e4");
                    b.move(Pawn.class, ChessPiece.Color.BLACK, "D5");
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "D5");
                    b.move(Queen.class, ChessPiece.Color.BLACK, "d5");
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "c4");
                    b.move(Queen.class, ChessPiece.Color.BLACK, "E4");
                    b.move(Pawn.class, ChessPiece.Color.WHITE, "F3");
                });
    }
    @Test
    void isCheckCantMoveOther2(){
        Board b = new Board();
        assertThrows(IllegalChessMoveException.class,
                () -> {
                    b.move("e2", "e4");
                    b.move("d7", "D5");
                    b.move("e4", "D5");
                    b.move("D8", "d5");
                    b.move("C2", "c4");
                    b.move("d5", "E4");
                    b.move("F2", "F3");
                });
    }
    @Test
    void coverage(){
        Board board = new Board();
        board.setActiveFigures(null);
    }
    // fali pokrivenost linija koda za CloneNotSupportedException
}