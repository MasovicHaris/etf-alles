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
using Vicinor.Forme;
using Vicinor.ViewModel;
using Windows.Data.Json;
using Vicinor.Model;
using System.Net.Http;
using System.Threading.Tasks;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.View
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class UserStartPage : Page
    {
        int id_korisnika;  
        public static List<Restoran> listaRecommended;
        public UserStartPage()
        {
            
            this.InitializeComponent();
            listaRecommended = new List<Restoran>();
            id_korisnika = PocetnaFormaViewModel.KORISNIK_ID;
        }

        private async void userListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (fListBoxItem.IsSelected)
            {
                if (PocetnaForma.guestUser)
                {
                    DisplayGuestDialog();
                    return;
                }
                myFrame.Navigate(typeof(FavouritesList));
                userControlUser.Visibility = Visibility.Collapsed;


            }
            else if (srListBoxItem.IsSelected)
            {
                var b = await Initial();
                myFrame.Navigate(typeof(SearchRestaurants));
                userControlUser.Visibility = Visibility.Collapsed;


            }
            else if (upListBoxItem.IsSelected)
            {
                if (PocetnaForma.guestUser)
                {
                    DisplayGuestDialog();
                    return;
                }
                myFrame.Navigate(typeof(UpdateProfil));
                userControlUser.Visibility = Visibility.Collapsed;

            }

            else if (loListBoxItem.IsSelected)
            {
                DisplayLogOutDialog();
            }

        }

        private async void DisplayLogOutDialog()
        {
            ContentDialog logOutDialog = new ContentDialog()
            {
                Title = "LogOut",
                Content = "Are you sure you want to log out?",
                PrimaryButtonText = "Yes",
                SecondaryButtonText = "Cancel"
            };

            ContentDialogResult r = await logOutDialog.ShowAsync();
            if (r== ContentDialogResult.Primary)
            {
                //Otvaramo Poctnu formu
                this.Frame.Navigate(typeof(PocetnaForma));
            }
            else
            {          
                this.Frame.Navigate(typeof(UserStartPage));

            }
        }
        public async Task<bool> Initial()
        {

            //Otvaranje forme za pretragu, dobivanje rezultata sa api-ja
            // liste Restorana
            listaRecommended = new List<Restoran>();


            var client = new HttpClient();


            HttpResponseMessage response = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/search/json?types=restaurant&location=43.84301249454391,18.34612836298834&radius=5000&sensor=false&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));
            var jsonString = await response.Content.ReadAsStringAsync();

            JsonObject root = JsonValue.Parse(jsonString).GetObject();

            JsonArray REzultati = root.GetNamedArray("results");

            for (uint i = 0; i < REzultati.Count; ++i)
            {
                JsonObject restoran = REzultati.GetObjectAt(i);

                Restoran novi = new Restoran();

                string name_ime_restorana = restoran.GetNamedString("name");
                string place_id_kao_deskripcija = restoran.GetNamedString("vicinity");
                string adresa_kao_phone_number;
                try
                {
                    adresa_kao_phone_number = restoran.GetNamedValue("rating").ToString();

                }
                catch (Exception k)
                {
                    adresa_kao_phone_number = "";
                }
                string place_id = null;
                novi.Name = name_ime_restorana;

                novi.PhoneNumber = "+38733225 883";

                novi.RestoranId = (int)i;

                novi.Description = place_id_kao_deskripcija;

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
                    //Postaviti phone number
                    //                    https://maps.googleapis.com/maps/api/place/details/json?placeid=ChIJS51qkj_KWEcRLePQI32zgn0&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s
                    //link
                }



                try
                {
                    objekatPhotosM = restoran.GetNamedArray("photos");
                }
                catch (Exception)
                {
                }

                if (objekatPhotosM != null && objekatPhotosM.Count > 0)
                {
                    JsonObject objekatPhotos = objekatPhotosM.GetObjectAt(0);

                    string slikaReferenca = objekatPhotos.GetNamedString("photo_reference");

                    double MAX_HEIGHT = objekatPhotos.GetNamedNumber("height");

                    double MAX_WIDTH = objekatPhotos.GetNamedNumber("width");

                    novi.SlikaURL = "https://maps.googleapis.com/maps/api/place/photo?photoreference=" +
                        slikaReferenca + "&sensor=false&maxheight=" + MAX_HEIGHT.ToString() +
                        "&maxwidth=" + MAX_WIDTH.ToString() + "&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s";
                    novi.Slika = new Windows.UI.Xaml.Media.Imaging.BitmapImage(new Uri(novi.SlikaURL, UriKind.Absolute));
                }
                else novi.SlikaURL = "";


                // dobavljanje lokacije

                JsonObject lokacija = null;

                try
                {
                    lokacija = restoran.GetNamedObject("geometry");

                    JsonObject lokacijav2 = lokacija.GetNamedObject("location");

                    double longitude = lokacijav2.GetNamedNumber("lng");    // x

                    double latitude = lokacijav2.GetNamedNumber("lat");     // y

                    Tuple<double, double> novaLokacija = new Tuple<double, double>(0, 0);

                    novaLokacija = new Tuple<double, double>(latitude, longitude);



                    novi.Location = novaLokacija;
                }
                catch (Exception) { }

                listaRecommended.Add(novi);
            }
            return true;

        }

        private async void DisplayGuestDialog()
        {
            ContentDialog guestDialog = new ContentDialog()
            {
                Title = "Message",
                Content = "This option is only available for registered users!",
                PrimaryButtonText = "Ok",
              
            };

            await guestDialog.ShowAsync();
            
        }

        private void hamburgerButton_Click(object sender, RoutedEventArgs e)
        {
            mySplitView.IsPaneOpen = !mySplitView.IsPaneOpen;


        }
    }
}
