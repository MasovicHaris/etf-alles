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
using System.Drawing.Imaging;

namespace NMK_17993.Forme
{
    public partial class Portirnica : Form
    {
        Klinika novaKlinika;
        public Portirnica(ref Klinika novaKlinika1)
        {
            novaKlinika = novaKlinika1;
            InitializeComponent();
        }

        static bool sveOk = true;
        private void Portirnica_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void odjavaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Registracija form = new Registracija(ref novaKlinika);
            this.Hide();
            form.Show();
        }

        static bool desioSePrenos00, desioSePreno10;
        static bool pamti = false;
        private void button1_Click(object sender, EventArgs e)
        {
            Pacijent noviPacijent = new Pacijent("x", "x", "0000000000000", "x x 1", DateTime.Parse("1.1.1111"), Osoba.Spol.M, Osoba.bracnoStanje.nijeUBraku);
            noviPacijent.LicniKarton = new KartonPacijenta();
            noviPacijent.LicniKarton.SpisakPregleda1 = new List<Pregled>();

            if (textBox1.Text == "" || textBox2.Text == "" || textBox3.Text == "" || textBox4.Text == "") sveOk = false;
            if (radioButton1.Checked || radioButton2.Checked) sveOk = true;
            else sveOk = false;
            if (radioButton3.Checked || radioButton4.Checked) sveOk = true;
            else sveOk = false;

            if (sveOk && userControl11.UbacenaSlika)
            {
                if (Validacije.jedinstvenjmbg(textBox3.Text, novaKlinika.ListaPacijenata))
                {
                    TimeSpan diff1 = DateTime.Now.Subtract(userControl11.vratiDatum());
                    if (diff1.TotalDays > 185)
                    {
                        toolStripStatusLabel1.ForeColor = Color.Red;
                        toolStripStatusLabel1.Text = "Molimo unesite noviju sliku!";
                        errorProvider1.SetError(userControl11, "Slika mora biti maximalno 6 mjeseci stara!");
                    }
                    else if (Validacije.crossValidacijaJMBG(textBox3.Text, dateTimePicker1.Value))
                    {
                        noviPacijent.Ime = textBox1.Text;
                        noviPacijent.Prezime = textBox2.Text;
                        noviPacijent.MaticniBroj = textBox3.Text;
                        noviPacijent.AdresaStanovanja = textBox4.Text;
                        noviPacijent.DatumRodenja = dateTimePicker1.Value;
                        if (radioButton1.Checked)
                        {
                            noviPacijent.Spol1 = Osoba.Spol.M;
                        }
                        else noviPacijent.Spol1 = Osoba.Spol.Z;
                        if (radioButton3.Checked)
                        {
                            noviPacijent.BrStanje = Osoba.bracnoStanje.uBraku;
                        }
                        else noviPacijent.BrStanje = Osoba.bracnoStanje.nijeUBraku;

                        novaKlinika.ListaPacijenata.Add(noviPacijent);
                        textBox1.Clear(); textBox2.Clear(); textBox3.Clear(); textBox4.Clear();
                        dateTimePicker1.ResetText();
                        errorProvider1.Clear();
                        toolStripStatusLabel1.ForeColor = Color.Red;
                        toolStripStatusLabel1.Text = "Uspješno registrovan pacijent!";
                        radioButton1.Checked = false;
                        radioButton2.Checked = false;
                        radioButton3.Checked = false;
                        radioButton4.Checked = false;
                        noviPacijent.SlikaPacijenta = userControl11.vratiSliku();
                        userControl11.resetuj();
                    }
                    else
                    {
                        toolStripStatusLabel1.ForeColor = Color.Red;
                        toolStripStatusLabel1.Text = "Molimo promjenite datum ili unesite ispravan JMBG!";
                        errorProvider1.SetError(textBox3, "Nedozvoljen datum/JMBG!");
                        errorProvider1.SetError(dateTimePicker1, "Nedozvoljen datum/JMBG!");
                        sveOk = false;
                    }
                }
                else
                {
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripStatusLabel1.Text = "Molimo unesite jedinstven JMBG!";
                    errorProvider1.SetError(textBox3, "Nije jedinstven JMBG!");
                    errorProvider1.SetError(dateTimePicker1, "Nije jedinstven JMBG!");
                    sveOk = false;
                }
            }
            else
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Provjerite opet unos (Moraju biti popunjenji svi podaci i mora biti slika)!";
            }

