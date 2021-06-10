using System;
using System.ComponentModel.DataAnnotations;

namespace Vicinor.Model
{
    public abstract class Korisnik
    {
        private int korisnikId;

        public int KorisnikId
        {
            get { return korisnikId; }
            set { korisnikId = value; }
        }
    }
}
