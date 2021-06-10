package com.rpr.t5;

import java.util.ArrayList;
import java.util.List;

public class Banka {
    private static Long brojRacuna = 1000000000000000L;
    private List<Uposlenik> uposleni;
    private List<Korisnik> korisnici;

    public Banka() {
        uposleni = new ArrayList<>();
        korisnici = new ArrayList<>();
    }

    public List<Uposlenik> getUposleni() {
        return uposleni;
    }

    public List<Korisnik> getKorisnici() {
        return korisnici;
    }

    public Korisnik kreirajNovogKorisnika(String ime, String prezime) {
        Korisnik k = new Korisnik(ime, prezime);
        korisnici.add(k);
        return k;
    }

    public Racun kreirajRacun(Korisnik k) {
        brojRacuna++;
        Racun r = new Racun(brojRacuna, k);
        k.dodajRacun(r);   //u javi je sve referenca!
        return r;
    }

    public Uposlenik dodajNovogUposlenog(String ime, String prezime) {
        Uposlenik u = new Uposlenik(ime, prezime);
        uposleni.add(u);
        return u;
    }


}
