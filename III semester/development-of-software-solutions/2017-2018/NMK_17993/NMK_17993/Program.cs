using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using NMK_17993.Forme;
using NMK_17993.Entiteti;

namespace NMK_17993
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Klinika nova = new Klinika();
            Application.Run(new Registracija(ref nova));
        }


    }
}
