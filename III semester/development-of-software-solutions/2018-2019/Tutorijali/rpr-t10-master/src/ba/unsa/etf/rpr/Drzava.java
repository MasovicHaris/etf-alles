package ba.unsa.etf.rpr;

public class Drzava {
    private int id = -1;
    private String naziv;
    private Grad glavniGrad;

    public Drzava(){}
    public Drzava(int id, String naziv, Grad glavniGrad){
        setId(id);
        setNaziv(naziv);
        setGlavniGrad(glavniGrad);
    }
    public Drzava(String naziv, Grad glavniGrad) {
        setNaziv(naziv);
        setGlavniGrad(glavniGrad);
    }

    public String getNaziv() {
        return naziv;
    }

    public void setNaziv(String naziv) {
        this.naziv = naziv;
    }

    public Grad getGlavniGrad() {
        return glavniGrad;
    }

    public void setGlavniGrad(Grad glavniGrad) {
        this.glavniGrad = glavniGrad;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

}
