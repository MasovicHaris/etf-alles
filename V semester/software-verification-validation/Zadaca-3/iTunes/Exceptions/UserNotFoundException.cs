using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Exceptions
{
    public class UserNotFoundException : Exception
    {
        public UserNotFoundException(string p)
            : base(p)
        {

        }
    }
}