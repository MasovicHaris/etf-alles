using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    public partial class Terapija
    {
        public Terapija()
        {
            VrstaTerap = vrstaTerapije.kratkorocna;
            datumPotpisivanjeTerapije = DateTime.Today;
            NazivTerapije = "";
        }

    }
}
