package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class StudentTest {

    @Test
    void increasePoints(){
        Student student = new Student("nermin", "Krdzic");
        ;student.increasePoints(5);
        assertEquals(5, student.getNumberOfECTSPoints());
    }
    @Test
    void decreasePoints(){
        Student student = new Student("nermin", "Krdzic");
        student.decreasePoints(5);
        assertEquals(-5, student.getNumberOfECTSPoints());
    }
    @Test
    void _toString(){
        Student student = new Student("Nermin", "Krdzic");
        student.increasePoints(5);
        student.setIndex(17825);
        assertEquals("Nermin Krdzic 17825 5", student.toString());
    }
}