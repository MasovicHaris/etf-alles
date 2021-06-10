using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Popups;
using Vicinor.ViewModel;
using Vicinor.Model;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage.Pickers;
using Windows.Storage;
using Windows.Storage.Streams;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    interface IComponent
    {
        void prevediLabele();
    }

    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class UpdateProfil : Page
    {
        UpdateProfilViewModel upvm;
        RegistrovaniKorisnik regUser;
        String newUsername = "", newPassword = "", newFirstName = "", newLastName = "", newEmail = "";
        String u, p;
        int id = 0;
        Boolean showPassword = false, changePassword = false;

        private void showPasswordButton_Click(object sender, RoutedEventArgs e)
        {
            showPassword = !showPassword;
            if (showPassword)
            {
                Password.Visibility = Visibility.Visible;
                pTextBox.Visibility = Visibility.Collapsed;
            }
            else
            {
                Password.Visibility = Visibility.Collapsed;
                pTextBox.Visibility = Visibility.Visible;
            }
        }

        private void changePasswordButton_Click(object sender, RoutedEventArgs e)
        {
            changePassword = !changePassword;
            if (changePassword)
            {
                NewPassword.Visibility = Visibility.Visible;
                newPasswordTextBlock.Visibility = Visibility.Visible;
                changePasswordButton.Content = "Cancle change";
            }
            else
            {
                NewPassword.Visibility = Visibility.Collapsed;
                newPasswordTextBlock.Visibility = Visibility.Collapsed;
                changePasswordButton.Content = "Change password";
            }


        }

        private async void AddImage_Click(object sender, RoutedEventArgs e)
        {
            FileOpenPicker f = new FileOpenPicker();
            f.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            f.ViewMode = PickerViewMode.Thumbnail;
            f.FileTypeFilter.Clear();
            f.FileTypeFilter.Add(".jpg");
            f.FileTypeFilter.Add(".png");
            f.FileTypeFilter.Add(".jpeg");
            StorageFile sf = await f.PickSingleFileAsync();
            if (sf != null)
            {
                IRandomAccessStream fs = await sf.OpenAsync(FileAccessMode.Read);
                BitmapImage bm = new BitmapImage();
                bm.SetSource(fs);
                Picture.Source = bm;
            }

        }

        public UpdateProfil()
        {
            upvm = new UpdateProfilViewModel();
            regUser = PocetnaFormaViewModel.getRegUser();
            this.InitializeComponent();

            NewPassword.Visibility = Visibility.Collapsed;
            newPasswordTextBlock.Visibility = Visibility.Collapsed;
            Password.Visibility = Visibility.Collapsed;
            Initiale();
        }

        public async void Initiale()
        {
            u = PocetnaFormaViewModel.getUsernameG();
            p = PocetnaFormaViewModel.getPasswordG();
            if (u != null)
                Username.Text = u;
            if (p != null)
            {
                Password.Text = p;
                pTextBox.Password = p;
            }

            bool i = await upvm.Initial(u, p);
            regUser = upvm.dajKorisnika();
            if (regUser != null)
            {
                id = regUser.KorisnikId;
                if (regUser.FirstName != null) firstName.Text = regUser.FirstName;
                if (regUser.LastName != null) lastName.Text = regUser.LastName;
                if (regUser.Email != null) Email.Text = regUser.Email;
                if (regUser.DateOfBirth != null) DateTextBox.Text = regUser.DateOfBirth.Day.ToString() + "/" + regUser.DateOfBirth.Month.ToString() + "/" + regUser.DateOfBirth.Year.ToString();
            }

            byte[] buffer = regUser.Image;

            using (InMemoryRandomAccessStream stream = new InMemoryRandomAccessStream())
            {
                using (DataWriter writer = new DataWriter(stream.GetOutputStreamAt(0)))
                {
                    writer.WriteBytes(buffer);
                    await writer.StoreAsync();
                }
                BitmapImage image = new BitmapImage();
                // await image.SetSourceAsync(stream);
                Picture.Source = image;

            }
            //       Picture.Source = new BitmapImage(new Uri("ms-appx:///Assets/vicinor-logo.png"));


        }

        async void messageDialog(String s)
        {
            var dialog = new MessageDialog(s);
            await dialog.ShowAsync();
        }

        private async void Update_Click(object sender, RoutedEventArgs e)
        {
            newFirstName = firstName.Text;
            newLastName = lastName.Text;
            newPassword = NewPassword.Text;
            newUsername = Username.Text;
            newEmail = Email.Text;
            String poruka = "";

            if (newFirstName != regUser.FirstName)
            {
                Tuple<bool, String> rez = ValidacijaUser.validateFirstName(newFirstName);
                poruka += rez.Item2 + "\n";
                if (rez.Item1)
                {
                    //Vrsimo upis novih podataka u bazu 
                    if (await upvm.changeFirstName(id, newFirstName)) regUser.FirstName = newFirstName;
                }
            }
            if (newLastName != regUser.LastName)
            {
                Tuple<bool, String> rez = ValidacijaUser.validateLastName(newLastName);
                poruka += rez.Item2 + "\n";
                if (rez.Item1)
                {
                    //Vrsimo upis novih podataka u bazu 
                    if (await upvm.changeLastName(id, newFirstName)) regUser.LastName = newLastName;
                }
            }
            if (newPassword != regUser.Password)
            {
                Tuple<bool, String> rez1 = ValidacijaUser.validatePasswordLength(newPassword);
                Tuple<bool, String> rez2 = ValidacijaUser.validatePasswordContent(newPassword);
                //Validacija

                if (!rez1.Item1)
                {
                    poruka += rez1.Item2 + "\n";

                }
                else if (!rez2.Item1)
                {
                    poruka += rez2.Item2 + "\n";
                }
                else
                {
                    poruka += "New password is valid.\n";
                    //Vrsimo upis u bazu
                    bool izmjenjen = await upvm.changePassword(id, newPassword);
                    if (izmjenjen)
                    {
                        PocetnaFormaViewModel.setPasswordG(newPassword);
                        regUser.Password = newPassword;
                    }
                }



            }
            if (newEmail != regUser.Email)
            {
                Tuple<bool, String> rez = ValidacijaUser.validateEmail(newEmail);
                poruka += rez.Item2 + "\n";
                if (rez.Item1)
                {
                    //Vrsimo upis novih podataka u bazu 
                    if (await upvm.changeEmail(id, newEmail)) regUser.Email = newEmail;

                }

            }
            if (newUsername != regUser.Username)
            {
                Tuple<bool, String> rez1 = ValidacijaUser.validateUsernameLength(newUsername);
                Tuple<bool, String> rez2 = ValidacijaUser.validateUsernameContent(newUsername);
                //Validacija
                if (rez1.Item1 && rez2.Item1)
                {
                    poruka += "New username is valid.\n";
                    //Vrsimo upis novih podataka u bazu 
                    bool izmjenjen = await upvm.changeUsername(id, newUsername);

                    if (izmjenjen)
                    {
                        PocetnaFormaViewModel.setUsernameG(newUsername);
                        regUser.Username = newUsername;
                    }

                }
                else
                {
                    if (!rez1.Item1)
                    {
                        poruka += rez1.Item2;

                    }
                    if (!rez2.Item1)
                    {
                        poruka += "\n" + rez2.Item2;
                    }
                }

            }


            messageDialog(poruka);
            //Refresh form




            //this.Frame.Navigate(typeof(SearchRestaurants));
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {

            //Otvaranje pocetne forme
            messageDialog("Update canceled");
            // this.Frame.Navigate(typeof(SearchRestaurants));
        }
    }
}
