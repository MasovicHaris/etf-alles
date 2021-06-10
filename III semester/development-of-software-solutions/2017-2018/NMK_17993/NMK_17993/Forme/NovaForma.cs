using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace NMK_17993.Forme
{
    public partial class NovaForma : Form
    {
        public NovaForma()
        {
            InitializeComponent();
        }


        public async void ubacuj()
        {
            foreach (string file in System.IO.Directory.GetFiles(textBox1.Text))
            {
                await Task.Delay(500);
                this.Invoke(new Action(() => { listBox1.Items.Add(file); listBox1.Sorted = true; }));
            }
            foreach (string file in System.IO.Directory.GetDirectories(textBox1.Text))
            {
                await Task.Delay(500);
                this.Invoke(new Action(() => { listBox1.Items.Add(file); listBox1.Sorted = true; }));
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                listBox1.Items.Clear();
                if (System.IO.Directory.GetFiles(textBox1.Text).Length > 0 || System.IO.Directory.GetDirectories(textBox1.Text).Length > 0)
                {
                    Thread t = new Thread(new ThreadStart(ubacuj));
                    t.Start();
                }
                else
                {
                    listBox1.Items.Add(String.Format("Nema fajlova na lokaciji: {0}", textBox1.Text));
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            listBox1.Items.Clear();
            FolderBrowserDialog folderBrowserDlg = new FolderBrowserDialog();

            folderBrowserDlg.ShowNewFolderButton = true;

            DialogResult dlgResult = folderBrowserDlg.ShowDialog();
            if (dlgResult.Equals(DialogResult.OK))
            {
                textBox1.Text = folderBrowserDlg.SelectedPath;

                Environment.SpecialFolder rootFolder = folderBrowserDlg.RootFolder;
            }
        }

        private void NovaForma_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }
    }
}
