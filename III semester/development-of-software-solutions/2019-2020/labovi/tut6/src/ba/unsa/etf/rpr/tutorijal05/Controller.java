package ba.unsa.etf.rpr.tutorijal05;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class Controller {

    @FXML
    private Label rezultat;
    private double broj1;
    private double broj2;
    private String operator = "";
    private boolean start=true;
    private Model model = new Model();
    public void obradiBrojeve(ActionEvent actionEvent) {
        if(start)
        {
            rezultat.setText("");
            start = false;
        }
        String value = ((Button)actionEvent.getSource()).getText();
        rezultat.setText(rezultat.getText() + value);
    }

    @FXML
    public void obradiOperatore(ActionEvent actionEvent) {
        String value = ((Button)actionEvent.getSource()).getText();
        if(!value.equals("="))
        {
            if(!operator.isEmpty()) return;
            operator=value;
            broj1=Double.parseDouble(rezultat.getText());
            System.out.println(broj1);
            rezultat.setText("");
        }
        else
        {
            if(operator.isEmpty()) return;
            broj2=Double.parseDouble(rezultat.getText());
            System.out.println(broj2);
            double ispis = model.izracunaj(broj1, broj2, operator);
            System.out.println(ispis);
            rezultat.setText(String.valueOf(ispis));
            operator="";
            start=true;
        }
    }
}
