using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.Forme
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class AdminStartPage : Page
    {
        public AdminStartPage()
        {
            this.InitializeComponent();
            var appView = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView();
            appView.TitleBar.BackgroundColor = Windows.UI.Colors.LightBlue; // or {a: 255, r: 0, g: 0, b: 0}
            appView.TitleBar.InactiveBackgroundColor = Windows.UI.Colors.Black;
            appView.TitleBar.ButtonBackgroundColor = Windows.UI.Colors.LightBlue;
            appView.TitleBar.ButtonHoverBackgroundColor = Windows.UI.Colors.Black;
            appView.TitleBar.ButtonPressedBackgroundColor = Windows.UI.Colors.LightBlue;
            appView.TitleBar.ButtonInactiveBackgroundColor = Windows.UI.Colors.Black;


        }

        private void adminListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (sListBoxItem.IsSelected)
            {
                myFrame.Navigate(typeof(AdminStatistika));
                userControlAdmin.Visibility = Visibility.Collapsed;
                
            }
            else if (uoListBoxItem.IsSelected)
            {
                myFrame.Navigate(typeof(AdminUserOverview));
                userControlAdmin.Visibility = Visibility.Collapsed;

            }
            else if (upListBoxItem.IsSelected)
            {
                myFrame.Navigate(typeof(AdminUpdate));
                userControlAdmin.Visibility = Visibility.Collapsed;

            }
            
        }

        private void hamburgerButton_Click(object sender, RoutedEventArgs e)
        {
            mySplitView.IsPaneOpen = !mySplitView.IsPaneOpen;
        
           
        }
    }
}

