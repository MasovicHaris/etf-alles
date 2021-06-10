package ba.unsa.etf.rpr;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.Scanner;

import static javafx.scene.layout.Region.USE_COMPUTED_SIZE;

public class Main extends Application {

    public static String ispisiGradove(){
        GeografijaDAO dao = GeografijaDAO.getInstance();
        ArrayList<Grad> gradovi = dao.gradovi();
        String rez = "";
        if(gradovi!=null) {
            for (Grad g : gradovi) {
                rez += g.getNaziv() + " (" + g.getDrzava().getNaziv() + ")" + " - " + g.getBrojStanovnika() + "\n";
            }
        }
        return rez;
    }

    public static void glavniGrad(){
        GeografijaDAO dao = GeografijaDAO.getInstance();
        Scanner ulaz = new Scanner(System.in);
        System.out.print("Unesite naziv države : ");
        String nazivDrzave=ulaz.nextLine();
        Drzava drzava = dao.nadjiDrzavu(nazivDrzave);
        if(drzava!=null) {
            System.out.printf("\nGlavni grad države " + drzava.getNaziv() + " je " + drzava.getGlavniGrad().getNaziv());
            return;
        }
        System.out.print("\nNepostojeća država");
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader ldr = new FXMLLoader(getClass().getResource("/fxml/glavna.fxml")); //loadaj fxml fajl
        GlavnaController gc = new GlavnaController();
        ldr.setController(gc);    //setupaj određeni kontroler koji će ga kontrolisati
        Parent p =(Parent) ldr.load();  //učitaj elemente (parent je gridpane)
        Scene s = new Scene(p);     //postavi scenu
        primaryStage.setTitle("Gradovi svijeta");
        primaryStage.setScene(s);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
