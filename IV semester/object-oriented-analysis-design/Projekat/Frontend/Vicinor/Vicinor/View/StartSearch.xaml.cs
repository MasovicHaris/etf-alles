using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Vicinor.Model;
using Vicinor.View;
using Vicinor.ViewModel;

using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;


// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class StartSearch1 : Page
    {
        public static List<Restoran> dRestorani;
        StartSearchViewModel ssvm;
        public static double rating = 0;
        public static int idRestoranaKliknuto = 0;
        public StartSearch1()
        {
            this.InitializeComponent();

            dRestorani = new List<Restoran>();
            dRestorani = SearchRestaurants.listaDobavljenih;
            //   flip.ItemsSource = dRestorani;
            ssvm = new StartSearchViewModel();

        }

       
        private void flip_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void FlipView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void star1Button_Click(object sender, RoutedEventArgs e)
        {
            if (PocetnaForma.guestUser)
            {
                DisplayGuestDialog();
                return;
            }
            Restoran r = dRestorani[flip.SelectedIndex];
            ssvm.AddToFavourite(r);

        }

        async void messageDialog(String s)
        {
            var dialog = new MessageDialog(s);
            await dialog.ShowAsync();
        }

        private void routeButton_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(PrikazOdabranogRestorana));
        }

        private void phoneCallButton_Click(object sender, RoutedEventArgs e)
        {
            messageDialog("Restoran " + dRestorani[flip.SelectedIndex].Name + " pozivate na broj: " + dRestorani[flip.SelectedIndex].PhoneNumber);

        }

        private void commentsHyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            Recenzija r = dRestorani[flip.SelectedIndex].ListRezension.OfType<Recenzija>().First();
            if (r != null)
                rating = r.StarRating;
            else rating = 0;
            idRestoranaKliknuto = flip.SelectedIndex;

            this.Frame.Navigate(typeof(Comments));
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
    }


}
