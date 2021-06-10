package ba.unsa.etf.rpr;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import net.sf.jasperreports.engine.JRException;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.ResourceBundle;

public class GeografijaController {

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

    @FXML
    private BorderPane borderPane;

    private Drzava tekucaDrzavaPretraga = null;

    GeografijaDAO dao = GeografijaDAO.getInstance();

    @FXML
    public void initialize() {
        nazivDrzavePretraga.editableProperty().setValue(false);

        nazivGradaPretraga.textProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
                if (tekucaDrzavaPretraga == null) return;
                if (newValue == null || newValue == "") {
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
                if (tekucaDrzavaPretraga == null) return;
                if (newValue == null || newValue == "") {
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
        if (getNazivTextField().equals("")) {
            setPorukaPretraga("Unesite naziv drzave");
            return;
        }
        Drzava d = dao.nadjiDrzavu(getNazivTextField());
        if (d == null) {
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
        if (getNazivDrzaveDodavanje().isEmpty() || getNazivGradaDodavanje().isEmpty() || getBrojStanovnikaDodavanje().isEmpty()) {
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
        if (getNazivDrzaveDodavanje() == null || getNazivDrzaveDodavanje().isEmpty()) {
            setPorukaDodavanje("Morate unijeti naziv drzave");
            return;
        }
        setPorukaDodavanje("");
        dao.obrisiDrzavu(getNazivDrzaveDodavanje());
        setPorukaDodavanje("Drzava je obrisana");
    }

    public void ispisi() {
        ObservableList<String> gradovi = FXCollections.observableArrayList();
        ArrayList<Grad> gi = dao.gradovi();
        for (Grad g : gi) {
            gradovi.add(g.toString());
        }
        setIspisArea(gradovi);
        Main.stampajGradove();
    }


    private void selectLanguage(Locale locale) {
        Stage primaryStage = (Stage) borderPane.getScene().getWindow();
        Locale.setDefault(locale);
        ResourceBundle bundle = ResourceBundle.getBundle("translation");
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/geografija.fxml"), bundle);
        Parent root = null;
        try {
            root = loader.load();
        } catch (IOException e) {
            System.out.println(e.getMessage());
            return;
        }
        primaryStage.setScene(new Scene(root, 600, 410));
        primaryStage.setMinWidth(600);
        primaryStage.setMinHeight(450);
        primaryStage.setMaxHeight(450);
        primaryStage.setMaxWidth(600);
        primaryStage.show();
    }

    public void bosanskiClicked(ActionEvent actionEvent) {
        selectLanguage(new Locale("bs", "BA"));
    }

    public void engleskiClicked(ActionEvent actionEvent) {
        selectLanguage(new Locale("en", "US"));
    }

    public void njemackiClicked(ActionEvent actionEvent) {
        selectLanguage(new Locale("de", "DE"));
    }

    public void francuskiClicked(ActionEvent actionEvent) {
        selectLanguage(new Locale("fr", "FR"));
    }


    public String getNazivTextField() {
        return nazivTextField.textProperty().get();
    }

    public void setNazivTextField(String value) {
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

    private void doSave(File datoteka) {
        try {
            new GradoviReport().saveAs(datoteka.getAbsolutePath(), GeografijaDAO.getInstance().getConnection());
        } catch (Exception e) {
            System.out.println( e.getMessage() );
        }
    }

    public void saveAs(ActionEvent event) {
        FileChooser fc = new FileChooser();
        FileChooser.ExtensionFilter xslmExtenizija = new FileChooser.ExtensionFilter("XSLX", "*.xslx");
        fc.getExtensionFilters().add( xslmExtenizija );
        FileChooser.ExtensionFilter docxExtenzija = new FileChooser.ExtensionFilter("DOCX", "*.docx");
        fc.getExtensionFilters().add( docxExtenzija );
        FileChooser.ExtensionFilter pdfExtenzija = new FileChooser.ExtensionFilter("PDF", "*.pdf");
        fc.getExtensionFilters().add( pdfExtenzija );
        fc.setTitle("SAVING A REPORT");
        File selectedFile = fc.showSaveDialog(null);

        //Ako ne odaberemo nista, nista se i ne desi.
        if (selectedFile != null)
            doSave(selectedFile);
    }

    @FXML
    private TextField nazivDrzave;

    public void ispisiZaDrzavu(ActionEvent event) {
        if(nazivDrzave.textProperty().get().isEmpty()) return;
        Drzava d = GeografijaDAO.getInstance().nadjiDrzavu(nazivDrzave.textProperty().get());
        if(d == null) return;
        try {
            new GradoviReport().showForState(GeografijaDAO.getInstance().getConnection(), d);
        } catch (JRException e1) {
            e1.printStackTrace();
        }
    }
}
