package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SubjectTest {

    @Test
    void enrollStudent() {
        Subject subject = new Electoral("MLTI", "Dikno Osmanovic", 7);
        Student student1 = new Student("Nermin", "Krdzic");
        student1.setIndex(17825);
        Student student2 = new Student("Haris", "Masovic");
        student2.setIndex(17696);
        subject.enrollStudent(student1);
        subject.enrollStudent(student2);
        assertEquals(2, subject.getEnrolledStudents().size());
        assertEquals(17825, (int) subject.getEnrolledStudents().get(0).getIndex());
        assertEquals(17696, (int) subject.getEnrolledStudents().get(1).getIndex());
        assertEquals(7, student1.getNumberOfECTSPoints());
        assertEquals(7, student2.getNumberOfECTSPoints());
    }

    @Test
    void deleteStudent() {
        Subject subject = new Electoral("MLTI", "Dikno Osmanovic", 7);
        Student student1 = new Student("Nermin", "Krdzic");
        student1.setIndex(17825);
        Student student2 = new Student("Haris", "Masovic");
        student2.setIndex(17696);
        subject.enrollStudent(student1);
        subject.enrollStudent(student2);
        subject.deleteStudent(17825);
        assertEquals(0, student1.getNumberOfECTSPoints());
        assertEquals(1, subject.getEnrolledStudents().size());
        assertEquals(17696, (int) subject.getEnrolledStudents().get(0).getIndex());
    }

    @Test
    void printStudents() {
        Subject subject = new Electoral("MLTI", "Dikno Osmanovic", 7);
        Student student1 = new Student("Nermin", "Krdzic");
        student1.setIndex(17825);
        Student student2 = new Student("Haris", "Masovic");
        student2.setIndex(17696);
        subject.enrollStudent(student1);
        subject.enrollStudent(student2);
        assertEquals("1. Nermin Krdzic 17825 7\n2. Haris Masovic 17696 7\n", subject.printStudents());
    }
}