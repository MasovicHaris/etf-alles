package ba.unsa.etf.rpr.tutorijal05;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("digitron.fxml"));
        primaryStage.setTitle("Digitron");
        Scene scene = new Scene(root, 225, 235);
        primaryStage.setMinHeight(295);
        primaryStage.setMinWidth(240);
        primaryStage.setScene(scene);
        root.getStylesheets().add("styling/definitions.css");
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
