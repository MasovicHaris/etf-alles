using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Exceptions
{
    public class NoMoneyException : Exception
    {
        public NoMoneyException(string p)
            : base(p)
        {

        }
    }
}
