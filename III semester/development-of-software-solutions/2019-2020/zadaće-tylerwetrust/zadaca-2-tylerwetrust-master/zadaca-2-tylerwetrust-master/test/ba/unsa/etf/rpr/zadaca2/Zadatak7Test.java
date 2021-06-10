package ba.unsa.etf.rpr.zadaca2;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
class Zadatak7Test {
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

    // Pomoćna funkcija za CSS
    boolean sadrziStil(TextField polje, String stil) {
        for (String s : polje.getStyleClass())
            if (s.equals(stil)) return true;
        return false;
    }

    @Test
    void testPassword1(FxRobot robot) {
        // Provjera da li se polje Lozinka validira po pravilima opisanim u postavci zadatka
        robot.clickOn("Delić Amra");
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("ab");

        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("ab");

        TextField ime = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        // Zamjenjujem redoslijed kako bih izbjegao da repeat polje forsira password na korisnika
        robot.clickOn("#fldPasswordRepeat");
        robot.write("C");
        robot.clickOn("#fldPassword");
        robot.write("C");
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("1");
        robot.clickOn("#fldPassword");
        robot.write("1");
        assertTrue(sadrziStil(ime, "poljeIspravno"));

        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));
    }

    @Test
    void testPassword2(FxRobot robot) {
        // Provjera da li se polje Lozinka validira po pravilima opisanim u postavci zadatka
        robot.clickOn("Delić Amra");
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("1234");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("1234");

        TextField ime = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("C");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("C");
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("c");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("c");
        assertTrue(sadrziStil(ime, "poljeIspravno"));

        robot.clickOn("#fldPassword");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("De");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("De");
        assertTrue(sadrziStil(ime, "poljeIspravno"));
    }

    @Test
    void testPassword3(FxRobot robot) {
        // Provjera da li se polje Lozinka validira po pravilima opisanim u postavci zadatka
        robot.clickOn("Delić Amra");
        robot.clickOn("#fldPassword");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("Aa1");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("Aa1");

        TextField ime = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(sadrziStil(ime, "poljeIspravno"));

        robot.clickOn("#fldPassword");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.press(KeyCode.BACK_SPACE).release(KeyCode.BACK_SPACE);
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("C");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("C");
        assertTrue(sadrziStil(ime, "poljeNijeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("9");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("9");
        assertTrue(sadrziStil(ime, "poljeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("De8");
        // Ako ste uradili zadatak 4, otkomentarišite kod ispod
        robot.clickOn("#fldPasswordRepeat");
        robot.write("De8");
        assertTrue(sadrziStil(ime, "poljeIspravno"));
    }

    @Test
    void testIspravniPasswordi() {
        // Test funkcije checkPassword sa nekoliko ispravnih lozinki
        Korisnik k = new Korisnik("Mia", "Miić", "mia@etf.ba", "miamiic", "abc");
        assertFalse(k.checkPassword());
        k.setPassword("0Aa");
        assertTrue(k.checkPassword());
        k.setPassword("A0a");
        assertTrue(k.checkPassword());
        k.setPassword("Zz9");
        assertTrue(k.checkPassword());
        k.setPassword("qwertYiuopasdfghjk0lzxcvmnbm");
        assertTrue(k.checkPassword());
        k.setPassword("z999999999Z");
        assertTrue(k.checkPassword());
    }

    @Test
    void testRubniPasswordi() {
        // Test funkcije checkPassword sa karakterima na rubovima opsega
        Korisnik k = new Korisnik("Mia", "Miić", "mia@etf.ba", "miamiic", "123ABCabc");
        assertTrue(k.checkPassword());
        k.setPassword("[|]aa1");
        assertFalse(k.checkPassword());
        k.setPassword("012345ABCD`");
        assertFalse(k.checkPassword());
        k.setPassword("qwertQWERT:;<=>?@");
        assertFalse(k.checkPassword());
        k.setPassword("dfgd/DFGDFG");
        assertFalse(k.checkPassword());
    }

    @Test
    void testPogresniPasswordi() {
        // Test funkcije checkPassword sa nekoliko pogrešnih lozinki
        Korisnik k = new Korisnik("Mia", "Miić", "mia@etf.ba", "miamiic", "DEF987def");
        assertTrue(k.checkPassword());
        k.setPassword("qwertYIUOPASdfghjklzxcvmnbm");
        assertFalse(k.checkPassword());
        k.setPassword("a");
        assertFalse(k.checkPassword());
        k.setPassword("");
        assertFalse(k.checkPassword());
        k.setPassword("12346789");
        assertFalse(k.checkPassword());
        k.setPassword("12346789Z");
        assertFalse(k.checkPassword());
        k.setPassword("12346789Zz");
        assertTrue(k.checkPassword());
        k.setPassword("abcABCdefDEFghiGHIjklJKL");
        assertFalse(k.checkPassword());
        k.setPassword("abcABCdefDEF4ghiGHIjklJKL");
        assertTrue(k.checkPassword());
    }

    @Test
    void testNistaNijeIzabrano(FxRobot robot) {
        // Nemoj se krahirati ako nijedan korisnik nije izabran
        robot.clickOn("#fldPassword");
        robot.write("Aa1");
        robot.clickOn("#fldPasswordRepeat");
        robot.write("Aa1");
        assertNull(model.getTrenutniKorisnik());
    }
}