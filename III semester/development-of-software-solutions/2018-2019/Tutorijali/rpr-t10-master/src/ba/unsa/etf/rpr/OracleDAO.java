package ba.unsa.etf.rpr;

import java.sql.*;
import java.util.ArrayList;

public class OracleDAO {
    private final String kreirajTabele = "CREATE TABLE grad (" +
            "                    id int not null primary key ," +
            "                    naziv VARCHAR2(20) not null ," +
            "                    broj_stanovnika int," +
            "                    drzava int" +
            ");\n" +
            "create table drzava (" +
            "                      id int not null primary key ," +
            "                      naziv VARCHAR2(20) not null ," +
            "                      glavni_grad int\n" +
            ");\n" +
            "commit ;\n" +
            "alter table grad add foreign key (drzava) references drzava(id) on delete cascade ;" +
            "alter table drzava add foreign key (glavni_grad) references grad(id) on delete cascade ;" +
            "commit ;";
    private static GenerateID lastID;
    private static OracleDAO instance = null;
    private final String URL = "jdbc:oracle:thin:@ora.db.lab.ri.etf.unsa.ba:1521:ETFLAB";
    private Connection connection;
    private PreparedStatement glavniGradQuery, obrisiDrzavuQuery1, obrisiDrzavuQuery2, gradoviQuery, dodajGradQuery, dodajDrzavuQuery, izmijeniGradQuery, nadjiDrzavuQuery;
    private PreparedStatement selektGradovi, selektDrzave;
    private OracleDAO(){
        try {
            connection = DriverManager.getConnection(URL, "NK17825", "xuYoshjV");
            imaLiBaza(); // gleda ima li uopste potrebnih tabela u bazi
            prepareStatements();
            ResultSet idEvi = selektGradovi.executeQuery();
            lastID = new GenerateID(vratiMaxID(idEvi));
            ResultSet gradovi = selektGradovi.executeQuery();
            ResultSet drzave = selektDrzave.executeQuery();
            if(!gradovi.next() || !drzave.next())
                regenerisi();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private int vratiMaxID(ResultSet idEvi){
        int maxID = 108;
        try {
            if(idEvi.next()){
                if(idEvi.getInt(1) > idEvi.getInt(4))
                    maxID = idEvi.getInt(1);
                else
                    maxID = idEvi.getInt(4);
            }
            while (idEvi.next()) {
                if(idEvi.getInt(1) > maxID)
                    maxID = idEvi.getInt(1);
                if(idEvi.getInt(4) > maxID)
                    maxID = idEvi.getInt(4);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return maxID;
    }

    private void imaLiBaza(){
        boolean dropovoJeTabele = false;
        try{
            //ako bilo koji selekt ne uspije jedna ili obije tabele ne postoje
            getConnection().createStatement().executeQuery("SELECT * FROM grad");
            getConnection().createStatement().executeQuery("select * from drzava");
        } catch (SQLException e){
            dropovoJeTabele = true;
            try{ // treba dropati kolone koji su strani kljucevi prvo
                getConnection().createStatement().executeUpdate("alter table grad drop column drzava;");
            } catch (SQLException f) {}
            try{
                getConnection().createStatement().executeUpdate("alter table drzava drop column glavni_grad;");
            } catch (SQLException f) {}
            try{ // pa dropamo obije tabele da bi ih fino kreirali
                getConnection().createStatement().executeUpdate("drop table grad;");
            } catch (SQLException f) {}
            try{
                getConnection().createStatement().executeUpdate("drop table drzava;");
            } catch (SQLException f) {}
        }
        if(dropovoJeTabele){
            try{
                getConnection().createStatement().executeUpdate(kreirajTabele);
            } catch (SQLException e){
                e.printStackTrace();
            }
        }
    }

    public void resetBazu(){
        regenerisi();
        try{
            ResultSet idEvi = selektGradovi.executeQuery();
            lastID = new GenerateID(vratiMaxID(idEvi));
        } catch (SQLException e){
            e.printStackTrace();
        }
    }

    private void prepareStatements() throws SQLException {
        selektGradovi = getConnection().prepareStatement("SELECT * FROM NK17825.GRAD");
        selektDrzave = getConnection().prepareStatement("select * from NK17825.DRZAVA");
        glavniGradQuery = getConnection().prepareStatement("select * from NK17825.GRAD where drzava = (select id from NK17825.DRZAVA where naziv = ?)");
        obrisiDrzavuQuery1 = getConnection().prepareStatement("delete from NK17825.GRAD where drzava = (select id from NK17825.DRZAVA where naziv = ?)");
        obrisiDrzavuQuery2 = getConnection().prepareStatement("delete from NK17825.DRZAVA where naziv = ?");
        gradoviQuery = getConnection().prepareStatement("select * from NK17825.GRAD order by broj_stanovnika desc");
        dodajGradQuery = getConnection().prepareStatement("insert into NK17825.GRAD values (?, ?, ?, ?)");
        dodajDrzavuQuery = getConnection().prepareStatement("insert into NK17825.DRZAVA values(?, ?, null)");
        izmijeniGradQuery = getConnection().prepareStatement("update NK17825.GRAD set naziv = ?, broj_stanovnika = ? where id = ?");
        nadjiDrzavuQuery = getConnection().prepareStatement("select * from NK17825.DRZAVA where naziv = ?");
    }

    private static void initialize(){
        instance = new OracleDAO();
    }

    public static OracleDAO getInstance(){
        if(instance == null) initialize();
        return instance;
    }

    public static void removeInstance(){
        if(instance != null) {
            try{
                instance.getConnection().close();
            } catch (SQLException e) { }
        }
        instance = null;
    }

    private void regenerisi(){
        try{
            getConnection().createStatement().executeUpdate("delete from NK17825.GRAD where id > 0");
            getConnection().createStatement().executeUpdate("delete from NK17825.DRZAVA where id > 0");
            getConnection().createStatement().executeUpdate("commit ");
        } catch (SQLException e){
            e.printStackTrace();
        }
        try{
            getConnection().createStatement().executeUpdate("insert into DRZAVA values (101, 'Francuska',  null)");
            getConnection().createStatement().executeUpdate("insert into DRZAVA values (103, 'Velika Britanija', null)");
            getConnection().createStatement().executeUpdate("insert into DRZAVA values (105, 'Austrija', null)");
            getConnection().createStatement().executeUpdate("insert into GRAD values (100, 'Pariz', 2206488, 101)");
            getConnection().createStatement().executeUpdate("insert into GRAD values (102, 'London', 8825000, 103)");
            getConnection().createStatement().executeUpdate("insert into GRAD values (104, 'Beč', 1899055, 105)");
            getConnection().createStatement().executeUpdate("insert into GRAD values (106, 'Manchester', 545500, 103)");
            getConnection().createStatement().executeUpdate("insert into GRAD values (108, 'Graz', 280200, 105)");
            getConnection().createStatement().executeUpdate("commit ");
            getConnection().createStatement().executeUpdate("update NK17825.DRZAVA set GLAVNI_GRAD = 100 where id = 101");
            getConnection().createStatement().executeUpdate("update NK17825.DRZAVA set GLAVNI_GRAD = 102 where id = 103");
            getConnection().createStatement().executeUpdate("update NK17825.DRZAVA set GLAVNI_GRAD = 104 where id = 105");
            getConnection().createStatement().executeUpdate("commit ");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Grad glavniGrad(String drzava){
        Grad grad = null;
        try{
            ArrayList<Grad> gradovi = new ArrayList<>();
            glavniGradQuery.setString(1, drzava);
            ResultSet resultSet = glavniGradQuery.executeQuery();
            while (resultSet.next()){ // trebala bi biti samo jedna iteracija
                int idGrada = resultSet.getInt(1);
                ResultSet drzavaResult = connection.createStatement().executeQuery("select * from drzava where glavni_grad = " + idGrada);
                Drzava d = null;
                while(drzavaResult.next()) { // trebala bi biti samo jedna iteracija
                    d = new Drzava(drzavaResult.getString(2), new Grad());
                    grad = new Grad(resultSet.getString(2), resultSet.getInt(3), d);
                    grad.setId(resultSet.getInt(1));
                    d.setGlavniGrad(grad);
                    d.setId(drzavaResult.getInt(1));
                    gradovi.add(grad);
                }
                if(gradovi.size() >= 1){
                    grad = gradovi.get(0);
                    for(Grad g: gradovi){
                        if(g.getBrojStanovnika() > grad.getBrojStanovnika())
                            grad = g;
                    }
                }
            }
        } catch (SQLException e){
            e.printStackTrace();
        }
        return grad;
    }

    public void obrisiDrzavu(String drzava){
        try{
            obrisiDrzavuQuery1.setString(1, drzava);
            obrisiDrzavuQuery2.setString(1, drzava);
            obrisiDrzavuQuery1.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
            obrisiDrzavuQuery2.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
        } catch (SQLException e){
            e.printStackTrace();
        }
    }

    public ArrayList<Grad> gradovi(){
        ArrayList<Grad> gradovi = new ArrayList<>();
        try{
            ResultSet gradoviSet = gradoviQuery.executeQuery();
            while(gradoviSet.next()){
                Grad g = new Grad(gradoviSet.getInt(1), gradoviSet.getString(2), gradoviSet.getInt(3), null);
                ResultSet drzava = getConnection().createStatement().executeQuery("select naziv from drzava where id = " + gradoviSet.getInt(4));
                Drzava d = null;
                if(drzava.next()){
                    d = nadjiDrzavu(drzava.getString(1));
                }
                g.setDrzava(d);
                gradovi.add(g);
            }
        } catch (SQLException e){
            e.printStackTrace();
        }
        return gradovi;
    }

    public void dodajGrad(Grad grad){
        try{
            ArrayList<Grad> gradovi = gradovi();
            for(Grad g: gradovi){
                if(g.getNaziv().equalsIgnoreCase(grad.getNaziv()))
                    return;
            }
            int drzavaID;
            Drzava d = nadjiDrzavu(grad.getDrzava().getNaziv());
            int gradID = lastID.generateID();
            if(d != null){
                drzavaID = d.getId();
            } else {
                drzavaID = lastID.generateID();
                dodajDrzavuQuery.setInt(1, drzavaID);
                dodajDrzavuQuery.setString(2, grad.getDrzava().getNaziv());
                dodajDrzavuQuery.executeUpdate();
                getConnection().createStatement().executeUpdate("commit ");
            }
            dodajGradQuery.setInt(1, gradID);
            dodajGradQuery.setString(2, grad.getNaziv());
            dodajGradQuery.setInt(3, grad.getBrojStanovnika());
            dodajGradQuery.setInt(4, drzavaID);
            dodajGradQuery.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
            if(d != null) getConnection().createStatement().executeUpdate("update NK17825.DRZAVA set GLAVNI_GRAD = " + gradID + " where id = " + drzavaID);
            getConnection().createStatement().executeUpdate("commit ");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void dodajDrzavu(Drzava drzava){
        try{
            Drzava d = nadjiDrzavu(drzava.getNaziv());
            if(d != null) return;

            int gradID = lastID.generateID();
            int drzavaID = lastID.generateID();
            drzava.setId(drzavaID);
            drzava.getGlavniGrad().setId(gradID);
            dodajDrzavuQuery.setInt(1, drzavaID);
            dodajDrzavuQuery.setString(2, drzava.getNaziv());
            dodajDrzavuQuery.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
            dodajGradQuery.setInt(1, gradID);
            dodajGradQuery.setString(2, drzava.getGlavniGrad().getNaziv());
            dodajGradQuery.setInt(3, drzava.getGlavniGrad().getBrojStanovnika());
            dodajGradQuery.setInt(4, drzavaID);
            dodajGradQuery.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
            getConnection().createStatement().executeUpdate("update NK17825.DRZAVA set GLAVNI_GRAD = " + gradID + " where id = " + drzavaID);
            getConnection().createStatement().executeUpdate("commit ");
        } catch (SQLException e){
            e.printStackTrace();
        }
    }

    public void izmijeniGrad(Grad grad){
        try {
            izmijeniGradQuery.setString(1, grad.getNaziv());
            izmijeniGradQuery.setInt(2, grad.getBrojStanovnika());
            izmijeniGradQuery.setInt(3, grad.getId());
            izmijeniGradQuery.executeUpdate();
            getConnection().createStatement().executeUpdate("commit ");
        } catch (SQLException e) {
            e.printStackTrace();
        }

    }

    public Drzava nadjiDrzavu(String drzava){
        Drzava result = null;
        try{
            nadjiDrzavuQuery.setString(1, drzava);
            ResultSet resultSet = nadjiDrzavuQuery.executeQuery();
            while (resultSet.next()){
                result = new Drzava(resultSet.getInt(1), resultSet.getString(2), null);
                ResultSet r = connection.createStatement().executeQuery("select * from grad where drzava = " + resultSet.getInt(1));
                while (r.next()){
                    result.setGlavniGrad(new Grad(r.getInt(1), r.getString(2), r.getInt(3), result));
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    public Connection getConnection() {
        return connection;
    }
}