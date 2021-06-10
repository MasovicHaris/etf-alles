using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

namespace Vicinor.UserControls
{
    public sealed partial class RatingCont : UserControl
    {
        public RatingCont()
        {
            this.InitializeComponent();
        }

        public void setRating(double r)
        {
            rating.Text = Math.Round(r, 1).ToString();
            star1.Text = "\xE734";
            star2.Text = "\xE734";
            star3.Text = "\xE734";
            star4.Text = "\xE734";
            star5.Text = "\xE734";
            if (r < 0.5) return;
            else
            {
                star1.Text = "\xE735";
                if (r > 1.5)
                {
                    star2.Text = "\xE735";
                }
                if (r > 2.5)
                {
                    star3.Text = "\xE735";
                }
                if (r > 3.5)
                {
                    star4.Text = "\xE735";
                }
                if (r > 4.5)
                {
                    star5.Text = "\xE735";
                }
            }

        }
    }
}
