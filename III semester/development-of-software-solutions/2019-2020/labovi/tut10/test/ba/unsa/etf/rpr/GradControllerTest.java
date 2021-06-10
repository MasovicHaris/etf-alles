package ba.unsa.etf.rpr;

import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
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

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;
import static org.junit.jupiter.api.Assertions.*;


@ExtendWith(ApplicationExtension.class)
class GradControllerTest {
    Stage theStage;
    GradController ctrl;

    @Start
    public void start (Stage stage) throws Exception {
        // Brisemo bazu za slucaj da su prethodni testovi kreirali/brisali drzave
        GeografijaDAO.removeInstance();
        File dbfile = new File("baza.db");
        dbfile.delete();
        GeografijaDAO dao = GeografijaDAO.getInstance();

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/grad.fxml"));
        ctrl = new GradController(null, dao.drzave());
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
    public void testValidacijaGrada(FxRobot robot) {
        // Klik na dugme ok
        robot.clickOn("#btnOk");

        // Polje fieldNaziv je nevalidno jer je prazno
        TextField ime = robot.lookup("#fieldNaziv").queryAs(TextField.class);
        Background bg = ime.getBackground();
        boolean colorFound = false;
        for (BackgroundFill bf : bg.getFills())
            if (bf.getFill().toString().contains("ffb6c1"))
                colorFound = true;
        assertTrue(colorFound);

        // Upisujemo grad
        robot.clickOn("#fieldNaziv");
        robot.write("Sarajevo");
        robot.clickOn("#fieldBrojStanovnika");
        robot.write("-15");

        // Klik na dugme ok
        robot.clickOn("#btnOk");

        // Sada je naziv validan
        ime = robot.lookup("#fieldNaziv").queryAs(TextField.class);
        bg = ime.getBackground();
        colorFound = false;
        for (BackgroundFill bf : bg.getFills())
            if (bf.getFill().toString().contains("adff2f"))
                colorFound = true;
        assertTrue(colorFound);

        // Polje fieldBrojStanovnika je nevalidno jer je broj negativan
        TextField brojStanovnika = robot.lookup("#fieldBrojStanovnika").queryAs(TextField.class);
        bg = brojStanovnika.getBackground();
        colorFound = false;
        for (BackgroundFill bf : bg.getFills())
            if (bf.getFill().toString().contains("ffb6c1"))
                colorFound = true;
        assertTrue(colorFound);

        // Upisujemo validan broj stanovnika
        robot.clickOn("#fieldBrojStanovnika");
        robot.press(KeyCode.CONTROL).press(KeyCode.A).release(KeyCode.A).release(KeyCode.CONTROL);
        robot.write("350000");

        // Klik na dugme ok
        robot.clickOn("#btnOk");

        // Sada je i broj stanovnika validan, forma se zatvorila
        assertFalse(theStage.isShowing());
    }

    @Test
    public void testVracanjeGrada(FxRobot robot) {
        // Upisujemo grad
        robot.clickOn("#fieldNaziv");
        robot.write("Sarajevo");
        robot.clickOn("#fieldBrojStanovnika");
        robot.write("350000");
        robot.clickOn("#choiceDrzava");
        robot.clickOn("Francuska");

        // Klik na dugme ok
        robot.clickOn("#btnOk");

        Grad sarajevo = ctrl.getGrad();
        assertEquals("Sarajevo", sarajevo.getNaziv());
        assertEquals(350000, sarajevo.getBrojStanovnika());
        assertEquals("Francuska", sarajevo.getDrzava().getNaziv());

    }
}