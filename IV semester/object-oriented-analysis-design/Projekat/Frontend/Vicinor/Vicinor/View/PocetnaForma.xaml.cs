using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Vicinor.View;


// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
   
    public sealed partial class PocetnaForma : Page
    {
        public static bool guestUser = false;
       // PocetnaFormaViewModel pvm;
        public PocetnaForma()
        {
            //pvm = new PocetnaFormaViewModel();
            this.InitializeComponent();
            guestUser = false;
            loginUC.onNavigateParentReadyAdminStartPage += LoginUC_onNavigateParentReadyAdminStartPage;
            loginUC.onNavigateParentReadySearchForRestaurants += LoginUC_onNavigateParentReadySearchForRestaurants;
            loginUC.onNavigateParentReadyUserStartPage += LoginUC_onNavigateParentReadyUserStartPage; ;
        }

        private void LoginUC_onNavigateParentReadyUserStartPage(object source, EventArgs e)
        {
            Frame.Navigate(typeof(UserStartPage));
        }

        private void LoginUC_onNavigateParentReadySearchForRestaurants(object source, EventArgs e)
        {
            Frame.Navigate(typeof(SearchRestaurants));
            
        }

       

        private void LoginUC_onNavigateParentReadyAdminStartPage(object source, EventArgs e)
        {
 
            Frame.Navigate(typeof(AdminStartPage));
        }


        /* private void logInButton_Click(object sender, RoutedEventArgs e)
         {
             //LogIn korisnika
             //Otvaranje forme search for restaurants
             //SearchForRestaurants sfr = new SearchForRestaurants();
             Boolean b1 = pvm.loginAdmin(textBox.Text, textBox1.Text).Result;
             Boolean b2 = pvm.loginUser(textBox.Text, textBox1.Text).Result;
             errorTextBlock.Visibility = Visibility.Collapsed;
             errorTextBlock.Text = "";
             if (b1)
             {
                 Frame.Navigate(typeof(AdminStartPage));
             }
              else if (b2)
              {
                  Frame.Navigate(typeof(SearchRestaurants));
              }
             else
             {
                 //textBox1.Text = "Again";
                 // prijava greske            
                 errorTextBlock.Visibility = Visibility.Visible;
                 errorTextBlock.Text = "Invalid username or password!";
             }
         }*/

        private async void registerHyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            //Otvaranje forme za registraciju korisnika
            this.Frame.Navigate(typeof(RegistracijaKorisnika));
      //      bool result = await Launcher.LaunchUriAsync(new Uri("ms-settings:privacy-location"));

        }

        private void continueHyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            //Otvaranje forme search for restaurants
            guestUser = true;
           this.Frame.Navigate(typeof(UserStartPage));
        }
    }
}
