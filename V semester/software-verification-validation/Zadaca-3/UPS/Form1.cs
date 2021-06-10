using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;

namespace UPS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            double finalnaCijena = 0.0;

            double distanca = Convert.ToDouble(textBox2.Text);
            double tezinaPosiljke = Convert.ToDouble(textBox3.Text);
            double takseUpROCENTIMA = Convert.ToDouble(textBox4.Text);
            int koliko = trackBar1.Value;

            finalnaCijena = (distanca / 95.643) + tezinaPosiljke * ((1 + koliko * 0.1) * distanca) * 0.00055;

            finalnaCijena = finalnaCijena + (finalnaCijena * (takseUpROCENTIMA));

            textBox1.Text = finalnaCijena.ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public void klikDugmeDodaj(String prvi, String drugi, String treci, String c, String p, String sest,
            String sedmi, String osmi, String deveti)
        {
            string xmlFilePath = Path.GetDirectoryName(Path.GetDirectoryName(Path.GetDirectoryName(System.IO.Directory.GetCurrentDirectory()))) + "\\redovi.xml";
            XDocument doc = XDocument.Load(xmlFilePath);
            XElement school = doc.Element("redovi");

            school.Add(new XElement("red", new XElement("distanca", prvi), new XElement("tezina", drugi),
                new XElement("takse", treci), new XElement("hitnost", c), new XElement("posiljaoc",
                p + " " + sest),
                new XElement("jmbg", sedmi), new XElement("kontakt", osmi), new XElement("komentar", deveti)));
            doc.Save(xmlFilePath);

            DataSet dataSet = new DataSet();
      
            dataSet.ReadXml(xmlFilePath);
            dataGridView1.DataSource = dataSet.Tables[0];
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int koliko = trackBar1.Value;
            klikDugmeDodaj(textBox2.Text, textBox3.Text, textBox4.Text, koliko.ToString(), textBox5.Text.ToString(), textBox6.Text.ToString(), textBox7.Text, textBox8.Text, textBox9.Text);
        }


        public void klikDugmeOduzmi(int b)
        {
            int kojaKliknuta = b;

            string xmlFilePath = Path.GetDirectoryName(Path.GetDirectoryName(Path.GetDirectoryName(System.IO.Directory.GetCurrentDirectory()))) + "\\redovi.xml";

            XmlDocument doc = new XmlDocument();
            doc.Load(xmlFilePath);

            if (doc.DocumentElement.ChildNodes.Count > kojaKliknuta) doc.DocumentElement.RemoveChild(doc.DocumentElement.ChildNodes[kojaKliknuta]);
            doc.Save(xmlFilePath);

            DataSet dataSet = new DataSet();

            dataSet.ReadXml(xmlFilePath);
            if (doc.DocumentElement.ChildNodes.Count == 0) dataGridView1.DataSource = "Nema podataka.";
            else dataGridView1.DataSource = dataSet.Tables[0];
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            klikDugmeOduzmi(e.RowIndex);   
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }
    }
}
