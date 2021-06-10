package ba.unsa.etf.rpr;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ProgramTest {

    @Test
    void provjeriPodatkePredmeta() {
        Program program = new Program();
        assertEquals(true, program.provjeriPodatkePredmeta("MLTI", 1, 1));
        program.kreirajPredmet("MLTI", 1, 1);
        assertEquals(false, program.provjeriPodatkePredmeta("MLTI", 1, 1));
        assertEquals(false, program.provjeriPodatkePredmeta(null, 1,1));
        assertEquals(false, program.provjeriPodatkePredmeta("RPR", 1,1));
        assertEquals(false, program.provjeriPodatkePredmeta("RPR", 2,0));
        assertEquals(true, program.provjeriPodatkePredmeta("RPR", 2, 2));
    }

    @Test
    void provjeriPodatkeStudenta() {
        Program program = new Program();
        assertEquals(false, program.provjeriPodatkeStudenta(null, "nermin", 17825));
        assertEquals(false, program.provjeriPodatkeStudenta("Krdzic", "", 17825));
        assertEquals(true, program.provjeriPodatkeStudenta("Krdzic", "Nermin", 17825));
        program.dodajStudenta("Krdzic", "Nermin", 17825);
        assertEquals(false, program.provjeriPodatkeStudenta("Hasic", "Hasan", 17825));
        assertEquals(true, program.provjeriPodatkeStudenta("Krdzic", "nermin", 17826));


    }

    @Test
    void imaPredmet() {
        Program program = new Program();
        assertEquals(false, program.imaPredmet("awkward"));
        program.kreirajPredmet("awkward", 1, 2);
        assertEquals(true, program.imaPredmet("awkward"));
        assertEquals(true, program.imaPredmet("Awkward"));
    }

    @Test
    void imaStudent() {
        Program program = new Program();
        assertEquals(false, program.imaStudent(17665));
        program.dodajStudenta("Hasic", "Hasan", 17999);
        assertEquals(true, program.imaStudent(17999));
    }

    @Test
    void kreirajPredmet() {
        // ova metoda je provjerena metodom ImaPredmet()
    }

    @Test
    void dodajStudenta() {
        //Ova metoda je provjerena metodom ImaStudent()
    }

    @Test
    void upisiStudentaNaPredmet() {
        Program program = new Program();
        program.dodajStudenta("Krdzic", "Nermin", 17825);
        program.dodajStudenta("Masovic", "Haris", 17696);
        program.dodajStudenta("xxxxx", "Faris", 17777);
        program.kreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Student student3 = program.getStudenti()[2];
        Predmet predmet = program.getPredmeti()[0];
        assertEquals(false, predmet.upisan(student1));
        program.upisiStudentaNaPredmet(17825, "");
        assertEquals(false, predmet.upisan(student1));
        program.upisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.upisan(student1));
        program.upisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.upisan(student2));
        program.upisiStudentaNaPredmet(17777, "mlti");
        assertEquals(false, predmet.upisan(student3));
    }

    @Test
    void ispisiStudentaSaPredmeta() {
        Program program = new Program();
        program.dodajStudenta("Krdzic", "Nermin", 17825);
        program.dodajStudenta("Masovic", "Haris", 17696);
        program.kreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Predmet predmet = program.getPredmeti()[0];
        program.upisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.upisan(student1));
        program.upisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.upisan(student2));
        program.ispisiStudentaSaPredmeta(17825, "mlti");
        assertEquals(false, predmet.upisan(student1));
        assertEquals(true, predmet.upisan(student2));
        program.ispisiStudentaSaPredmeta(17696, "mlti");
        assertEquals(false, predmet.upisan(student2));

    }

    @Test
    void obrisiStudenta() {
        Program program = new Program();
        program.dodajStudenta("Krdzic", "Nermin", 17825);
        program.dodajStudenta("Masovic", "Haris", 17696);
        program.kreirajPredmet("MLTI", 1, 2);
        Student student1 = program.getStudenti()[0];
        Student student2 = program.getStudenti()[1];
        Predmet predmet = program.getPredmeti()[0];
        program.upisiStudentaNaPredmet(17825, "mlti");
        assertEquals(true, predmet.upisan(student1));
        program.upisiStudentaNaPredmet(17696, "mlti");
        assertEquals(true, predmet.upisan(student2));
        program.obrisiStudenta(17825);
        assertEquals(false, program.imaStudent(17825));
    }

    @Test
    void obrisiPredmet() {
        Program program = new Program();
        program.kreirajPredmet("mlti", 1, 1);
        assertEquals(true, program.imaPredmet("mlti"));
        program.obrisiPredmet("Mlti");
        assertEquals(false, program.imaPredmet("mLti"));
    }

    @Test
    void ispisiSpisakStudenata() {
        // provjereno u klasi PredmetTest u funkciji toString()
    }
}