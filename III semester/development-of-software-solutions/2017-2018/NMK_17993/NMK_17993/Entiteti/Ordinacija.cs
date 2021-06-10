using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public class Ordinacija
    {
        public enum stanje { Slobodno, Zauzeto }
        private stanje stanjeOrdinacije;
        public enum funkcija { radi, neRadi }
        private funkcija jelradi;
        string nazivOrdinacije;
        public stanje StanjeOrdinacije
        {
            get
            {
                return stanjeOrdinacije;
            }

            set
            {
                stanjeOrdinacije = value;
            }
        }

        public funkcija Jelradi
        {
            get
            {
                return jelradi;
            }

            set
            {
                jelradi = value;
            }
        }

        public string NazivOrdinacije
        {
            get
            {
                return nazivOrdinacije;
            }

            set
            {
                nazivOrdinacije = value;
            }
        }

        public Ordinacija(stanje trenutno, funkcija f, string a)
        {
            StanjeOrdinacije = trenutno;
            Jelradi = f;
            nazivOrdinacije = a;
        }
        public Ordinacija()
        {
            StanjeOrdinacije = stanje.Zauzeto;
            Jelradi = funkcija.radi;
            nazivOrdinacije = "";
        }
    }
}
