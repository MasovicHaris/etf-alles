package ba.unsa.etf.rpr.zadaca2;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

@ExtendWith(ApplicationExtension.class)
class Zadatak10Test {
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

    @Test
    void testAdministratorNasljedjivanje(FxRobot robot) {
        // Da li je klasa Administrator naslijeđena iz klase Korisnik?
        Administrator a = new Administrator("Test", "Proba", "proba@test.ba", "test", "test");
        assertTrue(a instanceof Korisnik);
    }

    @Test
    void testAdministratorCheckPassword(FxRobot robot) {
        // Provjera funkcije checkPassword klase Administrator (potreban i specijalni znak)
        Administrator a = new Administrator("Test", "Proba", "proba@test.ba", "test", "test");
        assertFalse(a.checkPassword());
        a.setPassword("Aa1");
        assertFalse(a.checkPassword());
        a.setPassword("A!a1");
        assertTrue(a.checkPassword());
        a.setPassword("012345ABCDEFgjtlei123AVqwerty");
        assertFalse(a.checkPassword());
        a.setPassword("012345ABCDEF!gjtlei123AVqwerty");
        assertTrue(a.checkPassword());
    }

    @Test
    void testAdministratorRubni(FxRobot robot) {
        // Provjera rubnih karaktera u funkciji checkPassword
        Administrator a = new Administrator("Test", "Proba", "proba@test.ba", "test", "/0zZ");
        assertTrue(a.checkPassword());
        a.setPassword("Aa0@");
        assertTrue(a.checkPassword());
        a.setPassword("9zZ`");
        assertTrue(a.checkPassword());
        a.setPassword("0AzaZ9");
        assertFalse(a.checkPassword());
        a.setPassword("0:aA");
        assertTrue(a.checkPassword());
    }

    @Test
    void testPretvoriKorisnikaUAdmina(FxRobot robot) {
        // Biramo korisnika Ljubović Vedran
        robot.clickOn("Ljubović Vedran");
        Korisnik k = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k.getPrezime());
        // Korisnik nije klasa Administrator
        assertFalse(k instanceof Administrator);

        // Klikamo na checkbox
        robot.clickOn("#cbAdmin");
        // Korisnik sada jeste klasa Administrator
        Korisnik k2 = model.getTrenutniKorisnik();
        // I dalje ima standardne podatke korisnika Ljubović Vedran
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);
    }

    @Test
    void testCBGoreDole(FxRobot robot) {
        // Biramo korisnika Ljubović Vedran
        robot.clickOn("Ljubović Vedran");
        // Klikamo na checkbox
        robot.clickOn("#cbAdmin");
        // Korisnik sada jeste klasa Administrator
        Korisnik k2 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);

        // Mijenjamo na drugog korisnika pa na prvog, da vidimo da li je promjena trajno zapisana u modelu
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("Ljubović Vedran");
        // Korisnik je i dalje klasa Administrator
        Korisnik k3 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k3.getPrezime());
        assertTrue(k3 instanceof Administrator);
    }

    @Test
    void testPretvoriKorisnikaUObicnog(FxRobot robot) {
        // Biramo korisnika Ljubović Vedran
        robot.clickOn("Ljubović Vedran");
        // Klikamo na checkbox
        robot.clickOn("#cbAdmin");
        // Korisnik sada jeste klasa Administrator
        Korisnik k2 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);

        // Mijenjamo na drugog korisnika pa na prvog
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("Ljubović Vedran");
        // Opet klikamo na checkbox
        robot.clickOn("#cbAdmin");
        // Korisnik sada više nije klasa Administrator
        Korisnik k3 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k3.getPrezime());
        assertFalse(k3 instanceof Administrator);

        // Mijenjamo na drugog korisnika pa na prvog, da vidimo da li je promjena trajno zapisana u modelu
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("Ljubović Vedran");
        // Korisnik i dalje nije klasa Administrator
        Korisnik k4 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k4.getPrezime());
        assertFalse(k4 instanceof Administrator);
    }

    @Test
    void testValidirajPasswordAdmin(FxRobot robot) {
        // Proglašavamo korisnika Ljubović Vedran za administratora
        robot.clickOn("Ljubović Vedran");
        robot.clickOn("#cbAdmin");
        Korisnik k2 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);

        // Test da li se password validira po pravilima za administratora (obavezan specijalni znak)
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("ab");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("ab");

        TextField ime = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("C");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("C");
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("1");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("1");
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("@");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("@");
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeIspravno"));

        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.RIGHT).release(KeyCode.RIGHT);
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.RIGHT).release(KeyCode.RIGHT);
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeNijeIspravno"));


        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("@");
        robot.clickOn("#fldPassword");
        robot.write("@");
        assertTrue(KorisnikControllerTest.sadrziStil(ime, "poljeIspravno"));
    }

    @Test
    void testGenerisiPasswordAdmin(FxRobot robot) {
        // Ovaj test nema smisla bez urađenog zadatka 9

        // Proglašavamo korisnika Ljubović Vedran za administratora
        robot.clickOn("Ljubović Vedran");
        robot.clickOn("#cbAdmin");
        Korisnik k2 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);

        // Klikamo na dugme Generiši
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Password je validan i dužine je 8 znakova (defaultni "test" je 4 znaka)
        assertTrue(KorisnikControllerTest.sadrziStil(password, "poljeIspravno"));
        assertEquals(8, password.getText().length());
    }


    @Test
    void testGenerisiPasswordAdminModel(FxRobot robot) {
        // Ovaj test nema smisla bez urađenog zadatka 9

        // Proglašavamo korisnika Ljubović Vedran za administratora
        robot.clickOn("Ljubović Vedran");
        robot.clickOn("#cbAdmin");
        Korisnik k2 = model.getTrenutniKorisnik();
        assertEquals("Ljubović", k2.getPrezime());
        assertTrue(k2 instanceof Administrator);

        // Klikamo na dugme Generiši
        robot.clickOn("#btnGenerisi");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        TextField password = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertNotNull(password);

        // Pozivamo metodu checkPassword klase Administrator
        Administrator a = (Administrator)model.getTrenutniKorisnik();
        assertEquals(password.getText(), a.getPassword());
        assertTrue(a.checkPassword());
    }

    @Test
    void testNistaNijeIzabrano(FxRobot robot) {
        // Nemoj se krahirati ako nijedan korisnik nije izabran
        robot.clickOn("#cbAdmin");

        assertNull(model.getTrenutniKorisnik());
    }
}