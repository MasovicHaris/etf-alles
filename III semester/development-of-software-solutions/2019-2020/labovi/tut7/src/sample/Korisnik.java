package sample;

import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;

public class Korisnik {
    private SimpleStringProperty ime=new SimpleStringProperty();
    private SimpleStringProperty prezime=new SimpleStringProperty();
    private SimpleStringProperty email= new SimpleStringProperty();
    private SimpleStringProperty korisnickoIme = new SimpleStringProperty();
    private SimpleStringProperty sifra=new SimpleStringProperty();



    public Korisnik(String ime, String prezime, String email, String korisnickoIme, String sifra)
    {
        this.ime=new SimpleStringProperty();
        this.ime.set(ime);
        this.prezime=new SimpleStringProperty();
        this.prezime.set(prezime);
        this.email=new SimpleStringProperty();
        this.email.set(email);
        this.korisnickoIme=new SimpleStringProperty();
        this.korisnickoIme.set(korisnickoIme);
        this.sifra=new SimpleStringProperty();
        this.sifra.set(sifra);
    }


    public void setIme(String ime)
    {
        this.ime.set(ime);
    }

    public void setPrezime(String prezime)
    {
        this.prezime.set(prezime);
    }

    public void setEmail(String email)
    {
        this.email.set(email);
    }
    public void setKorisnickoIme(String korisnickoIme)
    {
        this.korisnickoIme.set(korisnickoIme);
    }
    public void setSifra(String sifra)
    {
        this.sifra.set(sifra);
    }

    public SimpleStringProperty dajImeProperty()
    {
        return this.ime;
    }
    public SimpleStringProperty dajPrezimeProperty()
    {
        return this.prezime;
    }
    public SimpleStringProperty dajEmailProperty()
    {
        return this.email;
    }
    public SimpleStringProperty dajKorisnickoImeProperty()
    {
        return this.korisnickoIme;
    }
    public SimpleStringProperty dajSifruProperty()
    {
        return this.sifra;
    }

    @Override
    public String toString() {
        String s="";
        s=s+this.dajPrezimeProperty().getValue()+" "+this.dajImeProperty().getValue();
        return s;
    }


}
