using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace NMK_17993.Entiteti
{
    public class Uposlenik : Osoba
    {
        protected int plataUposlenik;
        string username, sifraUposlenikaMD5Hash;

        public Uposlenik(string ime, string prezime, string maticni, string adresa, DateTime datumrodjenja, Spol s, bracnoStanje brS,
            int plata) : base(ime, prezime, maticni, adresa, datumrodjenja, s, brS)
        {
            plataUposlenik = plata;
        }

        public string Username
        {
            get
            {
                return username;
            }

            set
            {
                username = value;
            }
        }

        public string SifraUposlenikaMD5Hash
        {
            get
            {
                return sifraUposlenikaMD5Hash;
            }

            set
            {
                sifraUposlenikaMD5Hash = value;
            }
        }

        public bool JeLiPortir
        {
            get
            {
                return jeLiPortir;
            }

            set
            {
                jeLiPortir = value;
            }
        }

        public void postaviUser(string uzer)
        {
            Username = uzer;
        }

        public void postaviPassword(string sifra)
        {
            string hash = "";
            using (MD5 md5Hash = MD5.Create())
            {
                hash = GetMd5Hash(md5Hash, sifra);
            }
            SifraUposlenikaMD5Hash = hash;
        }

        public static string GetMd5Hash(MD5 md5Hash, string input)
        {
            byte[] data = md5Hash.ComputeHash(Encoding.UTF8.GetBytes(input));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString();
        }

        // provjera stringa i hasha
        public bool VerifyMd5Hash(MD5 md5Hash, string input, string hash)
        {
            string hashOfInput = GetMd5Hash(md5Hash, input);
            StringComparer comparer = StringComparer.OrdinalIgnoreCase;

            if (0 == comparer.Compare(hashOfInput, hash))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool jeLiPortir = false;

        public void PostaviPortira()
        {
            jeLiPortir = true;
        }

    }
}
