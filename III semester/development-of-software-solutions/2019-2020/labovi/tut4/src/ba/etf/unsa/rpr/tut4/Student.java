package ba.etf.unsa.rpr.tut4;

import java.util.HashMap;
import java.util.Map;

public class Student {
    private String imeIPrezime;
    private int brojIndeksa;
    private int semestar;
    private Map<Predmet, Boolean> predmeti;
    private Student(String ime, int brojIndeksa, int semestar){
        this.imeIPrezime=ime;
        this.brojIndeksa=brojIndeksa;
        this.semestar=semestar;
        this.predmeti = new HashMap<Predmet, Boolean>();
    }

    public void setImeIPrezime(String imeIPrezime) {
        this.imeIPrezime = imeIPrezime;
    }

    public void setBrojIndeksa(int brojIndeksa) {
        this.brojIndeksa = brojIndeksa;
    }

    public void setSemestar(int semestar) {
        this.semestar = semestar;
    }

    public String getImeIPrezime() {
        return imeIPrezime;
    }

    public int getBrojIndeksa() {
        return brojIndeksa;
    }

    public int getSemestar() {
        return semestar;
    }

    public Map<Predmet, Boolean> getPredmeti(){
        return this.predmeti;
    }
    //mora imat neki kontenjerski atribut koji ce cuvati sve predmete koje je taj student izabrao
    //kao i konstruktor
    //Klasa Student mora imati metodu ADD/DODAJ koja dodaje predmet koji student bira, u njoj se također poziva i dodaj metoda za taj predmet
    //tako da instanca klase Predmet npr RPR zna da je ovaj student izabrao RPR kao predmet i kako bi ga mogla ubacit u svoj atribut
    //Prije nego sto se pozove metoda klase Student, mora se proc kroz njen kolekcijski atribut i vidjeti da li je prebačen limit ECTS bodova
    //atribut klase student bi bila npr hashMapa<Predmet, nešto??>
    //mogli bi preko instanceof znati da li je Predmet u hashMapi izborni ili obavezni

    //trebao bi i Student imat atribut broj semestra kojeg upisuje tako da se iz liste svih predmeta mogu ponuditi samo oni koji su dostupni
    //na tom semestru

    //Ako je predmet obavezan i student upisuje taj semestar u kom je taj predmet obavezan, ti mu se predmeti sa tog semestra automatski
    //dodaju u kolekciju i ne ispisuju se prilikom izbora
    //odnosno prilikom ispisivanja citave kolekcije klase Predmet ispisat ce se oni sa tog semestra && oni za koje instanceof je Izborni
    //A ako se naleti na neki predmet prilikom searcha koji pripada tom semestru i koji instanceof bude Obavezan
    //poziva se ADD kod klase student



    //Main bi trebao izgledati da se unese Ime Prezime studenta, broj indeksa odjsek i semestar na koji se upisuje

    //potom se izlistavaju svi izborni predmeti za taj odsjek sa tog semestra .



}
