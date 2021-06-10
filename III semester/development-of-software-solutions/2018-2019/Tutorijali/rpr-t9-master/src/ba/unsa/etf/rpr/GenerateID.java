package ba.unsa.etf.rpr;

import javafx.scene.input.GestureEvent;

import java.beans.XMLDecoder;
import java.io.*;

public class GenerateID {
    private int lastID = 108;

    public GenerateID() {}
    public GenerateID(int lastID){
        this.setLastID(lastID);
    }
    public  int generateID(){
        lastID++;
        return lastID;

    }

    public int getLastID() {
        return lastID;
    }

    public void setLastID(int lastID) {
        this.lastID = lastID;
    }
}
