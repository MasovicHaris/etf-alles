package ba.unsa.etf.rpr;

import javafx.application.Platform;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.StandardCharsets;

public class PostNumberValidation  implements Runnable{
    private SendFile controller;

    public PostNumberValidation(SendFile controller){
        this.controller = controller;
    }
    @Override
    public void run() {
        String adress = "http://c9.etf.unsa.ba/proba/postanskiBroj.php?postanskiBroj=" + controller.getPostNumberTextField().textProperty().get();
        try{
            URL url = new URL(adress);
            BufferedReader input = new BufferedReader(new InputStreamReader(url.openStream(), StandardCharsets.UTF_8));
            if(input.readLine().equalsIgnoreCase("not ok")) {
                Platform.runLater(() -> {
                    controller.getPostNumberTextField().getStyleClass().removeAll("right");
                    controller.getPostNumberTextField().getStyleClass().add("wrong");
                });
            }
            else {
                Platform.runLater(() -> {
                    controller.getPostNumberTextField().getStyleClass().removeAll("wrong");
                    controller.getPostNumberTextField().getStyleClass().add("right");
                });
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
