package ba.unsa.etf.rpr.zadaca2;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.security.SecureRandom;
import java.util.Random;

public class KorisnikController {
    public TextField fldIme;
    public TextField fldPrezime;
    public TextField fldEmail;
    public TextField fldUsername;
    public ListView<Korisnik> listKorisnici;
    public PasswordField fldPassword;
    public PasswordField fldPasswordRepeat;
    public Slider sliderGodinaRodjenja;
    public CheckBox cbAdmin;
    private KorisniciModel model;

    public KorisnikController(KorisniciModel model) {
        this.model = model;
    }

    @FXML
    public void initialize() {
        listKorisnici.setItems(model.getKorisnici());
        listKorisnici.getSelectionModel().selectedItemProperty().addListener((obs, oldKorisnik, newKorisnik) -> {
            model.setTrenutniKorisnik(newKorisnik);
            listKorisnici.refresh();
         });
        sliderGodinaRodjenja.setValue(2000);
        model.trenutniKorisnikProperty().addListener((obs, oldKorisnik, newKorisnik) -> {
            if (oldKorisnik != null) {
                fldIme.textProperty().unbindBidirectional(oldKorisnik.imeProperty() );
                fldPrezime.textProperty().unbindBidirectional(oldKorisnik.prezimeProperty() );
                fldEmail.textProperty().unbindBidirectional(oldKorisnik.emailProperty() );
                fldUsername.textProperty().unbindBidirectional(oldKorisnik.usernameProperty() );
                fldPassword.textProperty().unbindBidirectional(oldKorisnik.passwordProperty() );
                fldPasswordRepeat.textProperty().unbindBidirectional(oldKorisnik.passwordRepeatProperty() );
                sliderGodinaRodjenja.valueProperty().unbindBidirectional(oldKorisnik.godinaRodjenjaProperty());


            }
            if (newKorisnik == null) {
                fldIme.setText("");
                fldPrezime.setText("");
                fldEmail.setText("");
                fldUsername.setText("");
                fldPassword.setText("");
                fldPasswordRepeat.setText("");
                sliderGodinaRodjenja.setValue(2000);
            }
            else {
                fldIme.textProperty().bindBidirectional( newKorisnik.imeProperty() );
                fldPrezime.textProperty().bindBidirectional( newKorisnik.prezimeProperty() );
                fldEmail.textProperty().bindBidirectional( newKorisnik.emailProperty() );
                fldUsername.textProperty().bindBidirectional( newKorisnik.usernameProperty() );
                fldPassword.textProperty().bindBidirectional( newKorisnik.passwordProperty() );
                fldPasswordRepeat.textProperty().bindBidirectional( newKorisnik.passwordRepeatProperty() );
                sliderGodinaRodjenja.valueProperty().bindBidirectional( newKorisnik.godinaRodjenjaProperty() );
            }
        });

        fldIme.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && imeIPrezimeValidation(newIme)) {
                fldIme.getStyleClass().removeAll("poljeNijeIspravno");
                fldIme.getStyleClass().add("poljeIspravno");
            } else {
                fldIme.getStyleClass().removeAll("poljeIspravno");
                fldIme.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPrezime.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && imeIPrezimeValidation(newIme)) {
                fldPrezime.getStyleClass().removeAll("poljeNijeIspravno");
                fldPrezime.getStyleClass().add("poljeIspravno");
            } else {
                fldPrezime.getStyleClass().removeAll("poljeIspravno");
                fldPrezime.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldEmail.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && emailValidation(newIme)) {
                fldEmail.getStyleClass().removeAll("poljeNijeIspravno");
                fldEmail.getStyleClass().add("poljeIspravno");
            } else {
                fldEmail.getStyleClass().removeAll("poljeIspravno");
                fldEmail.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldUsername.textProperty().addListener((obs, oldIme, newIme) -> {
            if (!newIme.isEmpty() && usernameValidation(newIme)) {
                fldUsername.getStyleClass().removeAll("poljeNijeIspravno");
                fldUsername.getStyleClass().add("poljeIspravno");
            } else {
                fldUsername.getStyleClass().removeAll("poljeIspravno");
                fldUsername.getStyleClass().add("poljeNijeIspravno");
            }
        });

        fldPassword.textProperty().addListener((obs, oldIme, newIme) -> {
            Korisnik k;
            if(model.getTrenutniKorisnik() instanceof Administrator){
              k = new Administrator("","","","",newIme);
            }
            else {
                 k= new Korisnik("","","","",newIme);
            }
            if (!newIme.isEmpty() && fldPassword.getText().equals(fldPasswordRepeat.getText()) && k.checkPassword()) {
                fldPasswordRepeat.getStyleClass().removeAll("poljeNijeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeIspravno");
                fldPassword.getStyleClass().removeAll("poljeNijeIspravno");
                fldPassword.getStyleClass().add("poljeIspravno");
            } else {
                fldPasswordRepeat.getStyleClass().removeAll("poljeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeNijeIspravno");
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
            }
        });
        fldPasswordRepeat.textProperty().addListener((obs, oldIme, newIme) -> {
            Korisnik k;
            if(model.getTrenutniKorisnik() instanceof Administrator){
                k = new Administrator("","","","",newIme);
            }
            else {
                k= new Korisnik("","","","",newIme);
            }
            if (!newIme.isEmpty() && fldPasswordRepeat.getText().equals(fldPassword.getText()) && k.checkPassword()) {
                fldPasswordRepeat.getStyleClass().removeAll("poljeNijeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeIspravno");
                fldPassword.getStyleClass().removeAll("poljeNijeIspravno");
                fldPassword.getStyleClass().add("poljeIspravno");
            } else {
                fldPasswordRepeat.getStyleClass().removeAll("poljeIspravno");
                fldPasswordRepeat.getStyleClass().add("poljeNijeIspravno");
                fldPassword.getStyleClass().removeAll("poljeIspravno");
                fldPassword.getStyleClass().add("poljeNijeIspravno");
            }
        });
        cbAdmin.selectedProperty().addListener((obs,oldValue,newValue) -> {
            if(model.getTrenutniKorisnik() != null) {
                Korisnik k = model.getTrenutniKorisnik();
                Korisnik admin = new Administrator(k.getIme(), k.getPrezime(), k.getEmail(), k.getUsername(), k.getPassword());
                int index = model.getKorisnici().indexOf(k);
                if (newValue) {
                    model.getKorisnici().set(index, admin);
                    model.setTrenutniKorisnik(model.getKorisnici().get(index));
                }
                else{
                    Korisnik k2 = new Korisnik(k.getIme(),k.getPrezime(),k.getEmail(),k.getUsername(),k.getPassword());
                    model.getKorisnici().set(index, k2);
                    model.setTrenutniKorisnik(k2);
                }
            }

        });
    }

