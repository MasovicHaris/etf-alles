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
    public partial class PacijentView : Form
    {
        Klinika novaKlinika;
        public PacijentView(ref Klinika a)
        {
            novaKlinika = a;
            InitializeComponent();
        }

        private void PacijentView_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void izlazToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Registracija nova = new Registracija(ref novaKlinika);
            this.Hide();
            nova.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                errorProvider1.SetError(textBox1, "Unesite JMBG!");
                toolStripStatusLabel1.Text = "Unesite JMBG pacijenta!";
                return;
            }

            try
            {
                Regex rgx2 = new Regex("^(\\d{13})?$");
                if (novaKlinika.ListaPacijenata.Capacity != 0 && novaKlinika.ListaPacijenata.Count != 0)
                {
                    if (!rgx2.IsMatch(textBox1.Text))
                    {
                        errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                        toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                        return;
                    }
                    if (!Validacije.provjeraJMBG(textBox1.Text))
                    {
                        errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                        toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                        return;
                    }
                }
                else
                {
                    toolStripStatusLabel1.Text = "Trenutno nema registrovanih pacijenata!";
                    return;
                }

                bool hehe = false;
                Parallel.ForEach(novaKlinika.ListaPacijenata, p => { 
                    if (textBox1.Text == p.MaticniBroj) hehe = true;
                });

                if (!hehe)
                {
                    textBox1.Clear();
                    errorProvider1.Clear();
                    toolStripStatusLabel1.Text = "Taj pacijent nije registrovan u ovoj klinici!";
                    return;
                }

                errorProvider1.Clear();
                toolStripStatusLabel1.Text = "";

                PacijentPregled pp = new PacijentPregled(ref novaKlinika, textBox1.Text);
                pp.ShowDialog();
                textBox1.Clear();
            }catch(Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                return;
            }
        }

        private void PacijentView_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.ForeColor = Color.Red;
        }

        private void textBox1_Validated(object sender, EventArgs e)
        {
            try
            {
                Regex rgx2 = new Regex("^(\\d{13})?$");
                if (novaKlinika.ListaPacijenata.Capacity != 0 && novaKlinika.ListaPacijenata.Count != 0)
                {
                    if (!rgx2.IsMatch(textBox1.Text))
                    {
                        errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                        toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                        return;
                    }
                    if (!Validacije.provjeraJMBG(textBox1.Text))
                    {
                        errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                        toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                        return;
                    }
                }
                else
                {
                    toolStripStatusLabel1.Text = "Trenutno nema registrovanih pacijenata!";
                    return;
                }
            }catch(Exception ex)
            {
                ex.GetType();
                errorProvider1.SetError(textBox1, "Neispravan JMBG!");
                toolStripStatusLabel1.Text = "Unesite ispravan JMBG pacijenta!";
                return;
            }
        }
    }
}
