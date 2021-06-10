using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor.ViewModel
{
    public class AdminUserOverviewViewModel
    {
        List<RegistrovaniKorisnik> listaKorisnika;

        public AdminUserOverviewViewModel()
        {
            listaKorisnika = new List<RegistrovaniKorisnik>();
        }

        public async Task<Boolean> Initial()
        {
            Boolean j = await getAllData();
            return j;

        }

        public List<RegistrovaniKorisnik> dajListuKorisnika()
        {
            return listaKorisnika;
        }


        private async Task<Boolean> getAllData()
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

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAll");
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/GetAll");
      
            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=Masha&Password=sifraHaris");

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
                listaKorisnika = JsonConvert.DeserializeObject<List<RegistrovaniKorisnik>>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }

            if (listaKorisnika.Count > 0) return true;
            return false;
        }


        public async Task<Boolean> banujUsera(String name)
        {
            Boolean b = false;
            RegistrovaniKorisnik a = new RegistrovaniKorisnik();
            a = listaKorisnika.Find(x => x.Username == name && x.Banned == false);
            if (a != null)
            {
                b = await banujKorisnika(a.KorisnikId);
            
            }
            return b;
        }

        public async Task<Boolean> unbanujUsera(String name)
        {
            Boolean b = false;
            RegistrovaniKorisnik a = new RegistrovaniKorisnik();
            a = listaKorisnika.Find(x => x.Username == name && x.Banned == true);
            if (a != null)
            {
                b = await unbanovanje(a.KorisnikId);

            }
            return b;
        }


        private async Task<Boolean> banujKorisnika(int id)
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

           // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/BanUser/" + id);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/BanUser/" + id);


            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {
                
                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
            //    listaKorisnika = JsonConvert.DeserializeObject<List<RegistrovaniKorisnik>>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }

        private async Task<Boolean> unbanovanje(int id)
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

        // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/UnbanUser/" + id);
        
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/UnbanUser/" + id);

            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
                //    listaKorisnika = JsonConvert.DeserializeObject<List<RegistrovaniKorisnik>>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }


    }
}