            if (desioSePrenos00)
            {
                if (desioSePreno10 &&redovanPacijent) toolStripStatusLabel2.Text = "Unešen je novi (hitan slučaj) pacijent!";
                else if(desioSePreno10 && !redovanPacijent)
                {
                    toolStripStatusLabel2.Text = "Pošto ste unijeli podatke, za hitan slučaj, popunite još jednom samo pregled za datog pacijenta!";
                    pamti = true;
                }
                else
                {
                    toolStripStatusLabel2.Text = "Unešen je novi pacijent! Možete pristupiti popunjavanju pregleda!";
                }
                tabControl1.SelectedTab = tabControl1.TabPages[1];
                desioSePrenos00 = false;
                desioSePreno10 = false;
                comboBox1.SelectedItem = null;
                comboBox2.SelectedItem = null;
                treeView1.Nodes.Clear();
                toolStripStatusLabel1.Text = "";
            }
            if (sveOk)
            {
                comboBox2.Items.Add(noviPacijent.MaticniBroj);
                comboBox3.Items.Add(noviPacijent.MaticniBroj);
            }
        }
                                                                                    // validacije od svakog unosa, preko Regexa iz prve zadace
                                                                                    // ako je gdje potreban cross regex biti će dodan :D
        private void textBox1_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            Regex rgx1 = new Regex("\\b[^\\d\\W]+\\b");

            if (!rgx1.IsMatch(textBox1.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite opet ime!";
                errorProvider1.SetError(textBox1, "Nedozvoljeno ime!");
                sveOk = false;
            }
            else sveOk = true;
        }

        private void textBox2_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            Regex rgx2 = new Regex("\\b[^\\d\\W]+\\b");

            if (!rgx2.IsMatch(textBox2.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite opet prezime!";
                errorProvider1.SetError(textBox2, "Nedozvoljeno prezime!");
                sveOk = false;
            }
            else sveOk = true;
        }

        private void textBox3_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            Regex rgx3 = new Regex("^(\\d{13})?$");

            if (!rgx3.IsMatch(textBox3.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                errorProvider1.SetError(textBox3, "Nedozvoljen JMBG!");
                sveOk = false;
            }
            else sveOk = true;

            try
            {
                if (!Validacije.provjeraJMBG(textBox3.Text))
                {
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                    errorProvider1.SetError(textBox3, "Nedozvoljen JMBG!");
                    sveOk = false;
                }
                else sveOk = true;
            }catch(Exception ex)
            {
                ex.GetType();
                sveOk = false;
            }

            if (!Validacije.jedinstvenjmbg(textBox3.Text, novaKlinika.ListaPacijenata))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite jedinstven JMBG!";
                errorProvider1.SetError(textBox3, "Nije jedinstven JMBG!");
            }

        }

        private void textBox4_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            Regex rgx4 = new Regex("\\w+\\s\\w+\\s+[0-9]{1,3}");

            if (!rgx4.IsMatch(textBox4.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite opet adresu!";
                errorProvider1.SetError(textBox4, "Nedozvoljena adresa!");
                sveOk = false;
            }
            else sveOk = true;
        }

        private void dateTimePicker1_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            if (!Validacije.crossValidacijaJMBG(textBox3.Text, dateTimePicker1.Value))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo promjenite datum ili unesite ispravan JMBG!";
                errorProvider1.SetError(textBox3, "Nedozvoljen datum/JMBG!");
                errorProvider1.SetError(dateTimePicker1, "Nedozvoljen datum/JMBG!");
                sveOk = false;
            }
            else sveOk = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (novaKlinika.ListaPacijenata.Capacity != 0 && novaKlinika.ListaPacijenata.Count != 0)
            {

                errorProvider1.Clear();
                toolStripStatusLabel1.Text = "";
                Regex rgx3 = new Regex("^(\\d{13})?$");

                if (!rgx3.IsMatch(textBox6.Text))
                {
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                    errorProvider1.SetError(textBox6, "Nedozvoljen JMBG!");
                    return;
                }

                try
                {
                    if (!Validacije.provjeraJMBG(textBox6.Text))
                    {
                        toolStripStatusLabel1.ForeColor = Color.Red;
                        toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                        errorProvider1.SetError(textBox6, "Nedozvoljen JMBG!");
                        return;               
                    }
                }
                catch (Exception ex)
                {
                    ex.GetType();
                    return;
                }

                bool imalGa = false;
                Parallel.For(0, novaKlinika.ListaPacijenata.Count, i =>
                {
                    if (novaKlinika.ListaPacijenata[i].MaticniBroj == textBox6.Text)
                    {
                        imalGa = true;
                    }
                });
                if(!imalGa)
                {
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripStatusLabel1.Text = "Taj pacijent nije registrovan u ovoj klinici!";
                    return;
                }
                Parallel.For(0, novaKlinika.ListaPacijenata.Capacity, i =>
                {
                    if (novaKlinika.ListaPacijenata[i].MaticniBroj == textBox6.Text && imalGa)
                    {
                        novaKlinika.ListaPacijenata.RemoveAt(i);
                        novaKlinika.ListaPacijenata.Capacity--;
                        toolStripStatusLabel1.ForeColor = Color.Red;
                        toolStripStatusLabel1.Text = "Uspješno izbrisan pacijent!";
                        comboBox2.Items.Remove(textBox6.Text);
                        comboBox3.Items.Remove(textBox6.Text);
                        textBox6.Clear();
                        return;
                    }
                });

            } else
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Trenutno nema pacijenata u klinici!";
            }
        }

        private void textBox6_Validated(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel1.Text = "";
            Regex rgx3 = new Regex("^(\\d{13})?$");

            if (!rgx3.IsMatch(textBox6.Text))
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                errorProvider1.SetError(textBox6, "Nedozvoljen JMBG!");
            }

            try
            {
                if (!Validacije.provjeraJMBG(textBox6.Text))
                {
                    toolStripStatusLabel1.ForeColor = Color.Red;
                    toolStripStatusLabel1.Text = "Molimo unesite opet JMBG!";
                    errorProvider1.SetError(textBox6, "Nedozvoljen JMBG!");
                }
            }
            catch (Exception ex)
            {
                ex.GetType();
            }
        }

        static TreeNode parent = new TreeNode();

        private void Portirnica_Load(object sender, EventArgs e)                
        {
            Parallel.ForEach(novaKlinika.ListaOrdinacija, o => {
                if (o.Jelradi == Ordinacija.funkcija.radi) comboBox1.Items.Add(o.NazivOrdinacije);
            });

            if (novaKlinika.ListaPacijenata.Count != 0)
            {

                Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
                {
                    comboBox2.Items.Add(p.MaticniBroj);

                    bool pp1 = false;
                    foreach (Pregled pp in p.LicniKarton.SpisakPregleda1)
                    {
                        if (pp.Placena == false && pp.Pregled1)
                        {
                            pp1 = true;
                            break;
                        }
                    }
                    if (pp1) comboBox3.Items.Add(p.MaticniBroj);
                });
               
                /*
                foreach (Pacijent p in novaKlinika.ListaPacijenata)
                {
                    comboBox2.Items.Add(p.MaticniBroj);

                    bool pp1 = false;
                    foreach(Pregled pp in p.LicniKarton.SpisakPregleda1)
                    {
                        if(pp.Placena == false && pp.Pregled1)
                        {
                            pp1 = true;
                            break;
                        }
                    }
                    if(pp1) comboBox3.Items.Add(p.MaticniBroj);
                }   */
            }

            comboBox1.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            comboBox1.AutoCompleteSource = AutoCompleteSource.ListItems;

            comboBox2.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            comboBox2.AutoCompleteSource = AutoCompleteSource.ListItems;
            comboBox3.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            comboBox3.AutoCompleteSource = AutoCompleteSource.ListItems;

            treeView1.Nodes.Clear();
            toolStripStatusLabel2.Text = "";
            toolStripStatusLabel2.ForeColor = Color.Red;
            toolStripStatusLabel3.Text = "";
            toolStripStatusLabel3.ForeColor = Color.Red;
        }





        static bool hitanSlucaj;
        static bool redovanPacijent;

        private void button3_Click(object sender, EventArgs e)
        {
            errorProvider1.Clear();
            toolStripStatusLabel2.Text = "";
            if (!(radioButton5.Checked || radioButton6.Checked))
            {
                toolStripStatusLabel2.Text = "Odaberite DA ili NE";
                errorProvider1.SetError(groupBox5, "Fali izbor!");

            }
            if (!(radioButton7.Checked || radioButton8.Checked))
            {
                toolStripStatusLabel2.Text = "Odaberite DA ili NE";
                errorProvider1.SetError(groupBox6, "Fali izbor!");
            }
            if (toolStripStatusLabel2.Text != "") return;


            if (radioButton5.Checked) hitanSlucaj = true;
            else hitanSlucaj = false;
            if (radioButton7.Checked) redovanPacijent = true;
            else redovanPacijent = false;


            if (!hitanSlucaj && !redovanPacijent)
            {
                tabControl1.SelectedTab = tabControl1.TabPages[0];
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo vas popunite prvo registraciju pacijenta, nakon unosa ćete popuniti podatke u vezi pregleda!";
                desioSePrenos00 = true;
            }
            else if (hitanSlucaj && !redovanPacijent)
            {
                comboBox1.SelectedItem = null;
                comboBox2.SelectedItem = null;
                treeView1.Nodes.Clear();
                desioSePreno10 = true;
                toolStripStatusLabel2.Text = "Hitan slučaj! Pratite strelicu i prvo popunite podatke u vezi pregleda!";
            }
            else
            {
                comboBox1.SelectedItem = null;
                comboBox2.SelectedItem = null;
                treeView1.Nodes.Clear();
                toolStripStatusLabel2.Text = "Uspješno odabran izbor pregleda i klasifikacija pacijenta! Pratite strelicu!";
            }
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            treeView1.Nodes.Clear();
            parent.Text = "Spisak slobodnih doktora";
            parent.Nodes.Clear();
            treeView1.Nodes.Add(parent);
            foreach (Uposlenik p in novaKlinika.ListaUposlenih)
            {
                if (p is Doktor)
                {
                    Doktor a = p as Doktor;
                    if (comboBox1.Text != "")
                    {
                        foreach(Ordinacija b in a.SpecijalistaZaOrdinacije)
                        {
                            if(b.NazivOrdinacije == comboBox1.Text)
                            {
                                TreeNode h =  new TreeNode(a.Ime + " " + a.Prezime + " " + a.MaticniBroj);
                                parent.Nodes.Add(h);
                            }
                        }
                    }
                }

            }
            treeView1.Nodes[0].Expand();
        }

        private void treeView1_BeforeSelect(object sender, TreeViewCancelEventArgs e)
        {
            if (e.Node == parent) e.Cancel = true;
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)         
        {
            if(!(radioButton9.Checked || radioButton10.Checked))
            {
                toolStripStatusLabel3.Text = "Molim izaberite način plačanja!";
                return;
            }
            NaplataPregleda novaNaplata = new NaplataPregleda();

            double sumaNaplate = 0.0;
            Parallel.For(0, novaKlinika.ListaPacijenata.Capacity, i =>
            {
                if (i < novaKlinika.ListaPacijenata.Count && novaKlinika.ListaPacijenata[i].MaticniBroj == comboBox3.Text)
                {

                    Parallel.ForEach(novaKlinika.ListaPacijenata[i].LicniKarton.SpisakPregleda1, p =>
                    {
                        if (p.Pregled1 == true && p.Placena == false)
                        {

                            NaplataPregleda.vrstaPlacanja placanje;
                            if (radioButton9.Checked) placanje = NaplataPregleda.vrstaPlacanja.gotovo;
                            else placanje = NaplataPregleda.vrstaPlacanja.rate;
                            sumaNaplate += novaNaplata.izracunajCijenuPregleda(novaKlinika.ListaPacijenata[i].LicniKarton.BrojPosjeta, placanje);

                        }
                        else
                        {
                            toolStripStatusLabel3.Text = "Traženi pacijent ili nema finalno završenih pregleda ili je pacijent sve platio!";
                            return;
                        }
                    });
                }
            });

            toolStripStatusLabel3.Text = "Ukupna suma plaćanja za datog pacijenta iznosi: " + sumaNaplate + "KM.";
            radioButton10.Checked = false;
            radioButton9.Checked = false;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            DodatnaAnaliza hehe = new DodatnaAnaliza(ref novaKlinika);
            hehe.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel3.Text = "Ukupan broj redovnih pacijenata: ";
            int broj = 0;
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                if (p.LicniKarton.BrojPosjeta > 3) broj++;
            });

            toolStripStatusLabel3.Text += broj;
            // analiza srednje vrijednosti placanja ukoliko se uzmu sve placeni
            // pregledi, i ukoliko se uvijek uzima paran broj odnosno neparan broj
            // da su bile plate, odnosno gleda se vrijednost kada bi bilo
            // jednak broj plata, i koliko bi klinika zaradila, zajedno sa
            // ratama i gotovinom
        }

        private void button7_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel3.Text = "Najveca suma kad bi bilo priblizno jednak nacin placanja za ukupne preglede: ";
            NaplataPregleda novaNaplata = new NaplataPregleda();
            double suma = 0;
            int brojac = 0;
            foreach (Pacijent p in novaKlinika.ListaPacijenata)
            {
                foreach (Pregled preg in p.LicniKarton.SpisakPregleda1)
                {
                    if (preg.Placena == true)
                    {
                        if (brojac % 2 == 0) suma += novaNaplata.izracunajCijenuPregleda(p.LicniKarton.BrojPosjeta, NaplataPregleda.vrstaPlacanja.gotovo);
                        else suma += novaNaplata.izracunajCijenuPregleda(p.LicniKarton.BrojPosjeta, NaplataPregleda.vrstaPlacanja.rate);

                        brojac++;
                    }
                }
            }
            toolStripStatusLabel3.Text += suma + "KM.";
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if(toolStripStatusLabel3.Text == "" || !(!radioButton9.Checked || !radioButton10.Checked))
            {
                toolStripStatusLabel3.Text = "Ponovite postupak!";
                return;
            }
            Parallel.For(0, novaKlinika.ListaPacijenata.Capacity, i =>
            {
                if (i < novaKlinika.ListaPacijenata.Count && novaKlinika.ListaPacijenata[i].MaticniBroj == comboBox3.Text)
                {
                    Parallel.ForEach(novaKlinika.ListaPacijenata[i].LicniKarton.SpisakPregleda1, p =>
                    {
                        if (p.Pregled1 == true && p.Placena == false)
                        {
                            p.Placena = true;
                        }
                    });
                }
            });


            radioButton10.Checked = false;
            radioButton9.Checked = false;
            comboBox3.Text = "";
            toolStripStatusLabel3.Text = "Uspješno izvršena naplata!";

            // update comboboxa, kad pacijent plati sve preglede.
            Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
            {
                bool pp1 = false;
                foreach (Pregled pp in p.LicniKarton.SpisakPregleda1)
                {
                    if (pp.Placena == false && pp.Pregled1)
                    {
                        pp1 = true;
                        break;
                    }
                }
                if (pp1) comboBox3.Items.Add(p.MaticniBroj);
            });
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Pregled noviPregled = new Pregled();
            noviPregled.Pregled1 = false;
            errorProvider1.Clear();
            if (hitanSlucaj && !redovanPacijent && !pamti)
            {
                if (comboBox1.Text == "" || treeView1.SelectedNode == null)
                {
                    if (comboBox1.Text == "") errorProvider1.SetError(comboBox1, "Fali odabir!");
                    if (treeView1.SelectedNode == null) errorProvider1.SetError(treeView1, "Fali odabir doktora!");
                    toolStripStatusLabel2.Text = "Unesite podatke vezane za pregled!";
                    return;
                }

                noviPregled.Pregled1 = false;
                Ordinacija nova = new Ordinacija(Ordinacija.stanje.Slobodno, Ordinacija.funkcija.radi, comboBox1.Text);

                for (int i = 0; i < novaKlinika.ListaOrdinacija.Capacity; i++)
                {
                    if (novaKlinika.ListaOrdinacija[i].NazivOrdinacije == comboBox1.Text)
                    {
                        novaKlinika.ListaOrdinacija[i] = nova;
                        break;
                    }
                }


                noviPregled.Ordinacija = nova;
            }
            else
            {
                if (comboBox1.Text == "" || comboBox2.Text == "" || treeView1.SelectedNode == null)
                {
                    if (comboBox2.Text == "") errorProvider1.SetError(comboBox2, "Fali odabir!");
                    if (comboBox1.Text == "") errorProvider1.SetError(comboBox1, "Fali odabir!");
                    if (treeView1.SelectedNode == null) errorProvider1.SetError(treeView1, "Fali odabir doktora!");
                    toolStripStatusLabel2.Text = "Unesite podatke vezane za pregled!";
                    return;
                }

                noviPregled.Pregled1 = false;
                Ordinacija nova = new Ordinacija(Ordinacija.stanje.Slobodno, Ordinacija.funkcija.radi, comboBox1.Text);

                for (int i = 0; i < novaKlinika.ListaOrdinacija.Capacity; i++)
                {
                    if (novaKlinika.ListaOrdinacija[i].NazivOrdinacije == comboBox1.Text)
                    {
                        novaKlinika.ListaOrdinacija[i] = nova;
                        break;
                    }
                }


                noviPregled.Ordinacija = nova;
                Pacijent noviPacijent = new Pacijent("x", "x", "0000000000000", "x x 1", DateTime.Parse("1.1.1111"), Osoba.Spol.M, Osoba.bracnoStanje.nijeUBraku);

                bool ima = false;
                Parallel.ForEach(novaKlinika.ListaPacijenata, p =>
                {
                    if (p.MaticniBroj == comboBox2.Text)
                    {
                        ima = true;
                        noviPacijent = p;
                    }
                });
                if (!ima) return;
                noviPacijent.LicniKarton.PovecajBrojPosjeta();
                noviPacijent.LicniKarton.SpisakPregleda1.Add(noviPregled);



                comboBox1.Text = "";
                comboBox2.Text = "";
                treeView1.Nodes.Clear();
                radioButton5.Checked = false; radioButton6.Checked = false;
                radioButton7.Checked = false; radioButton8.Checked = false;

                toolStripStatusLabel2.Text = "Unesen je novi pregled za datog pacijenta! Ako treba sačekajte malo.";
            }

            if (desioSePreno10)
            {
                toolStripStatusLabel1.ForeColor = Color.Red;
                toolStripStatusLabel1.Text = "Molimo vas popunite podatke za hitan slučaj";
                tabControl1.SelectedTab = tabControl1.TabPages[0];
                desioSePrenos00 = true;
            }



        }

    }
}

