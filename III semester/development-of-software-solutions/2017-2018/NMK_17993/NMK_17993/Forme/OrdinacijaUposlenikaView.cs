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
    public partial class OrdinacijaUposlenikaView : Form
    {
        Klinika novaKlinika;
        string jmbg;
        public OrdinacijaUposlenikaView(ref Klinika a, string b)
        {
            jmbg = b;
            novaKlinika = a;
            InitializeComponent();
        }

        private void OrdinacijaUposlenikaView_Load(object sender, EventArgs e)                  
        { 
            int i = 1;
            treeView1.Nodes.Clear();

            // prijasnje alergije
            TreeNode pa = new TreeNode("Prijašnje alergije: ");
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.PrijasnjeAlergije)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa.Nodes.Add(pa1);
                    }
                }
            }

            // sadašnje alergije
            TreeNode sad = new TreeNode("Sadašnje alergije: ");
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.SadasnjeAlergije)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        sad.Nodes.Add(pa1);
                    }
                }
            }

            // prijasnje bolesti
            TreeNode pa23 = new TreeNode("Prijašnje bolesti: ");
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.PrijasnjeBolesti)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa23.Nodes.Add(pa1);
                    }
                }
            }

            // sadasnje bolesti 
            TreeNode pa535 = new TreeNode("Sadašnje bolesti: ");
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                if (p.MaticniBroj == jmbg)
                {
                    foreach (string b in p.LicniKarton.SadasnjeBolesti)
                    {
                        TreeNode pa1 = new TreeNode(b);
                        pa535.Nodes.Add(pa1);
                    }
                }
            }

            treeView1.Nodes.Add(pa);
            treeView1.Nodes.Add(sad);
            treeView1.Nodes.Add(pa23);
            treeView1.Nodes.Add(pa535);

            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled pp in p.LicniKarton.SpisakPregleda1)
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
                }
                i = 1;
            }

        }
    }
}
