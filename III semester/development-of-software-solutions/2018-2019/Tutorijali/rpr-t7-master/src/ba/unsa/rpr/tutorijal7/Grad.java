package ba.unsa.rpr.tutorijal7;

import java.io.Serializable;

public class Grad implements Serializable {
    private String naziv = null;
    private int brojStanovnika = 0;
    private Double[] temperature = new Double[1000];

    public Grad(){}
    public Grad(String naziv, Double[] temperature){
        for (int i = 0; i < this.temperature.length; i++) {
            if (temperature != null && i < temperature.length) this.temperature[i] = temperature[i];
            else this.temperature[i] = 0.;
        }
        this.naziv = naziv;
    }
    public Grad(String naziv, int brojStanovnika, Double[] temperature){
        for (int i = 0; i < this.temperature.length; i++) {
            if (temperature != null && i < temperature.length) this.temperature[i] = temperature[i];
            else this.temperature[i] = 0.;
        }
        this.naziv = naziv;
        this.brojStanovnika = brojStanovnika;
    }


    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public int getBrojStanovnika() {
        return brojStanovnika;
    }

    public void setBrojStanovnika(int brojStanovnika) {
        this.brojStanovnika = brojStanovnika;
    }

    public Double[] getTemperature() {
        return temperature;
    }

    public void setTemperature(Double[] temperature) {
        this.temperature = temperature;
    }
}
