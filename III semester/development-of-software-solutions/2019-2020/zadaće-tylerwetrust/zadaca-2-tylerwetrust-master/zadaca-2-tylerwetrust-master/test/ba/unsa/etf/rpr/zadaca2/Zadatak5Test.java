package ba.unsa.etf.rpr.zadaca2;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.Slider;
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
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

@ExtendWith(ApplicationExtension.class)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class Zadatak5Test {
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
    void imaLiSlider(FxRobot robot) {
        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertNotNull(slider);
        boolean found = false;
        for (Node node : root.getChildrenUnmodifiable()) {
            if (node instanceof Label) {
                Label l = (Label) node;
                if (l.getText().equals("Godina rođenja:"))
                    found = true;
            }
        }
        assertTrue(found);
    }
    @Test
    void korisnikTest(FxRobot robot) {
        Korisnik k = new Korisnik("Test", "Proba", "proba@test.ba", "test", "test");
        assertEquals(2000, k.getGodinaRodjenja());
        k.setGodinaRodjenja(1995);
        assertEquals(1995, k.getGodinaRodjenja());
    }

    @Test
    void sliderTest(FxRobot robot) {
        model.setTrenutniKorisnik(model.getKorisnici().get(0));
        model.getTrenutniKorisnik().setGodinaRodjenja(1990);
        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertEquals(1990, slider.getValue());
    }


    @Test
    void promjenaUi(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertNotNull(slider);
        slider.setValue(1998);
        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals(1998, korisniks.get(2).getGodinaRodjenja());
    }

    @Test
    void dodavanjeUi(FxRobot robot) {
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldIme").write("Ime");
        robot.clickOn("#fldPrezime").write("Prezime");
        robot.clickOn("#fldEmail").write("Email");
        robot.clickOn("#fldUsername").write("Username");
        robot.clickOn("#fldPassword").write("Password");

        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertNotNull(slider);
        slider.setValue(1980);

        ListView lista = robot.lookup("#listKorisnici").queryAs(ListView.class);
        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals(5, korisniks.size());
        assertEquals(1980, korisniks.get(4).getGodinaRodjenja());
    }

    @Test
    void dodavanjeModel(FxRobot robot) {
        Platform.runLater(() -> {
            model.getKorisnici().add( new Korisnik("Ime", "Prezime", "a@b", "asdf", "asdf"));
            model.getKorisnici().get(4).setGodinaRodjenja(1945);
        });

        // Čekamo da se pojavi korisnik
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        robot.clickOn("Prezime Ime");

        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertEquals(1945, slider.getValue());
    }

    @Test
    void izmjenaModel(FxRobot robot) {
        model.getKorisnici().get(3).setGodinaRodjenja(1990);

        robot.clickOn("Fejzić Rijad");

        Slider slider = robot.lookup("#sliderGodinaRodjenja").queryAs(Slider.class);
        assertEquals(1990, slider.getValue());
    }
}
