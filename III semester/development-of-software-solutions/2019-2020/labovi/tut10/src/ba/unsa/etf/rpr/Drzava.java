package ba.unsa.etf.rpr;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;

import java.util.Objects;

public class Drzava {
    private SimpleIntegerProperty id=new SimpleIntegerProperty(0);
    private SimpleStringProperty naziv = new SimpleStringProperty("");
    private SimpleObjectProperty<Grad> glavniGrad = new SimpleObjectProperty<>();

    @Override
    public String toString() {
        return naziv.get();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Drzava drzava = (Drzava) o;
        return Objects.equals(id, drzava.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    public Drzava() {
    }

    public Drzava(int id, String naziv, Grad glavniGrad) {
        this.id.set(id);
        this.naziv.set(naziv);
        this.glavniGrad.set(glavniGrad);
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

    public Grad getGlavniGrad() {
        return glavniGrad.get();
    }

    public void setGlavniGrad(Grad glavniGrad) {
        this.glavniGrad.set(glavniGrad);
    }
}
