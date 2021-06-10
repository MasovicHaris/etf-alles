package ba.unsa.etf.rpr.zadaca2;

import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class Zadatak4Test {
    KorisniciModel model;
    Parent root;
    @Start
    public void start (Stage stage) throws Exception {
        model = new KorisniciModel();
        model.napuni();
        KorisnikController ctrl = new KorisnikController(model);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/korisnici.fxml"));
        loader.setController(ctrl);
        root = loader.load();
        stage.setTitle("Korisnici");
        stage.setScene(new Scene(root, USE_COMPUTED_SIZE, USE_COMPUTED_SIZE));
        stage.show();
        stage.toFront();
    }

    @Test
    @Order(1) // Ova anotacija postiže da se ovaj test izvrši prvi
    void imaLiLozinka(FxRobot robot) {
        TextField passwordRepeat = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertNotNull(passwordRepeat);
        boolean found = false;
        for (Node node : root.getChildrenUnmodifiable()) {
            if (node instanceof Label) {
                Label l = (Label) node;
                if (l.getText().equals("Ponovi lozinku:"))
                    found = true;
            }
        }
        assertTrue(found);
    }

    @Test
    void validacijaPasswordPrazno(FxRobot robot) {
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("#btnDodaj");
        TextField polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));
    }

    @Test
    void validacijaPasswordDrugiPrazan(FxRobot robot) {
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldPassword");
        robot.write("abcde");
        TextField polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));
    }

    @Test
    void validacijaPasswordJednaki(FxRobot robot) {
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldPassword");
        robot.write("abCD1");

        robot.clickOn("#fldPasswordRepeat");
        robot.write("abCD1");

        TextField polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));
    }

    @Test
    void validacijaPasswordRazlike(FxRobot robot) {
        robot.clickOn("Fejzić Rijad");
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldPassword");
        robot.write("qwE1r");
        robot.clickOn("#fldPasswordRepeat");
        robot.write("qwE1");
        TextField polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        robot.write("r");

        polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        robot.write("t");

        polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        robot.clickOn("#fldPassword");
        robot.write("t");

        polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertFalse(KorisnikControllerTest.sadrziStil(polje, "poljeNijeIspravno"));
        assertTrue(KorisnikControllerTest.sadrziStil(polje, "poljeIspravno"));
    }

    @Test
    void validacijaPopunjavanje(FxRobot robot) {
        // Korisnik 3 = Fejzić Rijad
        model.getKorisnici().get(3).setPassword("password");
        robot.clickOn("Fejzić Rijad");
        TextField polje = robot.lookup("#fldPassword").queryAs(TextField.class);
        assertEquals("password", polje.getText());

        polje = robot.lookup("#fldPasswordRepeat").queryAs(TextField.class);
        assertEquals("password", polje.getText());
    }
}
