using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NMK_17993.Entiteti;

namespace NMK_17993.Entiteti
{
    sealed class Pregled
    {
        bool placena;
        private List<Terapija> pregledTerapija;
        private string misljenjeDoktora;
        private Ordinacija ordinacija;
        bool pregled;
        public Pregled()
        {
            misljenjeDoktora = "";
            pregledTerapija = new List<Terapija>();
            ordinacija = new Ordinacija();
            pregled = false;
            placena = false;
        }
        public Pregled(List<Terapija> b, string misljenje, Ordinacija o)
        {
            PregledTerapija = b;
            MisljenjeDoktora = misljenje;
            Ordinacija = o;
            pregled = false;
            placena = false;
        }

        public List<Terapija> PregledTerapija
        {
            get
            {
                return pregledTerapija;
            }

            set
            {
                pregledTerapija = value;
            }
        }
        public string MisljenjeDoktora
        {
            get
            {
                return misljenjeDoktora;
            }

            set
            {
                misljenjeDoktora = value;
            }
        }
        internal Ordinacija Ordinacija
        {
            get
            {
                return ordinacija;
            }

            set
            {
                ordinacija = value;
            }
        }

        public bool Pregled1
        {
            get
            {
                return pregled;
            }

            set
            {
                pregled = value;
            }
        }

        public bool Placena
        {
            get
            {
                return placena;
            }

            set
            {
                placena = value;
            }
        }
    }
}
