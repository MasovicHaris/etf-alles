using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public class Klinika : InterfaceKlinika
    {
        List<Pacijent> listaPacijenata;
        List<Uposlenik> listaUposlenih;
        List<Ordinacija> listaOrdinacija;

        public List<Pacijent> ListaPacijenata
        {
            get
            {
                return listaPacijenata;
            }

            set
            {
                listaPacijenata = value;
            }
        }

        public List<Uposlenik> ListaUposlenih
        {
            get
            {
                return listaUposlenih;
            }

            set
            {
                listaUposlenih = value;
            }
        }

        public List<Ordinacija> ListaOrdinacija
        {
            get
            {
                return listaOrdinacija;
            }

            set
            {
                listaOrdinacija = value;
            }
        }

        public Klinika()
        {
            listaPacijenata = new List<Pacijent>();
            ListaUposlenih = new List<Uposlenik>();

            Doktor doktor17993_1 = new Doktor("Saban", "Saulic", "1410967150262", "Sabanova ulica 1", DateTime.Parse("14.10.1967"), Osoba.Spol.M, 
                Osoba.bracnoStanje.nijeUBraku, 10000);
            Doktor doktor17993_2 = new Doktor("Jasar", "Ahmedovski", "1410968150262", "Jasarova ulica 1", DateTime.Parse("14.10.1968"), Osoba.Spol.M,
                Osoba.bracnoStanje.nijeUBraku, 5000);
            Doktor doktor17993_3 = new Doktor("Aca", "Lukas", "1410987150262", "Acina ulica 1", DateTime.Parse("14.10.1987"), Osoba.Spol.M,
                Osoba.bracnoStanje.nijeUBraku, 9000);

           

            ListaOrdinacija = new List<Ordinacija>();

            Ordinacija ordinacija17993_1 = new Ordinacija(Ordinacija.stanje.Slobodno, Ordinacija.funkcija.radi, "Ginekologija");
            Ordinacija ordinacija17993_2 = new Ordinacija(Ordinacija.stanje.Slobodno, Ordinacija.funkcija.neRadi, "Ortopedija");
            Ordinacija ordinacija17993_3 = new Ordinacija(Ordinacija.stanje.Slobodno, Ordinacija.funkcija.radi, "Otorinolaringologija");

            ListaOrdinacija.Add(ordinacija17993_1);
            ListaOrdinacija.Add(ordinacija17993_2);
            ListaOrdinacija.Add(ordinacija17993_3);

            doktor17993_1.SpecijalistaZaOrdinacije.Add(ordinacija17993_1);
            doktor17993_1.SpecijalistaZaOrdinacije.Add(ordinacija17993_3);
            doktor17993_2.SpecijalistaZaOrdinacije.Add(ordinacija17993_2);
            doktor17993_3.SpecijalistaZaOrdinacije.Add(ordinacija17993_3);

            ListaUposlenih.Add(doktor17993_1);
            ListaUposlenih.Add(doktor17993_2);
            ListaUposlenih.Add(doktor17993_3);

            doktor17993_1.postaviUser("saban123");      doktor17993_1.postaviPassword("saban123");
            doktor17993_2.postaviUser("js111");      doktor17993_2.postaviPassword("js111");
            doktor17993_3.postaviUser("aca133");     doktor17993_3.postaviPassword("aca111");

            Uposlenik portir = new Uposlenik("Semso", "Portir", "28111996160002", "Džemala Bijedića 2", DateTime.Parse("14.10.1967"), Osoba.Spol.M,
            Osoba.bracnoStanje.nijeUBraku, 500);
            portir.postaviUser("semso");
            portir.postaviPassword("semso123");
            portir.JeLiPortir = true;
            ListaUposlenih.Add(portir);

            Uposlenik sestraHelga = new Uposlenik("Sestra", "Helga", "28111996160002", "Džemala Bijedića 2", DateTime.Parse("14.10.1967"), Osoba.Spol.Z,
            Osoba.bracnoStanje.nijeUBraku, 700);
            sestraHelga.postaviUser("helga1");
            sestraHelga.postaviPassword("helga1");
            sestraHelga.JeLiPortir = false;
            ListaUposlenih.Add(sestraHelga);


            Pacijent pacijent = new Pacijent("J", "K", "2111997170003", "Dz b 2", DateTime.Parse("14.10.1987"), Osoba.Spol.Z, Osoba.bracnoStanje.uBraku);
            pacijent.LicniKarton = new KartonPacijenta();
            pacijent.LicniKarton.SpisakPregleda1 = new List<Pregled>();
            ListaPacijenata.Add(pacijent);
        }

        public string ispisNazivKlinike()
        {
            return "Ovo je naša mala klinikaaa";
        }
    }
}
