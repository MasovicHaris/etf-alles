using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public class KartonPacijenta
    {
        private List<string> prijasnjeBolesti, sadasnjeBolesti, prijasnjeAlergije, sadasnjeAlergije;
        private int brojPosjeta;
        private List<Pregled> SpisakPregleda;

        public List<string> PrijasnjeBolesti
        {
            get
            {
                return prijasnjeBolesti;
            }

            set
            {
                prijasnjeBolesti = value;
            }
        }                   // properties
        public List<string> SadasnjeBolesti
        {
            get
            {
                return sadasnjeBolesti;
            }

            set
            {
                sadasnjeBolesti = value;
            }
        }
        public List<string> PrijasnjeAlergije
        {
            get
            {
                return prijasnjeAlergije;
            }

            set
            {
                prijasnjeAlergije = value;
            }
        }
        public List<string> SadasnjeAlergije
        {
            get
            {
                return sadasnjeAlergije;
            }

            set
            {
                sadasnjeAlergije = value;
            }
        }
        public int BrojPosjeta
        {
            get
            {
                return brojPosjeta;
            }

            set
            {
                brojPosjeta = value;
            }
        }

        internal List<Pregled> SpisakPregleda1
        {
            get
            {
                return SpisakPregleda;
            }

            set
            {
                SpisakPregleda = value;
            }
        }

        public KartonPacijenta()
        {
            prijasnjeBolesti = new List<string>();
            SadasnjeBolesti = new List<string>();
            PrijasnjeAlergije = new List<string>();
            SadasnjeAlergije = new List<string>();
            BrojPosjeta = 0;
        }
        KartonPacijenta(List<string> PB, List<string> SB, List<string> PA, List<string> SA, int brP = 0)
        {
            PrijasnjeBolesti = PB; SadasnjeBolesti = SB;
            prijasnjeAlergije = PA; SadasnjeAlergije = SA;
            BrojPosjeta = brP;
        }

        public void PovecajBrojPosjeta() { brojPosjeta++; }
    }
}
