using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using iTunes.Exceptions;
using iTunes.Klase;

namespace iTunes
{
    public class OnlineStore
    {
        String url;

        List<Tune> pjesme;
        List<RegisteredMember> regMembers;

        #region GETTERS_AND_SETTERS

        public String Url
        {
            get { return url; }
            set { url = value; }
        }

        public List<RegisteredMember> RegMembers
        {
            get { return regMembers; }
            set { regMembers = value; }
        }

        public List<Tune> Pjesme
        {
            get { return pjesme; }
            set { pjesme = value; }
        }

        #endregion GETTERS_AND_SETTERS
        #region KONSTRUKTORI

        public OnlineStore() { }
        
        public OnlineStore(String url) 
        {
            Url = url;
            Pjesme = new List<Tune>();
            RegMembers = new List<RegisteredMember>();
        }

        #endregion KONSTRUKTORI
        #region METODE_REGISTRACIJE_ODJAVE_PRETRAGE_NAPLATE_KORISNIKA

        // Registracija novog korisnika na aplikaciju
        public String registrirajKorisnika(String i, String p, DateTime dr, String bkk, String un, String pass) 
        {
            if (daLiPostoji(un))
                throw new Exception("Korisnik sa datim passwordom već postoji.");

            RegisteredMember rm = new RegisteredMember(i, p, dr, bkk, un, p);
            rm.Id = Guid.NewGuid().ToString();

            RegMembers.Add(rm);

            if (dr.Month == 2 && dr.Day == 24) // Rođendan Steve Jobs-a
            {
                Tune t = new Tune("Happy Birthday", "Patty Hill, Mildred J. Hill", "None", "Folk", 9.8, ".mp3", 60, 320, 9.50);
                rm.MojaBiblioteka.Add(t);
            }

            return rm.Id;
        }

        // Provjera da li postoji korisnik sa istim usernameom
        public Boolean daLiPostoji(String un) 
        {
            foreach (RegisteredMember r in RegMembers)
                if (r.Username.Equals(un))
                    return true;

            return false;
        }

        // Brisanje korisnika iz sistema
        public Boolean obrisiKorisnika(String Id)
        {
            foreach (RegisteredMember r in RegMembers)
                if (Id.Equals(r.Id))
                {
                    RegMembers.Remove(r);
                    return true;
                }

            return false;
        }

        // Pretraga za korisnikom po ID
        public RegisteredMember pretragaKorisnikaPoIdu(String id)
        {
            foreach (RegisteredMember r in RegMembers)
                if (id.Equals(r.Id))
                    return r;

            throw new UserNotFoundException("Korisnik sa datim ID-em nije pronađen.");
        }

        // Pretraga za korisnikom po imenu i prezimenu
        public List<RegisteredMember> pretragaKorisnikaPoImenu(String i, String p)
        {
            List<RegisteredMember> rezultati = new List<RegisteredMember>();

            foreach (RegisteredMember r in RegMembers)
                if (i.Equals(r.Ime) && p.Equals(r.Prezime))
                    rezultati.Add(r);

            if(rezultati.Count == 0)
                throw new UserNotFoundException("Korisnik sa datim podacima nije pronađen.");

            return rezultati;
        }

        // Promovisanje statusa korisnika u GoldMember status
        public void unaprijediNaGoldMember(String id)
        {
            if (this.pretragaKorisnikaPoIdu(id).GoldMember)
                throw new Exception("User is already a gold member of our site.");

            this.naplatiUslugu(id, 250.50); // Naplata 250$ da se postane gold member
            this.pretragaKorisnikaPoIdu(id).GoldMember = true;
        }

        // Naplata bilo koje usluge
        void naplatiUslugu(String id, Double amount)
        {
            foreach (RegisteredMember r in RegMembers)
                if (id.Equals(r.Id))
                    r.KorisnickiRacun.naplati(amount);
        }

        // Naplata bilo koje usluge uz obracunavanje popusta (Popust je u procentima)
        void naplatiUsluguUzPopust(String id, Double amount, Double popust)
        {
            naplatiUslugu(id, amount - (amount/popust));
        }

        #endregion
        #region METODE_REGISTRACIJE_PRETRAGE_PJESAMA

        // Registracija nove pjesme
        public String registrujNovuPjesmu(Tune pjesma)
        {
            pjesme.Add(pjesma);
            return pjesma.Id;
        }

        // Pretraga za pjesmom po ID
        public Tune pretragaPjesmePoIdu(String id)
        {
            foreach (Tune t in Pjesme)
                if (id.Equals(t.Id))
                    return t;

            throw new SongNotFoundException("Pjesma sa datim ID-em nije pronađena.");
        }

        // Pretraga za pjesmom po imenu i izvođaću
        public List<Tune> pretragaPjesamaPoNazivuIzvodacu(String n, String izv)
        {
            List<Tune> rezultati = new List<Tune>();

            foreach (Tune t in Pjesme)
                if (n.Equals(t.Title) && izv.Equals(t.Artist))
                    rezultati.Add(t);

            if (rezultati.Count == 0)
                throw new SongNotFoundException("Pjesma sa datim podacima nije pronađena.");

            return rezultati;
        }

        #endregion REGISTRACIJA_PJESAMA
        #region KUPOVINA_PJESAMA

        // Kupovina pjesme
        public void kupiPjesmu(String idKorisnika, String idPjesme)
        {
            if (pretragaKorisnikaPoIdu(idKorisnika).GoldMember) 
                naplatiUsluguUzPopust(idKorisnika, pretragaPjesmePoIdu(idPjesme).Price, 10);
            else
                naplatiUslugu(idKorisnika, pretragaPjesmePoIdu(idPjesme).Price);

            foreach (RegisteredMember r in RegMembers)
                if (idKorisnika.Equals(r.Id))
                    r.MojaBiblioteka.Add(pretragaPjesmePoIdu(idPjesme));
        }

        #endregion
        #region PRENOS_PJESAMA

        public void prenesiPjesmu(String idKorisnika1, String idKorisnika2, String idPjesme)
        {
            if (!pretragaKorisnikaPoIdu(idKorisnika1).GoldMember || !pretragaKorisnikaPoIdu(idKorisnika2).GoldMember)
                throw new Exception("Pjesme mogu prenositi samo između Gold članova.");

            naplatiUslugu(idKorisnika1, 0.19);

            pretragaKorisnikaPoIdu(idKorisnika1).MojaBiblioteka.Remove(pretragaPjesmePoIdu(idPjesme));
            pretragaKorisnikaPoIdu(idKorisnika2).MojaBiblioteka.Add(pretragaPjesmePoIdu(idPjesme));
        }

        #endregion
    }
}
