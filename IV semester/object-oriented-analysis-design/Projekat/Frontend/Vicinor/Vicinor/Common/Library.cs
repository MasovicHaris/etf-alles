using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Geolocation;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace Vicinor.Common
{
    public class Library
    {
        public async Task<Geopoint> Position()
        {
            return (await new Geolocator().GetGeopositionAsync()).Coordinate.Point;
        }

        public UIElement Marker()
        {
            Canvas marker = new Canvas();
            Ellipse outer = new Ellipse();
            outer.Fill = new SolidColorBrush(Color.FromArgb(255, 0, 0, 0));
            outer.Margin = new Thickness(-12.5, -12.5, 0, 0);
            Ellipse inner = new Ellipse() { Width = 50, Height = 50 };
            inner.Margin = new Thickness(-10, -10, 0, 0);
            Ellipse core = new Ellipse() { Width = 10, Height = 10 };
            core.Fill = new SolidColorBrush(Colors.Red);
            core.Margin = new Thickness(-5, -5, 0, 0);
            marker.Children.Add(outer);
            marker.Children.Add(inner);
            marker.Children.Add(core);
            return marker;
        }

        public UIElement MarkerText(string Text)
        {
            Canvas marker = new Canvas();
            TextBlock text = new TextBlock();
            text.Foreground = new SolidColorBrush(Colors.Red);
            marker.Background = new SolidColorBrush(Colors.Black);
            text.FontSize = 16;
            text.Text = Text;
            marker.Children.Add(text);
            return marker;
        }
    }
}



    
