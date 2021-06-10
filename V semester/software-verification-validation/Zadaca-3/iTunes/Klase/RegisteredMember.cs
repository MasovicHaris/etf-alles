using iTunes.Exceptions;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace iTunes.Klase
{
    public class RegisteredMember
    {
        String id; // Korisnikov ID u iTunes bazi
        String ime;  // Korisnikovo ime
        String prezime; // Korisnikovo prezime
        DateTime datumRodenja; // Korisnikov datum rođenja
        Racun korisnickiRacun; // Korisnikov račun odakle se skida novac pri kupovini pjesama. 
        String username; // Korisnikov username
        String password; // Korisnikov password
        Boolean goldMember; // Da li je korisnik gold member koji ima dodatne pogodnosti?

        List<Tune> mojaBiblioteka; // Lista pjesama koje je korisnik kupio i posjeduje u svojoj biblioteci

        #region GETTERS_AND_SETTERS

        public String Id
        {
            get { return id; }
            set { id = value; }
        }

        public String Ime
        {
            get { return ime; }
            set { ime = value; }
        }

        public String Prezime
        {
            get { return prezime; }
            set { prezime = value; }
        }

        public DateTime DatumRodenja
        {
            get { return datumRodenja; }
            set { datumRodenja = value; }
        }

        public Racun KorisnickiRacun
        {
            get { return korisnickiRacun; }
            set { korisnickiRacun = value; }
        }

        public String Username
        {
            get { return username; }
            set { username = value; }
        }

        public String Password
        {
            get { return password; }
            set { password = value; }
        }

        public Boolean GoldMember
        {
            get { return goldMember; }
            set { goldMember = value; }
        }

        public List<Tune> MojaBiblioteka
        {
            get { return mojaBiblioteka; }
            set { mojaBiblioteka = value; }
        }
        
        #endregion GETTERS_AND_SETTERS
        #region KONSTRUKTORI

        public RegisteredMember() { }

        public RegisteredMember(String i, String p, DateTime dr, String bkk, String un, String pass) 
        {
            Ime = i;
            Prezime = p;
            DatumRodenja = dr;
            KorisnickiRacun = new Racun(bkk, 500.0);
            Username = un;
            Password = p;
            GoldMember = false;

            MojaBiblioteka = new List<Tune>();
        }

        #endregion

        #region TDD_NOVA_METODA

        List<String> listaTopD = null;    // lista koja sadrzi top 10 po kriteriju koji se specificira
        List<Objekat> objekti;

        private void odradi(String y)
        {
            objekti = new List<Objekat>();
            foreach(Tune element in mojaBiblioteka)
            {
                Objekat a = new Objekat();
                if (y == "u") a.naziv = element.Artist;
                else if (y == "a") a.naziv = element.Album;
                else if (y == "z") a.naziv = element.Genre;
                a.cijena = element.Price;
                if (objekti.Find(x => x.naziv == a.naziv) == null) objekti.Add(a);
                else objekti.Find(x => x.naziv == a.naziv).cijena += a.cijena;    
            }
        }

        // vraca top 10 po kriteriju
        public List<String> VratiTopDeset(String kriterij)
        {
            listaTopD = new List<String>();
            if (kriterij == "u" || kriterij == "a" || kriterij == "z") // trazimo top 10 umjetnika
            {
                odradi(kriterij);
                objekti = objekti.OrderByDescending(x => x.cijena).ToList();
                var prvihDeset = objekti.Take(10);
                foreach (var element in prvihDeset)
                {
                    listaTopD.Add(element.naziv);
                }
            }
            else throw new Exception("Nije specificiran kriterij.");
            return listaTopD;
        }

        private class Objekat
        {
            public String naziv;
            public double cijena;
        }

        #endregion
    }


}
