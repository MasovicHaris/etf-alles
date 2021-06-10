package ba.unsa.etf.rpr.tutorijal03;

import java.util.*;

public class Imenik {
    private Map<String, TelefonskiBroj> hashPoImenu = new HashMap<>();

    public void dodaj(String ime, TelefonskiBroj broj){
        hashPoImenu.put(ime, broj);
    }

    public String dajBroj(String ime) {
        if(hashPoImenu.containsKey(ime))
            return hashPoImenu.get(ime).ispisi();
        return null;
    }

    public String dajIme(TelefonskiBroj broj) {
        for (Map.Entry<String, TelefonskiBroj> pair : hashPoImenu.entrySet())
            if (pair.getValue().getClass() == broj.getClass() && pair.getValue().equals(broj))
                return pair.getKey();
        return null;
    }

    public String naSlovo(char s){
        String slovo = Character.toString(s);
        String result = "";
        int i = 1;
        Iterator<Map.Entry<String, TelefonskiBroj>> it = hashPoImenu.entrySet().iterator();
        while(it.hasNext()){
            Map.Entry<String, TelefonskiBroj> pair = (Map.Entry<String, TelefonskiBroj>) it.next();
            if(pair.getKey().substring(0,1).equalsIgnoreCase(slovo)){
                result += Integer.toBinaryString(i) + ". " + pair.getKey() + " - " + pair.getValue().ispisi() + "\n";
                i++;
            }
        }
        return result;
    }

    public Set<String> izGrada(FiksniBroj.Grad g){
        Set<String> result = new TreeSet<>();
        Iterator<Map.Entry<String, TelefonskiBroj>> it = hashPoImenu.entrySet().iterator();
        while(it.hasNext()){
            Map.Entry<String, TelefonskiBroj> pair = (Map.Entry<String, TelefonskiBroj>) it.next();
            if(pair.getValue() instanceof FiksniBroj && ((FiksniBroj) pair.getValue()).getGrad().equals(g))
                result.add(pair.getKey());
        }
        return result;
    }

    public Set<TelefonskiBroj> izGradaBrojevi(FiksniBroj.Grad g){
        Set<TelefonskiBroj> result = new TreeSet<>();
        Iterator<Map.Entry<String, TelefonskiBroj>> it = hashPoImenu.entrySet().iterator();
        while(it.hasNext()){
            Map.Entry<String, TelefonskiBroj> pair = (Map.Entry<String, TelefonskiBroj>) it.next();
            if(pair.getValue() instanceof FiksniBroj && ((FiksniBroj) pair.getValue()).getGrad().equals(g))
                result.add(pair.getValue());
        }
        return result;
    }
}
