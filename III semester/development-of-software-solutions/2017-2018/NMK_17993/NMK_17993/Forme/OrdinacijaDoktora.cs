using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NMK_17993.Entiteti;

namespace NMK_17993.Forme
{
    public partial class OrdinacijaDoktora : Form
    {
        Klinika novaKlinika;
        string maticniDoktoraa;
        public OrdinacijaDoktora(ref Klinika a, string maticniDoktora)
        {
            novaKlinika = a;
            maticniDoktoraa = maticniDoktora;
            InitializeComponent();
        }

        private void OrdinacijaDoktora_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void odjavaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Registracija reg = new Registracija(ref novaKlinika);
            this.Hide();
            reg.Show();
        }

        Pregled k;
        private void button1_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "";
            errorProvider1.Clear();
            if (comboBox1.SelectedItem == null)
            {
                toolStripStatusLabel1.Text = "Molimo vas izaberite pacijenta (ukoliko nemate izbora, nemate ni aktivnih pregleda)!";
                errorProvider1.SetError(comboBox1, "Izaberite pacijenta!");
                return;
            }
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled preg in p.LicniKarton.SpisakPregleda1)
                {
                    if (preg.Pregled1 == false && comboBox1.Text == p.MaticniBroj)
                    {
                        preg.MisljenjeDoktora = textBox2.Text;
                        preg.Ordinacija.StanjeOrdinacije = Ordinacija.stanje.Slobodno;
                        preg.Pregled1 = true;

                        break;
                    }
                }
            }

            foreach (Uposlenik u in novaKlinika.ListaUposlenih)
            {
                if (u is Doktor)
                {
                    Doktor d = u as Doktor;
                    d.Zauzet = false;
                    d.BrojPregledanihPacijenata++;
                    break;
                }
            }


            // updateovanje comboboxa
            comboBox1.Items.Clear();
            Uposlenik novi = novaKlinika.ListaUposlenih.Single(x => x.MaticniBroj == maticniDoktoraa);
            Doktor a = novi as Doktor;

            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled preg in p.LicniKarton.SpisakPregleda1)
                {
                    bool pregledPregledaj = false;
                    foreach (Ordinacija ord in a.SpecijalistaZaOrdinacije)
                    {
                        if (preg.Ordinacija.NazivOrdinacije == ord.NazivOrdinacije && preg.Pregled1 == false)
                        {
                            pregledPregledaj = true; break;
                        }
                    }


                    if (pregledPregledaj)
                    {
                        comboBox1.Items.Add(p.MaticniBroj);
                    }
                }
            }
            comboBox1.Text = "";
            textBox2.Clear();
            textBox1.Clear();
            textBox3.Clear();
            radioButton1.Checked = false;
            radioButton2.Checked = false;
            toolStripStatusLabel1.Text = "Uspješno završen pregled!";
        }

        private void OrdinacijaDoktora_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.ForeColor = Color.Red;
            Uposlenik novi = novaKlinika.ListaUposlenih.Single(x => x.MaticniBroj == maticniDoktoraa);
            Doktor a = novi as Doktor;

            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled preg in p.LicniKarton.SpisakPregleda1)
                {
                    bool pregledPregledaj = false;
                    foreach (Ordinacija ord in a.SpecijalistaZaOrdinacije)
                    {
                        if (preg.Ordinacija.NazivOrdinacije == ord.NazivOrdinacije && preg.Pregled1 == false)
                        {
                            pregledPregledaj = true; break;
                        }
                    }


                    if (pregledPregledaj)
                    {
                        comboBox1.Items.Add(p.MaticniBroj);
                    }
                }
            }
            comboBox1.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            comboBox1.AutoCompleteSource = AutoCompleteSource.ListItems;


        }

        private void button2_Click(object sender, EventArgs e)
        {
            Terapija nova = new Terapija();
            nova.NazivTerapije = textBox1.Text;
            nova.DodatneSitnice = textBox3.Text;
            nova.DatumPotpisivanjeTerapije = DateTime.Today;

            if (radioButton1.Checked) nova.VrstaTerap1 = Terapija.vrstaTerapije.dugorocna;
            else nova.VrstaTerap1 = Terapija.vrstaTerapije.kratkorocna;
            foreach (Uposlenik u in novaKlinika.ListaUposlenih)
            {
                if (u is Doktor)
                {
                    Doktor d = u as Doktor;
                    if (maticniDoktoraa == d.MaticniBroj)
                    {
                        nova.OnajKojiIzdao = d;
                        break;
                    }
                }
            }
            k.PregledTerapija.Add(nova);
            textBox1.Clear();
            textBox3.Clear();
            radioButton1.Checked = false;
            radioButton2.Checked = false;
            toolStripStatusLabel1.Text = "Uspješno dodana, jedna od moguće više, terapija za ovaj pregled!";
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled preg in p.LicniKarton.SpisakPregleda1)
                {
                    if (preg.Pregled1 == false && comboBox1.Text == p.MaticniBroj)
                    {
                        k = preg;
                        break;
                    }
                }
            }
        }

        private void refreshF5ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OrdinacijaDoktora nova = new OrdinacijaDoktora(ref novaKlinika, maticniDoktoraa);
            this.Hide();
            nova.Show();
        }

        private void OrdinacijaDoktora_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F5)
            {
                OrdinacijaDoktora nova = new OrdinacijaDoktora(ref novaKlinika, maticniDoktoraa);
                this.Hide();
                nova.Show();
            }
        }
    }
}



