package ba.unsa.etf.rpr;

import java.util.Scanner;

public class Program {
    public static final String UNESITE_NAZIV_PREDMETA = "Unesite naziv predmeta";
    public static final String UNESITE_SIFRU_PREDMETA = "Unesite sifru predmeta";
    public static final String UNESITE_MAXIMALAN_BROJ_STUDENATA_NA_PREDMETU = "Unesite maximalan broj studenata na predmetu";
    public static final String STUDENT_NIJE_NADJEN = "Student nije nadjen!";
    public static final String NEMA_KREIRANIH_PREDMETA = "Nema kreiranih predmeta!";
    public static final String UNESITE_INDEX_STUDENTA = "Unesite index studenta";
    private Predmet[] predmeti = null;
    private Student[] studenti = null;
    public Predmet[] getPredmeti() {
        return predmeti;
    }

    public Student[] getStudenti() {
        return studenti;
    }

    public Boolean provjeriPodatkePredmeta(String nazivPredmeta, Integer sifraPredmeta, int maxBrojStudenata){
        if(nazivPredmeta == null || nazivPredmeta.isEmpty()){
            System.out.println("Niste unijeli naziv predmeta!");
            return false;
        }
        if(predmeti == null || predmeti.length == 0){
            return true;
        }
        for(Predmet p : predmeti) {
            if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                System.out.println("Predmet vec postoji!");
                return false;
            } else if (p.getSifraPredmeta().equals(sifraPredmeta)) {
                System.out.println("Poklapanje sifre predmeta!");
                return false;
            }
        }
        if(maxBrojStudenata == 0){
            System.out.println("Maximalan broj studenata na predmetu ne moze biti nula!");
            return false;
        }
        return true;
    }
    public Boolean provjeriPodatkeStudenta(String prezime, String ime, Integer brojIndexa){
        if(prezime == null || prezime.isEmpty()){
            System.out.println("Niste unijeli prezime studenta!");
            return false;
        }
        if(ime == null || ime.isEmpty()){
            System.out.println("Niste unijeli ime studenta!");
            return false;
        }
        if(studenti == null || studenti.length == 0) {
            return true;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(brojIndexa)) {
                System.out.println("Poklapanje broja indexa!");
                return false;
            }
        }
        return true;
    }
    public Boolean imaPredmet(String nazivPredmeta){
        if(predmeti == null || predmeti.length == 0) {
            return false;
        }
        for(Predmet p : predmeti) {
            if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                return true;
            }
        }
        return false;
    }
    public Boolean imaStudent(Integer brojIndexa){
        if(studenti == null || studenti.length == 0) {
            return false;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(brojIndexa)) {
                return true;
            }
        }
        return false;
    }

    public void kreirajPredmet (String nazivPredmeta, Integer sifraPredmeta, int maxBrojStudenata){
        if(!provjeriPodatkePredmeta(nazivPredmeta, sifraPredmeta, maxBrojStudenata)) {
            return;
        }
        if(predmeti == null || predmeti.length == 0){
            predmeti = new Predmet[1];
            predmeti[0] = new Predmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
            return;
        }
        Predmet[] novi = new Predmet[predmeti.length + 1];
        for(int i = 0; i < predmeti.length; i++) {
            novi[i] = predmeti[i];
        }
        novi[predmeti.length] = new Predmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
        predmeti = novi;
    }
    public void dodajStudenta(String prezime, String ime, Integer brojIndexa){
        if(!provjeriPodatkeStudenta(prezime, ime, brojIndexa)){
            return;
        }
        if(studenti == null || studenti.length == 0){
            studenti = new Student[1];
            studenti[0] = new Student(ime, prezime, brojIndexa);
            return;
        }
        Student[] novi = new Student[studenti.length + 1];
        for(int i = 0; i < studenti.length; i++) {
            novi[i] = studenti[i];
        }
        novi[studenti.length] = new Student(ime, prezime, brojIndexa);
        studenti = novi;
    }
    public void upisiStudentaNaPredmet(Integer brojIndexa, String nazivPredmeta){
        if(!imaStudent(brojIndexa)){
            System.out.println(STUDENT_NIJE_NADJEN);
            return;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(brojIndexa)) {
                if (predmeti == null || predmeti.length == 0) {
                    System.out.println(NEMA_KREIRANIH_PREDMETA);
                    break;
                } else {
                    for (Predmet p : predmeti) {
                        if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                            p.upisi(s);
                            return;
                        }
                    }
                }
            }
        }
    }
    public void ispisiStudentaSaPredmeta(Integer brojIndexa, String nazivPredmeta){
        if(!imaStudent(brojIndexa)){
            System.out.println(STUDENT_NIJE_NADJEN);
            return;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(brojIndexa)) {
                if (predmeti == null || predmeti.length == 0) {
                    System.out.println(NEMA_KREIRANIH_PREDMETA);
                    return;
                } else {
                    for (Predmet p : predmeti) {
                        if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                            p.ispisi(s);
                            return;
                        }
                    }
                }
            }
        }
    }
    public void obrisiStudenta(Integer brojIndexa){
        if(!imaStudent(brojIndexa)){
            System.out.println(STUDENT_NIJE_NADJEN);
            return;
        }
        for(Student s : studenti) {
            if (s.getBrojIndexa().equals(brojIndexa)) {
                for (Predmet p : predmeti) {
                    if (p.upisan(s)) {
                        p.ispisi(s);
                    }
                }
            }
        }
        Student[] novi = new Student[studenti.length - 1];
        int j = 0;
        for(int i = 0; i < novi.length; i++){
            if(!studenti[j].getBrojIndexa().equals(brojIndexa)){
                novi[i] = studenti[j];
                j++;
            }
            else {
                j++;
                novi[i] = studenti[j];
                j++;
            }
        }
        studenti = novi;
    }
    public void obrisiPredmet(String nazivPredmeta){
        if(!imaPredmet(nazivPredmeta)){
            System.out.println("Predmet nije nadjen!");
            return;
        }
        Predmet[] novi = new Predmet[predmeti.length - 1];
        int j = 0;
        for(int i = 0; i < novi.length; i++){
            if(!predmeti[j].getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)){
                novi[i] = predmeti[j];
                j++;
            }
            else {
                j++;
            }
        }
        predmeti = novi;
    }
    public void ispisiSpisakStudenata(String nazivPredmeta){
        for(Predmet p : predmeti) {
            if (p.getNazivPredmeta().equalsIgnoreCase(nazivPredmeta)) {
                System.out.println(p);
                return;
            }
        }
    }
    public void dodavanjeStudenta(){
        try{
            System.out.println("Unesite prezime");
            Scanner scanner = new Scanner(System.in);
            String prezime = scanner.nextLine();
            System.out.println("Unesite ime");
            scanner = new Scanner(System.in);
            String ime = scanner.nextLine();
            System.out.println("Unesite brojIndexa");
            scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            dodajStudenta(prezime, ime, brojIndexa);
        } catch(Exception e){
            System.out.println(e.toString());
        }
    }
    public void kreiranjePredmeta(){
        try{
            System.out.println(UNESITE_NAZIV_PREDMETA);
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            System.out.println(UNESITE_SIFRU_PREDMETA);
            scanner = new Scanner(System.in);
            Integer sifraPredmeta = scanner.nextInt();
            System.out.println(UNESITE_MAXIMALAN_BROJ_STUDENATA_NA_PREDMETU);
            scanner = new Scanner(System.in);
            int maxBrojStudenata = scanner.nextInt();
            kreirajPredmet(nazivPredmeta, sifraPredmeta, maxBrojStudenata);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void upisStudentaNaPredmet(){
        try{
            System.out.println(UNESITE_INDEX_STUDENTA);
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            System.out.println(UNESITE_NAZIV_PREDMETA);
            scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            upisiStudentaNaPredmet(brojIndexa, nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void ispisStudentaSaPredmeta(){
        try{
            System.out.println(UNESITE_INDEX_STUDENTA);
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            System.out.println(UNESITE_NAZIV_PREDMETA);
            scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            ispisiStudentaSaPredmeta(brojIndexa, nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void brisanjeStudenta(){
        try{
            System.out.println(UNESITE_INDEX_STUDENTA);
            Scanner scanner = new Scanner(System.in);
            Integer brojIndexa = scanner.nextInt();
            obrisiStudenta(brojIndexa);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void brisanjePredmeta(){
        try{
            System.out.println(UNESITE_NAZIV_PREDMETA);
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            obrisiPredmet(nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public void ispis(){
        try{
            System.out.println(UNESITE_NAZIV_PREDMETA);
            Scanner scanner = new Scanner(System.in);
            String nazivPredmeta = scanner.nextLine();
            ispisiSpisakStudenata(nazivPredmeta);
        } catch (Exception e){
            System.out.println(e.toString());
        }
    }

    public static void main(String[] args) {
        Program program = new Program();
        program.dodajStudenta("Krdzic", "Nermin", 17825);
        program.dodajStudenta("Masovic", "Haris", 17696);
        program.dodajStudenta("xxxxx", "Faris", 17777);
        program.kreirajPredmet("MLTI", 1, 1);
        program.kreirajPredmet("RPR", 2, 2);
        int izbor = 1;
        while(izbor != 0){
            System.out.println("Unesite:");
            System.out.println("1. za, Dodavanje studenta");
            System.out.println("2. za, Kreiranje predmeta");
            System.out.println("3. za, Upis studenta na predmet");
            System.out.println("4. za, Ispis studenta sa predmeta");
            System.out.println("5. za, Brisanje studenta");
            System.out.println("6. za, Brisanje predmeta");
            System.out.println("7. za, Ispis spiska studenata sa navedenog predmeta");
            System.out.println("0. za, Izlaz iz aplikacije.");
            Scanner scanner = new Scanner(System.in);
            izbor = scanner.nextInt();
            switch (izbor){
                case 0:
                    return;
                case 1:
                    program.dodavanjeStudenta();
                    break;
                case 2:
                    program.kreiranjePredmeta();
                    break;
                case 3:
                    program.upisStudentaNaPredmet();
                    break;
                case 4:
                    program.ispisStudentaSaPredmeta();
                    break;
                case 5:
                    program.brisanjeStudenta();
                    break;
                case 6:
                    program.brisanjePredmeta();
                    break;
                case 7:
                    program.ispis();
                    break;
            }
        }
    }
}
