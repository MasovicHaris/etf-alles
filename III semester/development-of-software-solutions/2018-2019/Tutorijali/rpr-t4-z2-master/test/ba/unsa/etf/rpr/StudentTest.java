package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StudentTest {

    @Test
    public void _toString() {
        assertEquals("Krdzic Nermin (17825)\n", (new Student("Nermin", "Krdzic", 17825)).toString());
    }
}