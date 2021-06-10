package ba.unsa.etf.rpr.tutorijal_3;

import java.util.*;

public class Imenik {
    private Map<String, TelefonskiBroj> mapa;


    public Imenik(){
        mapa = new HashMap<String, TelefonskiBroj>(); //hashmap je izvedena iz Map koja ima vise mogucnosti
    }
    void dodaj(String ime, TelefonskiBroj broj){
        mapa.put(ime, broj);
    }

    String dajBroj(String ime){
        TelefonskiBroj pom = mapa.get(ime);
        return pom.ispisi();
    }
    public String dajIme(TelefonskiBroj broj){
        for(Map.Entry<String, TelefonskiBroj> it : mapa.entrySet()) //iterator kroz mapu
        {
            if(it.getValue().ispisi().equals(broj.ispisi())){   //ispisi() vraca string pa poredimo dva stringa da li su brojevi isti
                return it.getKey(); //vraca ime osobe ciji je broj jednak poslanom parametru odnosno kljucu hashMape
            }
        }
        return "Nema te osobe u mapi";
    }


    String naSlovo(char i) {
        String pom="";
        int brojac=0;
        for(Map.Entry<String, TelefonskiBroj> it : mapa.entrySet()) //iterator kroz mapu
        {
            if(it.getKey().charAt(0)==i){
                brojac++;
                pom=pom+brojac+". "+it.getKey()+" - "+it.getValue().ispisi()+"\n";
            }
        }
        return pom;
    }

    Set<String> izGrada(FiksniBroj.Grad g){
        Set<String> s= new TreeSet<String>();
        for(Map.Entry<String, TelefonskiBroj> it : mapa.entrySet()) //iterator kroz mapu
        {
            if((it.getValue() instanceof FiksniBroj) && ((FiksniBroj) it.getValue()).getGrad()==g){ // da li ta osoba ima FiksniBroj
                s.add(it.getKey());   //TreeSet automatski leksikografski reda stringove            // i da li grad te osobe odgovara
            }                                                                                       //gradu kao parametru
        }
            return s;
    }

    Set<TelefonskiBroj> izGradaBrojevi(FiksniBroj.Grad g) {
        Set<TelefonskiBroj> s= new TreeSet<TelefonskiBroj>((o1, o2) -> {
            String pom1=o1.ispisi();                      // novi nacin komparacije preko lambde
            String pom2=o2.ispisi();                      //za TreeSet - reda leksikografski al po imenima
            return pom1.compareTo(pom2);

        });

        for(Map.Entry<String, TelefonskiBroj> it : mapa.entrySet()) //iterator kroz mapu
        {
            if((it.getValue() instanceof FiksniBroj) && ((FiksniBroj) it.getValue()).getGrad()==g){ // da li ta osoba ima FiksniBroj
                s.add(it.getValue());   //TreeSet automatski leksikografski reda stringove            // i da li grad te osobe odgovara
            }                                                                                       //gradu kao parametru
        }
        return s;
    }
}
