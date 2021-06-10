package ba.unsa.etf.rpr.tutorijal8;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.DoubleStream;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Tutorijal {

    public static void main(String[] args) {
        ArrayList<Grad> l = ucitajGradove();
    }

    public static ArrayList<Grad> ucitajGradove() {
        Scanner ulaz = null;
        // Konstruisanje ulaznog toka za datoteku brojevi.txt
        try {
            ulaz = new Scanner(new FileReader("mjerenja.txt"));
        } catch (FileNotFoundException e) {
            System.out.println("Datoteka se nije uspjesno otvorila!");
        }

        ArrayList<Grad> listaTemp = new ArrayList<>();
        while (ulaz.hasNext()) {
            Grad tempGrad = new Grad();

            String[] linija = ulaz.nextLine().split(",");       //splita se citav red po zarezu
            tempGrad.setNaziv(linija[0]);   //postavlja se prvo ime grada
            double[] novi = new double[linija.length - 1];        //pa se ono izbaci iz ostatka a to su samo preostali brojevi
            for (int i = 1; i < linija.length; i++) novi[i - 1] = Double.parseDouble(linija[i]);
            tempGrad.setTemperature(novi);
            listaTemp.add(tempGrad);
        }
        ulaz.close();

        return listaTemp;
    }


    //Pogledati jos!
/*    public static UN ucitajXml(ArrayList<Grad> l) {
        UN tempun = new UN();
        Document xmldoc = null;
        try {
            DocumentBuilder docReader
                    = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            xmldoc = docReader.parse(new File("drzave.xml"));
        } catch (Exception e) {
            System.out.println("drzave.xml nije validan XML dokument");
        }

        Element element = xmldoc.getDocumentElement();

        System.out.print("Element "+element.getTagName()+", ");

        int brAtributa = element.getAttributes().getLength();
        System.out.print(brAtributa+" atributa");

        NodeList djeca = element.getChildNodes(); //djeca su sve drzave koje sacinjavaju kolekciju i sad kroz svaku moramo iterirat for petljom

        // Ako nema djece ispisujemo sadržaj
        if (djeca.getLength() == 1) {
            String sadrzaj = element.getTextContent();
            System.out.println(", sadrzaj: '" + sadrzaj + "'");
        } else {
            System.out.println("");
        }

       ArrayList<Drzava> unc=new ArrayList<>();

        for(int i = 0; i < djeca.getLength(); i++) {
            Drzava d = new Drzava();
            Node dijete = djeca.item(i);//ovo nam dadne jednu drzavu iz koje opet moramo dobiti nodove
            if (dijete instanceof Element) {
                d.setNaziv(((Element) dijete).getAttribute("naziv"));
                d.setJedinicaZaPovrsinu(((Element) dijete).getAttribute("povrsina"));

                NodeList djeca2 = dijete.getChildNodes();
                for(int j=0; j<djeca2.getLength(); j++)
                {
                    Node podElement = djeca2.item(j);
                    if(podElement instanceof Element)
                    {
                        Element t2=(Element) podElement;
                        if(t2.getTagName().equals("glavnigrad")){
                            int brStan = Integer.parseInt(t2.getAttribute("stanovnika"));
                            for(int k=0; k<l.size(); k++)
                            {
                                if(l.get(k).getNaziv().equals(t2.getAttribute("naziv"))){
                                    l.get(k).setBrojStanovnika(brStan); break;
                                }
                            }
                        }

                    }

                }
            }
        }

        tempun.setLista(l);



    }*/
}






