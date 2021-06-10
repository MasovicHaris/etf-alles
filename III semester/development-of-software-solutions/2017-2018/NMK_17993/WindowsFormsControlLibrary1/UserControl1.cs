using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsControlLibrary1
{
    public partial class UserControl1: UserControl
    {
        bool ubacenaSlika = false;

        public bool UbacenaSlika
        {
            get
            {
                return ubacenaSlika;
            }

            set
            {
                ubacenaSlika = value;
            }
        }

        public UserControl1()
        {
            InitializeComponent();
        }

        public Image vratiSliku()
        {
            return pictureBox1.Image;
        }
        public DateTime vratiDatum()
        {
            return dateTimePicker1.Value;
        }
        public void resetuj()
        {
            pictureBox1.Image = null;
            dateTimePicker1.Value = DateTime.Today;
            ubacenaSlika = false;
        }


        public void postaviSliku(Image im)
        {
            pictureBox1.Image = im;
            UbacenaSlika = true;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.Title = "Izaberite sliku";
                dlg.Filter = "jpg files (*.jpg)|*.jpg";
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    pictureBox1.Image = new Bitmap(dlg.FileName);
                }
            }
            UbacenaSlika = true;
        }
    }
}
