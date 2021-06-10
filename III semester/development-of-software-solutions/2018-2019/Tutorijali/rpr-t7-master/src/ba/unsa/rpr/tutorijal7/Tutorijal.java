package ba.unsa.rpr.tutorijal7;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.beans.XMLEncoder;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;

public class Tutorijal {

    public static ArrayList<Grad> ucitajGradove(){
        ArrayList<Grad> gradovi  =  new ArrayList<>();
        Scanner ulaz = null;
        try {
            ulaz = new Scanner(new FileReader("mjerenja.txt"));
            while(ulaz.hasNextLine()){ // citamo liniju po liniju
                String grad = ulaz.nextLine();
                String naziv = null;
                Double[] temperature = new Double[1000];
                int index = 0;
                for(; index < grad.length(); index++){ // ucitamo naziv grada
                    if(grad.charAt(index) == ','){
                        naziv = grad.substring(0, index);
                        break;
                    }
                }
                index++;
                int poc = -1;
                for(int i = 0; i < temperature.length && index < grad.length(); index++){ // prelazimo na prepisivanje temperatura
                    if(poc == -1) poc = index;
                    if(grad.charAt(index) == ',') {
                        temperature[i] = Double.parseDouble(grad.substring(poc, index));
                        i++;
                        poc = -1;
                    } else if(index == grad.length() - 1){
                        temperature[i] = Double.parseDouble(grad.substring(poc, index + 1));
                        break;
                    }
                }
                gradovi.add(new Grad(naziv, temperature));
            }
        } catch (FileNotFoundException e) {
            System.out.println("Datoteka ulaz.txt ne postoji ili se ne može otvoriti");
        } finally{
            ulaz.close();
        }
        return gradovi;
    }

    public static UN ucitajXml(ArrayList<Grad> gradovi){
        ArrayList<Drzava> result = new ArrayList<>();
        Document xmldoc = null;
        try {
            DocumentBuilder docReader = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            xmldoc = docReader.parse(new File("drzave.xml"));
            Element korijen = xmldoc.getDocumentElement();
            NodeList djeca = korijen.getChildNodes();
            for(int i = 0; i < djeca.getLength(); i++){ // sada smo na samom pocetku gdje su elementi <drzave>
                Node drzava = djeca.item(i); // element je <drzave>
                if(drzava instanceof Element && drzava.getNodeName().equals("#text")) continue;
                if(drzava instanceof Element && ((Element) drzava).getTagName().equals("drzava")){

                    int brojStanovnikaDrzave = Integer.parseInt(((Element) drzava).getAttribute("stanovnika"));
                    String nazivDrzave = ((Element) drzava).getElementsByTagName("naziv").item(0).getTextContent();
                    Double povrsinaDrzave = Double.parseDouble(((Element) drzava).getElementsByTagName("povrsina").item(0).getTextContent());
                    String jedinicaZaPovrsinu = ((Element)((Element) drzava).getElementsByTagName("povrsina").item(0)).getAttribute("jedinica"); // tako je ruznoal mi mrsko pisati

                    NodeList glavniGrad = ((Element) drzava).getElementsByTagName("glavnigrad");
                    String nazivGlavnogGradaDrzave = ((Element)glavniGrad.item(0)).getElementsByTagName("naziv").item(0).getTextContent();
                    int brojStanovnikaGlavnogGradaDrzave = Integer.parseInt(((Element)glavniGrad.item(0)).getAttribute("stanovnika"));
                    Double[] temperatureGrada = new Double[1000];
                    Grad postoji = null;
                    for(Grad g: gradovi){
                        if(g.getNaziv().equals(nazivGlavnogGradaDrzave)){
                            postoji = g;
                            temperatureGrada = g.getTemperature();
                            g.setBrojStanovnika(brojStanovnikaGlavnogGradaDrzave);
                            break;
                        }
                    }
                    if(postoji != null) result.add(new Drzava(nazivDrzave, brojStanovnikaDrzave, povrsinaDrzave, jedinicaZaPovrsinu, postoji));
                    else result.add(new Drzava(nazivDrzave, brojStanovnikaDrzave, povrsinaDrzave, jedinicaZaPovrsinu, new Grad(nazivGlavnogGradaDrzave, brojStanovnikaGlavnogGradaDrzave, null)));
                }
            }
        } catch (Exception e) {
            System.out.println("drzave.xml nije validan XML dokument");
        }
        UN un = new UN();
        un.setDrzave(result);
        return un;
    }

    public static void zapisiXml(UN un){
        XMLEncoder izlaz = null;
        try{
            izlaz = new XMLEncoder(new FileOutputStream("un.xml"));
            izlaz.writeObject(un);
        } catch (FileNotFoundException e){
            System.out.println("Greska, datoteka nije nadjena");
        } finally {
            izlaz.close();
        }
    }

    public static void main(String[] args) {
        zapisiXml(ucitajXml(ucitajGradove()));
    }
}
