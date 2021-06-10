using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor.Model
{
    public class NeregistrovaniKorisnik: Korisnik
    {
        Lokacija location;

        public virtual Lokacija Location
        {
            get
            {
                return location;
            }

            set
            {
                location = value;
            }
        }
    }
}
