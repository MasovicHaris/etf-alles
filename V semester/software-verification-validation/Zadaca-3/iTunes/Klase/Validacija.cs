using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Klase
{
    public static class Validacija
    {
        public static bool validirajKreditnuKarticu(string brojKreditneKartice)
        {
            if (string.IsNullOrEmpty(brojKreditneKartice))
                return false;

            int sumaCifara = brojKreditneKartice.Where((e) => e >= '0' && e <= '9')
                            .Reverse()
                            .Select((e, i) => ((int)e - 48) * (i % 2 == 0 ? 1 : 2))
                            .Sum((e) => e / 10 + e % 10);

            return sumaCifara % 10 == 0;
        }
    }
}
