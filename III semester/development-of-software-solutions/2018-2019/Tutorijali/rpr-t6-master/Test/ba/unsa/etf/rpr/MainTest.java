package ba.unsa.etf.rpr;

import static javafx.scene.input.KeyCode.BACK_SPACE;
import static javafx.scene.input.KeyCode.ENTER;
import static org.junit.jupiter.api.Assertions.*;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;
import javafx.scene.text.TextFlow;
import javafx.stage.Stage;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.testfx.api.FxRobot;
import org.testfx.framework.junit5.ApplicationExtension;
import org.testfx.framework.junit5.Start;

@ExtendWith(ApplicationExtension.class)
class MainTest {

    public static final String POLJE_NIJE_ISPRAVNO = "poljeNijeIspravno";
    public static final String POLJE_ISPRAVNO = "poljeIspravno";
    private Label display;
    private TextField textField = null;

    @Start
    public void start (Stage stage) throws Exception {
        Parent mainNode = FXMLLoader.load(Main.class.getResource("sample.fxml"));
        stage.setScene(new Scene(mainNode));
        stage.show();
        stage.toFront();
    }

    @Test
    public void osnovniPodaciTest(FxRobot robot){
        TextField imeTextField, prezimeTextField, brojIndexaTextField;
        imeTextField = robot.lookup("#imeTextField").queryAs(TextField.class);
        prezimeTextField = robot.lookup("#prezimeTextField").queryAs(TextField.class);
        brojIndexaTextField = robot.lookup("#brojIndexaTextField").queryAs(TextField.class);
        robot.clickOn(imeTextField);
        robot.write("124235245");
        robot.clickOn(prezimeTextField);
        robot.write("124235245000000000000");
        robot.clickOn(brojIndexaTextField);
        robot.write("178251");
        assertAll(
                ()->assertEquals(true, imeTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO)),
                ()->assertEquals(true, prezimeTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO)),
                ()->assertEquals(true, brojIndexaTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO))
        );
        robot.clickOn(imeTextField);
        robot.write("Nermin");
        robot.clickOn(prezimeTextField);
        robot.type(BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE);
        robot.write("K");
        robot.clickOn(brojIndexaTextField);
        robot.type(BACK_SPACE);
        assertAll(
                ()->assertEquals(true, imeTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO)),
                ()->assertEquals(true, prezimeTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO)),
                ()->assertEquals(true, brojIndexaTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO))
        );
    }

    @Test
    public void detaljniLicniPodaci(FxRobot robot){
        TextField jmbgTextField;
        DatePicker datumDatePicker;
        jmbgTextField = robot.lookup("#jmbgTextField").queryAs(TextField.class);
        datumDatePicker = robot.lookup("#datumDatePicker").queryAs(DatePicker.class);
        robot.clickOn(jmbgTextField);
        robot.write("2105997170095");
        assertEquals(true, jmbgTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO));
        robot.clickOn(datumDatePicker);
        robot.write("5/21/1997");
        robot.type(ENTER);
        assertEquals(true, jmbgTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO));
    }

    @Test
    public void kontaktPodaci(FxRobot robot){
        TextField kontaktTelefonTextField;
        TextField emailAdresaTextField;
        kontaktTelefonTextField = robot.lookup("#kontaktTelefonTextField").queryAs(TextField.class);
        emailAdresaTextField = robot.lookup("#emailAdresaTextField").queryAs(TextField.class);
        robot.clickOn(kontaktTelefonTextField);
        robot.write("06033615");
        assertEquals(true, kontaktTelefonTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO));
        robot.write("610");
        assertEquals(true, kontaktTelefonTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO));
        robot.type(BACK_SPACE);
        robot.clickOn(emailAdresaTextField);
        robot.write("nkrdzic1@etf.unsa");
        assertEquals(true, emailAdresaTextField.getStyleClass().toString().contains(POLJE_NIJE_ISPRAVNO));
        robot.write(".ba");
        assertAll(
                () -> assertEquals(true, kontaktTelefonTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO)),
                () -> assertEquals(true, emailAdresaTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO))
        );
        robot.type(BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE);
        robot.write("hotmail.com");
        assertEquals(true, emailAdresaTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO));
        robot.type(BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE);
        robot.write("gmail.com");
        assertEquals(true, emailAdresaTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO));
        robot.type(BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE, BACK_SPACE);
        robot.write("outlook.com");
        assertEquals(true, emailAdresaTextField.getStyleClass().toString().contains(POLJE_ISPRAVNO));
    }


}