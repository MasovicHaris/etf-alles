using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vicinor.Model
{
    public class Pretraga
    {
        Korisnik user;
        ICollection<Restoran> listRestaurant;
        DateTime timeOfSearch;
        Restoran chosenRestaurant;
        private int pretragaId;

        public int PretragaId
        {
            get { return pretragaId; }
            set { pretragaId = value; }
        }

        public virtual Korisnik User
        {
            get
            {
                return user;
            }

            set
            {
                user = value;
            }
        }

        public virtual ICollection<Restoran> ListRestaurant
        {
            get
            {
                return listRestaurant;
            }

            set
            {
                listRestaurant = value;
            }
        }

        public DateTime TimeOfSearch
        {
            get
            {
                return timeOfSearch;
            }

            set
            {
                timeOfSearch = value;
            }
        }

        public virtual Restoran ChosenRestaurant
        {
            get
            {
                return chosenRestaurant;
            }

            set
            {
                chosenRestaurant = value;
            }
        }
    }
}
