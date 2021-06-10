using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Vicinor.View;
using Vicinor.Forme;
using Vicinor.ViewModel;
using System.Net.Http;
using Windows.Data.Json;
using System.Threading.Tasks;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.View
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Comments : Page
    {

        List<string> listaKomentara;

        public Comments()
        {
            this.InitializeComponent();
            Rating.setRating(StartSearch1.rating);
            DobaviKomentare();
        }

        private async void DobaviKomentare()
        {
            listaKomentara = new List<string>();

            var client = new HttpClient();

            var restoran = StartSearch1.dRestorani[StartSearch1.idRestoranaKliknuto];

            // https://maps.googleapis.com/maps/api/place/details/json?placeid={place_id}&key={api_key}

            HttpResponseMessage response = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/details/json?placeid=" +
                restoran.Place_id + "&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));
            var jsonString = await response.Content.ReadAsStringAsync();

            JsonObject root = JsonValue.Parse(jsonString).GetObject();

            JsonObject podaci = root.GetNamedObject("result");

            JsonArray komentari = podaci.GetNamedArray("reviews");

            for (uint i = 0; i < komentari.Count; ++i)
            {
                JsonObject komentar = komentari.GetObjectAt(i);

                komenatriListView.Items.Add("-"+komentar.GetNamedString("author_name")+": "+komentar.GetNamedString("text"));
            }
        }

        private void returnButton_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(StartSearch1));
        }
    }
}
