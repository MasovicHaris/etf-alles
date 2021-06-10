using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor
{
    public static class ValidacijeAndMore
    {
        static public bool validacijaPassworda(string a, string b)
        {
            return a.Equals(b);
        }

        public static bool crossValidacijaJMBG(string jmbg, DateTime datum)         // cross validacija usefull
        {
            if (jmbg.Length == 13)
            {
                int broj;
                Int32.TryParse(jmbg.Substring(0, 2), out broj);
                if (datum.Day != broj)
                {
                    return false;
                }
                Int32.TryParse(jmbg.Substring(2, 2), out broj);
                if (datum.Month != broj)
                {
                    return false;
                }
                Int32.TryParse(jmbg.Substring(4, 3), out broj);
                if (broj != (datum.Year % 1000))
                {
                    return false;
                }
                return true;
            }
            return false;
        }

        public static bool provjeraJMBG(string jmbgP)
        {
            if (jmbgP.Length != 13)
            {
                return false;
            }
            for (int i = 0; i < 13; i++)
            {
                if (jmbgP[i] < '0' || jmbgP[i] > '9')
                {
                    return false;
                }
            }
            int g = 0, m = 0, d = 0;
            //provjera ispravnosti datuma unutar jmbg
            d = Convert.ToInt32(jmbgP.Substring(0, 2));
            m = Convert.ToInt32(jmbgP.Substring(2, 2));
            if (jmbgP[4] == 0)
            {
                g = 2000 + Convert.ToInt32(jmbgP.Substring(4, 3));
            }
            else
            {
                g = 1000 + Convert.ToInt32(jmbgP.Substring(4, 3));
            }
            int[] broj_dana = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (g % 4 == 0 && g % 100 != 0 || g % 400 == 0)
            {
                broj_dana[1]++;
            }
            if (g < 1 || m < 1 || m > 12 || d < 1 || d > broj_dana[m - 1] || g > 2016)
            {
                throw new Exception("Datum je neispravan!");
            }

            return true;
        }

        public static string CreateMD5(string input)                            // MD5 hash kreiranje
        {
            if (input == null) input = "";
            // Use input string to calculate MD5 hash
            using (System.Security.Cryptography.MD5 md5 = System.Security.Cryptography.MD5.Create())
            {
                byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
                byte[] hashBytes = md5.ComputeHash(inputBytes);

                // Convert the byte array to hexadecimal string
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < hashBytes.Length; i++)
                {
                    sb.Append(hashBytes[i].ToString("X2"));
                }
                return sb.ToString();
            }
        }


    }
}
