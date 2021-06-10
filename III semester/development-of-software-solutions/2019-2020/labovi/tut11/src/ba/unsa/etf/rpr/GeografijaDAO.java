package ba.unsa.etf.rpr;

import javafx.beans.Observable;
import javafx.beans.property.ObjectProperty;
import javafx.beans.property.SimpleObjectProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;

public class GeografijaDAO {

    private static GeografijaDAO instance;
    private Connection conn=null;
    private PreparedStatement glavniGradUpit, dajDrzavuUpit, obrisiDrzavuUpit, obrisiGradoveZaDrzavu, nadjiDrzavuUpit, dajSveGradoveUpit,
    dodajGradUpit, dodajDrzavuUpit, odrediIdGradUpit, odrediIdDrzavaUpit, promijeniGradUpit, dajGradUpit, dajDrzaveUpit,nadjiGradUpit,
    obrisiGradUpit;

    private ObjectProperty<Grad> trenutniGrad = new SimpleObjectProperty<>();
    private ObservableList<Drzava> drzave = FXCollections.observableArrayList();
    private ObjectProperty<Drzava> trenutnaDrzava = new SimpleObjectProperty<>();
    private ObservableList<Grad> gradevi = FXCollections.observableArrayList();


    public static GeografijaDAO getInstance()  {
        if(instance==null) {
                instance=new GeografijaDAO();
        }
        return instance;
    }

    public static void removeInstance(){
        if(instance==null) return;
        instance.close();
        instance=null;
    }

