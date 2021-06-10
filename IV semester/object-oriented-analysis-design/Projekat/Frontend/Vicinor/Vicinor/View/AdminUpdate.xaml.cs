using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Popups;
using Vicinor.ViewModel;
using Vicinor.Model;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AdminUpdate : Page
    {
        AdminUpdateViewModel auvm;
        Administrator admin;
        String newUsername = "", newPassword = "", confirmPassword = "";
        String u, p;
        int id = 0;
        Boolean changeUsername = false, changePassword = false;

        public AdminUpdate()
        {
            auvm = new AdminUpdateViewModel();
            admin = new Model.Administrator();
            this.InitializeComponent();
            newUsernameTextBox.Visibility = Visibility.Collapsed;
            newUsernameTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBox.Visibility = Visibility.Collapsed;
            confirmPasswordTextBlock.Visibility = Visibility.Collapsed;
            confirmPasswordTextBox.Visibility = Visibility.Collapsed;
            errorTextBox.Visibility = Visibility.Collapsed;

            Initiale();
        }

        public async void Initiale()
        {
            u = PocetnaFormaViewModel.getUsernameG();
            p = PocetnaFormaViewModel.getPasswordG();
            if (u != null)
                usernameTextBox.Text = u;
            if (p != null)
                passwordTextBox.Text = p;
            bool i = await auvm.Initial(u, p);
            admin = auvm.dajAdmina();
            if (admin != null)
                id = admin.KorisnikId;
        }

        private void changeUsernameHyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            newUsernameTextBox.Visibility = Visibility.Visible;
            newUsernameTextBlock.Visibility = Visibility.Visible;
            changeUsername = true;
        }

        private void changePasswordHyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            newPasswordTextBlock.Visibility = Visibility.Visible;
            newPasswordTextBox.Visibility = Visibility.Visible;
            confirmPasswordTextBlock.Visibility = Visibility.Visible;
            confirmPasswordTextBox.Visibility = Visibility.Visible;
            changePassword = true;
        }

        private async void confirmButton_Click(object sender, RoutedEventArgs e)
        {
            newUsername = newUsernameTextBox.Text.ToString();
            newPassword = newPasswordTextBox.Text.ToString();
            confirmPassword = confirmPasswordTextBox.Text.ToString();

            //Password dozvoljena samo slova, brojevi i _, mora imati barem jedno veliko slovo i jedan broj, min duzina 6
            //Username dozvoljena samo mala slova, brojevi i _, mora biti jedinstven,  min duzina 6

            //Validacija promjena

            //Validiraj username
            if (changeUsername)
            {
                if (!ValidacijaUser.validateUsernameLength(newUsername).Item1)
                {
                    errorTextBox.Visibility = Visibility.Visible;
                    errorTextBox.Text = "Username must contain atleast 6 characters!";
                    return;
                }
                if (!ValidacijaUser.validateUsernameContent(newUsername).Item1)
                {
                    errorTextBox.Visibility = Visibility.Visible;
                    errorTextBox.Text = "Username must contain atleast one number! Username can contain only lower case letters, numbers and '_'. ";
                    return;
                }


                usernameTextBox.Text = newUsernameTextBox.Text.ToString();

                //Unos u bazu

                bool izmjenjen = await auvm.changeUsername(id, newUsername);
                if (izmjenjen)
                {
                    var dialog = new MessageDialog("Username changed successfully!");
                    await dialog.ShowAsync();
                }

                PocetnaFormaViewModel.setUsernameG(newUsername);
                Initiale();

            }


            //Validacija passworda
            if (changePassword)
            {
                if (!ValidacijaUser.validatePasswordLength(newPassword).Item1)
                {
                    errorTextBox.Visibility = Visibility.Visible;
                    errorTextBox.Text = "Password must contain atleast 6 characters!";
                    return;
                }

                if (!ValidacijaUser.validatePasswordContent(newPassword).Item1)
                {
                    errorTextBox.Visibility = Visibility.Visible;
                    errorTextBox.Text = "Password must contain atleast one number and one UpperCase letter! Password can only contain letters, numbers and '_'. ";
                    return;
                }


                if (!ValidacijaUser.validatePasswordConfirmPassword(newPassword, confirmPassword).Item1)
                {
                    errorTextBox.Visibility = Visibility.Visible;
                    errorTextBox.Text = "New password is not equal to Confirm password!";
                    return;
                }
                errorTextBox.Text = "";
                errorTextBox.Visibility = Visibility.Collapsed;
                passwordTextBox.Text = newPasswordTextBox.Text.ToString();

                //Unos u bazu

                bool izmjenjen = await auvm.changePassword(id, newPassword);
                if (izmjenjen)
                {
                    var dialog = new MessageDialog("Password changed successfully!");
                    await dialog.ShowAsync();
                }
                PocetnaFormaViewModel.setPasswordG(newPassword);
                Initiale();
            }

            //Sve uredu, uspješan unos
            errorTextBox.Visibility = Visibility.Collapsed;
            newUsernameTextBox.Visibility = Visibility.Collapsed;
            newUsernameTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBox.Visibility = Visibility.Collapsed;
            confirmPasswordTextBlock.Visibility = Visibility.Collapsed;
            confirmPasswordTextBox.Visibility = Visibility.Collapsed;

            newUsernameTextBox.Text = "";
            newPasswordTextBox.Text = "";
            confirmPasswordTextBox.Text = "";

            changePassword = false;
            changeUsername = false;
        }

        private void cancelButton_Click(object sender, RoutedEventArgs e)
        {
            newUsernameTextBox.Visibility = Visibility.Collapsed;
            newUsernameTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBlock.Visibility = Visibility.Collapsed;
            newPasswordTextBox.Visibility = Visibility.Collapsed;
            confirmPasswordTextBlock.Visibility = Visibility.Collapsed;
            confirmPasswordTextBox.Visibility = Visibility.Collapsed;
            errorTextBox.Text = "";
            errorTextBox.Visibility = Visibility.Collapsed;
            changePassword = false;
            changeUsername = false;
        }
    }
}
