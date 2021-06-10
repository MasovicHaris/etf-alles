using System;
using System.IO;
using System.Xml;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using UPS;

namespace UnitTestProject1
{
    [TestClass]
    public class TestoviUPS
    {
        // testirati ćemo 2 osnovne metode, dodavanje i brisanje u xml, sto predstavlja sustinsku logiku
        // samog zadatka
        [TestMethod]
        public void testDodavanjaUXml()
        {
            // testiramo dodavanje u xml
            Form1 forma = new Form1();
            string solutiondir = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName;
            string xmlFilePath = solutiondir + "\\redovi.xml";
            XmlDocument doc = new XmlDocument();
            doc.Load(xmlFilePath);
            int brojREdova = doc.DocumentElement.ChildNodes.Count;
            doc.Save(xmlFilePath);
            forma.klikDugmeDodaj("123", "123", "123", "123", "123", "123", "123", "123", "123");
            XmlDocument doc2 = new XmlDocument();
            doc2.Load(xmlFilePath);
            int brojREdovaN = doc2.DocumentElement.ChildNodes.Count;
            doc2.Save(xmlFilePath);
            Assert.AreEqual(brojREdova + 1, brojREdovaN);
        }

        [TestMethod]
        public void testBrisanjaIzXML()
        {
            // testiramo oduzimanje u xml
            Form1 forma = new Form1();
            string solutiondir = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.Parent.FullName;
            string xmlFilePath = solutiondir + "\\redovi.xml";
            XmlDocument doc = new XmlDocument();
            doc.Load(xmlFilePath);
            int brojREdova = doc.DocumentElement.ChildNodes.Count;
            doc.Save(xmlFilePath);
            if(brojREdova == 0)
            {
                forma.klikDugmeDodaj("123", "123", "123", "123", "123", "123", "123", "123", "123");
                brojREdova++;
            }
            forma.klikDugmeOduzmi(brojREdova - 1);
            XmlDocument doc2 = new XmlDocument();
            doc2.Load(xmlFilePath);
            int brojREdovaN = doc2.DocumentElement.ChildNodes.Count;
            doc2.Save(xmlFilePath);
            Assert.AreEqual(brojREdova - 1, brojREdovaN);
        }

    }
}
