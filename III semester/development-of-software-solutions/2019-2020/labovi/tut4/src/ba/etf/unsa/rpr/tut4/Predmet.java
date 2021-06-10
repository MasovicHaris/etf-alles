package ba.etf.unsa.rpr.tut4;

import java.util.HashMap;
import java.util.Map;

public class Predmet {
    private String imePredmeta;
    boolean obavezni;
    int ects;

    public Predmet(String naziv, boolean obavezni, int ects)
    {
        this.imePredmeta=naziv;
        this.obavezni=obavezni;
        this.ects=ects;
    }



    //napraviti kao apstraktnu klasu
    //izvesti iz nje Obavezni predmet kao i izborni predmet

    //klase izvedene iz klase predmet moraju imati metodu ADD/DODAJ koja dodaje studenta u isto tako
    //kontenjerski atribut u klasu predmet tako da se mogu lahko ispisivati studenti koji pohađaju neki predmet
    //predmet mora imati atribut ECTS koji nam govori koliko taj predmet nosi ECTS poena
    //predmet bi trebao imati int atribut kao broj semestra na kom je dostupan


}
