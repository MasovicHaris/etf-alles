using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iTunes.Exceptions
{
    public class SongNotFoundException : Exception
    {
        public SongNotFoundException(string p)
            : base(p)
        {

        }
    }
}
