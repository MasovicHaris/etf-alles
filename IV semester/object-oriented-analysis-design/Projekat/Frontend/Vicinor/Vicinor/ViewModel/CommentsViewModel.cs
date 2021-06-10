using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Forme;
using Vicinor.Model;
using Vicinor.View;
using Windows.Data.Json;

namespace Vicinor.ViewModel
{
    public class CommentsViewModel
    {
        public CommentsViewModel()
        {

        }

        List<string> listaKomentara;
        public async Task ucitajListuKomentara()
        {
            listaKomentara = new List<string>();
     
            var client = new HttpClient();

            var restoran = StartSearch1.dRestorani[StartSearch1.idRestoranaKliknuto];

            // https://maps.googleapis.com/maps/api/place/details/json?placeid={place_id}&key={api_key}

            HttpResponseMessage response = await client.GetAsync(new Uri("https://maps.googleapis.com/maps/api/place/details/json?placeid="+
                "ChIJS51qkj_KWEcRLePQI32zgn0" + "&key=AIzaSyBIl5KmMwk5NiP69tCPnhGZJ3CAr-ml65s"));
            var jsonString = await response.Content.ReadAsStringAsync();

            JsonObject root = JsonValue.Parse(jsonString).GetObject();

            JsonObject podaci = root.GetNamedObject("result");

            JsonArray komentari = podaci.GetNamedArray("reviews");

            for(uint i = 0; i < komentari.Count; ++i)
            {
                JsonObject komentar = komentari.GetObjectAt(i);

                listaKomentara.Add(komentar.GetNamedString("text") + " by: " + komentar.GetNamedString("author_name"));
            }

            
        }

        public List<string> dajListu()
        {
            return listaKomentara;
        }
    }
}
