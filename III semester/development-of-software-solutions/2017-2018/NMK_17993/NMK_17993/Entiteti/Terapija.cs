using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public partial class Terapija
    {
        public enum vrstaTerapije { kratkorocna, dugorocna }

        private DateTime datumPotpisivanjeTerapije;
        private Doktor onajKojiIzdao;
        private vrstaTerapije vrstaTerap;
        private string dodatneSitnice;
        private string nazivTerapije;

        public DateTime DatumPotpisivanjeTerapije
        {
            get
            {
                return datumPotpisivanjeTerapije;
            }

            set
            {
                datumPotpisivanjeTerapije = value;
            }
        }
        private vrstaTerapije VrstaTerap
        {
            get
            {
                return vrstaTerap;
            }

            set
            {
                vrstaTerap = value;
            }
        }
        public string DodatneSitnice
        {
            get
            {
                return dodatneSitnice;
            }

            set
            {
                dodatneSitnice = value;
            }
        }
        public Doktor OnajKojiIzdao
        {
            get
            {
                return onajKojiIzdao;
            }

            set
            {
                onajKojiIzdao = value;
            }
        }

        public string NazivTerapije
        {
            get
            {
                return nazivTerapije;
            }

            set
            {
                nazivTerapije = value;
            }
        }

        public vrstaTerapije VrstaTerap1
        {
            get
            {
                return vrstaTerap;
            }

            set
            {
                vrstaTerap = value;
            }
        }

        Terapija(vrstaTerapije tret, DateTime datum, Doktor doca, string sitnice = null)
        {
            VrstaTerap = tret;
            onajKojiIzdao = doca;
            DodatneSitnice = sitnice;
            nazivTerapije = "";
            
        }
        
        
    }
}
