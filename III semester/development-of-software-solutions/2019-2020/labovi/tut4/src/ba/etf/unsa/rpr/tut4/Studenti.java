package ba.etf.unsa.rpr.tut4;

import java.util.HashMap;
import java.util.Map;

public class Studenti {
    private Map<Student, Boolean> studenti;
    public Studenti(){
        this.studenti = new HashMap<Student, Boolean>();
    }
    public void dodajStudente(Student s)
    {
        this.studenti.put(s,true);
    }

    public Map<Student, Boolean> getStudenti() {
        return studenti;
    }
    public void dodajStudenta(Student s)
    {
        this.studenti.put(s, true);
    }
    public void printStudenteNaPredmetu(Predmet p)
    {
        /*getKey().getPredmeti() vraća Mapu predmeta koje određeni student pohađa i sad se kroz nju treba kretat
        i vidjeti da li je među njima predmet p! ako jest isprintaj ime prezime broj indeksa studenta
        ako nije samo skipaj!
        */
        return;
    }
}
