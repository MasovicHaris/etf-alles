package com.rpr.t5;

public class Racun {
    private final Long brojRacuna;
    private final Osoba korisnikRacuna;
    private Double stanjeRacuna;
    private boolean odobrenjePrekoracenja;

    public Racun(Long brojRacuna, Osoba korisnikRacuna) {
        this.brojRacuna = brojRacuna;
        this.korisnikRacuna = korisnikRacuna;
        this.stanjeRacuna = 0d;
        this.odobrenjePrekoracenja = false;
    }
    public Long getBrojRacuna() {
        return brojRacuna;
    }
    public void odobriPrekoracenje(){
        this.odobrenjePrekoracenja=true;
    }

    public boolean izvrsiUplatu(double v) {
        stanjeRacuna = stanjeRacuna + v;
        return true;
    }

    public boolean izvrsiIsplatu(double v){
        if(this.provjeriOdobrenjePrekoracenja(v)) {
            stanjeRacuna = stanjeRacuna - v;
            return true;
        }
        return false;
    }

    public Double getStanjeRacuna() {
        return stanjeRacuna;
    }

    private boolean provjeriOdobrenjePrekoracenja(Double broj){
        return this.odobrenjePrekoracenja;
    }

}
