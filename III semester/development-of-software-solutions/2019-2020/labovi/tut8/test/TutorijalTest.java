package ba.unsa.etf.rpr.tutorijal8;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.function.Executable;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

class TutorijalTest {
    @Test
    void daLiUcitavaGradoveKorektno() {
        PrintWriter writer = null;
        try {
            writer = new PrintWriter("mjerenja.txt", "UTF-8");
            writer.println("Neum,1,2,3,4,5,6,7,8,9");
            writer.println("Split,1,2,3,4");
            writer.close();
            ArrayList<Grad> gradovi = Tutorijal.ucitajGradove();
            assertAll(()->
            {
                assertEquals(2,gradovi.size());
                assertEquals("Neum",gradovi.get(0).getNaziv());
                assertEquals(9, Arrays.stream(gradovi.get(0).getTemperature()).distinct().count());
                assertEquals("Split",gradovi.get(1).getNaziv());
                assertEquals(4, Arrays.stream(gradovi.get(1).getTemperature()).distinct().count());
            });
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    @Test
    void daLiSeNeKrahiraPriUcitavanju2000() {
        PrintWriter printWriter = null;
        try{
            printWriter = new PrintWriter("mjerenja.txt","UTF-8");
            String multiplier = "1,1";
            multiplier = multiplier.replace("1","1,1,1,1,1,1,1,1,1,1");
            multiplier = multiplier.replace("1","1,1,1,1,1,1,1,1,1,1");
            multiplier = multiplier.replace("1","1,1,1,1,1,1,1,1,1,1");
            printWriter.println("Ottawa,"+multiplier);
            printWriter.close();
            assertDoesNotThrow((Executable) Tutorijal::ucitajGradove);
        } catch (FileNotFoundException | UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

  /*  @Test
    void daLiSuTemperatureUKorektnomRedoslijedu() {
        PrintWriter writer = null;
        try {
            writer = new PrintWriter("mjerenja.txt", "UTF-8");
            writer.println("Neum,1,2,3,4,5,6,7,8,9");
            writer.println("Split,1,2,3,4");
            writer.println("Tešanj,1,2,3,4,5,6,7,8,9");
            writer.println("Novi Sad,77.8,99.9,33.3,84.4");
            writer.close();
            double [] testTemperatures = new double[]{77.8,99.9,33.3,84.4};
            ArrayList<Grad> gradovi = Tutorijal.ucitajGradove();
            double[] realTemperatures = gradovi.get(3).getTemperature();
            for (int i = 0; i < 4; i++) {
                if( Double.compare(testTemperatures[i],realTemperatures[i])!=0){
                    fail();
                }
            }
            assertTrue(true);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }

    @Test
    void daLiSeXMLUcitaKorektno() {
        PrintWriter writer = null;
        try {
            writer = new PrintWriter("drzave.xml", "UTF-8");
            writer.println("<drzave>");
            writer.println("\t<drzava stanovnika=\"3500000\">");
            writer.println("\t\t<naziv>Bosna i Hercegovina</naziv>");
            writer.println("\t\t<glavnigrad stanovnika=\"400000\">");
            writer.println("\t\t\t<naziv>Sarajevo</naziv>");
            writer.println("\t\t</glavnigrad>");
            writer.println("\t\t<povrsina jedinica=\"km2\">51129</povrsina>");
            writer.println("\t</drzava>");
            writer.println("</drzave>");
            writer.close();
            UN un = Tutorijal.ucitajXml(new ArrayList<>());
            ArrayList<Drzava> drzave = un.getDrzave();
            assertAll(()->{
                assertEquals(1, drzave.size());
                assertEquals("Bosna i Hercegovina",drzave.get(0).getNaziv());
                assertEquals("km2",drzave.get(0).getJedinica());
                assertEquals("Sarajevo",drzave.get(0).getGlavniGrad().getNaziv());
            });
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }*/
}