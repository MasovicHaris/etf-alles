package ba.unsa.etf.rpr.tutorijal05;

import javafx.beans.property.SimpleStringProperty;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Text;

import java.awt.*;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class Controller {

    public static final Double DEFAULT_DIVIDER = 0.1;
    private SimpleStringProperty output;

    public SimpleStringProperty outputProperty(){ return output; }
    public String getOutput() {
        return Double.toString(Double.parseDouble(output.getValue()));
    }

    private Integer numberClicked = -1;
    private Double previousNumber = 0.;
    private Double divider = DEFAULT_DIVIDER;
    String operation = null;
    private boolean dot = false;

    public Controller(){
        output = new SimpleStringProperty("0");
    }
    private boolean doesntContainDecimals(){
        Double number = Double.parseDouble(output.get());
        return (number - round(number, 0) == 0);
    }
    private static double round(double value, int places) {
        if (places < 0) throw new IllegalArgumentException();

        BigDecimal bd = new BigDecimal(Double.toString(value));
        bd = bd.setScale(places, RoundingMode.HALF_UP);
        return bd.doubleValue();
    }

    private void writeNumber(){
        if(numberClicked != -1){
            if(dot) {
                if(divider == 0.001) return;
                output.set(Double.toString(round(Double.parseDouble(getOutput()) + numberClicked * divider, 2)));
                divider /= 10;
            }
            else output.set(Double.toString(round((Double.parseDouble(getOutput()) * 10) + numberClicked, 2)));
        }
        numberClicked = -1;
    }
    private void executeOperation(){
        if (operation == null) {
            previousNumber = Double.parseDouble(getOutput());
            output.set("0");
            dot = false;
            divider = DEFAULT_DIVIDER;
            numberClicked = -1;
            return;
        }
        switch (operation){
            case "%":
                previousNumber = previousNumber  % Double.parseDouble(getOutput());
                break;
            case "/":
                previousNumber = previousNumber / Double.parseDouble(getOutput());
                break;
            case "X":
                previousNumber = previousNumber * Double.parseDouble(getOutput());
                break;
            case "-":
                previousNumber = previousNumber - Double.parseDouble(getOutput());
                break;
            case "+":
                previousNumber = previousNumber + Double.parseDouble(getOutput());
                break;
        }
        dot= false;
        divider = DEFAULT_DIVIDER;
        operation = null;
        numberClicked = -1;
        output.set("0");
    }

    private void reset(){
        if (operation == null) return;
        if(operation.equals("=")){
            output.set("0");
            operation = null;
            previousNumber = 0.;
        }
    }

    public void moduleClicked() {
        executeOperation();
        operation = "%";
    }

    public void divideClicked() {
        executeOperation();
        operation= "/";
    }

    public void multiplyClicked() {
        executeOperation();
        operation= "X";
    }

    public void minusClicked() {
        executeOperation();
        operation= "-";
    }

    public void plusClicked() {
        executeOperation();
        operation= "+";
    }

    public void equalsClicked() {
        executeOperation();
        output.set(Double.toString(round(previousNumber, 2)));
        operation = "=";
    }

    public void dotClicked() {
        if(dot) return;
        dot = true;
    }

    public void sevenClicked() {
        reset();
        numberClicked = 7;
        writeNumber();
    }

    public void eightClicked() {
        reset();
        numberClicked = 8;
        writeNumber();
    }

    public void nineClicked() {
        reset();
        numberClicked = 9;
        writeNumber();
    }

    public void fourClicked() {
        reset();
        numberClicked = 4;
        writeNumber();
    }

    public void fiveClicked() {
        reset();
        numberClicked = 5;
        writeNumber();
    }

    public void sixClicked() {
        reset();
        numberClicked = 6;
        writeNumber();
    }

    public void oneClicked() {
        reset();
        numberClicked = 1;
        writeNumber();
    }

    public void twoClicked() {
        reset();
        numberClicked = 2;
        writeNumber();
    }

    public void threeClicked() {
        reset();
        numberClicked = 3;
        writeNumber();
    }

    public void zeroClicked() {
        reset();
        if(dot) {
            if(divider == 0.001) return;
            divider /= 10;
        }
        else output.set(Double.toString((Double.parseDouble(getOutput()) * 10) + 0));
    }


}
