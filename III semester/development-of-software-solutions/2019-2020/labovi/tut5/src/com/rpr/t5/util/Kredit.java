package com.rpr.t5.util;


import com.rpr.t5.Korisnik;
import com.rpr.t5.Osoba;
import com.rpr.t5.Racun;
import java.util.ArrayList;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Kredit implements KreditnaSposobnost {


    @Override
    public Double izracunaj(Racun r) {
        return 0d; //ne znam kako se racuna kreditna sposobnost!
    }

    public Double dajKreditnuSposobnost(Function<Racun, Double> func, Korisnik k){ //primit ce funkciju "izracunaj"
        return func.apply(k.getRacun());
    }

    public void bezPrekoracenja(ArrayList<Korisnik> lista){
        lista.stream().forEach((Korisnik user) -> {
            if(user.getRacun().getStanjeRacuna()>0d) {              //ako je stanje racuna korisnika > 0, isprintaj ga
                System.out.printf(("%s\n"), user.toString());
            }
        });
    }

    public void odobriPrekoracenje(ArrayList<Korisnik> lista){
     lista.stream().forEach((Korisnik user) -> {
            if(user.getRacun().getStanjeRacuna()>10000d) user.getRacun().odobriPrekoracenje();  //pozove odobri prekoracenje
        });                                                                                     //za svakog korisnijka
    }                                                                                           //cija je plata veca od 10000
}
