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
        primaryStage.setTitle("SEARCH DIRECTORIES");
        Scene scene = new Scene(root, 655, 285);
        primaryStage.setScene(scene);
        primaryStage.setMinWidth(665);
        primaryStage.setMaxWidth(665);
        primaryStage.setMinHeight(330);
        primaryStage.setMaxHeight(330);
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
