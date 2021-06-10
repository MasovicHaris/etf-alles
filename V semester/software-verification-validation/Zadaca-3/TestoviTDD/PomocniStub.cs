using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using iTunes;
using iTunes.Klase;
using iTunes.Exceptions;

namespace TestoviTDD
{
    class PomocniStub
    {
        // metoda koja se koristi za generisanje slucaja za umjetnike i vraca rezultat koji se mora dobiti
        public List<String> odradiUmjetnike(RegisteredMember noviKorisnik)
        {
            for (int i = 0; i < 15; ++i)
            {
                Tune nova = new Tune("prva", "saban" + i.ToString(), "sabanov prvi", "narodna", 10.0, ".mp3", 2400, 256, 10 + i);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            for (int i = 0; i < 5; ++i)
            {
                Tune nova = new Tune("prva" + i.ToString(), "jana", "sabanov prvi", "narodna", 10.0, ".mp3", 2400, 256, 20);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            List<String> vraceno = new List<String>();
            vraceno.Add("jana");
            vraceno.Add("saban14");
            vraceno.Add("saban13");
            vraceno.Add("saban12");
            vraceno.Add("saban11");
            vraceno.Add("saban10");
            vraceno.Add("saban9");
            vraceno.Add("saban8");
            vraceno.Add("saban7");
            vraceno.Add("saban6");
            return vraceno;
        }
        // metoda koja se koristi za generisanje albuma i vraca rezultat koji se mora dobiti
        public List<String> odradiAlbume(RegisteredMember noviKorisnik)
        {
            for (int i = 0; i < 15; ++i)
            {
                Tune nova = new Tune("prva", "saban", "sabanov prvi" + i.ToString(), "narodna", 10.0, ".mp3", 2400, 256, 10 + i);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            for (int i = 0; i < 5; ++i)
            {
                Tune nova = new Tune("prva" + i.ToString(), "jana", "janin", "narodna", 10.0, ".mp3", 2400, 256, 20);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            List<String> vraceno = new List<String>();
            vraceno.Add("janin");
            vraceno.Add("sabanov prvi14");
            vraceno.Add("sabanov prvi13");
            vraceno.Add("sabanov prvi12");
            vraceno.Add("sabanov prvi11");
            vraceno.Add("sabanov prvi10");
            vraceno.Add("sabanov prvi9");
            vraceno.Add("sabanov prvi8");
            vraceno.Add("sabanov prvi7");
            vraceno.Add("sabanov prvi6");
            return vraceno;
        }

        // metoda koja se koristi za generisanje zanrova i vraca rezultat koji se mora dobiti
        public List<String> odradiZanrove(RegisteredMember noviKorisnik)
        {
            for (int i = 0; i < 15; ++i)
            {
                Tune nova = new Tune("prva", "saban", "sabanov prvi", "narodna" + i.ToString(), 10.0, ".mp3", 2400, 256, 10 + i);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            for (int i = 0; i < 5; ++i)
            {
                Tune nova = new Tune("prva" + i.ToString(), "jana", "janin", "veselija", 10.0, ".mp3", 2400, 256, 20);
                noviKorisnik.MojaBiblioteka.Add(nova);
            }

            List<String> vraceno = new List<String>();
            vraceno.Add("veselija");
            vraceno.Add("narodna14");
            vraceno.Add("narodna13");
            vraceno.Add("narodna12");
            vraceno.Add("narodna11");
            vraceno.Add("narodna10");
            vraceno.Add("narodna9");
            vraceno.Add("narodna8");
            vraceno.Add("narodna7");
            vraceno.Add("narodna6");
            return vraceno;
        }
    }
}
