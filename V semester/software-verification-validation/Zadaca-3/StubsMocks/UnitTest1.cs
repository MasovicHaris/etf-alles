using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StubsMocks {

    public class KonverzijaStub {
        public KonverzijaStub() {
        }

        public Double KMUBTC(double KM) {
            return new double();
        }
    }

    public class KonverzijaMock {
        int brojPoziva;

        public KonverzijaMock() {
            BrojPoziva = 0;
        }

        public int BrojPoziva { get => brojPoziva; set => brojPoziva = value; }

        public Double KMUBTC(double KM) {
            BrojPoziva++;
            return new double();
        }
    }

    [TestClass]
    public class KonverijaValuta {
        [TestMethod]
        public void StubTest() {
            KonverzijaStub k = new KonverzijaStub();

            double ans = k.KMUBTC(6619.55);

            Assert.IsInstanceOfType(ans, typeof(Double));

        }

        [TestMethod]
        public void MockTest() {
            KonverzijaMock k = new KonverzijaMock();
            double ans = k.KMUBTC(5);
            Assert.IsInstanceOfType(ans, typeof(Double));
            Assert.AreEqual(1, k.BrojPoziva);
        }
    }

    interface iEvidentirajPosiljku{
        Boolean Odobri(Posiljka p);
        void Evidentiraj(Posiljka p);
    }

    public class Posiljka : iEvidentirajPosiljku {
        //Podaci o posiljci
        String polaziste;
        String destinacija;
        Double distanca;
        Double tezina;
        Decimal taksa;
        Int32 hitnost;
        Double CijenaIsporuke;

        //Podaci o posiljaocu
        String ime;
        String prezime;
        String jmbg;
        String telefon;
        String komentar;

        Boolean odobrena;
        Boolean spasena;

        public Posiljka(string polaziste, string destinacija, double distanca, double tezina, decimal taksa, int hitnost, double cijenaIsporuke, string ime, string prezime, string jmbg, string telefon, string komentar) {
            this.polaziste = polaziste;
            this.destinacija = destinacija;
            this.distanca = distanca;
            this.tezina = tezina;
            this.taksa = taksa;
            this.hitnost = hitnost;
            CijenaIsporuke = cijenaIsporuke;
            this.ime = ime;
            this.prezime = prezime;
            this.jmbg = jmbg;
            this.telefon = telefon;
            this.komentar = komentar;
            Odobrena = false;
        }

        public bool Odobrena { get => odobrena; set => odobrena = value; }
        public bool Spasena { get => spasena; set => spasena = value; }

        public void Evidentiraj(Posiljka p) {
            if (p.Odobrena) {
                p.Spasena = true;
                return;
            }
            p.Spasena = false;
        }

        public Boolean Odobri(Posiljka p) {
            return true;
        }
    }

    [TestClass]
    public class EvidencijaPosiljki {
        [TestMethod]
        public void SpasavanjeNeodobrenePosiljke() {
            Posiljka p = new Posiljka("BIH", "USA", 10121.16, 20, 0.1m, 5, 20, "Amir", "Muminovic", "5", "banana", ":O");

            Boolean ans = p.Odobri(p);
            Assert.IsInstanceOfType(ans, typeof(Boolean));
            p.Evidentiraj(p);
            Assert.IsFalse(p.Spasena);
        }
        [TestMethod]
        public void SpasavanjeOdobrenePosiljke() {
            Posiljka p = new Posiljka("BIH", "USA", 10121.16, 20, 0.1m, 5, 20, "Amir", "Muminovic", "5", "banana", ":O");

            Boolean ans = p.Odobri(p);
            Assert.IsInstanceOfType(ans, typeof(Boolean));
            p.Odobrena = true;
            p.Evidentiraj(p);
            Assert.IsTrue(p.Spasena);
        }
    }
}
