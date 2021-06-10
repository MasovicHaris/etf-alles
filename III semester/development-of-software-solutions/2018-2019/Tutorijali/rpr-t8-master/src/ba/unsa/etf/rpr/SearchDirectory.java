package ba.unsa.etf.rpr;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.io.File;

public class SearchDirectory implements Runnable {

    private String searchMaterial = new String();
    private ObservableList<String> list;
    private Controller controller;
    private File dat;
    private Thread blinker;

    public SearchDirectory(String searchMaterial, Controller controller, Thread blinker){
        this.searchMaterial = searchMaterial;
        this.controller = controller;
        this.blinker = blinker;
        list = FXCollections.observableArrayList();
        //home mi je sakriven a kazu da je negje u AppData\Local... direktoriju tako da....
        dat = new File("C:\\Users\\Default");
    }

    @Override
    public void run() {
        for(String s: dat.list()){
            searchInFile(new File(dat, s));
        }
        //at the end
        blinker.interrupt();
        Platform.runLater(() -> controller.setInformationLabel("Search is done"));
        Platform.runLater(() -> controller.getSearchButton().disableProperty().setValue(false));
        Platform.runLater(() -> controller.getStopButton().disableProperty().setValue(true));
        Platform.runLater(() -> controller.setResultListView(list));
    }

    private void searchInFile(File parent){
        int i = 0, j = searchMaterial.length();
        while(j <= parent.getName().length()){
            if(parent.getName().substring(i, j).equalsIgnoreCase(searchMaterial)){
                list.add(parent.getPath());
                break;
            }
            i++;
            j++;
        }
        if(parent.list() == null) return;
        for(String s: parent.list()){
            searchInFile( new File(parent, s));
        }

    }
}