    public void dodajAction(ActionEvent actionEvent) {
        model.getKorisnici().add(new Korisnik("", "", "", "", ""));
        listKorisnici.getSelectionModel().selectLast();
    }
    public void obrisiAction(ActionEvent actionEvent) {
        if(model.getKorisnici().size() != 0){
            model.getKorisnici().remove(model.getTrenutniKorisnik());
        }
        if(model.getKorisnici().size() != 0) model.setTrenutniKorisnik(model.getKorisnici().get(0));
        else model.setTrenutniKorisnik(null);
    }

    public void generisiAction(ActionEvent actionEvent){
        if(model.getTrenutniKorisnik().getIme().length() != 0 && model.getTrenutniKorisnik().getPrezime().length() != 0){
           String s1 = Character.toString(model.getTrenutniKorisnik().getIme().charAt(0));
           s1.toLowerCase();
           String s2 = model.getTrenutniKorisnik().getPrezime();
           s2 = s2.toLowerCase();
           String s3 = s1 + s2;
            s3 = s3.toLowerCase();
            s3 = s3.replaceAll("č","c");
            s3 = s3.replaceAll("ć","C");
            s3 = s3.replaceAll("đ","d");
            s3 = s3.replaceAll("ž","z");
            s3 = s3.replaceAll("š","s");
           s3 = s3.toLowerCase();
           model.getTrenutniKorisnik().setUsername(s3);
        }
        // generisanje passworda
        if(model.getTrenutniKorisnik() != null){
            final char[] lowercase = "abcdefghijklmnopqrstuvwxyz".toCharArray();
            final char[] uppercase = "ABCDEFGJKLMNPRSTUVWXYZ".toCharArray();
            final char[] numbers = "0123456789".toCharArray();
            final char[] symbols = "^$?!@#%&".toCharArray();
            final char[] allAllowed = "abcdefghijklmnopqrstuvwxyzABCDEFGJKLMNPRSTUVWXYZ0123456789".toCharArray();
            int length = 8;
            Random random = new SecureRandom();

            StringBuilder password = new StringBuilder();

            for (int i = 0; i < length-4; i++) {
                password.append(allAllowed[random.nextInt(allAllowed.length)]);
            }
            // u slucaju da je korisnik Administrator, u slucaju da je obicni Korisnik
            if(model.getTrenutniKorisnik() instanceof Administrator){
                password.insert(random.nextInt(password.length()), lowercase[random.nextInt(lowercase.length)]);
                password.insert(random.nextInt(password.length()), uppercase[random.nextInt(uppercase.length)]);
                password.insert(random.nextInt(password.length()), numbers[random.nextInt(numbers.length)]);
                password.insert(random.nextInt(password.length()), symbols[random.nextInt(symbols.length)]);
            }
            else {
                password.insert(random.nextInt(password.length()), lowercase[random.nextInt(lowercase.length)]);
                password.insert(random.nextInt(password.length()), uppercase[random.nextInt(uppercase.length)]);
                password.insert(random.nextInt(password.length()), numbers[random.nextInt(numbers.length)]);
                password.insert(random.nextInt(password.length()), numbers[random.nextInt(numbers.length)]);
            }
            model.getTrenutniKorisnik().setPassword(password.toString());
            model.getTrenutniKorisnik().setPasswordRepeat(password.toString());
            // Information prozor
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Information Dialog");
            alert.setHeaderText(null);
            alert.setContentText("Vaša lozinka glasi: " + password.toString());

            alert.showAndWait();

        }
    }

    public void krajAction(ActionEvent actionEvent) {
        System.exit(0);
    }
    // funkcije za validaciju, korišteni Java Regex kad god je bilo moguce
    private boolean imeIPrezimeValidation(String s){
        return s.length() >= 3 && s.matches("[\\- a-zA-zÀčćđžšČĆŽĐŠ]+") && !s.contains("_");
    }

    private boolean emailValidation(String s){
     return s.matches("[a-zA-Z0-9_.\\-]+@[a-zA-Z0-9_.\\-]+");
    }
    private boolean usernameValidation(String s){
        return s.length() <= 16 && s.matches("[_0-9a-zA-z]+");
    }

}
