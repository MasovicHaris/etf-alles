package ba.unsa.etf.rpr;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.util.ArrayList;

public class Geografija {

    @FXML
    private
    TextField nazivTextField;
    @FXML
    private TextField nazivDrzavePretraga;
    @FXML
    private TextField nazivGradaPretraga;
    @FXML
    private TextField brojStanovnikaPretraga;
    @FXML
    private TextField nazivDrzaveDodavanje;
    @FXML
    private TextField nazivGradaDodavanje;
    @FXML
    private TextField brojStanovnikaDodavanje;

    @FXML
    private Label porukaPretraga;
    @FXML
    private Label porukaDodavanje;

    @FXML
    private ListView ispisView;

    private Drzava tekucaDrzavaPretraga = null;

    GeografijaDAO dao = GeografijaDAO.getInstance();

    @FXML
    public void initialize(){
        nazivDrzavePretraga.editableProperty().setValue(false);

        nazivGradaPretraga.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(tekucaDrzavaPretraga == null) return;
                if(newValue == null || newValue == ""){
                    setPorukaPretraga("Morate unijeti naziv Grada");
                    setNazivGradaPretraga(tekucaDrzavaPretraga.getGlavniGrad().getNaziv());
                }
                setPorukaPretraga("");
                tekucaDrzavaPretraga.getGlavniGrad().setNaziv(getNazivGradaPretraga());
                dao.izmijeniGrad(tekucaDrzavaPretraga.getGlavniGrad());
                setPorukaPretraga("Naziv grada je izmijenjen");
            }
        });
        brojStanovnikaPretraga.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if(tekucaDrzavaPretraga == null) return;
                if(newValue == null || newValue == ""){
                    setPorukaPretraga("Morate unijeti broj stanovnika");
                    setBrojStanovnikaPretraga(Integer.toString(tekucaDrzavaPretraga.getGlavniGrad().getBrojStanovnika()));
                }
                setPorukaPretraga("");
                tekucaDrzavaPretraga.getGlavniGrad().setBrojStanovnika(Integer.parseInt(getBrojStanovnikaPretraga()));
                dao.izmijeniGrad(tekucaDrzavaPretraga.getGlavniGrad());
                setPorukaPretraga("Broj stanovnika grada je izmijenjen");
            }
        });
    }


    public void nadjiDrzavuClicked(ActionEvent actionEvent) {
        if(getNazivTextField().equals("")){
            setPorukaPretraga("Unesite naziv drzave");
            return;
        }
        Drzava d = dao.nadjiDrzavu(getNazivTextField());
        if(d == null) {
            setNazivDrzavePretraga("");
            setNazivGradaPretraga("");
            setBrojStanovnikaPretraga("");
            setPorukaPretraga("Drzva ne postoji");
            return;
        }
        setPorukaPretraga("");
        tekucaDrzavaPretraga = d;
        tekucaDrzavaPretraga.setGlavniGrad(d.getGlavniGrad());
        setNazivDrzavePretraga(d.getNaziv());
        setNazivGradaPretraga(d.getGlavniGrad().getNaziv());
        setBrojStanovnikaPretraga(Integer.toString(d.getGlavniGrad().getBrojStanovnika()));
        setPorukaPretraga("Pretraga je gotova");
    }

    public void dodajClicked(ActionEvent actionEvent) {
        if(getNazivDrzaveDodavanje().isEmpty() || getNazivGradaDodavanje().isEmpty() || getBrojStanovnikaDodavanje().isEmpty()){
            setPorukaDodavanje("Potrebno je da se popune sva polja");
            return;
        }
        setPorukaDodavanje("");
        Drzava d = new Drzava(getNazivDrzaveDodavanje(), null);
        Grad g = new Grad(getNazivGradaDodavanje(), Integer.parseInt(getBrojStanovnikaDodavanje()), d);
        d.setGlavniGrad(g);
        dao.dodajDrzavu(d);
        setNazivDrzaveDodavanje("");
        setNazivGradaDodavanje("");
        setBrojStanovnikaDodavanje("");
        setPorukaDodavanje("Drzava je dodana");
    }

    public void obrisiDrzavuClicked(ActionEvent actionEvent) {
        if(getNazivDrzaveDodavanje() == null || getNazivDrzaveDodavanje().isEmpty()){
            setPorukaDodavanje("Morate unijeti naziv drzave");
            return;
        }
        setPorukaDodavanje("");
        dao.obrisiDrzavu(getNazivDrzaveDodavanje());
        setPorukaDodavanje("Drzava je obrisana");
    }

    public void ispisi(){
        ObservableList<String> gradovi = FXCollections.observableArrayList();
        ArrayList<Grad> gi = dao.gradovi();
        for(Grad g: gi){
            gradovi.add(g.toString());
        }
        setIspisArea(gradovi);
    }



    public String getNazivTextField() {
        return nazivTextField.textProperty().get();
    }

    public void setNazivTextField(String value){
        this.nazivTextField.textProperty().setValue(value);
    }


    public String getNazivDrzavePretraga() {
        return nazivDrzavePretraga.textProperty().get();
    }

    public void setNazivDrzavePretraga(String value) {
        this.nazivDrzavePretraga.textProperty().setValue(value);
    }

    public String getNazivGradaPretraga() {
        return nazivGradaPretraga.textProperty().get();
    }

    public void setNazivGradaPretraga(String value) {
        this.nazivGradaPretraga.textProperty().setValue(value);
    }

    public String getBrojStanovnikaPretraga() {
        return brojStanovnikaPretraga.textProperty().get();
    }

    public void setBrojStanovnikaPretraga(String value) {
        this.brojStanovnikaPretraga.textProperty().setValue(value);
    }

    public String getNazivDrzaveDodavanje() {
        return nazivDrzaveDodavanje.textProperty().get();
    }

    public void setNazivDrzaveDodavanje(String value) {
        this.nazivDrzaveDodavanje.textProperty().setValue(value);
    }

    public String getNazivGradaDodavanje() {
        return nazivGradaDodavanje.textProperty().get();
    }

    public void setNazivGradaDodavanje(String value) {
        this.nazivGradaDodavanje.textProperty().setValue(value);
    }

    public String getBrojStanovnikaDodavanje() {
        return brojStanovnikaDodavanje.textProperty().get();
    }

    public void setBrojStanovnikaDodavanje(String value) {
        this.brojStanovnikaDodavanje.textProperty().setValue(value);
    }

    public void setPorukaPretraga(String value) {
        this.porukaPretraga.textProperty().setValue(value);
    }

    public void setPorukaDodavanje(String value) {
        this.porukaDodavanje.textProperty().setValue(value);
    }

    public ListView getIspisArea() {
        return ispisView;
    }

    public void setIspisArea(ObservableList<String> value) {
        this.ispisView.itemsProperty().setValue(value);
    }

}
