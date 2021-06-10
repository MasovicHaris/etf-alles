using System;
//using System.Drawing;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor.Model
{
    public class Restoran
    {
        string name, description, phoneNumber;
        byte[] image;
        Lokacija location;
        private ICollection<Recenzija> listRezension;
        public Restoran(string _name, string _description, string _phoneNumber)
        {
            name = _name;
            description = _description;
            phoneNumber = _phoneNumber;
        }
        public Restoran()
        {

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

        public System.String PhoneNumber
        {
            get
            {
                return phoneNumber;
            }

            set
            {
                phoneNumber = value;
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
        
        public virtual Lokacija Location
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
        public System.Drawing.Image GetBitmap()
        {
            using (var stream = new MemoryStream(Image))
            {
                return System.Drawing.Image.FromStream(stream);
            }
        }
    }
}
