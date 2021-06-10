using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NMK_17993.Entiteti
{
    /*
     * Kada se vrši obračun plate potrebno je diferencirati između redovnih i novih pacijenata.
Redovni pacijenti su oni pacijenti koji su posjetili kliniku više od tri puta. Redovni pacijenti
dobijaju 10% popusta na gotovinsko plaćanje, a za plaćanje na rate cijena ostaje ista. Novi
pacijenti nemaju popusta na cijenu za gotovinsko plaćanje, a ako je u pitanju plaćanje na rate
cijena se povećava za 15%. Svakom pacijentu je potrebno izdati štampanu formu fiskalnog
računa koji će sadržavati sve stavke za koje pacijent plaća, kao i iznos koji plaća. Ako je u
pitanju plaćanje na rate, onda je potrebno prikazati i broj rate koji se plaća odmah, te broj
preostalih rata. */

    public class NaplataPregleda
    {
        const double cijenaPregleda = 50;                                       // bilo kakav pregled je 50km fixno, da bude lakse
        public enum vrstaPlacanja { gotovo, rate }
        vrstaPlacanja vrstaKes;
        double novaCijena;
        public vrstaPlacanja VrstaKes
        {
            get
            {
                return vrstaKes;
            }

            set
            {
                vrstaKes = value;
            }
        }

        public static double CijenaPregleda
        {
            get
            {
                return cijenaPregleda;
            }
        }

        public double NovaCijena
        {
            get
            {
                return novaCijena;
            }

            set
            {
                novaCijena = value;
            }
        }

        public double izracunajCijenuPregleda(int brojPosjeta, vrstaPlacanja vrstica)
        {
            double cijenaPregledaNova = cijenaPregleda;

            if (brojPosjeta > 3 && vrstica == vrstaPlacanja.gotovo) cijenaPregledaNova -= 0.1 * cijenaPregleda;
            if (brojPosjeta < 3 && vrstica == vrstaPlacanja.rate) cijenaPregledaNova += 0.15 * cijenaPregleda;
            novaCijena = cijenaPregledaNova;
            return cijenaPregledaNova;
        }
    }
}
