using iTunes.Exceptions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Klase
{
    public class Racun
    {
        String brojKreditneKartice;
        // Validacija je stroga. Primjeri:
        // 1. 4012888888881881
        // 2. 4024007195736334
        // 3. 5560527397859946
        // 4. 6011816573426759
        // 5. 372948467675716
        Double stanje;

        #region GETTERI_I_SETTERI

        public String BrojKreditneKartice
        {
            get { return brojKreditneKartice; }
            set
            {
                if (Validacija.validirajKreditnuKarticu(value))
                    brojKreditneKartice = value;
                else
                    throw new CreditCardInvalidException("Broj kreditne kartice nije ispravan.");
            }
        }

        public Double Stanje
        {
            get { return stanje; }
            set { stanje = value; }
        }

        #endregion GETTERI_I_SETTERI
        #region KONSTRUKTORI_I_METODA

        public Racun() { }

        public Racun(String bkk, Double s)
        {
            BrojKreditneKartice = bkk;
            Stanje = s;
        }

        public Boolean naplati(Double iznos)
        {
            if (Stanje < iznos)
                throw new NoMoneyException("Na računu nema dovoljno sredstava.");
            else
            {
                Stanje = Stanje - iznos;
                return true;
            }
        }

        #endregion
    }
}
