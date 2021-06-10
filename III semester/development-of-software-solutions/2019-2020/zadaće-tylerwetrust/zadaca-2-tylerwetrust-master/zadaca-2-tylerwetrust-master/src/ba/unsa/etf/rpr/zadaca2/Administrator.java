package ba.unsa.etf.rpr.zadaca2;

public class Administrator extends Korisnik {
    public Administrator(String ime, String prezime, String email, String username, String password) {
        super(ime, prezime, email, username, password);
    }



    @Override
    public boolean checkPassword() {
        return super.checkPassword() && !this.getPassword().matches("[A-Za-z0-9]+");
    }
}
