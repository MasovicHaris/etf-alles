using System;
using iTunes;
using iTunes.Exceptions;
using iTunes.Klase;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace iTunesUnitTestovi {
    [TestClass]
    public class IzuzeciTestovi {
        [TestMethod, ExpectedException(typeof(CreditCardInvalidException))]
        public void KreirajNevalidanRacun() {
            Racun r1 = new Racun("5", 1000);
        }

        [TestMethod, ExpectedException(typeof(NoMoneyException))]
        public void NaplatiViseOdPostojeceg() {
            Racun r1 = new Racun("4024007195736334", 0);
            r1.naplati(50);
        }

        [TestMethod, ExpectedException(typeof (Exception))]
        public void KreirajKorisnikaIstiUsername() {
            OnlineStore prodavnica = new OnlineStore("pozz");
            prodavnica.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4024007195736334", "amuminovic", "<3-VVS-<3");
            prodavnica.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4024007195736334", "amuminovic", "<3-VVS-<3");
        }

        [TestMethod, ExpectedException(typeof(UserNotFoundException))]
        public void PretragaNepostojeceImePrezime() {
            OnlineStore prodavnica = new OnlineStore("pozz");
            prodavnica.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4024007195736334", "amuminovic", "<3-VVS-<3");
            prodavnica.pretragaKorisnikaPoImenu("Samir", "Muminovic");
        }

        [TestMethod, ExpectedException(typeof(Exception))]
        public void UnaprijediGoldMembera() {
            OnlineStore prodavnica = new OnlineStore("pozz");
            prodavnica.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4024007195736334", "amuminovic", "<3-VVS-<3");
            prodavnica.RegMembers[0].GoldMember = true;
            prodavnica.unaprijediNaGoldMember(prodavnica.RegMembers[0].Id);
        }

        [TestMethod, ExpectedException(typeof(SongNotFoundException))]
        public void PretragaPjesmeNazivIzvodjac() {
            OnlineStore prodavnica = new OnlineStore("pozz");
            prodavnica.registrujNovuPjesmu(new Tune("Hallowed Be Thy Name", "Iron Maiden", "The Number Of The Beast", "Metal", 10.0, ".mp3", 433, 256, 70.11));
            prodavnica.pretragaPjesamaPoNazivuIzvodacu("Master Of Puppets", "Metallica");
        }

        [TestMethod, ExpectedException(typeof(Exception))]
        public void NegoldPrenosPjesme() {
            OnlineStore prodavnica = new OnlineStore("pozz");
            prodavnica.registrirajKorisnika("Amir", "Muminovic", DateTime.Now, "4024007195736334", "amuminovic", "<3-VVS-<3");
            prodavnica.registrirajKorisnika("Haris", "Masovic", DateTime.Now, "4024007195736334", "hmasovic", "HarisVoliSabana");
            prodavnica.registrujNovuPjesmu(new Tune("Hallowed Be Thy Name", "Iron Maiden", "The Number Of The Beast", "Metal", 10.0, ".mp3", 433, 256, 70.11));
            prodavnica.RegMembers[0].GoldMember = true;
            prodavnica.prenesiPjesmu(prodavnica.RegMembers[0].Id, prodavnica.RegMembers[1].Id, prodavnica.Pjesme[0].Id);
        }
    }
}
