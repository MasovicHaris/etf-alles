package ba.unsa.etf.rpr;

import javafx.application.Platform;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import java.io.IOException;

public class Controller {

    @FXML
    private TextField searchTextField;

    @FXML
    private Button searchButton;
    @FXML
    private Button stopButton;

    @FXML
    private Label informationLabel;

    @FXML
    private ListView<String> resultListView;

    private Thread thread, blinker;

    @FXML
    public void initialize(){
    }

    public void searchButtonClicked(){
        if(getSearchTextField().textProperty().get().equals("")){
            setInformationLabel("Search field is empty!");
            return;
        }
        setInformationLabel("");
        blinker = new Thread(() -> {
            try {
                while (true) {
                    if (getInformationLabel().equals(""))
                        Platform.runLater(() -> setInformationLabel("Search is in action"));
                    else
                        Platform.runLater(() -> setInformationLabel(""));
                    Thread.sleep(200);
                }
            } catch (InterruptedException e) { }
        });
        blinker.start();
        searchButton.disableProperty().setValue(true);
        stopButton.disableProperty().setValue(false);
        thread = new Thread(new SearchDirectory(getSearchTextField().textProperty().get(), this, blinker));
        thread.start();
    }

    public void stopButtonClicked() {
        blinker.interrupt();
        thread.interrupt();
        searchButton.disableProperty().setValue(false);
        stopButton.disableProperty().setValue(true);
        setInformationLabel("Search has been interrupted");
    }

    public void itemClicked(){
        String selectedItem = resultListView.getSelectionModel().getSelectedItem().toString();
        try{
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("sendFile.fxml"));
            Parent root1 = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("SENDING FILE");
            stage.setScene(new Scene(root1, 425, 180));
            stage.setMinWidth(425);
            stage.setMaxWidth(425);
            stage.setMinHeight(230);
            stage.setMaxHeight(230);
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return;
    }

    public TextField getSearchTextField() {
        return searchTextField;
    }

    public void setSearchTextField(String string) {
        this.searchTextField.textProperty().setValue(string);
    }

    public Button getSearchButton() {
        return searchButton;
    }

    public Button getStopButton() {
        return stopButton;
    }

    public String getInformationLabel() {
        return informationLabel.textProperty().get();
    }

    public void setInformationLabel(String string) {
        this.informationLabel.textProperty().setValue(string);
    }

    public ListView<String> getResultListView() {
        return resultListView;
    }
    public void setResultListView(ObservableList<String> list){
        this.resultListView.itemsProperty().setValue(list);
    }
}
