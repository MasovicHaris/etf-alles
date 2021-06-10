using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Popups;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Net.Http;
using System.Net.Http.Headers;
using Newtonsoft.Json;
using Vicinor.Model;
using Vicinor.ViewModel;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Xaml.Media.Imaging;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class RegistracijaKorisnika : Page
    {
        byte[] buffer;

        RegistracijaKorisnikaViewModel rkvm;
        public RegistracijaKorisnika()
        {
            this.InitializeComponent();
            rkvm = new RegistracijaKorisnikaViewModel();
        }

        async void messageDialog(String s)
        {
            var dialog = new MessageDialog(s);
            await dialog.ShowAsync();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            //Povratak na pocetnu formu

            messageDialog("Registration canceled");
            this.Frame.Navigate(typeof(PocetnaForma));
        }

        private async void RegisterButton_Click(object sender, RoutedEventArgs e)
        {
            if (buffer == null) buffer = new byte[0];
            if (Password.Text == "" || Username.Text == "" || FirstName.Text == "" || LastName.Text == "" || Email.Text == "")
            {
                messageDialog("Enter all data!");
                return;
            }
            Boolean b = await rkvm.Registruj(Password.Text, Username.Text, FirstName.Text, LastName.Text, Email.Text, false, DateOfBirth.Date.DateTime, buffer);

            if (b) {
                messageDialog("Registration succesful");
                this.Frame.Navigate(typeof(PocetnaForma));
            }
            else messageDialog("Try again!");

        }
        private async void UploadButton_Click(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();
            picker.ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation =
                Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".jpeg");
            picker.FileTypeFilter.Add(".png");
            StorageFile file1 = await picker.PickSingleFileAsync();
            //Convert to byte[]
            using (var inputStream = await file1.OpenSequentialReadAsync())
            {
                var readStream = inputStream.AsStreamForRead();
                buffer = new byte[readStream.Length];
                await readStream.ReadAsync(buffer, 0, buffer.Length);
            }
            //Od Convert ahhah 
            using (InMemoryRandomAccessStream stream = new InMemoryRandomAccessStream())
            {
                using (DataWriter writer = new DataWriter(stream.GetOutputStreamAt(0)))
                {
                    writer.WriteBytes(buffer);
                    await writer.StoreAsync();
                }
                BitmapImage image = new BitmapImage();
                await image.SetSourceAsync(stream);
                Picture.Source = image;

            }

        }

        private void AddImageButton_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
