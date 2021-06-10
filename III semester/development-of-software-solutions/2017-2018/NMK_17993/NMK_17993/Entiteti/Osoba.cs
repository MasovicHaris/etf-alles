using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public abstract class Osoba
    {
        public enum Spol { M, Z };
        public enum bracnoStanje { uBraku, nijeUBraku };
        private string ime, prezime, maticniBroj, adresaStanovanja;
        private DateTime datumRodenja;
        private Spol spol;
        private bracnoStanje brStanje;

        public string Ime
        {
            get
            {
                return ime;
            }

            set
            {
                ime = value;
            }
        }

        public string Prezime
        {
            get
            {
                return prezime;
            }

            set
            {
                prezime = value;
            }
        }

        public string MaticniBroj
        {
            get
            {
                return maticniBroj;
            }

            set
            {
                maticniBroj = value;
            }
        }

        public string AdresaStanovanja
        {
            get
            {
                return adresaStanovanja;
            }

            set
            {
                adresaStanovanja = value;
            }
        }

        public bracnoStanje BrStanje
        {
            get
            {
                return brStanje;
            }

            set
            {
                brStanje = value;
            }
        }

        public Spol Spol1
        {
            get
            {
                return spol;
            }

            set
            {
                spol = value;
            }
        }

        public DateTime DatumRodenja
        {
            get
            {
                return datumRodenja;
            }

            set
            {
                datumRodenja = value;
            }
        }

        protected Osoba(string ime, string prezime, string maticni, string adresa, DateTime datumrodjenja, Spol s, bracnoStanje brS)
        {
            this.ime = ime;
            this.prezime = prezime;
            this.maticniBroj = maticni;
            this.adresaStanovanja = adresa;
            this.datumRodenja = datumrodjenja;
            this.spol = s;
            this.brStanje = brS;
        }
    }
}
