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
using System.Text.RegularExpressions;

namespace NMK_17993.Forme
{
    public partial class OrdinacijaUposlenika : Form
    {
        Klinika novaKlinika;
        public OrdinacijaUposlenika(ref Klinika a)
        {
            novaKlinika = a;
            InitializeComponent();
        }

        private void OrdinacijaUposlenika_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
        static bool imalPacijenta = false;
        static bool helpac1 = false;
        static bool helpac2 = false;
        private void button1_Click(object sender, EventArgs e)
        {
            helpac1 = false;
            helpac2 = false;
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            // karton je zamisljen kao anamneza datih pacijenata
            // pri cemu se nikad ne mjenja za svakog pacijenta
            // odnosno pacijent misli da moze mjenjati karton
            // zapravo samo mjenja svoj opis
            // pri cemu broj posjeta ostaje isti i sve ostale bitne stvari za kliniku 

            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal)
                {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }

                if (novaKlinika.ListaPacijenata.Capacity != 0 && novaKlinika.ListaPacijenata.Count != 0)
                {
                    foreach (Pacijent p in novaKlinika.ListaPacijenata)
                    {
                        if (p.MaticniBroj == textBox1.Text)
                        {
                             imalPacijenta = true;
                             bool dodan = false;
                              foreach (string a in comboBox1.Items)
                                { 
                                    if (a.Substring(a.Length - 13, 13) == p.MaticniBroj) { dodan = true; break; }
                                }
                            if(!dodan) comboBox1.Items.Add(p.Ime + " " + p.Prezime + " JMBG:" + p.MaticniBroj);
                         }

                    if ((p.LicniKarton.PrijasnjeBolesti.Count != 0 || p.LicniKarton.SadasnjeBolesti.Count != 0) && imalPacijenta)
                    {
                        errorProvider1.Clear();
                        textBox1.Clear();
                        textBox2.Clear();
                        textBox3.Clear();
                        textBox4.Clear();
                        textBox5.Clear();
                    }
                    }
                }
                else toolStripStatusLabel1.Text = "Trenutno ne mozete kreirati novi karton za pacijenta, jer u klinici nema registrovanih pacijenata!";

            
            if(imalPacijenta)
            {
                errorProvider1.Clear();
                toolStripStatusLabel1.Text = "Uspješno kreiran/ažuriran karton za datog pacijenta!";
                textBox1.Clear();
                textBox2.Clear();
                textBox3.Clear();
                textBox4.Clear();
                textBox5.Clear();
            }
        }

        private void OrdinacijaUposlenika_Load(object sender, EventArgs e)
        {
            comboBox1.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            comboBox1.AutoCompleteSource = AutoCompleteSource.ListItems;

            foreach(Pacijent p in novaKlinika.ListaPacijenata)
            {
                if(p.LicniKarton.PrijasnjeBolesti.Count !=0 || p.LicniKarton.SadasnjeBolesti.Count != 0)
                {
                    comboBox1.Items.Add(p.Ime + " " + p.Prezime + " JMBG:" + p.MaticniBroj );
                }
            }


            toolStripStatusLabel1.ForeColor = Color.Red;
            toolStripStatusLabel1.Text = "Ukoliko pacijent nema kreiran karton, pritiskom dugmeta bit će kreiran. Ukoliko ima, istom opcijom, bit će ažuriran!";
        }

        private void izlazToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Registracija nova = new Registracija(ref novaKlinika);
            this.Hide();
            nova.Show();
        }

        private void textBox1_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal) {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal)
                {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }

            if(e.KeyCode == Keys.Enter)
            {
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text)
                    {
                        p.LicniKarton.PrijasnjeAlergije.Add(textBox2.Text);
                    }
                }
                toolStripStatusLabel1.Text = "Podatak unesen!";
                textBox2.Clear();
            }
        }

        private void textBox3_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal)
                {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }


            if (e.KeyCode == Keys.Enter)
            {
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (!helpac1) { p.LicniKarton.SadasnjeAlergije.Clear(); helpac1 = true; }
                    if (p.MaticniBroj == textBox1.Text)
                    {
                        p.LicniKarton.SadasnjeAlergije.Add(textBox3.Text);
                    }
                }
                toolStripStatusLabel1.Text = "Podatak unesen!";
                textBox3.Clear();
            }
        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal)
                {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }

            if (e.KeyCode == Keys.Enter)
            {
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text)
                    {
                        p.LicniKarton.PrijasnjeBolesti.Add(textBox4.Text);
                    }
                }
                toolStripStatusLabel1.Text = "Podatak unesen!";
                textBox4.Clear();
            }
        }

        private void textBox5_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (!Validacije.provjeraJMBG(textBox1.Text))
                {
                    errorProvider1.SetError(textBox1, "Neispravan JMBG");
                    toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                    return;
                }

                bool imal = false;
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (p.MaticniBroj == textBox1.Text) imal = true;
                }

                if (!imal)
                {
                    errorProvider1.SetError(textBox1, "Nepostoji takav pacijent u");
                    toolStripStatusLabel1.Text = "Molimo vas unesite registrovanog pacijenta!";
                    return;
                }


            }
            catch (Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG");
                toolStripStatusLabel1.Text = "Molim vas unesite ispravan JMBG";
                return;
            }

            if (e.KeyCode == Keys.Enter)
            {
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    if (!helpac2) { p.LicniKarton.SadasnjeBolesti.Clear(); helpac2 = true; }
                    if (p.MaticniBroj == textBox1.Text)
                    {
                        p.LicniKarton.SadasnjeBolesti.Add(textBox5.Text);
                    }
                }
                toolStripStatusLabel1.Text = "Podatak unesen!";
                textBox5.Clear();
            }
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string izabrani = comboBox1.Text.Substring(comboBox1.Text.Length - 13, 13);
            OrdinacijaUposlenikaView nova = new OrdinacijaUposlenikaView(ref novaKlinika, izabrani);
            nova.ShowDialog();
            comboBox1.Text = "";
        }
    }
}
