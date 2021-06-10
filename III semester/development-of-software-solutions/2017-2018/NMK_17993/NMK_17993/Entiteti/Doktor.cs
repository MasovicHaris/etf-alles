using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace NMK_17993.Entiteti
{
    public class Doktor : Uposlenik
    {
        double bonusDoktoraPacijent;
        int brojPregledanihPacijenata = 0;          // ne mora se brinuti o danu tj. samo se gleda brojac
        bool zauzet;
        List<Ordinacija> specijalistaZaOrdinacije;                                     // ukoliko ima u listi ordinaciju
                                                                                       // on tu moze da radi

        public Doktor(string ime, string prezime, string maticni, string adresa, DateTime datumrodjenja, Spol s, bracnoStanje brS,
            int plata) : base(ime, prezime, maticni, adresa, datumrodjenja, s, brS, plata)
        {
            zauzet = false;
            SpecijalistaZaOrdinacije = new List<Ordinacija>();
        }

        public double BonusDoktoraPacijent
        {
            get
            {
                return bonusDoktoraPacijent;
            }

            set
            {
                bonusDoktoraPacijent = value;
            }
        }

        public int BrojPregledanihPacijenata
        {
            get
            {
                return brojPregledanihPacijenata;
            }

            set
            {
                brojPregledanihPacijenata = value;
            }
        }

        public bool Zauzet
        {
            get
            {
                return zauzet;
            }

            set
            {
                zauzet = value;
            }
        }

        public List<Ordinacija> SpecijalistaZaOrdinacije
        {
            get
            {
                return specijalistaZaOrdinacije;
            }

            set
            {
                specijalistaZaOrdinacije = value;
            }
        }

        void dodajBrojPregledanih() { BrojPregledanihPacijenata++; }

        delegate double ProcessDelegate();                                              // koristenje delegata i lambda funkcija
                                                                                        // za racunanje dodatka na platu

        public void dodajNaPlatu()
        {
            ProcessDelegate process;
            process = () => BrojPregledanihPacijenata / 100;                            // lambda funkcija


            BonusDoktoraPacijent = process();
            plataUposlenik += Convert.ToInt32(BonusDoktoraPacijent * plataUposlenik);
        }

    }
}
