using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace NMK_17993.Entiteti
{
    public class Pacijent : Osoba
    {
        KartonPacijenta licniKarton;
        DateTime datumVrijemSmrti;
        Image slikaPacijenta;

        internal KartonPacijenta LicniKarton
        {
            get
            {
                return licniKarton;
            }

            set
            {
                licniKarton = value;
            }
        }
        public DateTime DatumVrijemSmrti
        {
            get
            {
                return datumVrijemSmrti;
            }

            set
            {
                datumVrijemSmrti = value;
            }
        }

        public Image SlikaPacijenta
        {
            get
            {
                return slikaPacijenta;
            }

            set
            {
                slikaPacijenta = value;
            }
        }

        public Pacijent(string ime, string prezime, string maticni, string adresa, DateTime datumrodjenja, Spol s,
        bracnoStanje brS) : base(ime, prezime, maticni, adresa, datumrodjenja, s, brS)
        {
            LicniKarton = new KartonPacijenta();
        }

    }

}
