using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;
using Newtonsoft.Json;

namespace Vicinor.ViewModel
{
    class UpdateProfileViewModel
    {
        RegistrovaniKorisnik korisnik;
        public UpdateProfileViewModel()
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


            Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=" + u + "&Password=" + p);

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
    }
}
