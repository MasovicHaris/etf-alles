package ba.unsa.etf.rpr;

public class Student {
    private String ime = null;
    private String prezime = null;
    private Integer brojIndexa = null;
    public String getIme() {
        return ime;
    }

    public void setIme(String ime) {
        this.ime = ime;
    }

    public String getPrezime() {
        return prezime;
    }

    public void setPrezime(String prezime) {
        this.prezime = prezime;
    }

    public Integer getBrojIndexa() {
        return brojIndexa;
    }

    public void setBrojIndexa(Integer brojIndexa) {
        this.brojIndexa = brojIndexa;
    }

    public Student(String ime, String prezime,Integer brojIndexa){
        this.ime = ime;
        this.prezime = prezime;
        this.brojIndexa = brojIndexa;
    }

    @Override
    public String toString() {
        return prezime + " " + ime + " (" + Integer.toString(brojIndexa) + ")\n";
    }
}
