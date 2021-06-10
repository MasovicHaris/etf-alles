package ba.unsa.etf.rpr.zadaca2;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

@ExtendWith(ApplicationExtension.class)
class KorisnikControllerTest {
    KorisniciModel model;

    // Pomoćna funkcija za provjeru validacije text polja
    // Može se pozivati iz drugih klasa
    public static boolean sadrziStil(TextField polje, String stil) {
        for (String s : polje.getStyleClass())
            if (s.equals(stil)) return true;
        return false;
    }

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
    void listTest(FxRobot robot) {
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = lista.getItems();
        String s = "";
        for(Korisnik k : korisniks)
            s += k;
        String expected = "Ljubović VedranDelić AmraSijerčić TarikFejzić Rijad";
        assertEquals(expected, s);
    }

    @Test
    void promjena(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#fldIme").write("bbb");
        robot.clickOn("Fejzić Rijad");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = lista.getItems();
        assertEquals("Sijerčić Tarikbbb", korisniks.get(2).toString());
    }

    @Test
    void promjenaModel(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#fldIme").write("bbb");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals("Sijerčić Tarikbbb", korisniks.get(2).toString());
    }

    @Test
    void dodavanje(FxRobot robot) {
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldIme").write("Ime");
        robot.clickOn("#fldPrezime").write("Prezime");
        robot.clickOn("#fldEmail").write("email@email.ba");
        robot.clickOn("#fldUsername").write("Username");
        robot.clickOn("#fldPassword").write("Password");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = lista.getItems();
        assertEquals(5, korisniks.size());
        assertEquals("Prezime Ime", korisniks.get(4).toString());
        assertEquals("email@email.ba", korisniks.get(4).getEmail());
        assertEquals("Username", korisniks.get(4).getUsername());
        assertEquals("Password", korisniks.get(4).getPassword());
    }

    @Test
    void dodavanjeModel(FxRobot robot) {
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldIme").write("Ime");
        robot.clickOn("#fldPrezime").write("Prezime");
        robot.clickOn("#fldEmail").write("email@email.ba");
        robot.clickOn("#fldUsername").write("Username");
        robot.clickOn("#fldPassword").write("Password");
        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals(5, korisniks.size());
        assertEquals("Prezime Ime", korisniks.get(4).toString());
        assertEquals("email@email.ba", korisniks.get(4).getEmail());
        assertEquals("Username", korisniks.get(4).getUsername());
        assertEquals("Password", korisniks.get(4).getPassword());
    }


    @Test
    void validacija(FxRobot robot) {
        robot.clickOn("Delić Amra");
        robot.clickOn("#btnDodaj");

        TextField polje = robot.lookup("#fldIme").queryAs(TextField.class);
        assertTrue(sadrziStil(polje, "poljeNijeIspravno"));
        robot.clickOn("#fldIme").write("Ime");
        assertTrue(sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldPrezime").queryAs(TextField.class);
        assertTrue(sadrziStil(polje, "poljeNijeIspravno"));
        robot.clickOn("#fldPrezime").write("Prezime");
        assertTrue(sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldEmail").queryAs(TextField.class);
        assertTrue(sadrziStil(polje, "poljeNijeIspravno"));
        robot.clickOn("#fldEmail").write("email@email.ba");
        assertTrue(sadrziStil(polje, "poljeIspravno"));

        polje = robot.lookup("#fldUsername").queryAs(TextField.class);
        assertTrue(sadrziStil(polje, "poljeNijeIspravno"));
        robot.clickOn("#fldUsername").write("Username");
        assertTrue(sadrziStil(polje, "poljeIspravno"));
    }
}