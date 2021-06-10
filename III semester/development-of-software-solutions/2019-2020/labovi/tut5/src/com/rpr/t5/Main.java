package com.rpr.t5;

import com.rpr.t5.util.Kredit;
import com.rpr.t5.util.KreditnaSposobnost;

public class Main {

    public static void main(String[] args) {

        Banka banka = new Banka();
        Korisnik k1 = banka.kreirajNovogKorisnika("Maja", "Majić");
        banka.kreirajRacun(k1);
        k1.getRacun().izvrsiUplatu(2345.45d);
        banka.dodajNovogUposlenog("Marko", "Marić");
        KreditnaSposobnost funkcija = (Racun racun) -> {
            double stanje = racun.getStanjeRacuna().doubleValue();
            if (stanje > 1000) {
                return stanje / 2;
            } else {
                return 0d;
            }
        };
        Double value = Kredit.proracunKreditneSposobnosti(funkcija, k1);
        if(value > 0){
            System.out.println("Korisnik: "+k1.toString()+", broj racuna: " + k1.getRacun().getBrojRacuna() + " ,ima pravo na kredit iznosa "+value.toString());
        }
        else
        {
            System.out.println("Korisnik: "+k1.toString()+" nema pravo na kredit!");
        }

        Korisnik k2 = banka.kreirajNovogKorisnika("Veseli", "Veseljkovic");
        banka.kreirajRacun(k2);
        System.out.println("Korisnik: "+k2.toString()+", broj racuna: " + k2.getRacun().getBrojRacuna());

        Kredit.ispisiSveKorisnikeBezPrekoracenja(banka.getKorisnici());


    }
}