    public void close(){
        try{
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Connection dajKonekciju()
    {
        return this.conn;
    }

    private GeografijaDAO() {
        try {
            conn= DriverManager.getConnection("jdbc:sqlite:baza.db"); //uspostavi konekciju
        } catch (SQLException e) {
            e.printStackTrace();
        }
        try { //provjeri da li je uspostavljena dobra konekcija
            glavniGradUpit=conn.prepareStatement("SELECT grad.id, grad.naziv, grad.broj_stanovnika, grad.drzava FROM grad, drzava WHERE grad.drzava=drzava.id AND drzava.naziv=?");
        } catch (SQLException e) {
            regenerisiBazu(); //ako nije uspostavljena, probaj regenerisat bazu iz .sql datoteke koja je exportovana
            try {
                glavniGradUpit=conn.prepareStatement("SELECT grad.id, grad.naziv, grad.broj_stanovnika, grad.drzava FROM grad, drzava WHERE grad.drzava=drzava.id AND drzava.naziv=?");
            } catch (SQLException e1) {
            e1.printStackTrace();
        }
    }
        try {
            dajDrzavuUpit = conn.prepareStatement("SELECT * FROM DRZAVA WHERE id=?");
            dajGradUpit = conn.prepareStatement("SELECT * FROM grad WHERE id=?");
            obrisiDrzavuUpit = conn.prepareStatement("DELETE FROM drzava WHERE naziv=?");
            obrisiGradoveZaDrzavu = conn.prepareStatement("DELETE FROM grad WHERE drzava=?");
            nadjiDrzavuUpit=conn.prepareStatement("SELECT * FROM drzava WHERE naziv=?");
            dajSveGradoveUpit=conn.prepareStatement("SELECT * FROM grad ORDER BY broj_stanovnika DESC");
            dodajGradUpit=conn.prepareStatement("INSERT INTO grad VALUES(?,?,?,?,?,?)");
            odrediIdGradUpit=conn.prepareStatement("SELECT Max(id)+1 FROM grad");
            dodajDrzavuUpit=conn.prepareStatement("INSERT INTO drzava VALUES(?,?,?)");
            odrediIdDrzavaUpit=conn.prepareStatement("SELECT Max(id)+1 FROM drzava");
            promijeniGradUpit=conn.prepareStatement("UPDATE grad SET naziv=?, broj_stanovnika=?, drzava=?, slika=?, postanski_broj=?  WHERE id=?");
            dajDrzaveUpit=conn.prepareStatement("SELECT * FROM drzava");
            nadjiGradUpit=conn.prepareStatement("SELECT * FROM grad WHERE naziv=?");
            obrisiGradUpit=conn.prepareStatement("DELETE FROM grad WHERE id=?");
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    private void regenerisiBazu()  {
        Scanner ulaz = null;
        try {
            ulaz = new Scanner(new FileInputStream("baza.db.sql"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String upitSql="";
        while(ulaz.hasNext())
        {
            upitSql+=ulaz.nextLine();
            if(upitSql.charAt(upitSql.length()-1) == ';'){
                try {
                    Statement stmt= conn.createStatement();
                    stmt.execute(upitSql);
                    upitSql="";
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        ulaz.close();
    }

    public Grad glavniGrad(String drzava){
        try {
            glavniGradUpit.setString(1,drzava);
            ResultSet rs = glavniGradUpit.executeQuery();
            if(!rs.next()) return null;
            return dajGradIzResultSeta(rs);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }

    }

    private Grad dajGradIzResultSeta(ResultSet rs) throws SQLException {
        Grad grad = new Grad(rs.getInt(1), rs.getString(2), rs.getInt(3), null, rs.getInt(6));
        grad.setSlikaPutanja(rs.getString(5));
        grad.setDrzava(dajDrzavu(rs.getInt(4), grad));
        return grad;
    }



    private Drzava dajDrzavu(int id, Grad grad) {
        try {
            dajDrzavuUpit.setInt(1,id); //prepared statement smo vec u konstruktoru DAO definisali, ovdje ga fillujemo podacima
            ResultSet rs = dajDrzavuUpit.executeQuery();
            if(!rs.next()) return null; //ne postoji drzava sa tim id-om
            return dajDrzavuIzResultSeta(rs,grad);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    private Grad dajGrad(int id) {
        try {
            dajGradUpit.setInt(1,id); //prepared statement smo vec u konstruktoru DAO definisali, ovdje ga fillujemo podacima
            ResultSet rs = dajGradUpit.executeQuery();
            if(!rs.next()) return null; //ne postoji grad sa tim id-om
            return dajGradIzResultSeta(rs);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    private Drzava dajDrzavuIzResultSeta(ResultSet rs, Grad grad) throws SQLException {
        return new Drzava(rs.getInt(1), rs.getString(2), grad);  //grad moramo vući kako bi formirali državu
    }

    public void obrisiDrzavu(String nazivDrzava){
        try {
            nadjiDrzavuUpit.setString(1,nazivDrzava);
            ResultSet rs=nadjiDrzavuUpit.executeQuery();
            if(!rs.next()) return;
            Drzava drzava=dajDrzavuIzResultSeta(rs,null); //nadjemo drzavu sa tim nazivom, odnosno njen id
            obrisiGradoveZaDrzavu.setInt(1,drzava.getId()); //iz tabele grad uklonimo grad koji ima id drzave kao i nadjena drzava
            obrisiGradoveZaDrzavu.executeUpdate();
            obrisiDrzavuUpit.setInt(1, drzava.getId());
            obrisiDrzavuUpit.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public ArrayList<Grad> gradovi() {
        ArrayList<Grad> lista = new ArrayList<>();
        this.gradevi=FXCollections.observableArrayList();
        try {
            ResultSet rs=dajSveGradoveUpit.executeQuery(); //upit vraca set gradova u descendingu
            while(rs.next())
            {
                Grad grad = dajGradIzResultSeta(rs);
                lista.add(grad);
                gradevi.add(grad);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return lista;
    }


    public ObservableList<Grad> dajObservableGradove(){
        return this.gradevi;
    }

    public ObservableList<Drzava> drzave() {
        ObservableList<Drzava> lista = FXCollections.observableArrayList();
        try {
            ResultSet rs=dajDrzaveUpit.executeQuery(); //upit vraca set gradova u descendingu
            while(rs.next())
            {
                Drzava d = dajDrzavuIzResultSeta(rs, null);
                lista.add(d);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return lista;
    }

    public void dodajGrad(Grad grad) {
        try {
            ResultSet rs=odrediIdGradUpit.executeQuery();
            int id=1;
            if(rs.next()) id=rs.getInt(1);
            dodajGradUpit.setInt(1,id);
            dodajGradUpit.setString(2,grad.getNaziv());
            dodajGradUpit.setInt(3, grad.getBrojStanovnika());
            dodajGradUpit.setInt(4, grad.getDrzava().getId());
            dodajGradUpit.setString(5, grad.getSlikaPutanja());
            dodajGradUpit.setInt(6, grad.getPostanskiBroj());
            dodajGradUpit.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }


    }
    public void dodajDrzavu(Drzava drzava){
        try {
            ResultSet rs=odrediIdDrzavaUpit.executeQuery();
            int id=1;
            if(rs.next()) id=rs.getInt(1);
            dodajDrzavuUpit.setInt(1,id);
            dodajDrzavuUpit.setString(2,drzava.getNaziv());
            dodajDrzavuUpit.setInt(3, drzava.getGlavniGrad().getId());
            dodajDrzavuUpit.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

   public void izmijeniGrad(Grad grad){
       try {
           promijeniGradUpit.setString(1,grad.getNaziv());
           promijeniGradUpit.setInt(2,grad.getBrojStanovnika());
           promijeniGradUpit.setInt(3, grad.getDrzava().getId());
           promijeniGradUpit.setInt(6, grad.getId());
           promijeniGradUpit.setString(4, grad.getSlikaPutanja());
           promijeniGradUpit.setInt(5, grad.getPostanskiBroj());
           promijeniGradUpit.executeUpdate();
       } catch (SQLException e) {
           e.printStackTrace();
       }
   }

    public Drzava nadjiDrzavu(String nazivDrzava) {
        try {
            nadjiDrzavuUpit.setString(1, nazivDrzava);
            ResultSet rs = nadjiDrzavuUpit.executeQuery();
            if(!rs.next()) return null; //nema drzave
            return dajDrzavuIzResultSeta(rs,dajGrad(rs.getInt(3)));
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public Grad nadjiGrad(String nazivGrada){
        try{
            nadjiGradUpit.setString(1,nazivGrada);
            ResultSet rs = nadjiGradUpit.executeQuery();
            if(!rs.next()) return null; //nema grada
            return dajGradIzResultSeta(rs);
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public void obrisiGrad(Grad g){
        try{
            obrisiGradUpit.setInt(1, g.getId());
            obrisiGradUpit.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
