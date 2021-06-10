using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;
using Newtonsoft.Json;

namespace Vicinor.ViewModel
{
    class UpdateProfilViewModel
    {
        RegistrovaniKorisnik korisnik;
        public UpdateProfilViewModel ()
        {
            korisnik = new RegistrovaniKorisnik();
        }

        public async Task<Boolean> Initial(String u, String p)
        {
            Boolean j = await getData(u, p);
            return j;

        }

        public RegistrovaniKorisnik dajKorisnika()
        {
            return korisnik;
        }

        private async Task<Boolean> getData(String u, String p)
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


            // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=" + u + "&Password=" + p);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/GetAccount?Username=" + u + "&Password=" + p);

        
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
                korisnik = JsonConvert.DeserializeObject<RegistrovaniKorisnik>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }

            if (korisnik != null) return true;
            return false;
        }

        public async Task<Boolean> changeUsername(int id, String name)
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

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/changeUsername/" + id + "?Username=" + name);
        
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/changeUsername/" + id + "?Username=" + name);


            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }

        public async Task<Boolean> changePassword(int id, String password)
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

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/changePassword/" + id + "?Password=" + password);
    
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/changePassword/" + id + "?Password=" + password);



            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }

        public async Task<Boolean> changeEmail(int id, String email)
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

           // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/changeEmail/" + id + "?Email=" + email);
        
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/changeEmail/" + id + "?Email=" + email);


            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }

        public async Task<Boolean> changeFirstName(int id, String fName)
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

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/changeFirstName/" + id + "?FirstName=" + fName);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/changeFirstName/" + id + "?FirstName=" + fName);

        

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=Masha&Password=sifraHaris");
            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }

        public async Task<Boolean> changeLastName(int id, String lName)
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

        // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/changeLastName/" + id + "?LastName=" + lName);
        
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/changeLastName/" + id + "?LastName=" + lName);


            //Send the PUT request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {

                httpResponse = await httpClient.PutAsync(requestUri, null);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;

            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

        }



    }
}
