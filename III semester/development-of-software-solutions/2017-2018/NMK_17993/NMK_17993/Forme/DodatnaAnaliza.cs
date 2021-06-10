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
    public partial class DodatnaAnaliza : Form
    {
        Klinika novaKlinika;
        public DodatnaAnaliza(ref Klinika a)
        {
            novaKlinika = a;
            InitializeComponent();
        }

        private static void DrawPieChart(Graphics gr, Rectangle rect, Brush[] brushes, Pen[] pens, float[] values)
        {
            float total = values.Sum();
            float start_angle = 0;
            for (int i = 0; i < values.Length; i++)
            {
                float sweep_angle = values[i] * 360f / total;
                gr.FillPie(brushes[i % brushes.Length],
                    rect, start_angle, sweep_angle);
                gr.DrawPie(pens[i % pens.Length],
                    rect, start_angle, sweep_angle);
                start_angle += sweep_angle;
            }
        }

        private Brush[] SliceBrushes =
        {
    Brushes.Red,
    Brushes.LightGreen,
    Brushes.Blue,
    Brushes.LightBlue,
    Brushes.Green,
    Brushes.Lime,
    Brushes.Orange,
    Brushes.Fuchsia,
    Brushes.Yellow,
    Brushes.Cyan,
        };

 
        private Pen[] SlicePens = { Pens.Black };

        private float[] Values = new float[2];


        private void DodatnaAnaliza_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(BackColor);
            if ((ClientSize.Width < 20) || (ClientSize.Height < 20)) return;

            Rectangle rect = new Rectangle(10, 10, ClientSize.Width - 20, ClientSize.Height - 20);
            DrawPieChart(e.Graphics, rect, SliceBrushes, SlicePens, Values);
        }

        private void DodatnaAnaliza_Load(object sender, EventArgs e)
        {
            List<Uposlenik> a = novaKlinika.ListaUposlenih.FindAll(x => x is Doktor);
            int i = 0;
            foreach (Uposlenik b1 in a)
            {
                if (i > 2) break;
                if (b1 is Doktor)
                {
                    Doktor b2 = b1 as Doktor;
                    if (b2.SpecijalistaZaOrdinacije.Count > 1)
                    {
                        Values[0]++;
                    }
                    else Values[1]++;
                }
                i++;
            }
        }
    }
}
