using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using NMK_17993.Entiteti;
using System.Security.Cryptography;
using NMK_17993;
using Oracle.ManagedDataAccess.Client;
using System.Threading;

namespace NMK_17993.Forme
{
    public partial class Registracija : Form
    {
        static Klinika novaKlinika;
        static Graphics g;
        static Pen pn;

        public Registracija(ref Klinika a)
        {
            novaKlinika = a;
            InitializeComponent();
        }
        

        public  void crtanjeKruga() {
            pn = new Pen(Color.Black);
            pn.Width += 2;
            g.DrawEllipse(pn, 90, 20, 100, 100);
        }
        Rectangle rect, rect2;
        public void  crtanjeUnutarKruga()
        {
             rect = new Rectangle(130, 30, 20, 80);
            rect2 = new Rectangle(100, 60, 80, 20);
            LinearGradientBrush lBrush = new LinearGradientBrush(rect, Color.Red, Color.Red, LinearGradientMode.Horizontal);

            g.FillRectangle(lBrush, rect);
            g.FillRectangle(lBrush, rect2);


            
            Point pt1 = new Point(129, 30);
            Point pt2 = new Point(129, 62);
            g.DrawLine(pn, pt1, pt2);
            Point pt3 = new Point(150, 30);
            Point pt4 = new Point(150, 60);
            g.DrawLine(pn, pt3, pt4);
            Point pt5 = new Point(128, 30);
            Point pt6 = new Point(152, 30);
            g.DrawLine(pn, pt5, pt6);
            Point pt7 = new Point(100, 60);
            Point pt8 = new Point(130, 60);
            g.DrawLine(pn, pt7, pt8);
            Point pt9 = new Point(149, 60);
            Point pt10 = new Point(180, 60);
            g.DrawLine(pn, pt9, pt10);

            Point pt11 = new Point(100, 80);
            Point pt12 = new Point(130, 80);
            g.DrawLine(pn, pt11, pt12);
            Point pt13 = new Point(149, 80);
            Point pt14 = new Point(180, 80);
            g.DrawLine(pn, pt13, pt14);

            Point pt15 = new Point(129, 79);
            Point pt16 = new Point(129, 112);
            g.DrawLine(pn, pt15, pt16);
            Point pt17 = new Point(150, 80);
            Point pt18 = new Point(150, 110);
            g.DrawLine(pn, pt17, pt18);
            Point pt19 = new Point(128, 110);
            Point pt20 = new Point(152, 110);
            g.DrawLine(pn, pt19, pt20);

            Point pt21 = new Point(100, 59);
            Point pt22 = new Point(100, 82);
            g.DrawLine(pn, pt21, pt22);
            Point pt23 = new Point(180, 59);
            Point pt24 = new Point(180, 82);
            g.DrawLine(pn, pt23, pt24);

        }


        void pomjeri()
        {
            Thread.Sleep(1500);
            this.Invoke(new Action(() => pictureBox3.Hide()));
                Thread.Sleep(1500);
                this.Invoke(new Action(() => pictureBox1.Hide()));
            this.Invoke(new Action(() => pictureBox2.Hide()));            
        }


        public void crtanje()
        {
            Thread nit1 = new Thread(pomjeri);
            nit1.Start();
        }

        // crtanje LOGO
        protected override void OnPaint(PaintEventArgs pe)
        {
            g = pe.Graphics;
            Font fnt = new Font("Microsoft Sans Serif", 10);
            g.DrawString("Naša Mala Klinika", fnt, new SolidBrush(Color.Black), 84, 130);
            crtanjeKruga(); crtanjeUnutarKruga();
        }

        private void button1_Click(object sender, EventArgs e)    
        {                                                           
                                                                  
            toolStripStatusLabel1.Text = "";
            toolStripStatusLabel1.ForeColor = Color.Red;
            errorProvider1.Clear();
            string hash = "";
            string korisnickoIme = textBox1.Text;
            string sifra = textBox2.Text;

            using (MD5 md5Hash = MD5.Create())
            {
                hash = NMK_17993.Entiteti.Uposlenik.GetMd5Hash(md5Hash, sifra);
            }

            bool jeLiUposlenik = true;
            Uposlenik a, b;


            try
            {
                a = novaKlinika.ListaUposlenih.Single(x => x.Username == korisnickoIme);
            }
            catch (Exception ex)
            {
                ex.GetType();
                jeLiUposlenik = false;
                errorProvider1.SetError(textBox1, "Pogrešan user!");
                toolStripStatusLabel1.Text = "Pogrešan unos!";
                textBox1.Clear();
                textBox2.Clear();
                textBox3.Clear();
                return;
            }

            try
            {
                b = novaKlinika.ListaUposlenih.Single(x => x.SifraUposlenikaMD5Hash == hash);
            }
            catch (Exception ex)
            {
                ex.GetType();
                jeLiUposlenik = false;
                errorProvider1.SetError(textBox2, "Pogrešan password!");
                toolStripStatusLabel1.Text = "Pogrešan unos!";
                textBox2.Clear();
                textBox3.Clear();
                return;
            }

            if (!Validacije.validacijaPassworda(textBox2.Text, textBox3.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Ne poklapaju se šifre! Unesite opet potvrdu.";
                errorProvider1.SetError(textBox3, "Ne poklapa se šifra.");
                textBox3.Clear();
                return;
            }

      
            if (jeLiUposlenik)
            {
                a = novaKlinika.ListaUposlenih.Single(x => x.Username == korisnickoIme && x.SifraUposlenikaMD5Hash == hash);
                if(a.GetType() == typeof(Doktor))           // ukoliko je Doktor
                {
                    OrdinacijaDoktora nov = new OrdinacijaDoktora(ref novaKlinika, a.MaticniBroj);
                    this.Hide();
                    nov.Show();
                }
                else if(a.GetType() == typeof(Uposlenik) && a.JeLiPortir)
                {
                    Portirnica forma = new Portirnica(ref novaKlinika);
                    this.Hide();
                    forma.Show();
                }
                else
                {
                    OrdinacijaUposlenika form = new OrdinacijaUposlenika(ref novaKlinika);
                    this.Hide();
                    form.Show();
                }
            }

            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
        }

        private void Registracija_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void prijavaPacijentaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            PacijentView pw = new PacijentView(ref novaKlinika);
            this.Hide();
            pw.Show();
        }

        private void refreshF5ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Registracija nova = new Registracija(ref novaKlinika);
            this.Hide();
            nova.Show(); 
        }

        private void Registracija_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F5)
            {
                Registracija nova = new Registracija(ref novaKlinika);
                this.Hide();
                nova.Show();
            }
        }

        private void textBox3_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            if (!Validacije.validacijaPassworda(textBox2.Text, textBox3.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Ne poklapaju se šifre! Unesite opet potvrdu.";
                errorProvider1.SetError(textBox3, "Ne poklapa se šifra.");
            }
        }

        private void zadatak2Zadaca4ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Hide();
            NovaForma a = new NovaForma();
            a.Show();
        }

        private void Registracija_Load(object sender, EventArgs e)
        {
            pictureBox2.Show();
            pictureBox3.Show();
            pictureBox1.Show();
            crtanje();
        }
    }
}
