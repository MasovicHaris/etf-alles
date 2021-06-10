package ba.unsa.etf.rpr;

public class Grad {
    private int id = -1;
    private String naziv;
    private int brojStanovnika;
    private Drzava drzava;

    public Grad(){}
    public Grad(int id, String naziv, int brojStanovnika, Drzava drzava){
        setId(id);
        setNaziv(naziv);
        setBrojStanovnika(brojStanovnika);
        setDrzava(drzava);
    }
    public Grad(String naziv, int brojStanovnika, Drzava drzava) {
        setNaziv(naziv);
        setBrojStanovnika(brojStanovnika);
        setDrzava(drzava);

    }

    @Override
    public String toString(){
        return getNaziv() + " (" + getDrzava().getNaziv() + ") - " + getBrojStanovnika() + "\n";
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public Drzava getDrzava() {
        return drzava;
    }

    public void setDrzava(Drzava drzava) {
        this.drzava = drzava;
    }

    public int getBrojStanovnika() {
        return this.brojStanovnika;
    }

    public void setBrojStanovnika(int broj_stanovnika) {
        this.brojStanovnika = broj_stanovnika;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
