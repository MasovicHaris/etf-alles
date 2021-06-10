using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor.Model
{
    public class NeregistrovaniKorisnik: Korisnik
    {
        Tuple<double, double> location;

        public virtual Tuple<double, double> Location
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
