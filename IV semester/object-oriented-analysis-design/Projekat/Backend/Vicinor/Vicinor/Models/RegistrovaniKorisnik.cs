using System;
//using System.Drawing;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Drawing;
using System.IO;

namespace Vicinor.Model
{
    public class RegistrovaniKorisnik: KorisnikUSistemu
    {
        String firstName, lastName, email;
        Boolean banned;
        DateTime dateOfBirth;
        public RegistrovaniKorisnik()
        {
          
        }
        byte[] image;
        public RegistrovaniKorisnik(string Password,string Username,string FirstName,  string LastName, string Email, bool Banned, DateTime DateOfBirth, byte[] Image)
        {
            this.Password = Password;
            this.Username = Username;
            this.FirstName = FirstName;
            this.LastName = LastName;
            this.Email = Email;
            this.Banned = Banned;
            this.DateOfBirth = DateOfBirth;
            this.Image=Image;
            listOfRestaurants = new List<Restoran>();
        
        }
        ICollection<Restoran> listOfRestaurants;
        [Required]
        public String FirstName
        {
            get
            {
                return firstName;
            }

            set
            {
                firstName = value;
            }
        }
        [Required]
        public String LastName
        {
            get
            {
                return lastName;
            }

            set
            {
                lastName = value;
            }
        }

        public System.String Email
        {
            get
            {
                return email;
            }

            set
            {
                email = value;
            }
        }

     

        public Boolean Banned
        {
            get
            {
                return banned;
            }

            set
            {
                banned = value;
            }
        }

        public DateTime DateOfBirth
        {
            get
            {
                return dateOfBirth;
            }

            set
            {
                dateOfBirth = value;
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
        
        public virtual ICollection<Restoran> ListOfRestaurants
        {
            get
            {
                return listOfRestaurants;
            }
                
            set
            {
                listOfRestaurants = value;
            }
        }
        Lokacija location;

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
