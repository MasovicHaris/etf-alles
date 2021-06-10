using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Vicinor.ViewModel;
using Vicinor.Model;
using Windows.UI.Popups;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AdminUserOverview : Page
    {
        AdminUserOverviewViewModel auov;
        List<RegistrovaniKorisnik> listaKor; 
        public AdminUserOverview()
        {
            listaKor = new List<RegistrovaniKorisnik>();
            auov = new AdminUserOverviewViewModel();
            this.InitializeComponent();
           
            Initiale();
        }

 
        public async void Initiale()
        {
            bool i = await auov.Initial();
            listaKor = auov.dajListuKorisnika();
            if (i)
            {
                usersListView.Items.Clear();
                foreach(var a in listaKor)
                {
                    usersListView.Items.Add(a.Username);
                }
            }
        }
        
        private async void showProfileButton_Click(object sender, RoutedEventArgs e)
        {
            String a = null;
            if(usersListView.SelectedItem != null) a = usersListView.SelectedItem.ToString();
            if(a == null)
            {
                // implementacija greške
                var dialog = new MessageDialog("Select a user by clicking on the list item!");
                await dialog.ShowAsync();
            }
            else
            {
                // prikaz korisnika
                RegistrovaniKorisnik rk = listaKor.Find((x) => x.Username == a);
                String prikaz = null;

                prikaz = "Users profile: " + rk.Username
                    + "\n\nUser id: " + rk.KorisnikId
                    + "\nName and surname: " + rk.FirstName + " " + rk.LastName
                    + "\nBanned/a: " + rk.Banned.ToString()
                    + "\nE-mail: " + rk.Email;

                var dialog = new MessageDialog(prikaz);
                await dialog.ShowAsync();
            }
        }
        
        private async void banButton_Click(object sender, RoutedEventArgs e)
        {
            String a = "";
            if (usernameAusoSuggestBox.Text != null) {
                a = usernameAusoSuggestBox.Text.ToString();
            }
            bool banovan = await auov.banujUsera(a);
            if (banovan)
            {
                var dialog = new MessageDialog("User succesfully banned!");
                await dialog.ShowAsync();
            }
            else
            {
                var dialog = new MessageDialog("User is already banned or doesn't exist!");
                await dialog.ShowAsync();
            }
            Initiale();
        }


        private async void unbanButton_Click(object sender, RoutedEventArgs e)
        {
            String a = "";
            if (usernameAusoSuggestBox.Text != null)
            {
                a = usernameAusoSuggestBox.Text.ToString();
            }
            bool unbanovan = await auov.unbanujUsera(a);
            if (unbanovan)
            {
                var dialog = new MessageDialog("User successfully unbanned!");
                await dialog.ShowAsync();
            }
            else
            {
                var dialog = new MessageDialog("User is already unbanned or doesn't exist!");
                await dialog.ShowAsync();
            }
            Initiale();

        }
       
      
         
         
     

    }
}
