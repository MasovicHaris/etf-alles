using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor.ViewModel
{
    class FavouritesListViewModel
    {
        List<Restoran> listaDobavljenih = null;

        public FavouritesListViewModel()
        {
        }

        public async Task<List<Restoran>> dobaviRestorane(int id)
        {
            listaDobavljenih = new List<Restoran>();

           Task t = Task.Run(async () => await getDataUser(id));
           t.Wait();
            return listaDobavljenih;
        }

        
        public async Task<Boolean> getDataUser(int id)
        {
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

            // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetFavList/" + id.ToString());
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/GetFavList/" + id.ToString());
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            string httpResponseBody = "";
            try
            {
               
                httpResponse = await httpClient.GetAsync(requestUri);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
                listaDobavljenih = (List<Restoran>) JsonConvert.DeserializeObject<ICollection<Restoran>>(json);
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            if (listaDobavljenih != null) return true;
            return false;
        }
      
    }
}
