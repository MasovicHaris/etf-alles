using System;
using iTunes;
using iTunes.Klase;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace iTunesUnitTestovi {

    [TestClass]
    public class DataDrivenTests {
        private TestContext testContextInstance;
        public TestContext TestContext {
            get { return testContextInstance; }
            set { testContextInstance = value; }
        }

        [DataSource("Microsoft.VisualStudio.TestTools.DataSource.XML", "Tests.xml", "osoba",DataAccessMethod.Sequential), DeploymentItem("Tests.xml"), TestMethod]
        public void RegistrujKorisnikeTest() {
            OnlineStore o = new OnlineStore("banana");
            o.registrirajKorisnika(Convert.ToString(TestContext.DataRow["ime"]),
                Convert.ToString(TestContext.DataRow["prezime"]),
                Convert.ToDateTime(TestContext.DataRow["datumRodjenja"]),
                Convert.ToString(TestContext.DataRow["bkk"]),
                Convert.ToString(TestContext.DataRow["username"]),
                Convert.ToString(TestContext.DataRow["password"]));           
            Assert.IsTrue(o.RegMembers[o.RegMembers.Count - 1].Ime == Convert.ToString(TestContext.DataRow["ime"]));
            Assert.IsTrue(o.RegMembers[o.RegMembers.Count - 1].Prezime == Convert.ToString(TestContext.DataRow["prezime"]));
        }

        [DataSource("Microsoft.VisualStudio.TestTools.DataSource.XML", "pjesme.xml","pjesma", DataAccessMethod.Sequential), DeploymentItem("pjesme.xml"), TestMethod]
        public void RegistrujPjesmuTest() {
            Tune t = new Tune(
                Convert.ToString(TestContext.DataRow["title"]),
                Convert.ToString(TestContext.DataRow["artist"]),
                Convert.ToString(TestContext.DataRow["album"]),
                Convert.ToString(TestContext.DataRow["genre"]),
                Convert.ToDouble(TestContext.DataRow["rating"]),
                Convert.ToString(TestContext.DataRow["format"]),
                Convert.ToInt32(TestContext.DataRow["length"]),
                Convert.ToInt32(TestContext.DataRow["bitRate"]),
                Convert.ToDouble(TestContext.DataRow["price"])
                );
            Assert.AreEqual(t.Title, Convert.ToString(TestContext.DataRow["title"]));
            Assert.AreEqual(t.Artist, Convert.ToString(TestContext.DataRow["artist"]));
            Assert.AreEqual(t.Price, Convert.ToDouble(TestContext.DataRow["price"]));
        }
    }
}
