using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Exceptions
{
    public class CreditCardInvalidException : Exception
    {
        public CreditCardInvalidException(string p)
            : base(p)
        {

        }
    }
}
