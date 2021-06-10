package ba.unsa.etf.rpr;

public class Predmet {

    private String nazivPredmeta = null;
    private Integer sifraPredmeta = null;
    private int maxBrojStudenata = 0;
    private Student[] studenti = null;

    public String getNazivPredmeta() {
        return nazivPredmeta;
    }
    public Integer getSifraPredmeta() {
        return sifraPredmeta;
    }
    public Student[] getStudenti() {
        return studenti;
    }

    public Predmet(String nazivPredmeta, Integer sifraPredmeta, int maxBrojStudenata){
        this.nazivPredmeta = nazivPredmeta;
        this.sifraPredmeta = sifraPredmeta;
        this.maxBrojStudenata = maxBrojStudenata;
    }

    public Boolean upisan(Student student){
        if(studenti == null) {
            return false;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(student.getBrojIndexa())) {
                return true;
            }
        }
        return false;
    }

    public void upisi(Student student){
        if(studenti == null || studenti.length == 0){
            studenti = new Student[1];
            studenti[0] = student;
            return;
        }
        if(studenti.length == maxBrojStudenata){
            System.out.println("Izabrani predmet je popunjen");
            return;
        }
        if(upisan(student)){
            System.out.println("Student je vec upisan na navedeni predmet!");
            return;
        }
        Student[] novi = new Student[studenti.length + 1];
        for(int i = 0; i < studenti.length; i++) {
            novi[i] = studenti[i];
        }
        novi[studenti.length] = student;
        this.studenti = novi;
    }
    public void ispisi(Student student){
        if(studenti == null || studenti.length == 0){
            System.out.println("Predmet nema studenata!");
            return;
        }
        if(!upisan(student)){
            System.out.println("Student nije upisan na navedeni predmet!");
            return;
        }
        Student[] novi = new Student[studenti.length - 1];
        int j = 0;
        for(int i = 0; i < novi.length; i++){
            if(!student.getBrojIndexa().equals(studenti[j].getBrojIndexa())){
                novi[i] = studenti[j];
            }
            else {
                j++;
                novi[i] = studenti[j];
                j++;
            }
        }
        this.studenti = novi;
    }

    @Override
    public String toString() {
        String lista = "1. ";
        int i = 1;
        for(Student s : studenti){
            if(s == null) {
                break;
            }
            if(i == 1) {
                lista += s.toString();
                i++;
            }
            else {
                lista += Integer.toString(i) + ". " + s.toString();
                i++;
            }
        }
        return lista;
    }
}
