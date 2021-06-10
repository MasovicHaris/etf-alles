package ba.unsa.etf.rpr;

import javafx.beans.Observable;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import net.sf.jasperreports.engine.JRException;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.URL;
import java.util.*;

public class GlavnaController implements Initializable {

    private GeografijaDAO dao = GeografijaDAO.getInstance();



    @FXML
    public TableView<Grad> tableViewGradovi;
    public TableColumn colGradId;
    public TableColumn colGradNaziv;
    public TableColumn colGradStanovnika;
    public TableColumn colGradDrzava;
    public Button btnDodajGrad;
    public Button stampa;
    public Button jezikBiraj;

    public Grad trenGrad;



    public void dodajGradKlik(ActionEvent event) throws IOException {
        ResourceBundle bundle = ResourceBundle.getBundle("Translation");
        FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/grad.fxml"), bundle); //loadaj fxml fajl
        GradController gc = new GradController(null, dao.drzave());
        ldr.setController(gc);    //setupaj određeni kontroler koji će ga kontrolisati
        Parent p =(Parent) ldr.load();  //učitaj elemente (parent je gridpane)
        Scene s = new Scene(p);     //postavi scenu
        Stage prozor = new Stage(); //postavi pozornicu
        prozor.setTitle("Grad");
        prozor.setScene(s);
        prozor.setOnHiding(ev -> {
            Grad noviGrad = gc.getGrad();
            if(noviGrad==null){
                System.out.println("Prazan grad");
            }
            else{
                dao.dodajGrad(noviGrad);
                System.out.println(noviGrad);
                ArrayList<Grad> t=dao.gradovi();
                tableViewGradovi.setItems(dao.dajObservableGradove());
                tableViewGradovi.refresh();
            }
        });
        prozor.show();  //prikazi pozornicu
    }

    public void izmijeniGradKlik(ActionEvent event) throws IOException {
        this.trenGrad= tableViewGradovi.getSelectionModel().getSelectedItem();
        if(trenGrad!=null){
            ResourceBundle bundle = ResourceBundle.getBundle("Translation");
            FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/grad.fxml"), bundle); //loadaj fxml fajl
            GradController gc = new GradController(trenGrad, dao.drzave());
            ldr.setController(gc);    //setupaj određeni kontroler koji će ga kontrolisati
            Parent p = ldr.load();
            Scene s = new Scene(p);
            Stage prozor = new Stage();
            prozor.setTitle("Grad");
            prozor.setScene(s);
            prozor.setOnHiding(ev -> { //kako bi mogli preuzet grad nad kojim smo radili u GradControlleru
                Grad noviGrad = gc.getGrad();
                if(noviGrad==null){
                    System.out.println("Prazan grad");
                }
                else{
                    dao.izmijeniGrad(noviGrad);
                    System.out.println(noviGrad);
                    tableViewGradovi.getItems().clear();
                    ArrayList<Grad> t=dao.gradovi();
                    tableViewGradovi.setItems(dao.dajObservableGradove());
                    tableViewGradovi.refresh();
                }
            });
            prozor.show();
        }
        else {
            System.out.println("Niste odabrali nijedan grad");
        }

    }
    public void birajJezikAction(ActionEvent event)
    {
        List<String> choices = new ArrayList<>();
        choices.add("English");
        choices.add("Deutsch");
        choices.add("French");
        choices.add("Bosnian");

        ChoiceDialog<String> dialog = new ChoiceDialog<>("English", choices);
        dialog.setTitle("Choosing language");
        dialog.setHeaderText("Look, a Choice Dialog");
        dialog.setContentText("Choose your language:");

// Traditional way to get the response value.
        Optional<String> result = dialog.showAndWait();
        if (result.isPresent()){
            if(result.get().equals("English"))
            {
                Locale.setDefault(new Locale("en", "US"));
            }
            else if(result.get().equals("Deutsch"))
            {
                Locale.setDefault(new Locale("de", "DE"));
            }
            else if(result.get().equals("French"))
            {
                Locale.setDefault(new Locale("fr", "FRA"));
            }
            else
            {
                Locale.setDefault(new Locale("bs", "BA"));
            }
        }

        restartJezik();

    }
    public void dodajDrzavuKlik(ActionEvent event) throws IOException {
        ResourceBundle bundle = ResourceBundle.getBundle("Translation");
        FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/drzava.fxml"), bundle); //loadaj fxml fajl
        DrzavaController dc = new DrzavaController(null, dao.gradovi());
        ldr.setController(dc);    //setupaj određeni kontroler koji će ga kontrolisati
        Parent p = ldr.load();
        Scene s = new Scene(p);
        Stage prozor = new Stage();
        prozor.setTitle("Države");
        prozor.setScene(s);
        prozor.setOnHiding(ev -> {
            Drzava nDrzava = dc.getDrzava();
            if(nDrzava==null){
                System.out.println("Prazna drzava");
            }
            else{
                dao.dodajDrzavu(nDrzava);
                System.out.println(nDrzava);
            }
        });
        prozor.show();
    }


