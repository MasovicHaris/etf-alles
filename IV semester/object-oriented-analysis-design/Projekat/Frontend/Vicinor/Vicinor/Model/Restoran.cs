using System;
using System.Collections.Generic;
using Windows.UI.Xaml.Media.Imaging;

namespace Vicinor.Model
{
    public class Restoran
    {
        string name, description;
        byte[] image;

        string slikaURL;
        private string phoneNumber;

        private string place_id;

        public Restoran()
        {
            listRezension = new List<Recenzija>();
        }
        public string PhoneNumber
        {
            get { return phoneNumber; }
            set { phoneNumber = value; }
        }

        Tuple<double, double> location;
        private ICollection<Recenzija> listRezension;
        private BitmapImage slika;

        public BitmapImage Slika
        {
            get { return slika; }
            set { slika = value; }
        }

        public virtual ICollection<Recenzija> ListRezension
        {
            get { return listRezension; }
            set { listRezension = value; }
        }

        private int restoranId;

        public int RestoranId
        {
            get { return restoranId; }
            set { restoranId = value; }
        }



        public System.String Name
        {
            get
            {
                return name;
            }

            set
            {
                name = value;
            }
        }

        public System.String Description
        {
            get
            {
                return description;
            }

            set
            {
                description = value;
            }
        }


        public byte[] Image
        {
            get
            {
                return image;
            }

            set
            {
                image = value;
            }
        }

        public virtual Tuple<double, double> Location
        {
            get
            {
                return location;
            }

            set
            {
                location = value;
            }
        }

        public string SlikaURL
        {
            get
            {
                return slikaURL;
            }

            set
            {
                slikaURL = value;
            }
        }

        public string Place_id
        {
            get
            {
                return place_id;
            }

            set
            {
                place_id = value;
            }
        }

    }
}
