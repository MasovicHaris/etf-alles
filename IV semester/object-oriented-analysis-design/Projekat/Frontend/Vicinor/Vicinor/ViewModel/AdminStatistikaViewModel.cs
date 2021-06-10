using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor.ViewModel
{
    //Interfejs - zahtjevani novi standard (zaokruživanje na jednu decimalu)
    interface IAdminStatistika
    {
        double newGetPrecentageOfRegistered();
        double newGetPrecentageOfUnregistered();
    }

    //Klasa Adaptee sa implementiranim postojećim interfejsom 
    public class AdminStatistikaViewModel
    {
        List<RegistrovaniKorisnik> allRegisteredUsers = null;
        List<NeregistrovaniKorisnik> allUnregisteredUsers = null;


        public AdminStatistikaViewModel()
        {
            allRegisteredUsers = new List<RegistrovaniKorisnik>();
            allUnregisteredUsers = new List<NeregistrovaniKorisnik>();

        }
        public async Task<int> Initial()
        {
            int j = await GetAllUnregisteredUsers();

            int i = await GetAllRegisteredUsers();
            return i;
        }
        public int GetNumberOfUnregisteredUsers()
        {
            return allUnregisteredUsers.Count;
        }
        public int GetNumberOfRegisteredUsers()
        {
            return allRegisteredUsers.Count;
        }
        public double GetPrecentageOfRegistered()
        {
            //return Math.Round((double)(GetNumberOfRegisteredUsers() / GetAllUsers()) *100,2);
            return Math.Round(((double)GetNumberOfRegisteredUsers() / GetAllUsers()) * 100, 2);
        }
        public double GetPrecentageOfUnregistered()
        {
            return Math.Round(((double)GetNumberOfUnregisteredUsers() / GetAllUsers()) * 100, 2);


        }
        public int GetAllUsers()
        {
            return allUnregisteredUsers.Count + allRegisteredUsers.Count;
        }
        public int GetNumberOfBannedUsers()
        {
            return allRegisteredUsers.Where(x => x.Banned == true).Count();
        }
        public async Task<int> GetAllRegisteredUsers()
        {
            Windows.Web.Http.HttpClient httpClient = new Windows.Web.Http.HttpClient();

            //Add a user-agent header to the GET request. 
            var headers = httpClient.DefaultRequestHeaders;

            //The safe way to add a header value is to use the TryParseAdd method and verify the return value is true,
            //especially if the header value is coming from user input.
            string header = "ie";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }

            header = "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }

            // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAll");
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/GetAll");
       
            //Send the GET request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {
                //Send the GET request
                httpResponse = await httpClient.GetAsync(requestUri);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

                allRegisteredUsers = JsonConvert.DeserializeObject<List<RegistrovaniKorisnik>>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return 1;

        }
        public async Task<int> GetAllUnregisteredUsers()
        {
            Windows.Web.Http.HttpClient httpClient = new Windows.Web.Http.HttpClient();

            //Add a user-agent header to the GET request. 
            var headers = httpClient.DefaultRequestHeaders;

            //The safe way to add a header value is to use the TryParseAdd method and verify the return value is true,
            //especially if the header value is coming from user input.
            string header = "ie";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }

            header = "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)";
            if (!headers.UserAgent.TryParseAdd(header))
            {
                throw new Exception("Invalid header value: " + header);
            }

            //Uri requestUri = new Uri("http://localhost:6796/NeregistrovaniKorisniks/GetAll");
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/NeregistrovaniKorisniks/GetAll");
        
            //Send the GET request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";

            try
            {
                //Send the GET request
                httpResponse = await httpClient.GetAsync(requestUri);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

                allUnregisteredUsers = JsonConvert.DeserializeObject<List<NeregistrovaniKorisnik>>(json);

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return 1;
        }

    }

    //Klasa Adapter - implementira novi način prikaza podataka
    class Adapter : AdminStatistikaViewModel, IAdminStatistika
    {
        public double newGetPrecentageOfRegistered()
        {
            //return Math.Round((double)(GetNumberOfRegisteredUsers() / GetAllUsers()) *100,2);
            return Math.Round(((double)GetNumberOfRegisteredUsers() / GetAllUsers()) * 100, 1);
        }
        public double newGetPrecentageOfUnregistered()
        {
            return Math.Round(((double)GetNumberOfUnregisteredUsers() / GetAllUsers()) * 100, 1);


        }
    }


}
