using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using iTunes.Klase;
using iTunes;
using iTunes.Exceptions;
using System.Collections.Generic;

namespace TestoviTDD
{
    [TestClass]
    public class Testovi
    {
        
        [TestMethod]
        public void provjeraUmjetnikAlbumZanr()
        {
            RegisteredMember noviKorisnik = new RegisteredMember("Haris", "Masovic", DateTime.Now, "4012888888881881", "hmasovic1", "password");
            try
            {
                List<String> vracenaVrijednost1 = noviKorisnik.VratiTopDeset("u");
                List<String> vracenaVrijednost2 = noviKorisnik.VratiTopDeset("a");
                List<String> vracenaVrijednost3 = noviKorisnik.VratiTopDeset("z");
                Assert.AreEqual(true, true);
            }
            catch (Exception)
            {
                Assert.AreEqual(true, false);
            }
        }   

        [TestMethod]
        [ExpectedException(typeof(Exception), "Nije dobro specificiran kriterij.")]
        public void provjeraException()
        {
            RegisteredMember noviKorisnik = new RegisteredMember("Haris", "Masovic", DateTime.Now, "4012888888881881", "hmasovic1", "password");
            List<String> vracenaVrijednost1 = noviKorisnik.VratiTopDeset("nestolijevo");
        }


        [TestMethod]
        public void vrati10Umjetnika()
        {
            RegisteredMember noviKorisnik = new RegisteredMember("Haris", "Masovic", DateTime.Now, "4012888888881881", "hmasovic1", "password");
            // koristimo pomocni stub pomocu kojeg generisemo podatke za testiranje
            PomocniStub novi = new PomocniStub();
            List<String> rez = novi.odradiUmjetnike(noviKorisnik); 
            List<String> vracenaVrijednost1 = noviKorisnik.VratiTopDeset("u");

            CollectionAssert.AreEqual(rez, vracenaVrijednost1);
        }

        [TestMethod]
        public void vrati10Albuma()
        {
            RegisteredMember noviKorisnik = new RegisteredMember("Haris", "Masovic", DateTime.Now, "4012888888881881", "hmasovic1", "password");
            // koristimo pomocni stub pomocu kojeg generisemo podatke za testiranje
            PomocniStub novi = new PomocniStub();
            List<String> rez = novi.odradiAlbume(noviKorisnik);
            List<String> vracenaVrijednost1 = noviKorisnik.VratiTopDeset("a");

            CollectionAssert.AreEqual(rez, vracenaVrijednost1);
        }

        [TestMethod]
        public void vrati10Zanrova()
        {
            RegisteredMember noviKorisnik = new RegisteredMember("Haris", "Masovic", DateTime.Now, "4012888888881881", "hmasovic1", "password");
            // koristimo pomocni stub pomocu kojeg generisemo podatke za testiranje
            PomocniStub novi = new PomocniStub();
            List<String> rez = novi.odradiZanrove(noviKorisnik);
            List<String> vracenaVrijednost1 = noviKorisnik.VratiTopDeset("z");

            CollectionAssert.AreEqual(rez, vracenaVrijednost1);
        }

    }
}
