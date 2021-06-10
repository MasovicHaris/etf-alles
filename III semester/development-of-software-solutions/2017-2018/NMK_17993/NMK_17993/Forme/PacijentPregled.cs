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
    public partial class PacijentPregled : Form
    {
        Klinika novaKlinika;
        string jmbg;
        public PacijentPregled(ref Klinika a, string ab)
        {
            jmbg = ab;
            novaKlinika = a;
            InitializeComponent();
        }

        private void PacijentPregled_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.ForeColor = Color.Red;
            List<Ordinacija> nove = novaKlinika.ListaOrdinacija.FindAll(x => x.Jelradi == Ordinacija.funkcija.radi);
            Parallel.ForEach(nove, d => {
                listBox1.Items.Add(d.NazivOrdinacije);
            });
            foreach(Pacijent p in novaKlinika.ListaPacijenata)
            {
                if(p.MaticniBroj == jmbg)
                {
                   userControl11.postaviSliku(p.SlikaPacijenta);
                }
            }

            int i = 1;
            treeView1.Nodes.Clear();

            // prijasnje alergije
            TreeNode pa = new TreeNode("Prijašnje alergije: ");
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.PrijasnjeAlergije)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa.Nodes.Add(pa1);
                    }
                }
            });

            // sadašnje alergije
            TreeNode sad = new TreeNode("Sadašnje alergije: ");
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.SadasnjeAlergije)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        sad.Nodes.Add(pa1);
                    }
                }
            });

            // prijasnje bolesti
            TreeNode pa23 = new TreeNode("Prijašnje bolesti: ");
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.PrijasnjeBolesti)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa23.Nodes.Add(pa1);
                    }
                }
            });

            // sadasnje bolesti 
            TreeNode pa535 = new TreeNode("Sadašnje bolesti: ");
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.SadasnjeBolesti)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa535.Nodes.Add(pa1);
                    }
                }
            });

            treeView1.Nodes.Add(pa);
            treeView1.Nodes.Add(sad);
            treeView1.Nodes.Add(pa23);
            treeView1.Nodes.Add(pa535);
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                Parallel.ForEach(p.LicniKarton.SpisakPregleda1, pp =>
                {
                    if (pp.Pregled1)
                    {
                        bool jeste = false;
                        string onaj = "";
                        TreeNode pregled = new TreeNode("Pregled broj: " + i);
                        foreach (Terapija tt in pp.PregledTerapija)
                        {
                            jeste = true;
                            onaj = tt.OnajKojiIzdao.Ime + " " + tt.OnajKojiIzdao.Prezime;
                            TreeNode terpaija = new TreeNode("Terapija: " + tt.NazivTerapije);
                            TreeNode terpaija2 = new TreeNode("Dodatne stvari: " + tt.DodatneSitnice);
                            TreeNode terpaija3 = new TreeNode("Tip terapije: " + tt.VrstaTerap1.ToString());
                            TreeNode terpaija4 = new TreeNode("Datum terapije: " + tt.DatumPotpisivanjeTerapije.ToShortDateString());
                            pregled.Nodes.Add(terpaija);
                            terpaija.Nodes.Add(terpaija2); terpaija.Nodes.Add(terpaija3); terpaija.Nodes.Add(terpaija4);

                        }
                        TreeNode misljenje = new TreeNode("Mišljenje doktora: " + pp.MisljenjeDoktora);
                        TreeNode ordinacija = new TreeNode("Ordinacija: " + pp.Ordinacija.NazivOrdinacije);
                        pregled.Nodes.Add(misljenje);
                        pregled.Nodes.Add(ordinacija);
                        if (jeste) { TreeNode doca = new TreeNode("Doktor koji je uradio pregled: " + onaj); pregled.Nodes.Add(doca); }
                        treeView1.Nodes.Add(pregled);
                    }
                    i++;
                });
                i = 1;
            });

        }

        private void button1_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "";
            errorProvider1.Clear();
            TimeSpan diff1 = DateTime.Now.Subtract(userControl11.vratiDatum());
            if (diff1.TotalDays > 185)
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite noviju sliku!";
                errorProvider1.SetError(userControl11, "Slika mora biti maximalno 6 mjeseci stara!");
                return;
            }
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.MaticniBroj == jmbg)
                {
                    p.SlikaPacijenta = userControl11.vratiSliku();
                }
            });
            toolStripStatusLabel1.Text = "Slika uspješno ažurirana!";
        }
    }
}
