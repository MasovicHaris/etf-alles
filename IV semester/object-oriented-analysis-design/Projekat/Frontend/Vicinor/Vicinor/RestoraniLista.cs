using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Vicinor.Model;

namespace Vicinor
{
    class RestoraniLista : IEnumerable
    {

        public List<Restoran> restorani { get; set; }

        public RestoraniLista()
        {
            restorani = new List<Restoran>();
        }

        public IEnumerator GetEnumerator()
        {
            foreach(Restoran r in restorani)
            {
                yield return r;
            }
        }
    }
}
