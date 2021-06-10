package ba.unsa.etf.rpr;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;

public class SendFile {
    @FXML
    private TextField nameTextField;
    @FXML
    private TextField surnameTextField;
    @FXML
    private TextField adressTextField;
    @FXML
    private TextField townTextField;
    @FXML
    private TextField postNumberTextField;


    public String getNameTextField() {
        return nameTextField.textProperty().get();
    }

    public void setNameTextField(String value) {
        this.nameTextField.textProperty().setValue(value);
    }

    public String getSurnameTextField() {
        return surnameTextField.textProperty().get();
    }

    public void setSurnameTextField(String value) {
        this.surnameTextField.textProperty().setValue(value);
    }

    public String getAdressTextField() {
        return adressTextField.textProperty().get();
    }

    public void setAdressTextField(String value) {
        this.adressTextField.textProperty().setValue(value);
    }

    public String getTownTextField() {
        return townTextField.textProperty().get();
    }

    public void setTownTextField(String value) {
        this.townTextField.textProperty().setValue(value);
    }

    public TextField getPostNumberTextField() {
        return postNumberTextField;
    }

    public void setPostNumberTextField(String value) {
        this.postNumberTextField.textProperty().setValue(value);
    }

    @FXML
    public void initialize(){
        nameTextField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                validate(nameTextField);
            }
        });
        surnameTextField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                validate(surnameTextField);
            }
        });
        adressTextField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                validate(adressTextField);
            }
        });
        townTextField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                validate(townTextField);
            }
        });
        postNumberTextField.focusedProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, Boolean oldValue, Boolean newValue) {
                validatePostNumber();
            }
        });
    }

    private void validate(TextField field){
        if(field.textProperty().get().equals("")){
            field.getStyleClass().removeAll("right");
            field.getStyleClass().add("wrong");
        }
        else {
            field.getStyleClass().removeAll("wrong");
            field.getStyleClass().add("right");
        }
    }

    private void validatePostNumber(){
        PostNumberValidation validate = new PostNumberValidation(this);
        new Thread(validate).start();
    }
}
