using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Klase
{
    public class Tune
    {
        String id; // ID pjesme u sistemu

        String title; // Naziv pjesme (npr. Ironman)
        String artist; // Naziv izvođača (npr. Black Sabbath)
        String album; // Naziv albuma (npr. Paranoid)
        String genre; // Naziv žanra (Rock/Metal)
        Double rating; // Rating koji pjesma ima na iTunes (9.5/10)

        String format; // Format fajla (npr. .mp3, .wav itd.)
        Int32 length; // Dužina trajanja pjesme u sekundama (npr. 180 s)
        Int32 bitRate; // 256 kbps

        Double price; // Cijena pjesme

        #region KONSTRUKTORI

        public Tune() { }

        public Tune(String t, String art, String al, String g, Double r, String f, Int32 l, Int32 br, Double p) 
        {
            Id = Guid.NewGuid().ToString();
            Title = t;
            Artist = art;
            Album = al;
            Genre = g;
            Rating = r;
            Format = f;
            Length = l;
            BitRate = br;
            Price = p;
        }

        #endregion
        #region GETTERI_I_SETTERI

        public String Id
        {
            get { return id; }
            set { id = value; }
        }

        public String Title
        {
            get { return title; }
            set { title = value; }
        }

        public String Artist
        {
            get { return artist; }
            set { artist = value; }
        }

        public String Album
        {
            get { return album; }
            set { album = value; }
        }

        public String Genre
        {
            get { return genre; }
            set { genre = value; }
        }

        public Double Rating
        {
            get { return rating; }
            set { rating = value; }
        }

        public String Format
        {
            get { return format; }
            set { format = value; }
        }

        public Int32 Length
        {
            get { return length; }
            set { length = value; }
        }

        public Int32 BitRate
        {
            get { return bitRate; }
            set { bitRate = value; }
        }

        public Double Price
        {
            get { return price; }
            set { price = value; }
        }

        #endregion
    }
}
