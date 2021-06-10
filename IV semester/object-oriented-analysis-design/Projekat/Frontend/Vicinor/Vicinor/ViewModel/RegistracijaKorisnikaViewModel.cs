using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor.ViewModel
{
   

    class RegistracijaKorisnikaViewModel
    {
        public RegistrovaniKorisnik korisnik;
        public RegistracijaKorisnikaViewModel()
        {
            korisnik = new RegistrovaniKorisnik();

        }
        public async Task<bool> Registruj(string Password, string Username, string FirstName, string LastName, string Email, Boolean Banned, DateTime DateOfBirth, byte[] Image)
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
            string stri = Convert.ToBase64String(Image);
            korisnik = new RegistrovaniKorisnik(Password, Username, FirstName, LastName, Email, Banned, DateOfBirth, null);
            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/Add" + "?Password=" +korisnik.Password+ "&Username=" +korisnik.Username+ "&FirstName="+korisnik.FirstName + "&LastName="+korisnik.LastName + "&Email="+korisnik.Email + "&Banned=" + Banned+ "&DateOfBirth=" + korisnik.DateOfBirth+"&Image="+ stri);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/Add" + "?Password=" + korisnik.Password + "&Username=" + korisnik.Username + "&FirstName=" + korisnik.FirstName + "&LastName=" + korisnik.LastName + "&Email=" + korisnik.Email + "&Banned=" + Banned + "&DateOfBirth=" + korisnik.DateOfBirth + "&Image=" + stri);


            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();
            string httpResponseBody = "";
            try
            {
                httpResponse = await httpClient.PostAsync(requestUri, null);
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

   /* public byte[] ImageToByteArray(System.Drawing.Image imageIn)
    {
        using (var ms = new MemoryStream())
        {
            imageIn.Save(ms, imageIn.RawFormat);
            return ms.ToArray();
        }
    }*/
}
