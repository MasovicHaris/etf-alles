package ba.unsa.etf.rpr;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("Unos Studenta");
        Scene scene = new Scene(root, 650, 650);
        primaryStage.setScene(scene);
        primaryStage.setMaxHeight(650);
        primaryStage.setMaxWidth(650);
        primaryStage.setMinHeight(650);
        primaryStage.setMinWidth(650);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
