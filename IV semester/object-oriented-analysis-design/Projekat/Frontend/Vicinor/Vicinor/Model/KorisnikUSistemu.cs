using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Vicinor.Model
{
    public abstract class KorisnikUSistemu: Korisnik
    {

        
        String username, password;
        [Required]
        public String Password
        {
            get
            {
                return password;
            }

            set
            {
                password = value;
            }
        }
        [Required]
        public String Username
        {
            get
            {
                return username;
            }

            set
            {
                username = value;
            }
        }
    }
}
