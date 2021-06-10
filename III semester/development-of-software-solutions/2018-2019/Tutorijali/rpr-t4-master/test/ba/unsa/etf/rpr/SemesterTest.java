package ba.unsa.etf.rpr;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class SemesterTest {
    Semester semester = null;
    @BeforeEach
    void init(){
        ArrayList<Tuple<String, String, Integer, Class>> subjects = new ArrayList<>();
        subjects.add(new Tuple<>("Razvoj programskih rjesenja", "Vedran Ljubovic", 5, Obligatory.class));
        subjects.add(new Tuple<>("Diskretna matematika", "Zeljko Juric", 5, Obligatory.class));
        subjects.add(new Tuple<>("Logicki dizajn", "Novica Nosovic", 5, Obligatory.class));
        subjects.add(new Tuple<>("Algoritmi i strukture podataka", "Haris Supic", 5, Obligatory.class));
        subjects.add(new Tuple<>("Osnove baza podataka", "Emir Buza", 5, Obligatory.class));
        subjects.add(new Tuple<>("Sistemsko programiranje", "Samir Ribic", 5, Electoral.class));
        subjects.add(new Tuple<>("Numericki algoritmi", "Zeljko Juric", 5, Electoral.class));
        subjects.add(new Tuple<>("League of Legends", "RIOT", 5, Electoral.class));
        assertDoesNotThrow(() -> semester = new Semester(subjects));
    }
    public Semester getSemester(){ return this.semester; }
    @Test
    void getElectoralSubjects() {
        assertEquals("1. Subject name: Sistemsko programiranje, Responsible teacher: Samir Ribic, ECTS: 5\n" +
                "2. Subject name: Numericki algoritmi, Responsible teacher: Zeljko Juric, ECTS: 5\n" +
                "3. Subject name: League of Legends, Responsible teacher: RIOT, ECTS: 5\n", semester.getElectoralSubjects());
    }

    @Test
    void getObligatorySubjects() {
        assertEquals("1. Subject name: Razvoj programskih rjesenja, Responsible teacher: Vedran Ljubovic, ECTS: 5\n" +
                "2. Subject name: Diskretna matematika, Responsible teacher: Zeljko Juric, ECTS: 5\n" +
                "3. Subject name: Logicki dizajn, Responsible teacher: Novica Nosovic, ECTS: 5\n" +
                "4. Subject name: Algoritmi i strukture podataka, Responsible teacher: Haris Supic, ECTS: 5\n" +
                "5. Subject name: Osnove baza podataka, Responsible teacher: Emir Buza, ECTS: 5\n", semester.getObligatorySubjects());
    }


    @Test
    void enrollStudent() {
        ArrayList<String> electoral1 = new ArrayList<>();
        electoral1.add("Sistemsko programiranje");
        ArrayList<String> electoral2 = new ArrayList<>();
        electoral2.add("Numericki algoritmi");
        ArrayList<String> electoral3 = new ArrayList<>();
        electoral3.add("League of Legends");
        Student student1 = new Student("Nermin", "Krdzic");
        Student student2 = new Student("Haris", "Masovic");
        Student student3 = new Student("Faris", "Likic");
        assertDoesNotThrow(() -> semester.enrollStudent(student1, electoral1));
        assertDoesNotThrow(() -> semester.enrollStudent(student2, electoral2));
        assertDoesNotThrow(() -> semester.enrollStudent(student3, electoral3));
        assertEquals(30, student1.getNumberOfECTSPoints());
        Student student = new Student("Ime", "Prezime");
        assertThrows(IllegalArgumentException.class , () ->semester.enrollStudent(student, null));
        assertThrows(NotEnoughPoints.class, () -> semester.enrollStudent(student, new ArrayList<>()));
    }

    @BeforeEach
    void init2(){
        ArrayList<String> electoral1 = new ArrayList<>();
        electoral1.add("Sistemsko programiranje");
        ArrayList<String> electoral2 = new ArrayList<>();
        electoral2.add("League of Legends");
        try{
            semester.enrollStudent(new Student("Nermin", "Krdzic"), electoral1);
            semester.enrollStudent(new Student("Haris", "Masovic"), electoral2);
        }
        catch (IllegalArgumentException e) { }
        catch (NotEnoughPoints e) { }
    }
    @Test
    void deleteStudent() {
        semester.deleteStudent(semester.getStudents().get(1).getIndex());
        assertEquals(1, semester.getStudents().size());
        assertEquals("1. Nermin Krdzic " + semester.getStudents().get(0).getIndex().toString() + " 30\n", semester.getSubjects().get(5).printStudents());
    }

    @Test
    void addSubject() {
        semester.addSubject(new Electoral("predmet", "profesor", 20));
        assertEquals("predmet", semester.getSubjects().get(semester.getSubjects().size() - 1).getSubjectName());
    }

    @Test
    void deleteSubject() {
        semester.deleteSubject("League of Legends"); // drugi student je ispisan jer je izguio potrebni broj bodova
        assertEquals(1, semester.getStudents().size());
        assertEquals("1. Subject name: Sistemsko programiranje, Responsible teacher: Samir Ribic, ECTS: 5\n" +
                "2. Subject name: Numericki algoritmi, Responsible teacher: Zeljko Juric, ECTS: 5\n", semester.getElectoralSubjects());
    }
}