using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Popups;
using Vicinor.ViewModel;
using Vicinor.Model;
using System.Collections.Generic;


// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

namespace Vicinor.UserControls
{
    public sealed partial class banUserUserControl : UserControl
    {
        AdminUserOverviewViewModel auov;
        List<RegistrovaniKorisnik> listaKor;
        public banUserUserControl()
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
                foreach (var a in listaKor)
                {
                    usersListView.Items.Add(a.Username);
                }
            }

        }

        private async void banButton_Click_1(object sender, RoutedEventArgs e)
        {
            String a = "";
            if (usernameAusoSuggestBox.Text != null)
            {
                a = usernameAusoSuggestBox.Text.ToString();
            }
            bool banovan = await auov.banujUsera(a);
            if (banovan)
            {
                var dialog = new MessageDialog("User successfully banned!");
                await dialog.ShowAsync();
            }
            else {
                var dialog = new MessageDialog("User is already banned or does not exist!");
                await dialog.ShowAsync();
            }

            Initiale();
        }

        private async void unbanButton_Click_1(object sender, RoutedEventArgs e)
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
                var dialog = new MessageDialog("User is already unbanned or does not exist!");
                await dialog.ShowAsync();
            }
            Initiale();
        }
        private async void showProfileButton_Click(object sender, RoutedEventArgs e)
        {
            Initiale();
            String a = null;
            if (usersListView.SelectedItem != null) a = usersListView.SelectedItem.ToString();
            if (a == null)
            {
                // implementacija greške
                var dialog = new MessageDialog("Choose user!");
                await dialog.ShowAsync();
            }
            else
            {
                // prikaz korisnika
                RegistrovaniKorisnik rk = listaKor.Find((x) => x.Username == a);
                String prikaz = null;

                prikaz = "Prikaz profila o korisniku: " + rk.Username
                    + "\n\nId korisnika: " + rk.KorisnikId
                    + "\nPuno ime i prezime: " + rk.FirstName + " " + rk.LastName
                    + "\nBanovan/a: " + rk.Banned.ToString()
                    + "\nMail: " + rk.Email;

                var dialog = new MessageDialog(prikaz);
                await dialog.ShowAsync();
            }
        }

    }
}
