package sample;

import javafx.beans.Observable;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.util.ArrayList;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.toList;

public class KorisniciModel {

    private ObservableList<Korisnik> korisnici=FXCollections.observableArrayList();
    private SimpleObjectProperty<Korisnik> trenutniKorisnik=new SimpleObjectProperty<>();

    public void setKorisnici()
    {
        korisnici= FXCollections.<Korisnik>observableArrayList();
    }

    public void setTrenutniKorisnik(Korisnik k)
    {
        trenutniKorisnik.set(k);
    }

    public void napuni(ArrayList<Korisnik> l)
    {
        this.setKorisnici();
        korisnici.addAll(l);
        this.setTrenutniKorisnik(l.get(0));
    }

    public SimpleObjectProperty<Korisnik> getTrenutniKorisnik()
    {
        return this.trenutniKorisnik;
    }

    public ObservableList<Korisnik> getKorisnici()
    {
        return this.korisnici;
    }

    public void dodajNovogKorisnika(Korisnik k)
    {
        this.korisnici.add(k);
        this.setTrenutniKorisnik(k);
    }


}
