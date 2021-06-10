package ba.unsa.etf.rpr.tutorijal8;

public class Grad {

    private String naziv;
    private int brojStanovnika;
    private double[] temperature=new double[1000];
    private int velicina=1000;

    public Grad(){
        brojStanovnika=0;
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

    public double[] getTemperature() {
        return temperature;
    }

    public void setTemperature(double[] t) {
        if(t.length>999) {
            temperature=new double[velicina+t.length];
            velicina=velicina+t.length;
        }
        this.temperature = t;
    }
}