    public void obrisiGradKlik(ActionEvent event){
        Grad g = tableViewGradovi.getSelectionModel().getSelectedItem();
        if(g!=null){
            Alert alert = new Alert(Alert.AlertType.WARNING);//kreira alert window sto iskoci
            alert.setTitle("UPOZORENJE");
            alert.setHeaderText("Pažnja");
            alert.setContentText("Da li ste sigurni da želite obrisati odabrani grad?!");
            alert.setOnCloseRequest(new EventHandler<DialogEvent>() { //moramo skontat sta je korisnik pritisnuo kad mu je alert iskocio
                @Override
                public void handle(DialogEvent event) {
                    ButtonType result=alert.getResult();
                    if(result==null) alert.close(); //ako je x-irao to znaci da ce result biti null pa necemo nista uradit
                    else {
                        String resultText = result.getText();   //ako je pritisnuo OK , onda se i ime dugmeta mora poklapati sa "OK"
                        if (resultText.equals("OK")) {
                            dao.obrisiGrad(g);//Pozovi dao.obrisiGrad
                            ArrayList<Grad> bezze = dao.gradovi();  //moja glupava izvedba, sluzi samo da bi mogao pozvati dajObservableGradove
                            tableViewGradovi.setItems(dao.dajObservableGradove()); //setupaj opet sve kako bi se moglo refreshati
                            tableViewGradovi.refresh();
                            alert.close(); //ugasi alert
                        }
                    }
                }
            });
            alert.show();
        }//else do nothing
    }

    // Metoda za potrebe testova, vraća bazu u polazno stanje
    public void resetujBazu() {
        GeografijaDAO.removeInstance();
        File dbfile = new File("baza.db");
        dbfile.delete();
        dao = GeografijaDAO.getInstance();
    }

    public void stampaAction(ActionEvent event)
    {
        try {
            new GradoviReport().showReport(dao.dajKonekciju());
        } catch (JRException e1) {
            e1.printStackTrace();
        }
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        colGradId.setCellValueFactory(
                new PropertyValueFactory<Grad,Integer>("id"));
        colGradNaziv.setCellValueFactory(
                new PropertyValueFactory<Grad,String>("naziv"));

        colGradStanovnika.setCellValueFactory(
                new PropertyValueFactory<Grad,Integer>("brojStanovnika"));
        colGradDrzava.setCellValueFactory(
                new PropertyValueFactory<Grad,String>("drzava"));

        ArrayList<Grad> t=dao.gradovi();
        tableViewGradovi.setItems(dao.dajObservableGradove());
        tableViewGradovi.refresh();

        tableViewGradovi.getSelectionModel().selectedItemProperty().addListener((obs, oldValue, newValue) ->{ //da se refrešuje lista!
            this.trenGrad=newValue;
        });

    }


    private void restartJezik(){
        ResourceBundle bundle = ResourceBundle.getBundle("Translation");
        Stage scene = (Stage) tableViewGradovi.getScene().getWindow();
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/fxml/glavna.fxml"), bundle);
        loader.setController(this);
        try {
            scene.setScene(new Scene(loader.load()));
        } catch (IOException e) {
            e.printStackTrace();
        }

    }




}
