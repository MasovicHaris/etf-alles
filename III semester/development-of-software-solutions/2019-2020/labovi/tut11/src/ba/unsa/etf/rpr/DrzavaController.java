package ba.unsa.etf.rpr;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class DrzavaController implements Initializable {

    @FXML
    private Button btnCancel;

    @FXML
    private Button btnOk;

    @FXML
    TextField fieldNaziv;

    @FXML
    ChoiceBox<Grad> choiceGrad;

    public Drzava dr = null;

    ObservableList<Grad> gradevi = FXCollections.observableArrayList();

    public DrzavaController(Grad g, ArrayList<Grad> temp)
    {
        gradevi.addAll(temp);
    }

    public void CancelKlik(ActionEvent event){
        Stage stage = (Stage) btnCancel.getScene().getWindow(); //nadje objekat na ekranu i zatvori ga!
        stage.close();
    }



    public void okKlik(ActionEvent event){
        Stage stage = (Stage) btnOk.getScene().getWindow(); //uzme stejdž na kom se nalazi dugme Ok

        if (fieldNaziv.getText().equals("")) {
            fieldNaziv.getStyleClass().removeAll("poljeIspravno");
            fieldNaziv.getStyleClass().add("poljeNijeIspravno");
        } else {
            fieldNaziv.getStyleClass().removeAll("poljeNijeIspravno");
            fieldNaziv.getStyleClass().add("poljeIspravno");
            dr = new Drzava(0, fieldNaziv.getText(), choiceGrad.getSelectionModel().getSelectedItem());
            stage.close();
        }

    }

    public Drzava getDrzava(){
        return dr;
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        choiceGrad.setItems(this.gradevi);
        choiceGrad.getSelectionModel().selectFirst();
    }
}
