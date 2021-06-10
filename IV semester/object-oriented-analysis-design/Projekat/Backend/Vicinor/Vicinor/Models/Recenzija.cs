using System;
using System.Collections.Generic;
using System.Text;


namespace Vicinor.Model
{
    public class Recenzija
    {
        private int recenzijaId;
        public Recenzija()
        {

        }
        public int RecenzijaId
        {
            get { return recenzijaId; }
            set { recenzijaId = value; }
        }

        String comment;
        int starRating;
        DateTime timeOfRez;

        private RegistrovaniKorisnik user;

        public virtual RegistrovaniKorisnik User
        {
            get { return user; }
            set { user = value; }
        }


        public String Comment
        {
            get
            {
                return comment;
            }

            set
            {
                comment = value;
            }
        }

        public System.Int32 StarRating
        {
            get
            {
                return starRating;
            }

            set
            {
                starRating = value;
            }
        }

        public DateTime TimeOfRez
        {
            get
            {
                return timeOfRez;
            }

            set
            {
                timeOfRez = value;
            }
        }

        
    }
}
