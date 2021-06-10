package ba.unsa.etf.rpr.zadaca2;

import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.DialogPane;
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

@ExtendWith(ApplicationExtension.class)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class Zadatak8Test {
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
    @Order(1) // Ova anotacija postiže da se ovaj test izvrši prvi
    void imaLiDugme(FxRobot robot) {
        Button btnGenerisi = robot.lookup("#btnGenerisi").queryAs(Button.class);
        assertNotNull(btnGenerisi);
        assertEquals("Generiši", btnGenerisi.getText());
    }

    @Test
    void generisiLista(FxRobot robot) {
        robot.clickOn("Sijerčić Tarik");
        robot.clickOn("#btnGenerisi");

        // Kada riješite zadatak 9, otkomentarišite kod ispod
//        // Čekamo da dijalog postane vidljiv
         robot.lookup(".dialog-pane").tryQuery().isPresent();
//
//        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        robot.clickOn("Fejzić Rijad");
        robot.clickOn("Sijerčić Tarik");
        TextField username = robot.lookup("#fldUsername").queryAs(TextField.class);
        assertNotNull(username);

        assertEquals("tsijercic", username.getText());
    }

    @Test
    void generisiModel(FxRobot robot) {
        robot.clickOn("Fejzić Rijad");

        robot.clickOn("#btnGenerisi");

        // Kada riješite zadatak 9, otkomentarišite kod ispod
//        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();
//
//        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        robot.clickOn("Sijerčić Tarik");

        ObservableList<Korisnik> korisniks = model.getKorisnici();
        String s = "";
        for(Korisnik k : korisniks)
            if (k.getPrezime().equals("Fejzić"))
                s = k.getUsername();
        assertEquals("rfejzic", s);
    }

    @Test
    void generisiNovi(FxRobot robot) {
        robot.clickOn("#btnDodaj");
        robot.clickOn("#fldIme").write("Čćšđž");
        robot.clickOn("#fldPrezime").write("ČĆŠĐŽčćšđž");
        robot.clickOn("#fldEmail").write("a@a.ba");
        robot.clickOn("#fldUsername").write("usr");
        robot.clickOn("#fldPassword").write("Password");

        robot.clickOn("Delić Amra");
        robot.clickOn("ČĆŠĐŽčćšđž Čćšđž");

        robot.clickOn("#btnGenerisi");

        // Kada riješite zadatak 9, otkomentarišite kod ispod
//        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();
//
//        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals("cccsdzccsdz", korisniks.get(4).getUsername());
    }

    @Test
    void generisiNoviModel(FxRobot robot) {
        Platform.runLater(
                () ->  model.getKorisnici().add( new Korisnik("Žšćšđ", "žđščć", "a@b", "asdf", "asdf"))
        );

        // Čekamo da se pojavi korisnik
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        robot.clickOn("žđščć Žšćšđ");

        robot.clickOn("#btnGenerisi");

        // Kada riješite zadatak 9, otkomentarišite kod ispod
//        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();
//
//        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals("zzdscc", korisniks.get(4).getUsername());
    }

    @Test
    void testPrazno(FxRobot robot) {
        robot.clickOn("#btnDodaj");
        robot.clickOn("#btnGenerisi");
        Platform.runLater(
                () ->  model.getKorisnici().add( new Korisnik("", "", "", "", ""))
        );
        robot.clickOn("#btnGenerisi");

        // Kada riješite zadatak 9, otkomentarišite kod ispod
//        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();
//
//        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        ObservableList<Korisnik> korisniks = model.getKorisnici();
        assertEquals("", korisniks.get(4).getUsername());
    }
}
