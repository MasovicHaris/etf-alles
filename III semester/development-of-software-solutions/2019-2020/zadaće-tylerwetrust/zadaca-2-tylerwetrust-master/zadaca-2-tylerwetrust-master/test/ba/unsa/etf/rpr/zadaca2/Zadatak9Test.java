package ba.unsa.etf.rpr.zadaca2;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.DialogPane;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
class Zadatak9Test {
    KorisniciModel model;
    @Start
    public void start (Stage stage) throws Exception {
        model = new KorisniciModel();
        model.napuni();
        KorisnikController ctrl = new KorisnikController(model);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/korisnici.fxml"));
        loader.setController(ctrl);
        Parent root = loader.load();
        stage.setTitle("Korisnici");
        stage.setScene(new Scene(root, USE_COMPUTED_SIZE, USE_COMPUTED_SIZE));
        stage.show();
        stage.toFront();
    }

    // Zadatak 9 nema smisla ako nije barem započet zadatak 8 (kreirano dugme), pa to nećemo opet testirati

    @Test
    void generisiDugme(FxRobot robot) {
        // Biramo korisnika Sijerčić Tarik i klikamo na dugme Generiši
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Pronalazimo polje za lozinku na formi
        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Da li je polje za lozinku validno?
        assertTrue(KorisnikControllerTest.sadrziStil(password, "poljeIspravno"));
        // Da li je dužina lozinke 8 karaktera?
        assertEquals(8, password.getText().length());
    }

    @Test
    void generisiDugmeModel(FxRobot robot) {
        // Biramo korisnika Sijerčić Tarik i klikamo na dugme Generiši
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Pronalazimo polje za lozinku na formi
        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Da li je lozinka ispravno upisana u model (trenutni korisnik)?
        assertEquals(password.getText(), model.getTrenutniKorisnik().getPassword());
        // Pozivamo metodu checkPassword klase Korisnik da vidimo da li je lozinka validna
        assertTrue(model.getTrenutniKorisnik().checkPassword());
    }

    @Test
    void generisiDugmeGoreDole(FxRobot robot) {
        // Biramo korisnika Sijerčić Tarik i klikamo na dugme Generiši lozinku
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Mijenjamo na drugog korisnika pa na prvog, da vidimo da li je lozinka trajno zapisana u modelu
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("Sijerčić Tarik");
        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Da li je polje za lozinku validno?
        assertTrue(KorisnikControllerTest.sadrziStil(password, "poljeIspravno"));
        // Da li je dužina lozinke 8 karaktera?
        assertEquals(8, password.getText().length());
    }

    @Test
    void generisiDugmeGoreDoleModel(FxRobot robot) {
        // Biramo korisnika Sijerčić Tarik i klikamo na dugme Generiši lozinku
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Mijenjamo na drugog korisnika pa na prvog, da vidimo da li je lozinka trajno zapisana u modelu
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("Sijerčić Tarik");
        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Da li je lozinka ispravno upisana u model (trenutni korisnik)?
        assertEquals(password.getText(), model.getTrenutniKorisnik().getPassword());
        // Pozivamo metodu checkPassword klase Korisnik da vidimo da li je lozinka validna
        assertTrue(model.getTrenutniKorisnik().checkPassword());
    }


    @Test
    void generisiDugmeGoreDoleModelSvi(FxRobot robot) {
        // Biramo korisnika Sijerčić Tarik i klikamo na dugme Generiši lozinku
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Mijenjamo na drugog korisnika pa na prvog, da vidimo da li je lozinka trajno zapisana u modelu
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("Sijerčić Tarik");
        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Prolazimo kroz sve korisnike u modelu (getKorisnici), za slučaj da je promijenjen samo trenutni
        String lozinka = password.getText();
        for(Korisnik k : model.getKorisnici())
            if (k.getPrezime().equals("Sijerčić")) {
                // Ako je korisnik Sijerčić, njegova lozinka je jednaka onoj na formi
                assertEquals(lozinka, k.getPassword());
                // Pozivamo metodu checkPassword da još jednom provjerimo
                assertTrue(k.checkPassword());
            } else {
                // Provjeravamo da lozinka nije dodijeljena pogrešnom korisniku
                assertNotEquals(lozinka, k.getPassword());
            }
    }
}