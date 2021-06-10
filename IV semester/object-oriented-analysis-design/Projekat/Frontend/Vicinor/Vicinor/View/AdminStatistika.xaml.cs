using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Vicinor.Model;
using Vicinor.ViewModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AdminStatistika : Page
    {
         AdminStatistikaViewModel asvm;
        public AdminStatistika()
        {

            asvm = new AdminStatistikaViewModel();
            this.InitializeComponent();
            Initiale();

        }
        public async void Initiale()
        {
            int i = await asvm.Initial();
            brRegistrovanihTextBox.Text = asvm.GetNumberOfRegisteredUsers().ToString();
            brBanovanihTextBox.Text = asvm.GetNumberOfBannedUsers().ToString();
            procenatRegTextBox.Text = asvm.GetPrecentageOfRegistered().ToString()+"%";
            procenatNeregTextBox.Text = asvm.GetPrecentageOfUnregistered().ToString() + "%";
        }

    }
}
