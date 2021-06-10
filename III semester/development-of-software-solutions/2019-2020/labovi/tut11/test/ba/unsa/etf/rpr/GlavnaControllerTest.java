package ba.unsa.etf.rpr;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

import java.io.File;
import java.util.ResourceBundle;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(ApplicationExtension.class)
class GlavnaControllerTest {
    Stage theStage;
    GlavnaController ctrl;

    @Start
    public void start (Stage stage) throws Exception {
        ResourceBundle bundle = ResourceBundle.getBundle("Translation");
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/glavna.fxml"), bundle);
        ctrl = new GlavnaController();
        loader.setController(ctrl);
        Parent root = loader.load();
        stage.setTitle("Grad");
        stage.setScene(new Scene(root, USE_COMPUTED_SIZE, USE_COMPUTED_SIZE));
        stage.setResizable(false);
        stage.show();

        stage.toFront();

        theStage = stage;
    }

    @Test
    public void testTableView(FxRobot robot) {
        ctrl.resetujBazu();
        TableView tableViewGradovi = robot.lookup("#tableViewGradovi").queryAs(TableView.class);
        assertEquals(5, tableViewGradovi.getItems().size());
    }

    /*@Test
    public void testObrisiGrad(FxRobot robot) {
        ctrl.resetujBazu();
        robot.clickOn("Manchester");
        robot.clickOn("#btnObrisiGrad");

        // Čekamo da dijalog postane vidljiv
        robot.lookup(".dialog-pane").tryQuery().isPresent();

        // Klik na dugme Ok
        DialogPane dialogPane = robot.lookup(".dialog-pane").queryAs(DialogPane.class);
        Button okButton = (Button) dialogPane.lookupButton(ButtonType.OK);
        robot.clickOn(okButton);

        // Da li sada ima 4 grada u tableview?
        TableView tableViewGradovi = robot.lookup("#tableViewGradovi").queryAs(TableView.class);
        assertEquals(4, tableViewGradovi.getItems().size());

        // Da li je Manchester obrisan iz baze?
        GeografijaDAO dao = GeografijaDAO.getInstance();
        assertEquals(4, dao.gradovi().size());
    }*/

    @Test
    public void testDodajGrad(FxRobot robot) {
        ctrl.resetujBazu();

        // Otvaranje forme za dodavanje
        robot.clickOn("#btnDodajGrad");

        // Čekamo da dijalog postane vidljiv
        robot.lookup("#fieldNaziv").tryQuery().isPresent();

        // Postoji li fieldNaziv
        robot.clickOn("#fieldNaziv");
        robot.write("Sarajevo");

        robot.clickOn("#fieldBrojStanovnika");
        robot.write("350000");

        // Klik na dugme Ok
        robot.clickOn("#btnOk");

        // Da li je Sarajevo dodano u bazu?
        GeografijaDAO dao = GeografijaDAO.getInstance();
        assertEquals(6, dao.gradovi().size());

        boolean pronadjeno = false;
        for(Grad grad : dao.gradovi())
            if (grad.getNaziv().equals("Sarajevo") && grad.getBrojStanovnika() == 350000)
                pronadjeno = true;
        assertTrue(pronadjeno);
    }

   @Test
    public void testIzmijeniGrad(FxRobot robot) {
        ctrl.resetujBazu();

        // Ovaj test samo provjerava da li se otvara forma za dodavanje grada
        robot.clickOn("Graz");
        robot.clickOn("#btnIzmijeniGrad");

        // Čekamo da dijalog postane vidljiv
        robot.lookup("#fieldNaziv").tryQuery().isPresent();

        // Da li polje Naziv sadrži ispravno ime grada?
        TextField fieldNaziv = robot.lookup("#fieldNaziv").queryAs(TextField.class);
        assertNotNull(fieldNaziv);
        assertEquals("Graz", fieldNaziv.getText());

        // Da li polje broj stanovnika sadrži ispravan broj stanovnika
        TextField fieldBrojStanovnika = robot.lookup("#fieldBrojStanovnika").queryAs(TextField.class);
        assertNotNull(fieldBrojStanovnika);
        assertEquals("280200", fieldBrojStanovnika.getText());

        robot.clickOn("#fieldBrojStanovnika");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("123456");

        // Klik na dugme Ok
        robot.clickOn("#btnOk");

        // Da li je promijenjen broj stanovnika Graza?
        GeografijaDAO dao = GeografijaDAO.getInstance();
        Grad graz = dao.nadjiGrad("Graz");
        assertEquals(123456, graz.getBrojStanovnika());
    }

   /* @Test
    public void testDodajDrzavu(FxRobot robot) {
        ctrl.resetujBazu();

        // Otvaranje forme za dodavanje
        robot.clickOn("#btnDodajDrzavu");

        // Čekamo da dijalog postane vidljiv
        robot.lookup("#fieldNaziv").tryQuery().isPresent();

        // Postoji li fieldNaziv
        robot.clickOn("#fieldNaziv");
        robot.write("Bosna i Hercegovina");

        // Glavni grad će biti automatski izabran kao prvi

        // Klik na dugme Ok
        robot.clickOn("#btnOk");

        // Da li je BiH dodana u bazu?
        GeografijaDAO dao = GeografijaDAO.getInstance();
        assertEquals(4, dao.drzave().size());

        boolean pronadjeno = false;
        for(Drzava drzava : dao.drzave())
            if (drzava.getNaziv().equals("Bosna i Hercegovina"))
                pronadjeno = true;
        assertTrue(pronadjeno);
    }*/
}