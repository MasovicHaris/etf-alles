package ba.unsa.etf.rpr;

import javafx.beans.property.Property;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;

public class Grad {
    private SimpleIntegerProperty id = new SimpleIntegerProperty(0);
    private SimpleStringProperty naziv = new SimpleStringProperty("");
    private SimpleStringProperty slikaPutanja = new SimpleStringProperty("");
    private SimpleIntegerProperty postanskiBroj = new SimpleIntegerProperty();

    public int getPostanskiBroj() {
        return postanskiBroj.get();
    }

    public SimpleIntegerProperty postanskiBrojProperty() {
        return postanskiBroj;
    }

    public void setPostanskiBroj(int postanskiBroj) {
        this.postanskiBroj.set(postanskiBroj);
    }

    public SimpleIntegerProperty idProperty() {
        return id;
    }

    public SimpleStringProperty nazivProperty() {
        return naziv;
    }

    public SimpleIntegerProperty brojStanovnikaProperty() {
        return this.brojStanovnika;
    }

    public String getSlikaPutanja() {
        return slikaPutanja.get();
    }

    public SimpleStringProperty slikaPutanjaProperty() {
        return slikaPutanja;
    }

    public void setSlikaPutanja(String slikaPutanja) {
        this.slikaPutanja.set(slikaPutanja);
    }

    public SimpleObjectProperty<Drzava> drzavaProperty() {
        return drzava;
    }

    private SimpleIntegerProperty brojStanovnika= new SimpleIntegerProperty(0);
    private SimpleObjectProperty<Drzava> drzava = new SimpleObjectProperty<>();

    public Drzava getDrzava() {
        return drzava.get();
    }

    public void setDrzava(Drzava drzava) {
        this.drzava.set(drzava);
    }

    public Grad() {
    }

    @Override
    public String toString() {
        return naziv.get();
    }

    public Grad(int id, String naziv, int brojStanovnika, Drzava drzava, int postanskiBr) {
        this.id.set(id);
        this.naziv.set(naziv);
        this.brojStanovnika.set(brojStanovnika);
        this.drzava.set(drzava);
        this.slikaPutanja.set("");
        this.postanskiBroj.set(postanskiBr);
    }

    public int getId() {
        return id.get();
    }

    public void setId(int id) {
        this.id.set(id);
    }

    public String getNaziv() {
        return naziv.get();
    }

    public void setNaziv(String naziv) {
        this.naziv.set(naziv);
    }

    public int getBrojStanovnika() {
        return brojStanovnika.get();
    }

    public void setBrojStanovnika(int brojStanovnika) {
        this.brojStanovnika.set(brojStanovnika);
    }

}
