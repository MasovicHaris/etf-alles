package ba.unsa.etf.rpr;

import javafx.beans.Observable;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.util.converter.NumberStringConverter;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class GradController implements Initializable{

    private ObservableList<String> drzave = FXCollections.observableArrayList();

    @FXML
    private Button btnCancel;

    @FXML
    private Button btnOk;

    @FXML
    TextField fieldNaziv;

    @FXML
    TextField fieldBrojStanovnika;

    @FXML
    ChoiceBox<Drzava> choiceDrzava;

    public Grad tempGrad;
    public Grad trenutniG;


    private ObservableList<Drzava> drzaveSve = FXCollections.observableArrayList();

    public GradController(Grad grad, ObservableList<Drzava> drzave) { //kako bi mogo primit choicebox spisak država, a u fxml fajlu izbrisati kontroler!
        this.drzaveSve=drzave;
        this.trenutniG=grad;
    }



    public void CancelKlik(ActionEvent event){
        Stage stage = (Stage) btnCancel.getScene().getWindow(); //nadje objekat na ekranu i zatvori ga!
        this.tempGrad=null;
        stage.close();

    }

    public void okKlik(ActionEvent event){ //ovo radi
        if(trenutniG==null){ //malo ruzno ali radi haha, ima ponavljanja koda :(
            Stage stage = (Stage) btnOk.getScene().getWindow(); //uzme stejdž na kom se nalazi dugme Ok
            boolean nazivCheck = false;
            boolean brojCheck = false;
            Integer br = 1;
            if (fieldNaziv.getText().equals("")) {
                fieldNaziv.getStyleClass().removeAll("poljeIspravno");
                fieldNaziv.getStyleClass().add("poljeNijeIspravno");
            } else {
                fieldNaziv.getStyleClass().removeAll("poljeNijeIspravno");
                fieldNaziv.getStyleClass().add("poljeIspravno");
                nazivCheck = true;
            }
            try {
                br = Integer.parseInt(fieldBrojStanovnika.getText());
                if (br > 0) {
                    fieldBrojStanovnika.getStyleClass().removeAll("poljeNijeIspravno");
                    fieldBrojStanovnika.getStyleClass().add("poljeIspravno");
                    brojCheck = true;
                } else {
                    fieldBrojStanovnika.getStyleClass().removeAll("poljeIspravno");
                    fieldBrojStanovnika.getStyleClass().add("poljeNijeIspravno");
                }
            } catch (NumberFormatException e) {
                fieldBrojStanovnika.getStyleClass().removeAll("poljeIspravno");
                fieldBrojStanovnika.getStyleClass().add("poljeNijeIspravno");
            }

            if (brojCheck && nazivCheck && choiceDrzava.getSelectionModel().getSelectedItem() != null) {
                Grad tempG = new Grad(0, fieldNaziv.getText(), br, null);
                Drzava d = new Drzava(choiceDrzava.getSelectionModel().getSelectedItem().getId(), choiceDrzava.getSelectionModel().getSelectedItem().getNaziv(), null); //kasnije cemo saznat glavni grad
                tempG.setDrzava(d);
                this.tempGrad = tempG;
                stage.close();
            }
            else {
                this.tempGrad = null;
            }
        }
        else //izmjena
        {
            Stage stage = (Stage) btnOk.getScene().getWindow(); //uzme stejdž na kom se nalazi dugme Ok
            boolean nazivCheck = false;
            boolean brojCheck = false;
            Integer br = 1;
            if (fieldNaziv.getText().equals("")) {
                fieldNaziv.getStyleClass().removeAll("poljeIspravno");
                fieldNaziv.getStyleClass().add("poljeNijeIspravno");
            } else {
                fieldNaziv.getStyleClass().removeAll("poljeNijeIspravno");
                fieldNaziv.getStyleClass().add("poljeIspravno");
                nazivCheck = true;
            }
            try {
                br = Integer.parseInt(fieldBrojStanovnika.getText());
                if (br > 0) {
                    fieldBrojStanovnika.getStyleClass().removeAll("poljeNijeIspravno");
                    fieldBrojStanovnika.getStyleClass().add("poljeIspravno");
                    brojCheck = true;
                } else {
                    fieldBrojStanovnika.getStyleClass().removeAll("poljeIspravno");
                    fieldBrojStanovnika.getStyleClass().add("poljeNijeIspravno");
                }
            } catch (NumberFormatException e) {
                fieldBrojStanovnika.getStyleClass().removeAll("poljeIspravno");
                fieldBrojStanovnika.getStyleClass().add("poljeNijeIspravno");
            }

            if (brojCheck && nazivCheck && choiceDrzava.getSelectionModel().getSelectedItem() != null) {
                trenutniG.setNaziv(fieldNaziv.getText());
                trenutniG.setBrojStanovnika(br);
                Drzava d = new Drzava(choiceDrzava.getSelectionModel().getSelectedItem().getId(), choiceDrzava.getSelectionModel().getSelectedItem().getNaziv(), null); //kasnije cemo saznat glavni grad
                trenutniG.setDrzava(d);
                this.tempGrad = trenutniG;
                stage.close();
            }
            this.tempGrad = null;
            stage.close();
        }

    }


    public Grad getGrad(){ //Ona metoda getGrad sto ce se setOnHiding pozvat
        return  this.tempGrad;
    }
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        if(trenutniG==null) {
            choiceDrzava.setItems(drzaveSve);
            choiceDrzava.getSelectionModel().selectFirst();
        }
        else
        {
            fieldNaziv.setText(trenutniG.getNaziv());
            choiceDrzava.setItems(drzaveSve);
            choiceDrzava.getSelectionModel().select(trenutniG.getDrzava().getId()-1); //mora -1 jer indeksacija ide od 0 kako bi selektovao drzavu
            fieldBrojStanovnika.setText(String.valueOf(trenutniG.getBrojStanovnika()));
        }
    }
}
