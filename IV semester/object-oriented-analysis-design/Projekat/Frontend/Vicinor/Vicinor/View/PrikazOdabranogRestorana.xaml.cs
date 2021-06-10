using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Maps;
using Windows.Services.Maps;
using Windows.Devices.Geolocation;
using System.Threading;
using System.Threading.Tasks;
using Vicinor.Forme;



// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace Vicinor.View
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class PrikazOdabranogRestorana : Page
    {
        public Geolocator geolocator = null;
        Geoposition startPosition, endPosition;
        private CancellationTokenSource _geolocationCancelationTokenSource = null;

        double Lat1 = 0, Long1 = 0, Long2 = 0, Lat2 = 0;


        public PrikazOdabranogRestorana()
        {
            this.InitializeComponent();
            ucitajMapu();
     
        }

        private async void ucitajMapu()
        {
            await getLocationByGeolocatorAsync();
            Lat1 = startPosition.Coordinate.Point.Position.Latitude;
            Long1 = startPosition.Coordinate.Point.Position.Longitude;
            //Lat1 = SearchRestaurants.position.Coordinate.Point.Position.Latitude;
            //Long1 = SearchRestaurants.position.Coordinate.Point.Position.Longitude;

            Long2 = SearchRestaurants.novaLokacija.Item2;
            Lat2 = SearchRestaurants.novaLokacija.Item1;

            BasicGeoposition startLocation = new BasicGeoposition() { Latitude = Lat1, Longitude = Long1 };
            BasicGeoposition endLocation = new BasicGeoposition() { Latitude = Lat2, Longitude = Long2 };

            // Get the route between the points.
            MapRouteFinderResult routeResult =
                  await MapRouteFinder.GetDrivingRouteAsync(
                  new Geopoint(startLocation),
                  new Geopoint(endLocation),
                  MapRouteOptimization.Time,
                  MapRouteRestrictions.None);

            if (routeResult.Status == MapRouteFinderStatus.Success)
            {
                // Use the route to initialize a MapRouteView.
                MapRouteView viewOfRoute = new MapRouteView(routeResult.Route);
                viewOfRoute.RouteColor = Colors.Yellow;
                viewOfRoute.OutlineColor = Colors.Black;

                // Add the new MapRouteView to the Routes collection
                // of the MapControl.
                myMap.Routes.Add(viewOfRoute);

                // Fit the MapControl to the route.
                await myMap.TrySetViewBoundsAsync(
                      routeResult.Route.BoundingBox,
                      null,
                      Windows.UI.Xaml.Controls.Maps.MapAnimationKind.None);


                System.Text.StringBuilder routeInfo = new System.Text.StringBuilder();

                // Display summary info about the route.
                routeInfo.Append("Total estimated time (minutes) = ");
                double time =  Math.Round(routeResult.Route.EstimatedDuration.TotalMinutes, 1);
                routeInfo.Append(time.ToString());
                routeInfo.Append("\nTotal length (meters) = ");
                routeInfo.Append((Math.Round(routeResult.Route.LengthInMeters,0)).ToString());

                // Display the directions.
                routeInfo.Append("\n\nDIRECTIONS\n\n");

                foreach (MapRouteLeg leg in routeResult.Route.Legs)
                {
                    foreach (MapRouteManeuver maneuver in leg.Maneuvers)
                    {
                        routeInfo.AppendLine(maneuver.InstructionText);
                    }
                }

                // Load the text box.
                tbOutputText.Text = routeInfo.ToString();
            }
            else
            {
                tbOutputText.Text =
                      "A problem occurred: " + routeResult.Status.ToString();
            }
        }

       

        private async Task<bool> getLocationByGeolocatorAsync()
        {
            if (geolocator == null)
            {
                geolocator = new Geolocator();
            }

            bool boSuccess = false;

            //some preflight checks here
            if (geolocator.LocationStatus != PositionStatus.Disabled && geolocator.LocationStatus != PositionStatus.NotAvailable)
            {
                try
                {
                    // Get cancellation token 
                    _geolocationCancelationTokenSource = new CancellationTokenSource();

                    await this.cancelGeolocationTimerAsync();

                    startPosition = await geolocator.GetGeopositionAsync().AsTask();


                    boSuccess = true;
                }
                catch (Exception e)
                {
                }
                finally
                {
                    _geolocationCancelationTokenSource = null;
                }
            }
            return boSuccess;
        }


        private async Task cancelGeolocationTimerAsync()
        {
            //delay should be less than 7sec (cause 7sec is the default timeout of the geolocator)
            //if a delay > 7sec is needed a timer with a value set higher than the value here should 
            //be set to the geolocator manually
            await Task.Delay(2000);
            if (_geolocationCancelationTokenSource != null)
            {
                _geolocationCancelationTokenSource.Cancel();
                _geolocationCancelationTokenSource = null;
            }
        }



        private void myMap_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private void returnButton_Click(object sender, RoutedEventArgs e)
        {
            this.Frame.Navigate(typeof(SearchRestaurants));
        }
    }

}
