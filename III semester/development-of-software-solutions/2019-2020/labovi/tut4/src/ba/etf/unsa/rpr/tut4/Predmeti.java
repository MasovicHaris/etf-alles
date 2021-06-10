package ba.etf.unsa.rpr.tut4;

import java.util.HashMap;
import java.util.Map;

public class Predmeti {
    private Map<Predmet, Boolean> predmeti;
    public Predmeti(){
        this.predmeti=new HashMap<Predmet, Boolean>();
    }

    public Map<Predmet, Boolean> getPredmeti() {
        return predmeti;
    }

    public void dodajPredmet(Predmet p)
    {
        this.predmeti.put(p, true);
    }

    public void printStudenteNaPredmetu(Predmet p)
    {
        return;
    }
}
