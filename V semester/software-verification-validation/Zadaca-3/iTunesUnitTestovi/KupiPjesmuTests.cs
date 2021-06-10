using System;
using System.Collections.Generic;
using iTunes;
using iTunes.Exceptions;
using iTunes.Klase;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace iTunesUnitTestovi {
    
    [TestClass]
    public class KupiPjesmuTests {
        static OnlineStore testniStore;

        [ClassInitialize]
        public static void PripremaZaTest(TestContext t) {
            testniStore = new OnlineStore("/");

            testniStore.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4012888888881881", "amuminovic", "VVSJeTop");
            testniStore.registrirajKorisnika("Haris", "Masovic", DateTime.Now, "4024007195736334", "hmasovic", "HarisVoliSabana");
            testniStore.registrirajKorisnika("Bill", "Gates", DateTime.Now, "6011816573426759", "bgates", "C#FTW");
            testniStore.RegMembers[2].KorisnickiRacun.Stanje = 0; //Zao nam je bill, ali ovdje si broke :(

            testniStore.registrujNovuPjesmu(new Tune("Hallowed Be Thy Name", "Iron Maiden", "The Number Of The Beast", "Metal", 10.0, ".mp3", 433, 256, 70.11));
            testniStore.registrujNovuPjesmu(new Tune("Nothing else matters", "Metallica", "Metallica", "Metal", 9.5, ".mp3", 350, 256, 2.11));
            testniStore.registrujNovuPjesmu(new Tune("Run", "Foo Fighters", "Gold and Concrete", "Rock", 9.9, ".mp3", 413, 256, 5.05));
            testniStore.registrujNovuPjesmu(new Tune("Dumb", "Nirvana", "In Utero", "Rock", 9.0, ".mp3", 233, 256, 4.11));
            testniStore.registrujNovuPjesmu(new Tune("Kraljice srca moga", "Saban", "Single", "Folk", 2.0, ".mp3", 211, 256, 0)); //Free pjesma
            testniStore.registrujNovuPjesmu(new Tune("Nyan Cat", "Internet", "Single", "Techno", 11.0, ".mp3", 233, 256, -5)); // Pjesma koja daje pare
        }

        [TestCleanup]
        public void VratiVrijednosti() {
            testniStore.RegMembers[0].GoldMember = false;
            testniStore.RegMembers[0].KorisnickiRacun.Stanje = 500;
            testniStore.RegMembers[0].MojaBiblioteka = new List<Tune>();
        }

        [TestMethod, ExpectedException(typeof(UserNotFoundException))]
        public void KupovinaNepostojeciID() {
            testniStore.kupiPjesmu("", "");
        }

        [TestMethod, ExpectedException(typeof(NoMoneyException))]
        public void KupovinaBezNovaca() {
            testniStore.kupiPjesmu(testniStore.RegMembers[2].Id, testniStore.Pjesme[0].Id);
        }

        [TestMethod, ExpectedException(typeof(NoMoneyException))]
        public void KupovinaNepostojecePjesme() {
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, "");
        }

        [TestMethod, ExpectedException(typeof(SongNotFoundException))]
        public void KupovinaNepostojecePjesmeGoldMember() {
            testniStore.RegMembers[0].GoldMember = true;
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, "");
        }

        [TestMethod]
        public void KupovinaPjesmeRegularno() {
            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 0);

            double prosloStanje = testniStore.RegMembers[0].KorisnickiRacun.Stanje;
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[0].Id);

            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 1);
            Assert.AreNotEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje, prosloStanje);
            Assert.AreEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje + testniStore.Pjesme[0].Price, prosloStanje);

            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[0]);
        }

        [TestMethod]
        public void KupovinaPjesmeGoldMembership() {
            //Postavi korisnika za sljedeci test da bude gold memeber
            testniStore.RegMembers[0].GoldMember = true;

            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 0);

            double prosloStanje = testniStore.RegMembers[0].KorisnickiRacun.Stanje;
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[0].Id);

            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 1);
            Assert.AreNotEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje, prosloStanje);
            Assert.AreEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje + .9 * testniStore.Pjesme[0].Price, prosloStanje);

            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[0]);
        }

        [TestMethod]
        public void KupovinaVisePjesama() {
            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 0);

            double prosloStanje = testniStore.RegMembers[0].KorisnickiRacun.Stanje;
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[1].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[0].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[2].Id);

            Assert.AreEqual(testniStore.RegMembers[0].MojaBiblioteka.Count, 3);
            Assert.AreNotEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje, prosloStanje);

            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[0]);
            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[1]);
            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[2]);
        }

        [TestMethod] 
        public void JedinstvenostPjesama() {
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[1].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[1].Id);
            CollectionAssert.AllItemsAreUnique(testniStore.RegMembers[0].MojaBiblioteka);
        }

        [TestMethod]
        public void KupljenjePjesmePodskupSvihPjesama() {
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[0].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[1].Id);
            CollectionAssert.IsSubsetOf(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme);
        }

        [TestMethod]
        public void KupovinaBesplatnePjesme() {
            double stanje = testniStore.RegMembers[0].KorisnickiRacun.Stanje;
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[4].Id);

            Assert.AreEqual(testniStore.RegMembers[0].KorisnickiRacun.Stanje, stanje);
        }
    }
}
