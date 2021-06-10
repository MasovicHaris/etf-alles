using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Windows.System.Threading;
using Vicinor.Model;
using System.Threading.Tasks;
using System.Net.Http;

namespace Vicinor.ViewModel
{
    public class PocetnaFormaViewModel 
    {
        static String usernameG = null, passwordG = null;
        static RegistrovaniKorisnik regUser= new RegistrovaniKorisnik();

        public static RegistrovaniKorisnik getRegUser() { return regUser; }
        public static void setRegUser(RegistrovaniKorisnik r) { regUser = r; }

        public static int KORISNIK_ID = -1;

        public static String getUsernameG() { return usernameG; }
        public static String getPasswordG() { return passwordG; }

        public static void setUsernameG(String u) { usernameG = u; }
        public static void setPasswordG(String p) { passwordG = p; }

        Boolean adminDaNe=false, regUserDaNe = false;


        public async Task<Boolean> loginAdmin(String username, String pw)
        {
            Task t = Task.Run(() => getDataAdmin(username,pw));
            t.Wait();
            if (username == usernameG && passwordG == pw && adminDaNe) return true;
            return false;
        }

        public async Task<Boolean> loginUser(String username, String pw)
        {
            Task t = Task.Run(() => getDataUser(username, pw));
            t.Wait();

            if (username == usernameG && passwordG == pw && !adminDaNe) return true;
            return false;
        }


        public async Task<Boolean> getDataUser(String usernme, String pw)
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

           // Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=" + usernme + "&Password=" + pw);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/RegistrovaniKorisniks/GetAccount?Username=" + usernme + "&Password=" + pw);

            //Uri requestUri = new Uri("http://localhost:6796/RegistrovaniKorisniks/GetAccount?Username=Masha&Password=sifraHaris");

            //Send the GET request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            RegistrovaniKorisnik korisnik = null;
            string httpResponseBody = "";
            try
            {
                //Send the GET request
                httpResponse = await httpClient.GetAsync(requestUri);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
                korisnik = JsonConvert.DeserializeObject<RegistrovaniKorisnik>(json);

                if (korisnik != null)
                {
                    int a = korisnik.KorisnikId;
                    usernameG = korisnik.Username;
                    passwordG = korisnik.Password;
                    regUserDaNe = true;
                    regUser = korisnik;
                    KORISNIK_ID = korisnik.KorisnikId;          // samra ne diraj
                    return true;
                }
                else if (json == "")
                {
                    regUserDaNe = false;
                    usernameG = "";
                    passwordG = "";
                    return false;
                
                }
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
            }
            return true;

            /*
            if(korisnik != null){
                int a = korisnik.KorisnikId;
                usernameG = korisnik.Username;
                passwordG = korisnik.Password;
                KORISNIK_ID = korisnik.KorisnikId;
            }
            return false;*/

        }

        public async Task<Boolean> getDataAdmin(String usernme, String pw)
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
            Console.WriteLine("asda");
          //Uri requestUri = new Uri("http://localhost:6796/Administrators/GetAccount?Username=" + usernme + "&Password=" + pw);
            Uri requestUri = new Uri("https://vicinor.azurewebsites.net/Administrators/GetAccount?Username=" + usernme + "&Password=" + pw);

        
            //Send the GET request asynchronously and retrieve the response as a string.
            Windows.Web.Http.HttpResponseMessage httpResponse = new Windows.Web.Http.HttpResponseMessage();

            Administrator korisnik = null;
            string httpResponseBody = "";
            try
            {
                //Send the GET request
                httpResponse = await httpClient.GetAsync(requestUri);

                httpResponse.EnsureSuccessStatusCode();
                httpResponseBody = await httpResponse.Content.ReadAsStringAsync();

                string json = httpResponseBody;
                korisnik = JsonConvert.DeserializeObject<Administrator>(json);
                if (korisnik != null)
                {
                    usernameG = korisnik.Username;
                    passwordG = korisnik.Password;
                    adminDaNe = true;
                    return true;

                }
                else if (json == "")
                {
                    adminDaNe = false;
                    usernameG = "";
                    passwordG = "";
                    return false;

                }
            }
            catch (Exception ex)
            {
                httpResponseBody = "Error: " + ex.HResult.ToString("X") + " Message: " + ex.Message;
                
            }
            return true;
         
        }
    }

}
