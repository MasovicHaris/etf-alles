using System;
using System.Collections.Generic;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.Devices.Geolocation;
using System.Threading;
using System.Threading.Tasks;
using System.Net.Http;
using Windows.Data.Json;
using Vicinor.Model;
using Vicinor.View;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class SearchRestaurants : Page
    {
        public Geolocator geolocator = null;
        public static Geoposition position;

        public static Tuple<double, double> novaLokacija = new Tuple<double, double>(0, 0);

        public static List<Restoran> listaDobavljenih = null;
        public List<Restoran> listaRecommended = null;

        public SearchRestaurants()
        {
            listaDobavljenih = new List<Restoran>();
            listaRecommended = new List<Restoran>();
            listaRecommended = UserStartPage.listaRecommended;
            this.InitializeComponent();

        }
        private void flip_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void FlipView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
        public async void Initial()
        {
           bool a = await getLocationByGeolocatorAsync();
            
        }

        private CancellationTokenSource _geolocationCancelationTokenSource = null;

        private async Task<bool> getLocationByGeolocatorAsync()
        {
            if (geolocator == null)
            {
                geolocator = new Geolocator();
            }

            bool boSuccess = false;

            //some preflight checks here
            if (geolocator.LocationStatus != PositionStatus.Disabled && geolocator.LocationStatus != PositionStatus.NotAvailable)
            {
                try
                {
                    // Get cancellation token 
                    _geolocationCancelationTokenSource = new CancellationTokenSource();

                    await this.cancelGeolocationTimerAsync();

                     position = await geolocator.GetGeopositionAsync().AsTask();


                    boSuccess = true;
                }
                catch (Exception e) { 
                }
                finally
                {
                    _geolocationCancelationTokenSource = null;
                }
            }
            return boSuccess;
        }


        private async Task cancelGeolocationTimerAsync()
        {
            await Task.Delay(2000);
            if (_geolocationCancelationTokenSource != null)
            {
                _geolocationCancelationTokenSource.Cancel();
                _geolocationCancelationTokenSource = null;
            }
        }

        public static string PLACE_ID = "";

        private async void startSearchButton_Click(object sender, RoutedEventArgs e)
        {
            //Otvaranje forme za pretragu, dobivanje rezultata sa api-ja
            // liste Restorana
            listaDobavljenih = new List<Restoran>();
            bool b = await getLocationByGeolocatorAsync();

            if (radiusTextBox.Text == "")
            {
                radiusTextBox.Text = "UNESITE RADIUS U BROJEVIMA";
                return;
            }
            if(radiusTextBox.Text == "UNESITE RADIUS U BROJEVIMA")
            {
                radiusTextBox.Text = "1000";
                return;
            }

            var client = new HttpClient();

            string LONGITUDINALA ="0.0", LANGITUDINALA = "0.0";

            if(position != null)
            {
                LONGITUDINALA = position.Coordinate.Point.Position.Longitude.ToString();
                LANGITUDINALA = position.Coordinate.Point.Position.Latitude.ToString();
            }

            //HttpResponseMessage response = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/search/json?types=restaurant" 
            //    + "&location=" + LONGITUDINALA + "%2C" + LANGITUDINALA + "&radius=" + radiusTextBox.Text.ToString() 
            //    + "&sensor=false&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));

            HttpResponseMessage response = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/search/json?types=restaurant&"+
                "location="+LANGITUDINALA +"%2C"+LONGITUDINALA+"&radius="+radiusTextBox.Text.ToString()+"&sensor=false&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));
            var jsonString = await response.Content.ReadAsStringAsync();

            JsonObject root = JsonValue.Parse(jsonString).GetObject();

            JsonArray REzultati = root.GetNamedArray("results");

            for(uint i = 0; i < REzultati.Count; ++i)
            {
                JsonObject restoran = REzultati.GetObjectAt(i);

                Restoran novi = new Restoran();
                Recenzija r = new Recenzija();

                string name_ime_restorana = restoran.GetNamedString("name");
                string place_id_kao_deskripcija = restoran.GetNamedString("vicinity");
                double rating;
                try
                {
                     rating = restoran.GetNamedNumber("rating");
                    r.StarRating = (Int32) rating;
                    novi.ListRezension.Add(r);

                }
                catch (Exception k)
                {
                     rating = -1;
                }
                string place_id = null;
                novi.Name = name_ime_restorana;

                // novi.PhoneNumber = "+38733225 883";

                novi.RestoranId = (int) i;

                novi.Description = place_id_kao_deskripcija;

                novi.Place_id = restoran.GetNamedString("place_id");

                JsonArray objekatPhotosM = null;
                try
                {
                    place_id = restoran.GetNamedString("place_id");
                }
                catch (Exception)
                {
                
                }

                if (place_id != null)
                {

                    HttpResponseMessage response2 = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/details/json?placeid=" +
                    novi.Place_id + "&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));
                    var jsonString2 = await response2.Content.ReadAsStringAsync();

                    JsonObject root2 = JsonValue.Parse(jsonString2).GetObject();

                    JsonObject podaci = root2.GetNamedObject("result");
                    try
                    {

                        String phonenumber = podaci.GetNamedString("international_phone_number");

                        novi.PhoneNumber = phonenumber;
                    }
                    catch(Exception ex)
                    {
                        novi.PhoneNumber = "";
                    }
                }



                try
                {
                    objekatPhotosM = restoran.GetNamedArray("photos");
                }catch(Exception)
                {
                }

                if (objekatPhotosM != null && objekatPhotosM.Count > 0)
                {
                    JsonObject objekatPhotos = objekatPhotosM.GetObjectAt(0);

                    string slikaReferenca = objekatPhotos.GetNamedString("photo_reference");

                    double MAX_HEIGHT = objekatPhotos.GetNamedNumber("height");

                    double MAX_WIDTH = objekatPhotos.GetNamedNumber("width");

                    novi.SlikaURL = objekatPhotos.GetNamedString("photo_reference");

                    novi.Slika = new Windows.UI.Xaml.Media.Imaging.BitmapImage(new Uri("https://maps.googleapis.com/maps/api/place/photo?photoreference=" +
                        slikaReferenca + "&sensor=false&maxheight=" + MAX_HEIGHT.ToString() +
                        "&maxwidth=" + MAX_WIDTH.ToString() + "&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s", UriKind.Absolute));
                }
                else
                {
                    novi.SlikaURL = "";
                }


                // dobavljanje lokacije

                JsonObject lokacija = null;

                try
                {
                    lokacija = restoran.GetNamedObject("geometry");

                    JsonObject lokacijav2 = lokacija.GetNamedObject("location");
                        
                    double longitude = lokacijav2.GetNamedNumber("lng");    // x

                    double latitude = lokacijav2.GetNamedNumber("lat");     // y

                    novaLokacija = new Tuple<double, double>(latitude, longitude);

                    novi.Location = novaLokacija;
                }
                catch (Exception) { }

                listaDobavljenih.Add(novi);
            }

            this.Frame.Navigate(typeof(StartSearch1));
        }

        private void favListButton_Click(object sender, RoutedEventArgs e)
        {
            //Otvaranje forme FavList
            this.Frame.Navigate(typeof(FavouritesList));
        }

        private void updateButton_Click(object sender, RoutedEventArgs e)
        {
            //Otvaranje forme za update profila korisnika
            this.Frame.Navigate(typeof(UpdateProfil));
        }

        private void logOutButton_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(PocetnaForma));
        }
    }
}
