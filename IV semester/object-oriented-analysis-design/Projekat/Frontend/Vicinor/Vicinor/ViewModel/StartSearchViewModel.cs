using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor.ViewModel
{
    class StartSearchViewModel
    {
        public StartSearchViewModel()
        {

        }
        public async void AddToFavourite(Restoran r)
        {
            int id = PocetnaFormaViewModel.KORISNIK_ID;

            Windows.Web.Http.HttpClient httpClient = new Windows.Web.Http.HttpClient();
            var headers = httpClient.DefaultRequestHeaders;
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

           // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/AddRestoraunt/" + id + "?name=" + r.Name + "&description=" + r.Description + "&phone=" + r.SlikaURL);
        
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/AddRestoraunt/" + id + "?name=" + r.Name + "&description=" + r.Description + "&phone=" + r.SlikaURL);

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

        }
    }
}
