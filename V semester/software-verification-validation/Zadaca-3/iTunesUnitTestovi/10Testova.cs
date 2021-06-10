using System;
using System.Collections.Generic;
using iTunes;
using iTunes.Klase;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace iTunesUnitTestovi {
    [TestClass]
    public class DesetDodatnihTestova {
        static OnlineStore testniStore;
        [ClassInitialize]
        public static void PripremaZaTest(TestContext t) {
            testniStore = new OnlineStore("/");

            testniStore.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4012888888881881", "amuminovic", "VVSJeTop");
            testniStore.registrirajKorisnika("Haris", "Masovic", DateTime.Now, "4024007195736334", "hmasovic", "HarisVoliSabana");
            testniStore.registrirajKorisnika("Bill", "Gates", DateTime.Now, "6011816573426759", "bgates", "C#FTW");

            testniStore.registrujNovuPjesmu(new Tune("Hallowed Be Thy Name", "Iron Maiden", "The Number Of The Beast", "Metal", 10.0, ".mp3", 433, 256, 70.11));
            testniStore.registrujNovuPjesmu(new Tune("Nothing else matters", "Metallica", "Metallica", "Metal", 9.5, ".mp3", 350, 256, 2.11));
            testniStore.registrujNovuPjesmu(new Tune("Run", "Foo Fighters", "Gold and Concrete", "Rock", 9.9, ".mp3", 413, 256, 5.05));
            testniStore.registrujNovuPjesmu(new Tune("Dumb", "Nirvana", "In Utero", "Rock", 9.0, ".mp3", 233, 256, 4.11));
            testniStore.registrujNovuPjesmu(new Tune("Kraljice srca moga", "Saban", "Single", "Folk", 2.0, ".mp3", 211, 256, 0)); //Free pjesma
            testniStore.registrujNovuPjesmu(new Tune("Nyan Cat", "Internet", "Single", "Techno", 11.0, ".mp3", 233, 256, -5)); // Pjesma koja daje pare
        }

        [TestMethod]
        public void ProvjeraPocetnogKredita() {
            foreach (var i in testniStore.RegMembers) {
                Assert.AreEqual(500, i.KorisnickiRacun.Stanje);
            }
        }

        [TestMethod]
        public void DaLiPostojiTestTrue() {
            Assert.IsTrue(testniStore.daLiPostoji("amuminovic"));
        }

        [TestMethod]
        public void DaLiPostojiTestFalse() {
            Assert.IsFalse(testniStore.daLiPostoji("amuminovic3"));
        }

        [TestMethod]
        public void ObrisiKorisnikaTest() {
            int brojKorisnika = testniStore.RegMembers.Count;

            bool obrisan = testniStore.obrisiKorisnika(testniStore.RegMembers[2].Id);

            Assert.IsTrue(obrisan);
            Assert.AreEqual(brojKorisnika - 1, testniStore.RegMembers.Count);

            //Vrati kako je bilo
            testniStore.registrirajKorisnika("Bill", "Gates", DateTime.Now, "6011816573426759", "bgates", "C#FTW");
        }

        [TestMethod]
        public void PretragaKorisnikaPoImenu() {
            testniStore.registrirajKorisnika("Bill", "Gates", DateTime.Now, "6011816573426759", "bgates1", "C#FTW");

            List<RegisteredMember> billovi = testniStore.pretragaKorisnikaPoImenu("Bill", "Gates");

            CollectionAssert.AllItemsAreInstancesOfType(billovi, typeof(RegisteredMember));
            CollectionAssert.IsSubsetOf(billovi, testniStore.RegMembers);
        }

        [TestMethod]
        public void PretragaKorisnikaValidnaVrijednost() {

            string id = testniStore.pretragaKorisnikaPoIdu(testniStore.RegMembers[0].Id).Id;

            StringAssert.Contains(id, testniStore.RegMembers[0].Id);
            
        }

        [TestMethod]
        public void DodajPjesmuValidnost() {

            string id = testniStore.registrujNovuPjesmu(new Tune("Everlong", "Foo Fighters", "The Color And The Shape", "Rock", 10.0, ".mp3", 433, 256, 70.11));

            StringAssert.Contains(testniStore.Pjesme[testniStore.Pjesme.Count - 1].Id, id);
        }

        [TestMethod]
        public void ProvjeriJedinstvenostIDTunea() {
            List<Tune> pjesme = new List<Tune>();
            List<string> idovi = new List<string>();
            for (int i = 0; i < 2000; i++) {
                pjesme.Add(new Tune("Everlong", "Foo Fighters", "The Color And The Shape", "Rock", 10.0, ".mp3", 433, 256, 70.11));
                idovi.Add(pjesme[i].Id);
            }
            CollectionAssert.AllItemsAreUnique(idovi);
        }

        [TestMethod]
        public void PretragaNazimIzvodjac() {
            List<Tune> pjesme = testniStore.pretragaPjesamaPoNazivuIzvodacu("Run", "Foo Fighters");

            CollectionAssert.AllItemsAreNotNull(pjesme);
            CollectionAssert.AllItemsAreInstancesOfType(pjesme, typeof(Tune));
        }

        [TestMethod]
        public void PrenesiPjesmuKorektnostTest() {
            //Priprema - Oba obaju biti golden members
            testniStore.RegMembers[0].GoldMember = true;
            testniStore.RegMembers[1].GoldMember = true;

            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[0].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[0].Id, testniStore.Pjesme[2].Id);
            testniStore.kupiPjesmu(testniStore.RegMembers[1].Id, testniStore.Pjesme[4].Id);

            double prosloStanje = testniStore.RegMembers[0].KorisnickiRacun.Stanje;
            CollectionAssert.Contains(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[0]);
            CollectionAssert.DoesNotContain(testniStore.RegMembers[1].MojaBiblioteka, testniStore.Pjesme[0]);

            testniStore.prenesiPjesmu(testniStore.RegMembers[0].Id, testniStore.RegMembers[1].Id, testniStore.Pjesme[0].Id);

            Assert.AreEqual(prosloStanje - 0.19, testniStore.RegMembers[0].KorisnickiRacun.Stanje);
            CollectionAssert.DoesNotContain(testniStore.RegMembers[0].MojaBiblioteka, testniStore.Pjesme[0]);
            CollectionAssert.Contains(testniStore.RegMembers[1].MojaBiblioteka, testniStore.Pjesme[0]);

            testniStore.RegMembers[0].KorisnickiRacun.Stanje = 500;
            testniStore.RegMembers[1].KorisnickiRacun.Stanje = 500;
        }
    }
}
