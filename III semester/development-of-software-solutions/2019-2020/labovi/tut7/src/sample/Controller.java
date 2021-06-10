package sample;

import javafx.animation.PauseTransition;
import javafx.beans.InvalidationListener;
import javafx.beans.Observable;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.util.Duration;

import java.awt.event.ActionEvent;
import java.net.URL;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class Controller implements Initializable {

    private List<Korisnik> listaKorisnika=new ArrayList<>();

    @FXML
    private Button dugmeDodaj;

    @FXML
    private TextField imeF;
    @FXML
    private TextField prezimeF;
    @FXML
    private TextField emailF;
    @FXML
    private TextField korisnickoImeF;
    @FXML
    private TextField sifraF;

    @FXML
    private ListView<Korisnik> listKorisnici;

    private KorisniciModel model;

    private ArrayList<Korisnik> arejlista;


    public void setArejlista()
    {
        arejlista=new ArrayList<>();
        String tIme="huso", tPrezime="hamzic", tEmail="hhamzic1", tKorisnickoIme="who.so", tSifra="blabla";
        for (int l = 0; l < 4; l++) {
            arejlista.add(new Korisnik(tIme + Integer.toString(l), tPrezime+Integer.toString(l),
                    tEmail+Integer.toString(l), tKorisnickoIme+Integer.toString(l), tSifra+Integer.toString(l)));
        }

    }

    ChangeListener<String> zaIme = new ChangeListener<String>(){
        @Override
        public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
            model.setTrenutniKorisnik(model.getTrenutniKorisnik().getValue());
            if(!t1.equals(model.getTrenutniKorisnik().get().dajImeProperty().get()))
            {
                model.getTrenutniKorisnik().getValue().setIme(t1);
            }
            listKorisnici.refresh();
        }

    };
    ChangeListener<String> zaPrezime = new ChangeListener<String>(){
        @Override
        public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
            model.setTrenutniKorisnik(model.getTrenutniKorisnik().getValue());
            if(!t1.equals(model.getTrenutniKorisnik().get().dajPrezimeProperty().get()))
            {
                model.getTrenutniKorisnik().getValue().setPrezime(t1);
            }
            listKorisnici.refresh();
        }

    };
    ChangeListener<String> zaEmail = new ChangeListener<String>(){
        @Override
        public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
            model.setTrenutniKorisnik(model.getTrenutniKorisnik().getValue());
            if(!t1.equals(model.getTrenutniKorisnik().get().dajEmailProperty().get()))
            {
                model.getTrenutniKorisnik().getValue().setEmail(t1);
            }
            listKorisnici.refresh();
        }

    };

    ChangeListener<String> zaKorisnickoIme = new ChangeListener<String>(){
        @Override
        public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
            model.setTrenutniKorisnik(model.getTrenutniKorisnik().getValue());
            if(!t1.equals(model.getTrenutniKorisnik().get().dajKorisnickoImeProperty().get()))
            {
                model.getTrenutniKorisnik().getValue().setKorisnickoIme(t1);
            }
            listKorisnici.refresh();
        }
    };
    ChangeListener<String> zaSifru;

    {
        zaSifru = new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                model.setTrenutniKorisnik(model.getTrenutniKorisnik().getValue());
                if(!t1.equals(model.getTrenutniKorisnik().get().dajSifruProperty().get()))
                {
                    model.getTrenutniKorisnik().getValue().setSifra(t1);
                }
                listKorisnici.refresh();
            }
        };
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        if(model==null) //prva inicijalizacija svega
        {
            model=new KorisniciModel();
            this.setArejlista();
            model.napuni(arejlista);        //napunimo listView nekim random podacima
            listKorisnici.setItems(model.getKorisnici());
        }
        //dodajemo listenere za svaki textField
        imeF.textProperty().addListener(zaIme);
        prezimeF.textProperty().addListener(zaPrezime);
        emailF.textProperty().addListener(zaEmail);
        korisnickoImeF.textProperty().addListener(zaKorisnickoIme);
        sifraF.textProperty().addListener(zaSifru);
        listKorisnici.refresh();
        //ako se klikne na neku drugu osobu i Listi prebacujemo fokus na njega
        listKorisnici.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<Korisnik>() {
            @Override
            public void changed(ObservableValue<? extends Korisnik> observableValue, Korisnik korisnik, Korisnik t1) {
                model.setTrenutniKorisnik(t1);
                if(t1.dajImeProperty()!=null) imeF.textProperty().setValue(model.getTrenutniKorisnik().get().dajImeProperty().getValue());
                else if(t1.dajImeProperty()==null) imeF.setText("");
                if(t1.dajPrezimeProperty()!=null) prezimeF.textProperty().setValue(model.getTrenutniKorisnik().get().dajPrezimeProperty().getValue());
                else if(t1.dajPrezimeProperty()==null) prezimeF.setText("");
                if(t1.dajEmailProperty()!=null) emailF.textProperty().setValue(model.getTrenutniKorisnik().get().dajEmailProperty().getValue());
                else if(t1.dajEmailProperty()==null) emailF.setText("");
                if(t1.dajKorisnickoImeProperty()!=null) korisnickoImeF.textProperty().setValue(model.getTrenutniKorisnik().get().dajKorisnickoImeProperty().getValue());
                else if(t1.dajKorisnickoImeProperty()==null) korisnickoImeF.setText("");
                if(t1.dajSifruProperty()!=null) sifraF.textProperty().setValue(model.getTrenutniKorisnik().get().dajSifruProperty().getValue());
                else if(t1.dajSifruProperty()==null) sifraF.setText("");
            }
        });

    }


    public void dodajKlik(javafx.event.ActionEvent actionEvent) {

        Korisnik k = new Korisnik("","","","","");
        model.dodajNovogKorisnika(k);
        imeF.setText("");
        prezimeF.setText("");
        emailF.setText("");
        korisnickoImeF.setText("");
        sifraF.setText("");
    }

    public void prekiniProgram(javafx.event.ActionEvent actionEvent) {
        System.exit(0);
    }
}
